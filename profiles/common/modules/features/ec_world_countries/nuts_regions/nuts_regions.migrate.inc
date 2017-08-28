<?php

/**
 * @file
 * Defines migrations for the NUTS regions project.
 */

/**
 * Implements hook_migrate_api().
 */
function nuts_regions_migrate_api() {
  $api = array(
    'api' => 2,
    'groups' => array(
      'geos' => array(
        'title' => t('Geo imports'),
      ),
    ),
    'migrations' => array(
      'Nuts' => array(
        'class_name' => 'NutsRegonsMigration',
        'group_name' => 'geos',
      ),
    ),
  );
  return $api;
}

/**
 * Defines a dynamic migration that is reused for each source CSV file.
 */
class NutsRegonsMigration extends Migration {

  /**
   * Constructs the migration.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->team = array(
      new MigrateTeamMember('Boris Doesborg', 'bdoesborg@gmail.com',
        t('Implementor')),
      new MigrateTeamMember('Balázs János Tatár', 'balazs@example.com',
        t('Chief Quality Assurance Officer')),
    );

    $this->description = t('Import nuts from CSV file.');

    $this->map = new MigrateSQLMap($this->machineName, array(
      'order' => array(
        'type' => 'int',
        'length' => 24,
        'not null' => TRUE,
        'description' => 'Order',
      ),
    ), MigrateDestinationTerm::getKeySchema()
    );

    $this->path = drupal_get_path('module', 'nuts_regions') . '/data/nuts.csv';

    $this->source = new MigrateSourceCSV($this->path, $this->csvcolumns(), array(

      'header_rows' => 1,
      'delimiter' => ';',
      'enclosure' => '"',
    ));

    // Creates a destination object that receives the data.
    $this->destination = new MigrateDestinationTerm('nuts_regions');

    // Defines mapped source and destination fields.
    $this->addFieldMapping('name', 'description')->description('Title');
    $this->addFieldMapping('nuts_level', 'level');
    $this->addFieldMapping('nuts_id', 'order');
    $this->addFieldMapping('nuts_code', 'nuts_code');
    $this->addFieldMapping('nuts_country', 'country');
    $this->addFieldMapping('parent', 'parent_id');

    // Defines unmapped destination fields.
    $this->addUnmigratedDestinations(array(
      'nuts_description',
      'nuts_description:language',
      'nuts_country:language',
      'nuts_code:language',
      'path',
      'weight',
      'description',
      'format',
      'parent_name',
      'nuts_remark',
      'nuts_remark:language',
    ));

  }

  /**
   * Assigns csv column data to key.
   */
  public function csvcolumns() {

    $columns[0] = array('nuts_code', 'NUTS CODE');
    $columns[1] = array('description', 'NUTS LABEL');
    $columns[2] = array('level', 'NUTS LEVEL');
    $columns[3] = array('country', 'COUNTRY CODE');
    $columns[5] = array('order', 'ORDER');
    return $columns;
  }

  /**
   * Prepares rows before import.
   */
  public function prepareRow($row) {
    $row->parent_id = 0;

    // Tries to find the parent for higher level Nuts codes.
    if ($row->level > 0) {

      // Extracts the Nuts code of the possible parent as follows:
      // - Parent of BE2 is BE.
      // - Parent of BE21 is BE2.
      // - Parent of BE211 is BE21.
      $possible_parent = substr($row->nuts_code, 0, $row->level + 1);
      $query = new EntityFieldQuery();
      $query->entityCondition('entity_type', 'taxonomy_term')
        ->entityCondition('bundle', 'nuts_regions');
      $query->fieldCondition('nuts_code', 'value', $possible_parent);
      $result = $query->execute();
      if (isset($result['taxonomy_term'])) {
        $tids = array_keys($result['taxonomy_term']);
      }
      if ($tids) {

        // Fetches first found tid from results.
        $tid = array_shift(array_slice($tids, 0, 1));
        $row->parent_id = $tid;
      }
    }
  }

}
