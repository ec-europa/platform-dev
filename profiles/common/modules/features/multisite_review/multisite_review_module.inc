<?php

/**
 * @file
 * Contains a class that stores module data.
 */

/**
 * A module.
 *
 * @property array $info
 *   An array of module information from the module's .info file.
 * @property string $type
 *   The module type, either 'feature' or 'module'.
 */
class MultisiteReviewModule {

  /**
   * The module information from the .info file.
   *
   * @var array
   */
  protected $info;

  /**
   * The machine readable module name.
   *
   * @var string
   */
  protected $name;

  /**
   * The module path relative to the Drupal root folder.
   *
   * @var string
   */
  protected $path;

  /**
   * Modules selected to be reviewed from the setting form.
   */
  protected $specific;

  /**
   * Constructs a Module object.
   *
   * @param string $module_name
   *   The name of the module.
   */
  public function __construct($module_name) {
    $this->path = drupal_get_path('module', $module_name);
    $this->info = drupal_parse_info_file($this->path . '/' . $module_name . '.info');
    $this->name = $module_name;
    $this->specific = variable_get('what_to_review', '');
  }

  /**
   * Magic getter.
   *
   * @param string $property
   *   The property to get.
   *
   * @return mixed
   *   The corresponding value.
   *
   * @throws Exception
   *   Thrown when an undefined property was requested.
   */
  public function __get($property) {
    switch ($property) {
      case 'type':
        return $this->getType();
    }
    throw new \Exception("Undefined property $property.");
  }

  /**
   * Returns the module type.
   *
   * @return string
   *   The module type, either 'feature' or 'module'.
   */
  public function getType() {
    return $this->isFeature() ? 'feature' : 'module';
  }

  /**
   * Returns whether or not the module is a feature.
   *
   * @return bool
   *   TRUE if the module has '/features/' in its path, FALSE otherwise.
   */
  public function isFeature() {
    // Determine if the module is a feature. This is derived from the path
    // where the module is installed.
    return (bool) preg_match('/\/features\//', $this->path);
  }

  /**
   * Returns the module path.
   *
   * @return string
   *   The module path relative to the Drupal root folder.
   */
  public function getPath() {
    return $this->path;
  }

  /**
   * Returns the module information.
   *
   * @return array
   *   The module information from the module's .info file.
   */
  public function getInfo() {
    return $this->info;
  }

  /**
   * Returns the machine readable module name.
   *
   * @return string
   *   The module name.
   */
  public function getName() {
    return $this->name;
  }

  /**
   * Returns the human readable module name.
   *
   * @return string
   *   The human readable module name.
   */
  public function getHumanName() {
    return $this->info['name'];
  }

  /**
   * Returns whether or not the module is a custom module.
   *
   * @return bool
   *   TRUE if the module has '/custom/' in its path, FALSE otherwise.
   */
  public function isCustom() {
    return (bool) preg_match('/\/custom\//', $this->path);
  }

  /**
   * Returns only those custom modules which were selected via settings form.
   *
   * @return array
   *   Return an array of selected modules.
   */
  public function getSpecific() {
    $result = array();
    foreach ($this->specific as $key => $value) {

      if ($this->specific[$key] != '0') {
        $result[] = $this->specific[$key];
      }

    }
    return $result;
  }

}
