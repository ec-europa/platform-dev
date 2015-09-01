<?php

/**
 * @file
 * Defines migrations for the mapmock project which provides mock content.
 */

/**
 * Implements hook_migrate_api().
 */
function mapmock_migrate_api() {
  $api = array(
    'api' => 2,
    'groups' => array(
      'mocks' => array(
        'title' => t('Mock migrations'),
      ),
    ),
    'migrations' => array(
      'Users' => array(
        'class_name' => 'MapMockUserMigration',
        'group_name' => 'mocks',
      ),
      'Content' => array(
        'class_name' => 'MapMockContentMigration',
        'group_name' => 'mocks',
      ),
    ),
  );
  return $api;
}

/**
 * Defines common elements for all MapMock migrations.
 */
abstract class MapMockBaseMigration extends Migration {

  /**
   * Defines a migration group.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->issuePattern = 'https://webgate.ec.europa.eu/CITnet/jira/browse/DAE-xyz';
    $this->team = array(
      new MigrateTeamMember('Boris Doesborg', 'bdoesborg@gmail.com',
        t('Implementor')),
      new MigrateTeamMember('An Onymous', 'an@example.com',
        t('Product owner')),
    );
  }

  /**
   * Defines some fdefaults for a migration from CSV.
   */
  protected function sourceFileOptions() {
    return array(
      'header_rows' => 1,
      'delimiter' => ";",
      'enclosure' => '"',
    );
  }

}

/**
 * Migrates users from CSV.
 */
class MapMockUserMigration extends MapMockBaseMigration {

  /**
   * Sets migration source, destination including fields to migrate.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Import users.');
    $this->map = new MigrateSQLMap($this->machineName, array(
      'id' => array(
        'type' => 'int',
        'not null' => TRUE,
      ),
    ), MigrateDestinationNode::getKeySchema()
    );
    $this->source = new MigrateSourceCSV(
      drupal_get_path('module', 'mapmock') . '/data/users.csv', array(), $this->sourceFileOptions()
    );
    $this->destination = new MigrateDestinationUser();
    $this->addFieldMapping('name', 'nick_name');
    $this->addFieldMapping('mail', 'email');
    $this->addFieldMapping('nuts_region', 'country');
    $this->addFieldMapping('status')->defaultValue(1);
    $this->addFieldMapping('roles')->defaultValue(DRUPAL_AUTHENTICATED_RID);

    $this->addUnmigratedSources(array(
        'last_name',
        'first_name',
        'place_birth',
        'maiden_name',
        'punch_card_nr',
        'date_birth',
        'premium_member',
      )
    );

    // Defines unmapped destination fields.
    $this->addUnmigratedDestinations(array(
      'pass',
      'signature',
      'access',
      'login',
      'theme',
      'signature_format',
      'created',
      'timezone',
      'language',
      'picture',
      'init',
      'data',
      'role_names',
      'picture',
      'signature',
      'signature_format',
      'timezone',
      'language',
      'theme',
      'init',
      'data',
      'is_new',
      'path',
    ));
  }

  /**
   * Tinkers with values before migrating.
   */
  public function prepareRow($row) {
    $row->nick_name = _mapmock_slugify($row->nick_name);
    $row->country = ucwords(strtoupper($row->country));
  }

}

/**
 * Migrates nodes from CSV.
 */
class MapMockContentMigration extends MapMockBaseMigration {

  /**
   * Sets migration source, destination including fields to migrate.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Import content.');

    // Defines dependency on the Users migration.
    $this->dependencies = array('Users');
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'int',
          'not null' => TRUE,
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );
    $this->source = new MigrateSourceCSV(
      drupal_get_path('module', 'mapmock') . '/data/content.csv',
      array(),
      $this->sourceFileOptions()
    );
    $this->destination = new MigrateDestinationNode('den', array('text_format' => 'full_html'));
    $this->addFieldMapping('uid', 'author')->sourceMigration('Users');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('location', 'location')->defaultValue('');
    $this->addFieldMapping('location:input_format')->defaultValue('lat/lon');
    $this->addFieldMapping('location:lat', 'lat');
    $this->addFieldMapping('location:lon', 'lon');
    $this->addFieldMapping('topics', 'tags')->separator(' ');
    $this->addFieldMapping('topics:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('nuts_region', 'nuts');

    // Defines unmapped destination fields.
    $this->addUnmigratedDestinations(array(
      'created',
      'changed',
      'status',
      'promote',
      'sticky',
      'revision',
      'log',
      'language',
      'tnid',
      'translate',
      'revision_uid',
      'is_new',
      'topics:source_type',
      'topics:ignore_case',
      'body:summary',
      'body:format',
      'body:language',
      'location:wkt',
      'location:json',
      'location:left',
      'location:top',
      'location:right',
      'location:bottom',
      'path',
      'comment',
    ));

    $this->addUnmigratedSources(
      array('teaser', 'tag 1', 'tag 2', 'quantity', 'date', 'verified', 'email')
    );
  }

  /**
   * Tinkers with values before migrating.
   */
  public function prepareRow($row) {
    $row->tags = ucwords(strtolower($row->{'tag 1'}));
  }

}
