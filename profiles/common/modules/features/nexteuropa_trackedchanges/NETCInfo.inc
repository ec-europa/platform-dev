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
    if ($this->rel_entity_label) {
      return $this->rel_entity_label;
    }

    return t('Unknown label');
  }

  /**
   * Change the default URI for always pointing to the entities_list page.
   */
  protected function defaultUri() {
    return array('path' => 'admin/content/tracked_changes');
  }

}
