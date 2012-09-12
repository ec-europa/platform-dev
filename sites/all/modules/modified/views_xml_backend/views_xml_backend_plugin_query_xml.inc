<?php

/**
 * @file
 * Query plugin for views_xml_backend.
 */
class views_xml_backend_plugin_query_xml extends views_plugin_query {

  /**
   * Generate a query and a countquery from all of the information supplied to
   * the object.
   *
   * @param $get_count
   *   Provide a countquery if this is true, otherwise provide a normal query.
   */
  function query($get_count = FALSE) {
    $row_xpath = $this->options['row_xpath'];

    $wheres = array();
    if (!empty($this->filter)) {
      $filters = array();
      foreach ($this->filter as $filter) {
        $filters[$filter->options['xpath_operator']] = $filter->generate();
      }
      $filter_string = '(' . array_shift($filters);
      foreach($filters as $operator => $filter){
        $filter_string .= " $operator $filter";
      }
      $filter_string .= ')';
      $wheres[] = $filter_string;
    }

    if (!empty($this->argument)) {
      $arguments = array();
      foreach ($this->argument as $argument) {
        $arguments[] = $argument->generate();
      }
      $wheres[] = '(' . implode(' and ', $arguments) . ')';
    }

    if(!empty($wheres)){
      $where = '[' .  implode(' and ', $wheres) . ']';
    } else {
      $where = '';
    }

    return $row_xpath . $where;
  }

  /**
   * Builds the necessary info to execute the query.
   */
  function build(&$view) {
    $view->init_pager();

    // Let the pager modify the query to add limits.
    $this->pager->query();

    $view->build_info['query'] = $this->query();
    //dsm($view->build_info['query']); // TODO: Enable this to see the generated xpath
    $view->build_info['count_query'] = 'count(' . $view->build_info['query'] . ')';
    $view->build_info['query_args'] = array();
  }

