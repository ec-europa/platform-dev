<?php
/**
 * @file
 * Code for the newsroom_migrate module
 */

use Drupal\nexteuropa_migrate\migrate\MigrateItemJSON;
use Drupal\nexteuropa_migrate\migrate\MigrationAbstract;

/**
 * Class NewsroomServiceMigration.
 */
class NewsroomServiceMigration extends NewsroomMigrationAbstract {
  /**
   * TBD.
   */
  public function __construct($arguments) {
    parent::__construct('service', $arguments);

    $this->setMap(new MigrateSQLMap(
      $this->getMachineName(),
      $this->getSourceKey(),
      MigrateDestinationTerm::getKeySchema()
    ));

    $this->setDestination(new MigrateDestinationTerm('newsroom_service'));

    $this->addFieldMapping('name', 'subject');
    $this->addFieldMapping('name_field', 'subject');
    $this->addFieldMapping('language', 'default_language');
    $this->addFieldMapping('weight', 'weight');
    $this->addFieldMapping('service_id', 'field_newsroom_service_id');
    $this->addFieldMapping('service_type', 'field_service_type');
    $this->addFieldMapping('service_active', 'field_service_active');
  }

}
