<?php

/**
 * @file
 * Export into DGT supported HTML format.
 */

/**
 * DGT aproved HTML format exporter.
 */
class TMGMTFileDGTFormatHTML implements TMGMTFileFormatInterface {

  /**
   * Returns base64 encoded data that is safe for use in xml ids.
   */
  protected function encodeIdSafeBase64($data) {
    // Prefix with a b to enforce that the first character is a letter.
    return 'b' . rtrim(strtr(base64_encode($data), '+/', '-_'), '=');
  }

  /**
   * Returns decoded id safe base64 data.
   */
  protected function decodeIdSafeBase64($data) {
    // Remove prefixed b.
    $data = substr($data, 1);
    return base64_decode(str_pad(strtr($data, '-_', '+/'), strlen($data) % 4, '=', STR_PAD_RIGHT));
  }

  /**
   * {@inheritdoc}
   */
  public function export(TMGMTJob $job, $conditions = array()) {

    $items = array();
    foreach ($job->getItems($conditions) as $item) {
      $data = array_filter(tmgmt_flatten_data($item->getData()), '_tmgmt_filter_data');
      foreach ($data as $key => $value) {
        $items[$item->tjiid][$this->encodeIdSafeBase64($item->tjiid . '][' . $key)] = $value;
      }
    }

    return theme('tmgmt_dgt_html_template', array(
      'tjid' => $job->tjid,
      'source_language' => $job->getTranslator()->mapToRemoteLanguage($job->source_language),
      'target_language' => $job->getTranslator()->mapToRemoteLanguage($job->target_language),
      'items' => $items,
    ));
  }

  /**
   * {@inheritdoc}
   */
  public function import($imported_file, $is_file = TRUE) {
    $xml = $this->getXml($imported_file);
    // Extract the translation data from the imported file.
    $data = array();
    foreach ($xml->xpath("//div[@class='atom']") as $atom) {
      // Assets are our strings (eq fields in nodes).
      $key = $this->decodeIdSafeBase64((string) $atom['id']);

      $doc = new DOMDocument();
      $doc->loadXML($atom->asXML());
      $node = $doc->getElementsByTagName('div')->item(0);

      // Get all node childs even text node elements.
      $data[$key] = array("#text" => "");
      foreach ($node->childNodes as $child) {
        if ($child->nodeType == XML_TEXT_NODE) {
          $data[$key]['#text'] .= $child->nodeValue;
        }
        else {
          $data[$key]['#text'] .= $doc->saveXml($child);
        }
      }
    }
    // The job item IDs in the translation data are mapped to the language that
    // was originally exported. Remap them to the correct IDs before returning.
    return tmgmt_unflatten_data($data);
  }

  /**
   * {@inheritdoc}
   */
  public function validateImport($imported_file) {
    $dom = new DOMDocument();
    if (file_exists($imported_file)) {
      if (!multisite_drupal_toolbox_load_html_file($dom, $imported_file)) {
        return FALSE;
      }
    }
    else {
      if (!multisite_drupal_toolbox_load_html($dom, $imported_file)) {
        return FALSE;
      }
    }

    $xml = simplexml_import_dom($dom);

    // Collect meta information.
    $metadata = $this->getMetadata($xml);

    // Check required meta tags.
    foreach (array('JobID', 'languageSource', 'languageTarget') as $name) {
      if (!isset($metadata[$name])) {
        return FALSE;
      }
    }

    // Attempt to load the job.
    if (!$job = tmgmt_job_load($metadata['JobID'])) {
      drupal_set_message(t('The imported file job id @file_tjid is not available.', array(
        '@file_tjid' => $job->tjid,
      )), 'error');
      return FALSE;
    }

    // Check language.
    if ($metadata['languageSource'] != $job->getTranslator()->mapToRemoteLanguage($job->source_language) ||
      $metadata['languageTarget'] != $job->getTranslator()->mapToRemoteLanguage($job->target_language)) {
      return FALSE;
    }

    // Validation successful.
    return $job;
  }

  /**
   * Converts an imported XML document to a SimpleXMLElement object.
   *
   * @param string $imported_file
   *   The imported file.
   *
   * @return SimpleXMLElement
   *   The file converted to a SimpleXMLElement object.
   */
  protected function getXml($imported_file) {
    $dom = new DOMDocument();
    if (file_exists($imported_file)) {
      multisite_drupal_toolbox_load_html_file($dom, $imported_file);
    }
    else {
      multisite_drupal_toolbox_load_html($dom, $imported_file);
    }

    return simplexml_import_dom($dom);
  }

  /**
   * Extracts metadata from an imported file.
   *
   * This combines <meta> elements with other elements that have the "meta"
   * class. Meta elements are identified by their "name" attribute, while
   * elements with a meta class are identified by ID.
   *
   * @param SimpleXMLElement $xml
   *   The imported file, converted to a SimpleXMLElement object.
   *
   * @return array
   *   An associative array of metadata contained in the file, keyed on
   *   identifier.
   */
  protected function getMetadata(SimpleXMLElement $xml) {
    $metadata = array();

    // Collect all information from the actual meta tags.
    foreach ($xml->xpath('//meta') as $meta_tag) {
      if (!empty($meta_tag['name'])) {
        $metadata[(string) $meta_tag['name']] = (string) $meta_tag['content'];
      }
    }

    // Collect meta information from elements tagged with "meta". In our data
    // format this is currently is only a single element containing the target
    // language.
    foreach ($xml->xpath("//*[@class='meta']") as $meta_node) {
      if (!empty($meta_node['id'])) {
        $metadata[(string) $meta_node['id']] = (string) $meta_node;
      }
    }

    return $metadata;
  }

}
