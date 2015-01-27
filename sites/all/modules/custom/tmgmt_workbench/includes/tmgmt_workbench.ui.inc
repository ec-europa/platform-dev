<?php

/**
 * @file
 * Provides the Workbench Moderation UI source controller.
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
  
  /**
   * {@inheritdoc}
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    if (isset($items['admin/tmgmt/sources/workbench_moderation_node'])) {
      $items['admin/tmgmt/sources/workbench_moderation_node']['weight'] = -19;
    }
    return $items;
  }

  /**
   * Utility method: get moderation state.
   * 
   * @param type $node
   *    Fully loaded node object.
   * @param type $type
   *    
   * @return null
   */
  private function getModerationState($node, $type = 'current') {
    if (is_object($node) && property_exists($node, 'workbench_moderation') && isset($node->workbench_moderation[$type])){
      $state = $node->workbench_moderation[$type];
      return $state->state;
    }
    return NULL;
  }

  /**
   * Utility method: get moderation revision.
   * 
   * @param type $node
   * @param type $type
   * @return null
   */
  private function getModerationRevision($node, $type = 'current') {
    if (is_object($node) && property_exists($node, 'workbench_moderation') && isset($node->workbench_moderation[$type])){
      $vid = $node->workbench_moderation[$type]->vid;
      return node_load($node->nid, $vid);
    }
    return NULL;
  }

  /**
   * Utility method: get translatable states from module's settings.
   * 
   * @return array
   */
  public function getTranslatableStates() {
    return variable_get('tmgmt_workbench_moderation_states', array());
  }
  
}
        
