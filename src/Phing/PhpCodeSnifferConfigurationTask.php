<?php

/**
 * @file
 * Contains \NextEuropa\build\Phing\PhpCodeSnifferConfigurationTask.
 */

namespace NextEuropa\Phing;

require_once 'phing/Task.php';

/**
 * A Phing task to generate a configuration file for PHP CodeSniffer.
 */
class PhpCodeSnifferConfigurationTask extends \Task {

  /**
   * The path to the configuration file to generate.
   *
   * @var string
   */
  private $configFile = '';

  /**
   * The extensions to scan.
   *
   * @var array
   */
  private $extensions = array();

  /**
   * The list of files and folders to scan.
   *
   * @var array
   */
  private $files = array();

  /**
   * The path to the global configuration file to generate.
   *
   * @var string
   */
  private $globalConfig = '';

  /**
   * The list of patterns to ignore.
   *
   * @var array
   */
  private $ignorePatterns = array();

  /**
   * Whether or not to pass with warnings.
   *
   * @var bool
   */
  private $ignoreWarnings = FALSE;

  /**
   * The report format to use.
   *
   * @var string
   */
  private $report = '';

  /**
   * Whether or not to show progress.
   *
   * @var bool
   */
  private $showProgress = FALSE;

  /**
   * Whether or not to show sniff codes in the report.
   *
   * @var bool
   */
  private $showSniffCodes = FALSE;

  /**
   * The coding standards to use.
   *
   * @var array
   */
  private $standards = array();

  /**
   * The install paths of standards.
   *
   * @var string
   */
  private $installedPaths = '';


  /**
   * Configures PHP CodeSniffer.
   */
  public function main() {
    // Check if all required data is present.
    $this->checkRequirements();

    $document = new \DOMDocument('1.0', 'UTF-8');
    $document->formatOutput = TRUE;

    // Create the root 'ruleset' element.
    $root_element = $document->createElement('ruleset');
    $root_element->setAttribute('name', 'NextEuropa_default');
    $document->appendChild($root_element);

    // Add the description.
    $element = $document->createElement('description', 'Default PHP CodeSniffer configuration for NextEuropa Platform.');
    $root_element->appendChild($element);

    // Add the coding standards.
    foreach ($this->standards as $standard) {

      $installedPaths = $this->explodeToken($this->installedPaths);
      // @codingStandardsIgnoreLine
      if (substr($standard, -4) === '.xml') {
        if (file_exists($standard)) {
          $element = $document->createElement('rule');
          $element->setAttribute('ref', $standard);
          $root_element->appendChild($element);
        }
      }
      else {
        foreach ($installedPaths as $installedPath) {
          $ruleset = $installedPath . "/" . $standard . "/ruleset.xml";
          if (file_exists($ruleset)) {
            $element = $document->createElement('rule');
            $element->setAttribute('ref', $ruleset);
            $root_element->appendChild($element);
          }
        }
      }
    }

    // Add the files to check.
    foreach ($this->files as $file) {
      $element = $document->createElement('file', $file);
      $root_element->appendChild($element);
    }

    // Add file extensions.
    if (!empty($this->extensions)) {
      $extensions = implode(',', $this->extensions);
      $this->appendArgument($document, $root_element, $extensions, 'extensions');
    }

    // Add ignore patterns.
    foreach ($this->ignorePatterns as $pattern) {
      $element = $document->createElement('exclude-pattern', $pattern);
      $root_element->appendChild($element);
    }

    // Add the report type.
    if (!empty($this->report)) {
      $this->appendArgument($document, $root_element, $this->report, 'report');
    }

    // Add the shorthand options.
    $shorthand_options = array(
      'p' => 'showProgress',
      's' => 'showSniffCodes',
    );

    $options = array_filter($shorthand_options, function ($value) {
      return $this->$value;
    });

    if (!empty($options)) {
      $this->appendArgument($document, $root_element, implode('', array_flip($options)));
    }

    // Save the file.
    file_put_contents($this->configFile, $document->saveXML());

    // If a global configuration file is passed, update this too.
    if (!empty($this->globalConfig)) {
      $ignore_warnings_on_exit = $this->ignoreWarnings ? 1 : 0;
      $global_config = <<<PHP
<?php
 \$phpCodeSnifferConfig = array (
  'default_standard' => '$this->configFile',
  'ignore_warnings_on_exit' => '$ignore_warnings_on_exit',
  'installed_paths' => '$this->installedPaths'
);
PHP;
      file_put_contents($this->globalConfig, $global_config);
    }
  }

