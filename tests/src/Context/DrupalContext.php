<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\DrupalContext.
 */

namespace Drupal\nexteuropa\Context;

use Drupal\DrupalExtension\Context\DrupalContext as DrupalExtensionDrupalContext;
use Behat\Gherkin\Node\TableNode;

/**
 * Provides step definitions for interacting with Drupal.
 */
class DrupalContext extends DrupalExtensionDrupalContext {

  /**
   * List of modules enabled before the scenario.
   *
   * @var array
   */
  protected $defaultEnabledModules = array();

  /**
   * The last node id before a scenario starts.
   *
   * @var int
   */
  protected $maxNodeId;

  /**
   * {@inheritdoc}
   */
  public function loggedIn() {
    $session = $this->getSession();
    $session->visit($this->locatePath('/'));

    // Check if the 'logged-in' class is present on the page.
    $element = $session->getPage();
    return $element->find('css', 'body.logged-in');
  }

  /**
   * Visit a node page given its type and title.
   *
   * @param string $type
   *    The node type.
   * @param string $title
   *    The node title.
   *
   * @Then I visit the :type content with title :title
   */
  public function visitContentPage($type, $title) {
    $nodes = node_load_multiple([], ['title' => $title, 'type' => $type], TRUE);
    if (!$nodes) {
      throw new \InvalidArgumentException("Node of type '{$type}' and title '{$title}' not found.");
    }
    // Get node path without any base path by setting 'base_url' and 'absolute'.
    $node = array_shift($nodes);
    $path = 'node/' . $node->nid;
    cache_clear_all($path, 'cache_path');
    $path = url($path, ['base_url' => '', 'absolute' => TRUE]);
    // Visit newly created node page.
    $this->visitPath($path);
  }

  /**
   * Remember the last node id.
   *
   * @BeforeScenario @reset-nodes
   */
  public function rememberCurrentLastNode() {
    $query = db_select('node');
    $query->addExpression('MAX(nid)');
    $max_node_id = $query->execute()->fetchField();

    if (NULL === $max_node_id) {
      $this->maxNodeId = 0;
    }
    else {
      $this->maxNodeId = intval($max_node_id);
    }
  }

  /**
   * Removes any nodes created after the last node id remembered.
   *
   * @AfterScenario @reset-nodes
   */
  public function resetNodes() {
    if (!isset($this->maxNodeId)) {
      return;
    }

    $all_nodes_after_query = (new \EntityFieldQuery())
      ->entityCondition('entity_type', 'node')
      ->propertyCondition('nid', $this->maxNodeId, '>');

    $all_nodes_after = $all_nodes_after_query->execute();
    $all_nodes_after = reset($all_nodes_after);
    if (is_array($all_nodes_after)) {
      entity_delete_multiple('node', array_keys($all_nodes_after));
    }
    unset($this->maxNodeId);
  }

  /**
   * Remember the list of active modules.
   *
   * @BeforeScenario
   */
  public function rememberCurrentModules() {
    $this->defaultEnabledModules = module_list();
  }

  /**
   * Disabled and uninstall modules.
   *
   * @AfterScenario
   */
  public function cleanModule() {
    $current_enabled_list = module_list(TRUE);
    $diff_modules_list = array_diff($current_enabled_list, $this->defaultEnabledModules);
    if (!empty($diff_modules_list)) {
      // Disable and uninstall any modules that were enabled.
      $keys = array_keys($diff_modules_list);
      do {
        $key = array_pop($keys);
        $module_to_treat = $diff_modules_list[$key];
        // Why passing by a custom recursive process instead of just using
        // "module_disable" and "drupal_uninstall_modules"?
        // Because of the order of execution of them for each modules;
        // in some cases, the process ends up with some modules that are still
        // enabled while they have to.
        $this->uninstallModuleWithDependents($module_to_treat);
        unset($diff_modules_list[$key]);
      } while (!empty($keys));

      $this->defaultEnabledModules = array();
      // Clearing the caches to remove modules related data from them.
      drupal_flush_all_caches();
    }
  }

  /**
   * Uninstall a module by uninstalling first its dependent modules.
   *
   * @param string $module_name
   *   The module to uninstall.
   *
   * @throws \Exception
   *   If the uninstall failed because of problem with a dependency.
   */
  private function uninstallModuleWithDependents($module_name) {
    if (isset($this->defaultEnabledModules[$module_name])) {
      // If the module was already active before the scenario,
      // The process cannot not run longer because something is abnormal in
      // the module dependencies.
      throw new \Exception(
        sprintf(
          'The "%s" Module uninstall failed because of a potential bidirectional dependency problem. ',
          $module_name
        )
      );
    }

    if ($module_name && module_exists($module_name)) {
      $module_data = system_rebuild_module_data();
      if (isset($module_data[$module_name])) {
        $module_info = $module_data[$module_name];
        // First treating dependent modules that have been activated with this
        // module.
        if (!empty($module_info->required_by)) {
          $dependents = array_keys($module_info->required_by);
          foreach ($dependents as $dependent) {
            $this->uninstallModuleWithDependents($dependent);
          }
        }
        // Then, Disabling and uninstalling the currently treated module.
        module_disable(array($module_name));
        if (!drupal_uninstall_modules(array($module_name))) {
          throw new \Exception(
            sprintf(
              'The "%s" Module uninstall failed because of a dependency problem',
              $module_name
            )
          );
        }
      }
    }
  }

  /**
   * Enables one or more modules.
   *
   * Provide modules data in the following format:
   *
   * | modules  |
   * | blog     |
   * | book     |
   *
   * @param TableNode $modules_table
   *   The table listing modules.
   *
   * @return bool
   *   Always returns TRUE.
   *
   * @throws \Exception
   *   Thrown when a module does not exist.
   *
   * @Given the/these module/modules is/are enabled
   */
  public function enableModule(TableNode $modules_table) {
    $rebuild = FALSE;
    $message = array();
    foreach ($modules_table->getHash() as $row) {
      if (!module_exists($row['modules'])) {
        if (!module_enable($row)) {
          $message[] = $row['modules'];
        }
        else {
          $rebuild = TRUE;
        }
      }
    }

    if (!empty($message)) {
      throw new \Exception(sprintf('Modules "%s" not found', implode(', ', $message)));
    }
    else {
      if ($rebuild) {
        drupal_flush_all_caches();
      }
      return TRUE;
    }
  }

}
