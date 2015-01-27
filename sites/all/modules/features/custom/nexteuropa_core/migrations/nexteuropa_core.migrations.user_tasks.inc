<?php

/**
 * Import terms on "User tasks" vocabulary.
 */
class NextEuropaCoreUserTasksMigration extends Migration {

  public function __construct($arguments) {
    parent::__construct($arguments);
    
    $this->description = t('Import "User tasks" terms');
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'name' => array(
          'type' => 'varchar',
          'length' => '255',
          'not null' => TRUE,
          'description' => 'Term name',
        ),
      ),
      MigrateDestinationTerm::getKeySchema()
    );

    $path = drupal_get_path('module', 'nexteuropa_core') . '/data/user_tasks.csv';
    $this->source = new MigrateSourceCSV($path, array(array('name', 'Name')), array('delimiter' => ';'));
    $this->destination = new MigrateDestinationTerm('core_user_tasks');

    $this->addFieldMapping('name', 'name');
  }

}