  function fetch_file($uri) {
    $parsed = parse_url($uri);
    // Check for local file.
    if (empty($parsed['host'])) {
      if (!file_exists($uri)) {
        throw new Exception(t('Local file not found.'));
      }
      return file_get_contents($uri);
    }

    $destination = 'public://views_xml_backend';
    if (!file_prepare_directory($destination, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
      throw new Exception(t('Files directory either cannot be created or is not writable.'));
    }

    $headers = array();
    $cache_file = 'views_xml_backend_' . md5($uri);
    if ($cache = cache_get($cache_file)) {
      $last_headers = $cache->data;

      if (!empty($last_headers['etag'])) {
        $headers['If-None-Match'] = $last_headers['etag'];
      }
      if (!empty($last_headers['last-modified'])) {
        $headers['If-Modified-Since'] = $last_headers['last-modified'];
      }
    }

    $result = drupal_http_request($uri, array('headers' => $headers));
    if (isset($result->error)) {
      $args = array('%error' => $result->error, '%uri' => $uri);
      $message = t('HTTP response: %error. URI: %uri', $args);
      throw new Exception($message);
    }
    $cache_file_uri = "$destination/$cache_file";

    if ($result->code == 304) {
      if (file_exists($cache_file_uri)) {
        return file_get_contents($cache_file_uri);
      }
      // We have the headers but no cache file. :(
      // Run it back.
      cache_clear_all($cache_file, 'cache');
      return $this->fetch_file($uri);
    }

    // As learned from Feeds caching mechanism, save to file.
    file_save_data($result->data, $cache_file_uri, FILE_EXISTS_REPLACE);
    cache_set($cache_file, $result->headers);
    return $result->data;
  }

  function execute(&$view) {
    $start = microtime(TRUE);

    // Avoid notices about $view->execute_time being undefined if the query
    // doesn't finish.
    $view->execute_time = NULL;

    // Make sure that an xml file exists.
    // This could happen if you come from the add wizard to the actual views
    // edit page.
    if (empty($this->options['xml_file'])) {
      return FALSE;
    }

    $data = new stdClass();
    try {
      $xml_file = $this->replace_arguments($view, $this->options['xml_file']);
      $data->contents = $this->fetch_file($xml_file);
    }
    catch (Exception $e) {
      drupal_set_message(t('Views XML Backend: ' . $e->getMessage()), 'error');
      return;
    }

    // Allow other modules to alter the data. Could be used for adding Tidy
    // support.
    // @todo Document this.
    drupal_alter('views_xml_backend_data', $data, $view->name);

    // When content is empty, parsing it is pointless.
    if (!$data->contents) {
      if ($this->options['show_errors']) {
        drupal_set_message(t('Views XML Backend: File is empty.'), 'warning');
      }
      return;
    }

    $use = $this->errorStart();

    // Go!
    $this->parse($view, $data);

    $view->execute_time = microtime(TRUE) - $start;
    $this->errorStop($use, $this->options['show_errors']);
  }

  function replace_arguments($view, $string){
    if(isset($view->build_info['substitutions']) && count($view->build_info['substitutions'])>0){
      $substitutions = $view->build_info['substitutions'];
      $string = str_replace(array_keys($substitutions), array_values($substitutions), $string);
    }
    return $string;
  }

  function parse(&$view, $data) {

    $doc = new DOMDocument();
    $success = $doc->loadXML($data->contents);
    // If the file fails to load, bail. The appropriate error messages will be
    // displayed automatically.
    if (!$success) {
      return;
    }

    $xpath = new DOMXPath($doc);
    // Make php functions available in xpath (use for filtering)
    $xpath->registerNamespace("php", "http://php.net/xpath");
    $xpath->registerPHPFunctions();

    // Create a simplexml object so that we can use
    // SimpleXMLElement::getNamespaces().
    // Does anyone know a better way to do it?
    $simple = simplexml_import_dom($doc);
    if (!$simple) {
      return;
    }
    $namespaces = $simple->getNamespaces(TRUE);

    // Register namespaces. Allow for overriding the default namespace.
    foreach ($namespaces as $prefix => $namespace) {
      if ($prefix === '') {
        if (empty($this->options['default_namespace'])) {
          $prefix = 'default';
        }
        else {
          $prefix = $this->options['default_namespace'];
        }
      }
      $xpath->registerNamespace($prefix, $namespace);
    }

    try {
      if ($this->pager->use_count_query() || !empty($view->get_total_rows)) {
        // $this->pager->execute_count_query($count_query);

        // Hackish execute_count_query implementation.
        $this->pager->total_items = $xpath->evaluate($view->build_info['count_query']);
        if (!empty($this->pager->options['offset'])) {
          $this->pager->total_items -= $this->pager->options['offset'];
        }

        $this->pager->update_page_info();
      }

      // Let the pager modify the query to add limits.
      $this->pager->pre_execute($view->build_info['query']);

      // Get the rows.
      $rows = $xpath->query($view->build_info['query']);

      $result = array();
      foreach ($rows as $row) {
        $item = new stdClass();

        // Query each field per row.
        foreach ($this->fields as $field) {
          $field_key = $field['field'];
          if (!$field_key) {
            continue;
          }
          $node_list = $xpath->evaluate($field_key, $row);
          if ($node_list && $node_list->length>0) { // It can happen that a field is not present, but the path is valid, in that case the evaluate function returns an empty list
            // Allow multiple values in a field.
            if ($field['multiple']) {

              $item->$field_key = array();
              foreach ($node_list as $node) {
                $item->{$field_key}[] = $node->nodeValue;
              }
            }
            // Single value, just pull the first.
            else {
              $item->$field_key = $node_list->item(0)->nodeValue;
            }
          }
          else {
            // Make sure all of the fields are set. Allows us to do less error
            // checking later on.
            $item->$field_key = NULL;
          }
        }
        $result[] = $item;
      }

      if (!empty($this->orderby)) {
        // Array reverse, because the most specific are first.
        foreach (array_reverse($this->orderby) as $orderby) {
          $orderby->sort($result);
        }
      }

      /* Now limit the query to the page requested */
      if (!empty($this->limit) || !empty($this->offset)) {
        $result = array_slice($result, $this->offset, $this->limit, true);
      }

      $view->result = $result;
      $view->total_rows = count($result);

      $this->pager->post_execute($view->result);
    }
    catch (Exception $e) {
      $view->result = array();
      if (!empty($view->live_preview)) {
        drupal_set_message(time());
        drupal_set_message($e->getMessage(), 'error');
      }
      else {
        debug($e->getMessage(), 'Views XML Backend');
      }
    }
  }

  function add_signature(&$view) {}

  function option_definition() {
    $options = parent::option_definition();
    $options['xml_file'] = array('default' => '');
    $options['row_xpath'] = array('default' => '');
    $options['default_namespace'] = array('default' => '');
    $options['show_errors'] = array('default' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['xml_file'] = array(
      '#type' => 'textfield',
      '#title' => t('XML File'),
      '#default_value' => $this->options['xml_file'],
      '#description' => t("The URL or path to the XML file."),
      '#maxlength' => 1024,
    );
    $form['row_xpath'] = array(
      '#type' => 'textfield',
      '#title' => t('Row Xpath'),
      '#default_value' => $this->options['row_xpath'],
      '#description' => t("An xpath function that selects rows."),
      '#required' => TRUE,
    );
    $form['default_namespace'] = array(
      '#type' => 'textfield',
      '#title' => t('Default namespace'),
      '#default_value' => $this->options['default_namespace'],
      '#description' => t("If the xml contains a default namespace, it will be accessible as 'default:element'. If you want something different, declare it here."),
      '#required' => FALSE,
    );
    $form['show_errors'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show XML errors'),
      '#default_value' => $this->options['show_errors'],
      '#description' => t('If there were any errors during XML parsing, display them. It is recommended to leave this on during development.'),
      '#required' => FALSE,
    );
  }

  function add_field($table, $field, $alias = '', $params = array()) {
    $alias = $field;

    // Add field info array.
    if (empty($this->fields[$field])) {
      if(is_null($params)){
        $params = array();
      }
      $this->fields[$field] = array(
      'field' => $field,
      'table' => $table,
      'alias' => $alias,
      ) + $params;
    }

    return $field;
  }

  function add_orderby($orderby) {

    if(is_null($orderby)){
      return;
    }

    $this->add_field($orderby->table_alias, $orderby->options['xpath_selector'], '', $orderby->options);

    $this->orderby[] = $orderby;
  }

  function add_filter($filter) {
    $this->filter[] = $filter;
  }


  function add_argument($argument) {
    $this->argument[] = $argument;
  }

  /**
   * Return info to base the uniqueness of the result on.
   *
   * @return $cache_info
   *   Array with query unique data.
   */
  function get_cache_info() {
    return array(
      'xml_file' => $this->options['xml_file'],
      'row_xpath' => $this->options['row_xpath'],
      'default_namespace' => $this->options['default_namespace']
    );
  }

  /**
   * Start custom error handling.
   *
   * @return bool
   *   The previous value of use_errors.
   */
  protected function errorStart() {
    return libxml_use_internal_errors(TRUE);
  }

  /**
   * Stop custom error handling.
   *
   * @param bool $use
   *   The previous value of use_errors.
   * @param bool $print
   *   (Optional) Whether to print errors to the screen. Defaults to TRUE.
   */
  protected function errorStop($use, $print = TRUE) {
    if ($print) {
      foreach (libxml_get_errors() as $error) {
        switch ($error->level) {
          case LIBXML_ERR_WARNING:
          case LIBXML_ERR_ERROR:
            $type = 'warning';
            break;
          case LIBXML_ERR_FATAL:
            $type = 'error';
            break;

        }
        $message = t('Views XML Backend: %error on line %num. Error code: %code', array('%error' => trim($error->message), '%num' => $error->line, '%code' => $error->code));
        drupal_set_message($message, $type, FALSE);
      }
    }
    libxml_clear_errors();
    libxml_use_internal_errors($use);
  }
}
