<?php

/**
 * @file
 * Provides the Workbench Moderation UI source controller.
 */

/**
 * Class TMGMTWorkbenchSourceUIController.
 */
class TMGMTWorkbenchSourceUIController extends TMGMTEntitySourceUIController {

  /**
   * {@inheritdoc}
   */
  public function overviewFormHeader($type) {
    $header = parent::overviewFormHeader($type);
    $header['state'] = t('Current state');
    return $header;
  }

  /**
   * {@inheritdoc}
   */
  public function overviewRow($data) {
    $row = parent::overviewRow($data);
    $node = node_load($data['entity_id']);
    $state = $this->getModerationState($node);
    $current_revision = $this->getModerationRevision($node);
    if ($state == 'published') {
      $row['title'] = l($current_revision->title, 'node/' . $current_revision->nid);
    }
    else {
      $row['title'] = l($current_revision->title, 'node/' . $current_revision->nid . '/draft');
    }
    $row['state'] = $state;
    return $row;
  }

  /**
   * {@inheritdoc}
   */
  public function overviewForm($form, &$form_state, $type) {
    // Unfortunately using hook_query_TAG_alter() is the only way we have to
    // alter the actual query, for this reason we need to use drupal_static().
    drupal_static('tmgmt_workbench_overview_form', TRUE);
    return parent::overviewForm($form, $form_state, $type);
  }

  // @codingStandardsIgnoreStart
  /**
   * {@inheritdoc}
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    if (isset($items['admin/tmgmt/sources/workbench_moderation_node'])) {
      $items['admin/tmgmt/sources/workbench_moderation_node']['weight'] = -25;
    }
    return $items;
  }
  // @codingStandardsIgnoreEnd

  /**
   * Gets entities data of provided type needed to build overview form list.
   *
   * @param string $type
   *   Entity type for which to get list of entities.
   * @param array $property_conditions
   *   Array of key => $value pairs passed into
   *   tmgmt_entity_get_translatable_entities() as the second parameter.
   *
   * @return array
   *   Array of entities.
   */
  public function getEntitiesTranslationData($type, $property_conditions = array()) {

    $return_value = array();

    $entities = tmgmt_entity_get_translatable_entities($type, $property_conditions, TRUE);

    $entity_info = entity_get_info($type);
    $bundles = tmgmt_entity_get_translatable_bundles($type);

    // For retrieved entities add translation specific data.
    foreach ($entities as $entity) {

      list($entity_id, , $bundle) = entity_extract_ids($type, $entity);
      $entity_uri = entity_uri($type, $entity);

      // This occurs on user entity type.
      if (empty($entity_id)) {
        continue;
      }

      // @var EntityTranslationDefaultHandler $handler.
      $handler = entity_translation_get_handler($type, $entity);

      // Get existing translations and current job items for the entity.
      // to determine translation statuses.
      $translations = $handler->getTranslations();
      $source_lang = entity_language($type, $entity);
      $current_job_items = tmgmt_job_item_load_latest('workbench_moderation', $type, $entity_id, $source_lang);

      // Load basic entity data.
      $return_value[$entity_id] = array(
        'entity_type' => $type,
        'entity_id' => $entity_id,
        'entity_label' => entity_label($type, $entity),
        'entity_uri' => $entity_uri['path'],
      );

      if (count($bundles) > 1) {
        $return_value[$entity_id]['bundle'] = isset($bundles[$bundle]) ? $bundles[$bundle] : t('Unknown');
      }

      // Load entity translation specific data.
      foreach (language_list() as $langcode => $language) {

        $translation_status = 'current';

        if ($langcode == $source_lang) {
          $translation_status = 'original';
        }
        elseif (!isset($translations->data[$langcode])) {
          $translation_status = 'missing';
        }
        elseif (!empty($translations->data[$langcode]['translate'])) {
          $translation_status = 'outofdate';
        }

        $return_value[$entity_id]['current_job_items'][$langcode] = isset($current_job_items[$langcode]) ? $current_job_items[$langcode] : NULL;
        $return_value[$entity_id]['translation_statuses'][$langcode] = $translation_status;
      }
    }

    return $return_value;
  }

  /**
   * Get moderation state.
   *
   * @param object $node
   *    Node object.
   * @param string $type
   *    Moderation type.
   *
   * @return string|null
   *    Moderation state or null.
   */
  private function getModerationState($node, $type = 'current') {
    if (is_object($node) && property_exists($node, 'workbench_moderation')
      && isset($node->workbench_moderation[$type])
    ) {
      $state = $node->workbench_moderation[$type];
      return $state->state;
    }
    return NULL;
  }

  /**
   * Get moderation revision.
   *
   * @param object $node
   *    Node object.
   * @param string $type
   *    Moderation type.
   *
   * @return object|null
   *    Node revision or null.
   */
  private function getModerationRevision($node, $type = 'current') {
    if (is_object($node) && property_exists($node, 'workbench_moderation') && isset($node->workbench_moderation[$type])) {
      $vid = $node->workbench_moderation[$type]->vid;
      return node_load($node->nid, $vid);
    }
    return NULL;
  }

  /**
   * Implements TMGMTSourceUIControllerInterface::overviewFormSubmit().
   */
  public function overviewFormSubmit($form, &$form_state, $type) {
    // Handle search redirect.
    $this->overviewSearchFormRedirect($form, $form_state, $type);

    $jobs = array();
    $entities = entity_load($type, $form_state['values']['items']);
    $source_lang_registry = array();

    // Loop through entities to create individual jobs for each source language.
    foreach ($entities as $entity) {

      // EntityTranslationDefaultHandler $handler.
      $source_lang = entity_language($type, $entity);
      list($entity_id, ,) = entity_extract_ids($type, $entity);

      try {

        // For given source lang no job exists yet.
        if (!isset($source_lang_registry[$source_lang])) {
          // Create new job.
          $job = tmgmt_job_create($source_lang, NULL, $GLOBALS['user']->uid);
          // Add initial job item.
          $job->addItem('workbench_moderation', $type, $entity_id);
          // Add job identifier into registry.
          $source_lang_registry[$source_lang] = $job->tjid;
          // Add newly created job into jobs queue.
          $jobs[$job->tjid] = $job;
        }
        // We have a job for given source lang, so just add new job item for the
        // existing job.
        else {
          $jobs[$source_lang_registry[$source_lang]]->addItem('workbench_moderation', $type, $entity_id);
        }
      }
      catch (TMGMTException $e) {
        watchdog_exception('tmgmt_workbench', $e);
        $entity_label = entity_label($type, $entity);
        drupal_set_message(t('Unable to add job item for workbench_moderation item %name (using overview table): %error.', array(
          '%name' => $entity_label,
          '%error' => $e->getMessage(),
        )), 'error');
      }
    }

    // If necessary, do a redirect.
    $redirects = tmgmt_ui_job_checkout_multiple($jobs);
    if ($redirects) {
      tmgmt_ui_redirect_queue_set($redirects, current_path());
      $form_state['redirect'] = tmgmt_ui_redirect_queue_dequeue();
      drupal_set_message(format_plural(count($redirects), t('One job needs to be checked out.'), t('@count jobs need to be checked out.')));
    }
  }

  /**
   * Utility method: get translatable states from module's settings.
   *
   * @return [a-zA-Z]+
   *   [a-zA-Z]+ translatable moderation states.
   */
  public function getTranslatableStates() {
    return variable_get('tmgmt_workbench_moderation_states', array());
  }

}
