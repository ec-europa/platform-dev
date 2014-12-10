<?php

/**
 * Export to XLIFF format.
 *
 * The XLIFF processor follows this specification:
 * @link http://docs.oasis-open.org/xliff/v1.2/xliff-profile-html/xliff-profile-html-1.2-cd02.html
 *
 * The purpose of this class is to mask or process HTML elements in the source
 * and target elements so that translation tools are able to understand which
 * content needs to be translated and ignored.
 *
 * On the other hand we need to properly unmask the XLIFF markup back to HTML on
 * the translation import. So the process is bidirectional and prior to running
 * the unmasking process we try to validate the integrity in the
 * validateJobTranslationUponImport() method. Currently the integrity check
 * involves only a counter of XLIFF elements that have been created during
 * source processing and has to mach number of XLIFF elements being imported
 * with the translation.
 *
 * To process the content DOMDocument object is used due to its ability to
 * read broken HTML. This also implies that if broken HTML is in the source
 * content the translation content will be fixed into the extend of DOMDocument
 * abilities.
 *
 * Following is implemented:
 * - All pair tags get escaped using <bpt><ept> markup.
 * - <br> tags are marked with <x ctype="lb">.
 * - <img> tags are marked with <ph ctype="image"> tags. The title and alt
 *   attributes should have been extracted into <sub> elements, however are not
 *   as Trados studio triggers a fatal error in case there are two <sub>
 *   elements at the same level.
 *
 * Not implemented:
 * - Attributes of <img> element are written only as attributes of <ph> element
 *   instead of using x-html: prefix. This results in conflict with own <ph>
 *   element's attributes such as "id". The reason why x-html prefix has not
 *   been used is that Trados studio triggered fatal error on xml validation.
 * - Translatable attributes like title and alt.
 *   @link http://docs.oasis-open.org/xliff/v1.2/xliff-profile-html/xliff-profile-html-1.2-cd02.html#elem_img
 * - Forms - this is big part
 *   @link http://docs.oasis-open.org/xliff/v1.2/xliff-profile-html/xliff-profile-html-1.2-cd02.html#HTMLForms
 * - <pre> elements
 *   @link http://docs.oasis-open.org/xliff/v1.2/xliff-profile-html/xliff-profile-html-1.2-cd02.html#Elem_preformatted
 */
class TMGMTFTPformatXLIFF extends XMLWriter implements TMGMTFileFormatInterface {

  /**
   * Contains a reference to the currently being exported job.
   *
   * @var TMGMTJob
   */
  protected $job;

  protected $importedXML;
  protected $importedTransUnits;

  /**
   * Adds a job item to the xml export.
   *
   * @param $item
   *   The job item entity.
   */
  protected function addItem(TMGMTJobItem $item) {
    $this->startElement('group');
    $this->writeAttribute('id', $item->tjiid);

    // Add a note for the source label.
    $this->writeElement('note', $item->getSourceLabel());

    // @todo: Write in nested groups instead of flattening it.
    $data = array_filter(tmgmt_flatten_data($item->getData()), '_tmgmt_filter_data');
    foreach ($data as $key => $element) {
      $this->addTransUnit($item->tjiid . '][' . $key, $element, $this->job);
    }
    $this->endElement();
  }

  /**
   * Adds a single translation unit for a data element.
   *
   * @param $key
   *   The unique identifier for this data element.
   * @param $element
   *   Array with the properties #text and optionally #label.
   * @param TMGMTJob $job
   *   Translation job.
   */
  protected function addTransUnit($key, $element, TMGMTJob $job) {

    $key_array = tmgmt_ensure_keys_array($key);

    $this->startElement('trans-unit');
    $this->writeAttribute('id', $key);
    $this->writeAttribute('resname', $key);

    $this->startElement('source');
    $this->writeAttribute('xml:lang', $this->job->getTranslator()->mapToRemoteLanguage($this->job->source_language));

    if ($job->getSetting('xliff_processing')) {
      $this->writeRaw($this->processForExport($element['#text'], $key_array));
    }
    else {
      $this->text($element['#text']);
    }

    $this->endElement();
    $this->startElement('target');
    $this->writeAttribute('xml:lang', $this->job->getTranslator()->mapToRemoteLanguage($this->job->target_language));

    if (!empty($element['#translation']['#text'])) {
      if ($job->getSetting('xliff_processing')) {
        $this->writeRaw($this->processForExport($element['#translation']['#text'], $key_array));
      }
      else {
        $this->text($element['#translation']['#text']);
      }
    }

    $this->endElement();
    if (isset($element['#label'])) {
      $this->writeElement('note', $element['#label']);
    }
    $this->endElement();
  }

