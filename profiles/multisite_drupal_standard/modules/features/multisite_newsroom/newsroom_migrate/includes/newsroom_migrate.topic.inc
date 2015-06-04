<?php
/**
 * @file
 * Code for the newsroom_migrate module.
 */

use Drupal\nexteuropa_migrate\migrate\MigrateItemJSON;
use Drupal\nexteuropa_migrate\migrate\MigrationAbstract;

/**
 * Class NewsroomTopicMigration.
 */
class NewsroomTopicMigration extends NewsroomMigrationAbstract {
  /**
   * TBD.
   */
  public function __construct($arguments) {
    parent::__construct('topic', $arguments);

    $this->setMap(new MigrateSQLMap(
      $this->getMachineName(),
      $this->getSourceKey(),
      MigrateDestinationTerm::getKeySchema()
    ));

    $this->setDestination(new MigrateDestinationTerm('newsroom_topic'));

    $this->addFieldMapping('name', 'subject');
    $this->addFieldMapping('name_field', 'subject');
    $this->addFieldMapping('language', 'default_language');
    $this->addFieldMapping('weight', 'weight');
    $this->addFieldMapping('topic_id', 'field_newsroom_topic_id');
    $this->addFieldMapping('category_domain', 'field_newsroom_category_domai');
  }

}
