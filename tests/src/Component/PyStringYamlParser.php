<?php

namespace Drupal\nexteuropa\Component;

use Behat\Gherkin\Node\PyStringNode;
use Symfony\Component\Yaml\Yaml;

/**
 * Class PyStringYamlParser.
 *
 * @package Drupal\nexteuropa\Component
 */
class PyStringYamlParser {

  /**
   * PyStringNode object.
   *
   * @var PyStringNode;
   */
  protected $node;

  /**
   * PyStringYamlParser constructor.
   *
   * @param \Behat\Gherkin\Node\PyStringNode $node
   *    PyString containing text in YAML format.
   */
  public function __construct(PyStringNode $node) {
    $this->node = $node;
  }

  /**
   * Parse YAML contained in a PyString node.
   *
   * @return array
   *    Parsed YAML.
   */
  public function parse() {
    // Sanitize PyString test by removing initial indentation spaces.
    $strings = $this->node->getStrings();
    if ($strings) {
      preg_match('/^(\s+)/', $strings[0], $matches);
      $indentation_size = isset($matches[1]) ? strlen($matches[1]) : 0;
      foreach ($strings as $key => $string) {
        $strings[$key] = substr($string, $indentation_size);
      }
    }
    $raw = implode("\n", $strings);
    return Yaml::parse($raw);
  }

}