  /**
   * {@inheritdoc}
   */
  public function export(TMGMTJob $job) {

    $this->job = $job;

    $this->openMemory();
    $this->setIndent(true);
    $this->setIndentString(' ');
    $this->startDocument('1.0', 'UTF-8');

    // Root element with schema definition.
    $this->startElement('xliff');
    $this->writeAttribute('version', '1.2');
    $this->writeAttribute('xmlns', 'urn:oasis:names:tc:xliff:document:1.2');
    $this->writeAttribute('xmlns:xsi', 'http://www.w3.org/2001/XMLSchema-instance');
    $this->writeAttribute('xsi:schemaLocation', 'urn:oasis:names:tc:xliff:document:1.2 xliff-core-1.2-strict.xsd');

    // File element.
    $this->startElement('file');
    $this->writeAttribute('original', 'xliff-core-1.2-strict.xsd');
    $this->writeAttribute('source-language', $job->getTranslator()->mapToRemoteLanguage($job->source_language));
    $this->writeAttribute('target-language', $job->getTranslator()->mapToRemoteLanguage($job->target_language));
    $this->writeAttribute('datatype', 'plaintext');
    // Date needs to be in ISO-8601 UTC
    $this->writeAttribute('date', date('Y-m-d\Th:m:i\Z'));

    $this->startElement('header');
    $this->startElement('phase-group');
    $this->startElement('phase');
    $this->writeAttribute('tool-id', 'tmgmt');
    $this->writeAttribute('phase-name', 'extraction');
    $this->writeAttribute('process-name', 'extraction');
    $this->writeAttribute('job-id', $job->tjid);

    $this->endElement();
    $this->endElement();
    $this->startElement('tool');
    $this->writeAttribute('tool-id', 'tmgmt');
    $this->writeAttribute('tool-name', 'Drupal Translation Management Tools');
    $this->endElement();
    $this->endElement();

    $this->startElement('body');

    foreach ($job->getItems() as $item) {
      $this->addItem($item);
    }

    // End the body, file and xliff tags.
    $this->endElement();
    $this->endElement();
    $this->endElement();
    $this->endDocument();
    return $this->outputMemory();
  }

  /**
   * {@inheritdoc}
   */
  public function import($imported_file) {
    $this->getImportedXML($imported_file);
    $phase = $this->importedXML->xpath("//xliff:phase[@phase-name='extraction']");
    $phase = reset($phase);
    $job = tmgmt_job_load((string) $phase['job-id']);
    return tmgmt_unflatten_data($this->getImportedTargets($job));
  }

  /**
   * Validates imported XLIFF file.
   *
   * Checks:
   * - Job ID.
   * - Target ans source languages
   * - Content integrity by
   */
  public function validateImport($imported_file) {
    $xml = $this->getImportedXML($imported_file);
    // Check if our phase information is there.
    $phase = $xml->xpath("//xliff:phase[@phase-name='extraction']");
    if ($phase) {
      $phase = reset($phase);
    }
    else {
      return FALSE;
    }

    // Check if the job can be loaded.
    if (!isset($phase['job-id']) || (!$job = tmgmt_job_load((string) $phase['job-id']))) {
      return FALSE;
    }

    // Compare source language.
    if (!isset($xml->file['source-language']) || $job->getTranslator()->mapToRemoteLanguage($job->source_language) != $xml->file['source-language']) {
      return FALSE;
    }

    // Compare target language.
    if (!isset($xml->file['target-language']) || $job->getTranslator()->mapToRemoteLanguage($job->target_language) != $xml->file['target-language']) {
      return FALSE;
    }

    $targets = $this->getImportedTargets($job);

    if (empty($targets)) {
      return FALSE;
    }

    // In case we do not do xliff processing we cannot do the elements
    // count validation.
    if (!$job->getSetting('xliff_processing')) {
      return $job;
    }

    $reader = new XMLReader();
    $xliff_validation = $job->getSetting('xliff_validation');

    foreach ($targets as $id => $target) {
      $array_key = tmgmt_ensure_keys_array($id);
      $job_item = tmgmt_job_item_load(array_shift($array_key));
      $count = 0;
      $reader->XML('<translation>' . $target['#text'] . '</translation>');
      while ($reader->read()) {
        if (in_array($reader->name, array('translation', '#text'))) {
          continue;
        }
        $count++;
      }

      if (!isset($xliff_validation[$id]) || $xliff_validation[$id] != $count) {
        $job_item->addMessage('Failed to validate semantic integrity of %key element. Please check also the HTML code of the element in the review process.',
          array('%key' => tmgmt_ensure_keys_string($array_key)));
      }
    }

    // Validation successful.
    return $job;
  }

