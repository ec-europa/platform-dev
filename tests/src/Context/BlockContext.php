<?php
/**
 * @file
 * Contains \Drupal\nexteuropa\Context\BlockContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;

/**
 * Context with Block functionality.
 */
class BlockContext implements Context {

  /**
   * List of Blocks changed during test execution.
   *
   * @var \Block[]
   */
  protected $blocks = [];

  /**
   * TaxonomyContext constructor.
   */
  public function __construct() {

  }

  /**
   * Check vocabulary.
   *
   * @param string $delta
   *    Identifier of the block.
   * @param string $module
   *    Module that produced the block.
   *
   * @Given the block :delta from the module :module exists
   */
  public function assertBlock($delta, $module) {
    $this->getBlockInfo($delta, $module);
  }

  /**
   * Create vocabulary.
   *
   * @param string $delta
   *    Identifier of the block.
   * @param string $module
   *    Module that produced the block.
   * @param string $region
   *    Region to asign the block to.
   *
   * @Given that the block :delta from module :module is assigned to the region :region
   *
   * @When I assign the block :delta from module :module to the region :region
   */
  public function iAssignTheBlockFromModuleToTheRegion($delta, $module, $region) {
    global $theme;

    $available_regions = system_region_list($theme, REGIONS_ALL, FALSE);
    if (!in_array($region, $available_regions)) {
      throw new \InvalidArgumentException("The region '{$region}' is not defined in the default theme.");
    }

    $block = $this->getBlockInfo($delta, $module);
    // Save the block for cleaning.
    $this->blocks[] = $block;

    db_update('block')
      ->fields(array(
        'region' => $region,
        'status' => 1,
      ))
      ->condition('delta', $delta, '=')
      ->condition('module', $module, '=')
      ->condition('theme', $theme, '=')
      ->execute();

  }

  /**
   * Revert to previous block settings after scenario execution.
   *
   * @AfterScenario @RevertBlockConfiguration
   */
  public function revertBlockConfiguration() {
    // Remove the vocabularies.
    foreach ($this->blocks as $block) {
      db_update('block')
        ->fields(array(
          'region' => $block['region'],
          'status' => $block['status'],
        ))
        ->condition('bid', $block['bid'], '=')
        ->execute();
    }
  }


  /**
   * Get the Taxonomy Id by the name.
   *
   * @param string $delta
   *    Identifier of the block.
   * @param string $module
   *    Module that produced the block.
   *
   * @return \stdClass
   *    Block object.
   */
  private function getBlockInfo($delta, $module) {
    global $theme;
    $query = db_select('block', 'b');
    $query
      ->fields('b')
      ->condition('module', $module)
      ->condition('delta', $delta)
      ->condition('theme', $theme);
    $result = $query->execute();
    $block = $result->fetchAssoc();
    if (empty($block)) {
      throw new \InvalidArgumentException("The block '{$delta}' in the module '{$module}' doesn't exist.");
    }
    return $block;
  }

}
