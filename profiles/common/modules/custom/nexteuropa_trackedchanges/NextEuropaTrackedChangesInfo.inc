<?php
/**
 * @file
 * Contains \NextEuropaTrackedChangesInfo.
 */

/**
 * Class NextEuropaTrackedChangesInfo.
 */
class NextEuropaTrackedChangesInfo extends Entity {

  /**
   * Change the default URI for always pointing to the entities_list page.
   */
  protected function defaultUri() {
    return array('path' => 'admin/content/tracked_changes/entities_list');
  }

}
