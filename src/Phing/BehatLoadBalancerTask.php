<?php

/**
 * @file
 * Contains \NextEuropa\Phing\BehatLoadBalancerTask.
 */

namespace NextEuropa\Phing;

require_once 'phing/Task.php';

/**
 * Class BehatLoadBalancerTask.
 *
 * @package NextEuropa\Phing
 */
class BehatLoadBalancerTask extends \Task {

  /**
   * Number of containers.
   *
   * @var int
   */
  private $containers;

  /**
   * Behat root directory.
   *
   * @var string
   */
  private $root;

  /**
   * Destination directory where individual behat.yml files will be created.
   *
   * @var string
   */
  private $destination;

  /**
   * Full path to behat.yml file to be imported.
   *
   * @var string
   */
  private $import;

  /**
   * Set number of containers..
   *
   * @param string $containers
   *    Number of containers.
   */
  public function setContainers($containers) {
    $this->containers = $containers;
  }

  /**
   * Set Behat root directory.
   *
   * @param string $root
   *    Behat root directory.
   */
  public function setRoot($root) {
    $this->root = $root;
  }

  /**
   * Set destination directory.
   *
   * @param string $destination
   *    Destination directory.
   */
  public function setDestination($destination) {
    $this->destination = $destination;
  }

  /**
   * Set full path to import behat.yml.
   *
   * @param string $import
   *    Import behat.yml full path.
   */
  public function setImport($import) {
    $this->import = $import;
  }

  /**
   * Main callback.
   */
  public function main() {
    if (!is_dir($this->destination)) {
      throw new \InvalidArgumentException("{$this->destination} is not a valid directory.");
    }

    // Remove already existing .yml files.
    foreach ($this->scanDirectory($this->destination, '/.yml/') as $file) {
      unlink($file);
    }

    // Generate feature files.
    foreach ($this->getContainers($this->root) as $key => $container) {
      $content = $this->generateBehatYaml($container);
      file_put_contents($this->destination . "/behat.{$key}.yml", $content);
    }
  }

  /**
   * Scan and divide feature files into containers.
   *
   * @param string $root
   *    Root directory to scan.
   *
   * @return array
   *    List of feature files divided into containers.
   */
  protected function getContainers($root) {
    $files = $this->scanDirectory($root, '/.feature/');
    $size = ceil(count($files) / $this->containers);
    return array_chunk($files, $size);
  }

  /**
   * Recursively scan a directory.
   *
   * @param string $dir
   *   The base directory, without trailing slash.
   * @param string $mask
   *   The preg_match() regular expression of the files to find.
   *
   * @return array
   *    List of files with their absolute path.
   */
  public function scanDirectory($dir, $mask) {
    $depth = 0;
    $files = [];
    if (is_dir($dir) && $handle = opendir($dir)) {
      while (FALSE !== ($filename = readdir($handle))) {
        if (!preg_match('/(\.\.?|CVS)$/', $filename) && $filename[0] != '.') {
          $uri = "$dir/$filename";
          if (is_dir($uri)) {
            $files = array_merge($this->scanDirectory($uri, $mask), $files);
          }
          elseif ($depth >= 0 && preg_match($mask, $filename)) {
            $files[] = $uri;
          }
        }
      }
      closedir($handle);
    }

    return $files;
  }

  /**
   * Generate behat.yml files.
   *
   * @param array $container
   *    Array of feature file locations.
   *
   * @return string
   *    Return behat.yaml file.
   */
  protected function generateBehatYaml($container) {
    $features = implode("\n        - ", $container);
    return <<<YAML
imports:
  - {$this->import}
default:
  suites:
    default:
      paths:
        - {$features}
YAML;

  }

}
