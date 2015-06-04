<?php
/**
 * @file
 * newsroom_migrate.item.inc
 */

use Drupal\nexteuropa_migrate\migrate\MigrateItemJSON;
use Drupal\nexteuropa_migrate\migrate\MigrationAbstract;

/**
 * Class NewsroomItemMigration.
 */
class NewsroomItemMigration extends NewsroomMigrationAbstract  {

  /**
   * TBD.
   */
  public function __construct($arguments) {
    parent::__construct('items', $arguments);

    // Requires taxonomy terms migration to run before content migration.
    $this->setHardDependencies(array(
      'NewsroomType',
      'NewsroomTopic',
      'NewsroomService',
    ));

    $this->setMap(new MigrateSQLMap(
      $this->getMachineName(),
      $this->getSourceKey(),
      MigrateDestinationNode::getKeySchema()
    ));

    $this->setDestination(new MigrateDestinationNode('newsroom_item'));
    // Node properties.
    $this->addFieldMapping('promote')->defaultValue(FALSE);
    $this->addFieldMapping('status')->defaultValue(NODE_PUBLISHED);

    // Title.
    $this->addFieldMapping('title', 'title_field');
    $this->addFieldMapping('title_field', 'title_field');

    // Body.
    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('body:format')
      ->defaultValue('full_html');

    $this->addFieldMapping('item_type', 'field_newsroom_item_type');
    $this->addFieldMapping('category', 'field_newsroom_category');
    $this->addFieldMapping('primary_topic', 'field_primary_topic');
    $this->addFieldMapping('topics', 'field_newsroom_topics');
    $this->addFieldMapping('topics', 'field_highlighted_newsroom_topic');
    $this->addFieldMapping('short_title', 'field_newsroom_item_short_title');
    $this->addFieldMapping('short_title', 'field_teaser');
    $this->addFieldMapping('pre_title', 'field_newsroom_item_pre_title');
    $this->addFieldMapping('quote_box', 'field_newsroom_item_quote_box');
    $this->addFieldMapping('linked_obj', 'field_newsroom_item_linked_obj');
    $this->addFieldMapping('illustrative_image', 'field_illustrative_image');
    $this->addFieldMapping('documents', 'field_newsroom_documents');
    $this->addFieldMapping('contact_text', 'field_newsroom_item_contact_text');
    $this->addFieldMapping('contact_mail', 'field_newsroom_item_contact_mail');
    $this->addFieldMapping('item_speaker', 'field_newsroom_item_speaker');
    $this->addFieldMapping('item_venue', 'field_newsroom_item_venue');
    $this->addFieldMapping('files', 'field_newsroom_files');
    $this->addFieldMapping('other_link', 'field_newsroom_item_other_link');
    $this->addFieldMapping('project', 'field_newsroom_project');
    $this->addFieldMapping('project_acr', 'field_newsroom_project_acr');
    $this->addFieldMapping('image', 'field_newsroom_item_image');
    $this->addFieldMapping('slide', 'field_newsroom_slide');
    $this->addFieldMapping('item_date', 'field_newsroom_item_date');
    $this->addFieldMapping('rapid_pr', 'field_newsroom_item_rapid_pr');
    $this->addFieldMapping('main_link', 'field_newsroom_item_main_link');
    $this->addFieldMapping('short_item', 'field_newsroom_short_item');
    $this->addFieldMapping('newsletter_only', 'field_newsletter_only');
    $this->addFieldMapping('teaser_only', 'field_newsroom_teaser_only');
    $this->addFieldMapping('related_content', 'field_related_content');

    // Meta tags.
    $this->addFieldMapping('field_meta_classification', 'meta_classification');
    $this->addFieldMapping('field_meta_classification:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_meta_description', 'meta_description');
    $this->addFieldMapping('field_tags', 'meta_keywords');
    $this->addFieldMapping('field_tags:create_term')->defaultValue(TRUE);

    // Field image.
    $this->addFieldMapping('field_reps_core_image', 'field_reps_core_image');
    $this->addFieldMapping('field_reps_core_image:destination_dir', 'reps/malta/img');
    $this->addFieldMapping('field_reps_core_image:alt', 'field_reps_core_image_alt_text');
    $this->addFieldMapping('field_reps_core_image:title', 'field_reps_core_image_alt_text');
    $this->addFieldMapping('field_reps_core_image:file_replace')->defaultValue('FILE_EXISTS_REPLACE');
    $this->addFieldMapping('language', 'default_language');
  }

  /**
   * Process Row.
   */
  public function prepareRow($row) {

  }

  public function preImport() {
    parent::preImport();
  }

  public function postImport() {
    parent::postImport();
  }
}
