<?php
/**
 * @file
 * Contains \NextEuropaTrackedChangesInfo.
 */

/**
 * Class NETCInfo.
 */
class NETCInfo extends Entity {

  /**
   * Change the default URI for always pointing to the entities_list page.
   */
  protected function defaultLabel() {
    return $this->rel_entity_label;
  }

  /**
   * Change the default URI for always pointing to the entities_list page.
   */
  protected function defaultUri() {
    return array('path' => 'admin/content/tracked_changes/entities_list');
  }

}