  protected function getImportedXML($imported_file) {
    if (empty($this->importedXML)) {
      // It is not possible to load the file directly with simplexml as it gets
      // url encoded due to the temporary://. This is a PHP bug, see
      // https://bugs.php.net/bug.php?id=61469
      $xml_string = file_get_contents($imported_file);
      $this->importedXML = simplexml_load_string($xml_string);
      // Register the XLIFF namespace, required for xpath.
      $this->importedXML->registerXPathNamespace('xliff', 'urn:oasis:names:tc:xliff:document:1.2');
    }

    return $this->importedXML;
  }

  protected function getImportedTargets(TMGMTJob $job) {
    if (empty($this->importedXML)) {
      return FALSE;
    }

    if (empty($this->importedTransUnits)) {
      $reader = new XMLReader();
      foreach ($this->importedXML->xpath('//xliff:trans-unit') as $unit) {
        $reader->XML($unit->target->asXML());
        $reader->read();
        $this->importedTransUnits[(string) $unit['id']]['#text'] =
            $this->processForImport($reader->readInnerXML(), $job);
      }
    }

    return $this->importedTransUnits;
  }

  /**
   * Processes trans-unit/target to rebuild back the HTML.
   *
   * @param string $translation
   *   Job data array.
   * @param TMGMTJob $job
   *   Translation job.
   *
   * @return string
   */
  protected function processForImport($translation, TMGMTJob $job) {
    // In case we do not want to do xliff processing return the translation as
    // is.
    if (!$job->getSetting('xliff_processing')) {
      return $translation;
    }

    $reader = new XMLReader();
    $reader->XML('<translation>' . $translation . '</translation>');
    $text = '';

    while ($reader->read()) {
      // If the current element is text append it to the result text.
      if ($reader->name == '#text' || $reader->name == '#cdata-section') {
        $text .= $reader->value;
      }
      elseif ($reader->name == 'x') {
        if ($reader->getAttribute('ctype') == 'lb') {
          $text .= '<br />';
        }
      }
      elseif ($reader->name == 'ph') {
        if ($reader->getAttribute('ctype') == 'image') {
          $text .= '<img';
          while ($reader->moveToNextAttribute()) {
            // @todo - we have to use x-html: prefixes for attributes.
            if ($reader->name != 'ctype' && $reader->name != 'id') {
              $text .= " {$reader->name}=\"{$reader->value}\"";
            }
          }
          $text .= ' />';
        }
      }
    }
    return $text;
  }

  /**
   * Helper function to process the source text.
   *
   * @param string $source
   *   Job data array.
   * @param array $key_array
   *   The source item data key.
   *
   * @return string
   */
  protected function processForExport($source, array $key_array) {
    $tjiid = $key_array[0];
    $key_string = tmgmt_ensure_keys_string($key_array);
    // The reason why we use DOMDocument object here and not just XMLReader
    // is the DOMDocument's ability to deal with broken HTML.
    $dom = new DOMDocument();
    // We need to append the head with encoding so that special characters
    // are read correctly.
    $dom->loadHTML("<html><head><meta http-equiv='Content-type' content='text/html; charset=UTF-8' /></head><body>" . $source . '</body></html>');

    $iterator = new RecursiveIteratorIterator(
      new RecursiveDOMIterator($dom),
      RecursiveIteratorIterator::SELF_FIRST);

    $writer = new XMLWriter();
    $writer->openMemory();
    $writer->startDocument('1.0', 'UTF-8');
    $writer->startElement('wrapper');

    $tray = array();
    $non_pair_tags = array('br', 'img');

    if (!isset($this->job->settings['xliff_validation'])) {
      $this->job->settings['xliff_validation'] = array();
    }
    $xliff_validation = $this->job->settings['xliff_validation'];

    /** @var DOMElement $node */
    foreach ($iterator as $node) {

      if (in_array($node->nodeName, array('html', 'body', 'head', 'meta'))) {
        continue;
      }

      if ($node->nodeType === XML_ELEMENT_NODE) {
        // Increment the elements count and compose element id.
        if (!isset($xliff_validation[$key_string])) {
          $xliff_validation[$key_string] = 0;
        }
        $xliff_validation[$key_string]++;
        $id = 'tjiid' . $tjiid . '-' . $xliff_validation[$key_string];

        $is_pair_tag = !in_array($node->nodeName, $non_pair_tags);

        if ($is_pair_tag) {
          $this->writeBPT($writer, $node, $id);
        }
        elseif ($node->nodeName == 'img') {
          $this->writeIMG($writer, $node, $id);
        }
        elseif ($node->nodeName == 'br') {
          $this->writeBR($writer, $node, $id);
        }

        // Add to tray new element info.
        $tray[$id] = array(
          'name' => $node->nodeName,
          'id' => $id,
          'value' => $node->nodeValue,
          'built_text' => '',
          'is_pair_tag' => $is_pair_tag,
        );

      }
      // The current node is a text.
      elseif ($node->nodeName == '#text') {
        // Add the node value to the text output.
        $writer->writeCdata($this->toEntities($node->nodeValue));
        foreach ($tray as &$info) {
          $info['built_text'] .= $node->nodeValue;
        }
      }

      // Reverse so that pair tags are closed in the expected order.
      $reversed_tray = array_reverse($tray);
      foreach ($reversed_tray as $_info) {
        // If the build_text equals to the node value and it is not a pair tag
        // add the end pair tag markup.
        if ($_info['value'] == $_info['built_text'] && $_info['is_pair_tag']) {
          // Count also for the closing elements.
          $xliff_validation[$key_string]++;
          $this->writeEPT($writer, $_info['name'], $_info['id']);
          // When the end pair tag has been written unset the element info
          // from the tray.
          unset($tray[$_info['id']]);
        }
      }
    }

    // Set the xliff_validation data and save the job.
    $this->job->settings['xliff_validation'] = $xliff_validation;
    $this->job->save();

    $writer->endElement();
    // Load the output with XMLReader so that we can easily get the inner xml.
    $reader = new XMLReader();
    $reader->XML($writer->outputMemory());
    $reader->read();
    return $reader->readInnerXML();
  }

