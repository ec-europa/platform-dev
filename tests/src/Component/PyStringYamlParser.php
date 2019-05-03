<?php

namespace Drupal\nexteuropa\Component;

use Behat\Gherkin\Node\PyStringNode;
use Symfony\Component\Config\Definition\Exception\Exception;
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
   * @var \Behat\Gherkin\Node\PyStringNode
   */
  protected $node;

  /**
   * The raw contents of he PyStringNode object.
   *
   * @var array
   */
  protected $raw = [];

  /**
   * Yaml array for the current PyStringNode object.
   *
   * @var array
   */
  protected $yaml;

  /**
   * Get the Yaml array.
   *
   * @return array
   *   The yaml array.
   */
  public function getYaml() {
    $this->process();

    return $this->yaml;
  }

  /**
   * Process the raw array into a Yaml array.
   *
   * @return PyStringYamlParser
   *   The current instance.
   */
  private function process() {
    $input = implode("\n", $this->raw);
    $this->yaml = Yaml::parse($input);

    return $this;
  }

  /**
   * PyStringYamlParser constructor.
   *
   * @param \Behat\Gherkin\Node\PyStringNode $node
   *   PyString containing text in YAML format.
   */
  public function __construct(PyStringNode $node) {
    $this->node = $node;
  }

  /**
   * Parse YAML contained in a PyString node.
   *
   * @return PyStringYamlParser
   *   The current instance.
   */
  public function parse() {
    // Sanitize PyString test by removing initial indentation spaces.
    $this->raw = $this->node->getStrings();
    if (!$this->raw) {
      throw new Exception("No string to parse");
    }

    preg_match('/^(\s+)/', $this->raw[0], $matches);
    $indentation_size = isset($matches[1]) ? strlen($matches[1]) : 0;
    foreach ($this->raw as $key => $string) {
      $this->raw[$key] = substr($string, $indentation_size);
    }

    return $this;
  }

  /**
   * Replace tokens within the PyString node.
   *
   * @param array $replacements
   *   Key value pairs of replacements.
   *
   * @return PyStringYamlParser
   *   The current instance.
   */
  public function replace(array $replacements) {
    foreach ($this->raw as $key => $string) {
      $this->raw[$key] = str_replace(array_keys($replacements), array_values($replacements), $string);
    }

    return $this;
  }

}
