<?php

class views_xml_backend_handler_argument extends views_handler_argument {

  /**
   * Set up the query for this argument.
   *
   * The argument sent may be found at $this->argument.
   */
  function query($group_by = FALSE) {
    $this->query->add_argument($this);//TODO: how to handle group_by argument ??
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['xpath_selector'] = array('default' => '');
    $options['strict'] = array('default' => 0);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['xpath_selector'] = array(
        '#type' => 'textfield',
        '#title' => 'XPath selector',
        '#description' => t('The field name in the table that will be used as the filter.'),
        '#default_value' => $this->options['xpath_selector'],
        '#required' => TRUE,
    );
    $form['strict'] = array(
        '#type' => 'checkbox',
        '#title' => 'Strict comparison',
        '#description' => t('Should the compare function be strict (case-sensitive) or loose (case-insensitive).'),
        '#default_value' => $this->options['strict'],
        '#required' => FALSE,
    );
  }

  function generate() {
    $xpath = $this->options['xpath_selector'];
    $strict = $this->options['strict'];
    $value = $this->get_value();
    $method = 'views_xml_backend_argument_text_op_equal';
    $value = htmlspecialchars($value, ENT_QUOTES);
    return $xpath . "[php:functionString('$method', ., \"$value\", " . ($strict?1:0) . ", 0)]";
  }
}

// TEXT FILTER OPERATOR METHODS
function views_xml_backend_argument_text_op_equal($value, $search, $strict, $negate){
  $search = htmlentities($search, ENT_QUOTES);
  if($strict){
    $result = (strcmp($value, $search)===0);
  } else {
    $result = (strcasecmp($value, $search)===0);
  }
  return $negate?!$result:$result;
}