  /**
   * Writes br tag.
   *
   * @param XMLWriter $writer
   *   Writer that writes the output.
   * @param DOMElement $node
   *   Current node.
   * @param $id
   *   Current node id.
   */
  protected function writeBR(XMLWriter $writer, DOMElement $node, $id) {
    $writer->startElement('x');
    $writer->writeAttribute('id', $id);
    $writer->writeAttribute('ctype', 'lb');
    $writer->endElement();
  }

  /**
   * Writes beginning pair tag.
   *
   * @param XMLWriter $writer
   *   Writer that writes the output.
   * @param DOMElement $node
   *   Current node.
   * @param $id
   *   Current node id.
   */
  protected function writeBPT(XMLWriter $writer, DOMElement $node, $id) {
    $beginning_tag = '<' . $node->nodeName;
    if ($node->hasAttributes()) {
      $attributes = array();
      /** @var DOMAttr $attribute */
      foreach ($node->attributes as $attribute) {
        $attributes[] = $attribute->name . '="' . $attribute->value . '"';
      }

      $beginning_tag .= ' '. implode(' ', $attributes);
    }
    $beginning_tag .= '>';
    $writer->startElement('bpt');
    $writer->writeAttribute('id', $id);
    $writer->text($beginning_tag);
    $writer->endElement();
  }

  /**
   * Writes ending pair tag.
   *
   * @param XMLWriter $writer
   *   Writer that writes the output.
   * @param string $name
   *   Ending tag name.
   * @param $id
   *   Current node id.
   */
  protected function writeEPT(XMLWriter $writer, $name, $id) {
    $writer->startElement('ept');
    $writer->writeAttribute('id', $id);
    $writer->text('</' . $name . '>');
    $writer->endElement();
  }

  /**
   * Writes img tag.
   *
   * Note that alt and title attributes are not written as sub elements as
   * Trados studio is not able to deal with two sub elements at one level.
   *
   * @param XMLWriter $writer
   *   Writer that writes the output.
   * @param DOMElement $node
   *   Current node.
   * @param $id
   *   Current node id.
   */
  protected function writeIMG(XMLWriter $writer, DOMElement $node, $id) {
    $writer->startElement('ph');
    $writer->writeAttribute('id', $id);
    $writer->writeAttribute('ctype', 'image');
    foreach ($node->attributes as $attribute) {
      // @todo - uncomment when issue with Trados/sub elements fixed.
      /*
      if (in_array($attribute->name, array('title', 'alt'))) {
        continue;
      }
      */
      $writer->writeAttribute($attribute->name, $attribute->value);
    }
    /*
    if ($alt_attribute = $node->getAttribute('alt')) {
      $writer->startElement('sub');
      $writer->writeAttribute('id', $id . '-img-alt');
      $writer->writeAttribute('ctype', 'x-img-alt');
      $writer->text($alt_attribute);
      $writer->endElement();
      $this->elementsCount++;
    }
    if ($title_attribute = $node->getAttribute('title')) {
      $writer->startElement('sub');
      $writer->writeAttribute('id', $id . '-img-title');
      $writer->writeAttribute('ctype', 'x-img-title');
      $writer->text($title_attribute);
      $writer->endElement();
      $this->elementsCount++;
    }
    */
    $writer->endElement();
  }

  /**
   * Convert critical characters to HTML entities.
   *
   * DOMDocument will convert HTML entities to its actual characters. This can
   * lead into situation when not allowed characters will appear in the content.
   *
   * @param string $string
   *   String to escape.
   *
   * @return string
   *   Escaped string.
   */
  protected function toEntities($string) {
    return str_replace(array('&', '>', '<'), array('&amp;', '&gt;', '&lt;'), $string);
  }

}
