<?php
/**
 * @file
 * Code for the newsroom_migrate module.
 */

use Drupal\nexteuropa_migrate\migrate\MigrateItemJSON;
use Drupal\nexteuropa_migrate\migrate\MigrationAbstract;

/**
 * Class NewsroomTypeMigration
 */
class NewsroomTypeMigration extends NewsroomMigrationAbstract {
  /**
   * TBD.
   */
  public function __construct($arguments) {
    parent::__construct('type', $arguments);

    $this->setMap(new MigrateSQLMap(
      $this->getMachineName(),
      $this->getSourceKey(),
      MigrateDestinationTerm::getKeySchema()
    ));

    $this->setDestination(new MigrateDestinationTerm('newsroom_item_type'));

    $this->addFieldMapping('name', 'subject');
    $this->addFieldMapping('name_field', 'subject');
    $this->addFieldMapping('language', 'default_language');
    $this->addFieldMapping('weight', 'weight');
    $this->addFieldMapping('newsroom_type', 'field_newsroom_type');
    $this->addFieldMapping('type_id', 'field_newsroom_type_id');
    $this->addFieldMapping('import_name', 'field_newsroom_import_name');
    $this->addFieldMapping('display_date', 'field_display_date');
    $this->addFieldMapping('date_label', 'field_date_label');
    $this->addFieldMapping('direct_link', 'field_direct_link_if_teaser_only');
    $this->addFieldMapping('hightlighted', 'field_newsroom_highlighted');
    $this->addFieldMapping('read_more_text', 'field_read_more_text');
  }

}