  /**
   * Appends an argument element to the XML document.
   *
   * This will append an XML element in the following format:
   * <arg name="name" value="value" />
   *
   * @param \DOMDocument $document
   *   The document that will contain the argument to append.
   * @param \DOMElement $element
   *   The parent element of the argument to append.
   * @param string $value
   *   The argument value.
   * @param string $name
   *   Optional argument name.
   */
  protected function appendArgument(\DOMDocument $document, \DOMElement $element, $value, $name = '') {
    $argument = $document->createElement('arg');
    if (!empty($name)) {
      $argument->setAttribute('name', $name);
    }
    if (!empty($value)) {
      $argument->setAttribute('value', $value);
    }
    $element->appendChild($argument);
  }

  /**
   * Checks if all properties required for generating the config are present.
   *
   * @throws \BuildException
   *   Thrown when a required property is not present.
   */
  protected function checkRequirements() {
    $required_properties = array('configFile', 'files', 'standards');
    foreach ($required_properties as $required_property) {
      if (empty($this->$required_property)) {
        throw new \BuildException("Missing required property '$required_property'.");
      }
    }
  }

  /**
   * Sets the path to the configuration file to generate.
   *
   * @param string $configFile
   *   The path to the configuration file to generate.
   */
  public function setConfigFile($configFile) {
    $this->configFile = $configFile;
  }

  /**
   * Sets the file extensions to scan.
   *
   * @param string $extensions
   *   A string containing file extensions, delimited by spaces, commas or
   *   semicolons.
   */
  public function setExtensions($extensions) {
    $this->extensions = $this->explodeToken($extensions);
  }

  /**
   * Sets the list of files and folders to scan.
   *
   * @param string $files
   *   A list of paths, delimited by spaces, commas or semicolons.
   */
  public function setFiles($files) {
    $this->files = $this->explodeToken($files);
  }

  /**
   * Sets the path to the global configuration file to generate.
   *
   * @param string $globalConfig
   *   The path to the global configuration file to generate.
   */
  public function setGlobalConfig($globalConfig) {
    $this->globalConfig = $globalConfig;
  }

  /**
   * Sets the installed_paths configuration..
   *
   * @param string $installedPaths
   *   The paths in which the standards are installed..
   */
  public function setInstalledPaths($installedPaths) {
    $this->installedPaths = $installedPaths;
  }


  /**
   * Sets the list of patterns to ignore.
   *
   * @param string $ignorePatterns
   *   The list of patterns, delimited by spaces, commas or semicolons.
   */
  public function setIgnorePatterns($ignorePatterns) {
    $this->ignorePatterns = $this->explodeToken($ignorePatterns);
  }

  /**
   * Sets whether or not to pass with warnings.
   *
   * @param bool $ignoreWarnings
   *   Whether or not to pass with warnings.
   */
  public function setIgnoreWarnings($ignoreWarnings) {
    $this->ignoreWarnings = (bool) $ignoreWarnings;
  }

  /**
   * Sets the report format to use.
   *
   * @param string $report
   *   The report format to use.
   */
  public function setReport($report) {
    $this->report = $report;
  }

  /**
   * Sets whether or not to show progress.
   *
   * @param bool $showProgress
   *   Whether or not to show progress.
   */
  public function setShowProgress($showProgress) {
    $this->showProgress = (bool) $showProgress;
  }

  /**
   * Sets whether or not to show sniff codes in the report.
   *
   * @param bool $showSniffCodes
   *   Whether or not to show sniff codes.
   */
  public function setShowSniffCodes($showSniffCodes) {
    $this->showSniffCodes = (bool) $showSniffCodes;
  }

  /**
   * Sets the coding standards to use.
   *
   * @param string $standards
   *   A list of paths, delimited by spaces, commas or semicolons.
   */
  public function setStandards($standards) {
    $this->standards = $this->explodeToken($standards);
  }

  /**
   * Transform a String to Array with strtok().
   *
   * @param string $string
   *   A list of items.
   * @param string $token
   *   A list of token, by default is space, comma and semicolon.
   *
   * @return array $array
   *   A list of items in an array.
   */
  private function explodeToken($string, $token = ' ,;') {
    $array = array();
    $item = strtok($string, $token);
    while ($item !== FALSE) {
      $array[] = $item;
      $item = strtok($token);
    }
    return $array;
  }

}
