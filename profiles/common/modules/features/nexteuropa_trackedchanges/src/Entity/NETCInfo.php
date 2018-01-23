<?php

namespace Drupal\nexteuropa_trackedchanges\Entity;

/**
 * Class NETCInfo.
 */
class NETCInfo extends \Entity {
  // @codingStandardsIgnoreStart
  /**
   * Entity id.
   *
   * @var int
   */
  public $info_id;

  /**
   * Type of the related entity.
   *
   * @var string
   */
  public $rel_entity_type;

  /**
   * Machine name of the type of the related entity.
   *
   * @var string
   */
  public $rel_entity_type_name;

  /**
   * Id of the related entity.
   *
   * @var int
   */
  public $rel_entity_id;

  /**
   * Bundle of the related entity.
   *
   * @var string
   */
  public $rel_entity_bundle;

  /**
   * Machine name of the bundle of the related entity.
   *
   * @var string
   */
  public $rel_entity_bundle_name;

  /**
   * URI of the related entity.
   *
   * @var string
   */
  public $rel_entity_uri;

  /**
   * Label of the related entity.
   *
   * @var string
   */
  public $rel_entity_label;

  /**
   * Moderation state of the related entity.
   *
   * @var string
   */
  public $rel_entity_state;

  /**
   * Machine name of the moderation state of the related entity.
   *
   * @var string
   */
  public $rel_entity_state_human_name;

  /**
   * Source language of the related entity.
   *
   * @var string
   */
  public $rel_entity_language;

  /**
   * Path of the related entity.
   *
   * @var string
   */
  public $rel_entity_path;
  // @codingStandardsIgnoreEnd

  /**
   * Creation/update timestamp of the entity.
   *
   * @var string
   */
  public $scanned;

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
