<?php

/**
 * @file
 * Nexteuropa Newsroom blocks hooks and helpers.
 */

/**
 * Implements hook_block_info().
 */
function nexteuropa_newsroom_block_info() {
  $blocks = array();
  $blocks['newsroom_summary_blocks'] = array(
    'info' => t('Newsroom Summary Blocks'),
    'cache' => DRUPAL_CACHE_CUSTOM,
  );
  $blocks['newsroom_related_content'] = array(
    'info' => t('Newsroom Related Content'),
    'cache' => DRUPAL_CACHE_GLOBAL,
  );
  $blocks['newsroom_admin_tools'] = array(
    'info' => t('Newsroom administration buttons'),
    'cache' => DRUPAL_CACHE_PER_PAGE,
  );
  $blocks['newsroom_newsletter_subscription'] = array(
    'info' => t('Newsroom Newsletter Subscription'),
    'cache' => DRUPAL_CACHE_PER_PAGE,
  );
  $blocks['.'] = array(
    'info' => t('Newsroom List Filter'),
    'cache' => DRUPAL_CACHE_CUSTOM,
  );
  $blocks['newsroom_proposal'] = array(
    'info' => t('Newsroom items proposal'),
    'cache' => DRUPAL_CACHE_GLOBAL,
  );
  $blocks['newsroom_agenda_block'] = array(
    'info' => t('Newsroom agenda block'),
    'cache' => DRUPAL_CACHE_PER_PAGE,
  );
  return $blocks;
}

/**
 * Implements hook_block_view().
 */
function nexteuropa_newsroom_block_view($delta = '') {
  switch ($delta) {
    case 'newsroom_summary_blocks':
      $block['subject'] = l(t('Newsroom'), NewsroomHelper::getNewsroomPageUrl(array(NEXTEUROPA_NEWSROOM_ALL)));
      $block['content'] = _nexteuropa_nexteuropa_get_summary_blocks();
      break;

    case 'newsroom_related_content':
      $block['subject'] = t('Related content');
      $block['content'] = _nexteuropa_nexteuropa_related_content();
      break;

    case 'newsroom_admin_tools':
      $block['subject'] = NULL;
      $block['content'] = _nexteuropa_newsroom_tools();
      break;

    case 'newsroom_newsletter_subscription':
      $block['subject'] = NULL;
      $block['content'] = _nexteuropa_newsroom_newsletter_subscription();
      break;

    case 'newsroom_proposal':
      $block['subject'] = t('Newsroom item proposal');
      $block['content'] = _nexteuropa_newsroom_block_news_proposal();
      break;

    case 'newsroom_agenda_block':
      $block['subject'] = NULL;
      $block['content'] = _nexteuropa_newsroom_agenda_block();
      break;
  }
  return $block;
}

/**
 * Gets newsroom agenda block content.
 *
 * @return string
 *   Content.
 */
function _nexteuropa_newsroom_agenda_block() {
  $type = _nexteuropa_nexteuropa_agenda_block_reaction();
  if ($type) {
    $agenda_block = new NewsroomBlockAgenda($type, array(), NEXTEUROPA_NEWSROOM_TOPIC_OPERATOR_OR);
    return $agenda_block->generateContent();
  }
  else {
    return NULL;
  }
}

/**
 * Detects agenda block reaction.
 *
 * @return object
 *   Taxonomy term.
 */
function _nexteuropa_nexteuropa_agenda_block_reaction() {
  $type = NULL;
  $active_contexts = context_active_contexts();
  foreach ($active_contexts as $active_context) {
    if (is_array($active_context->reactions) && count($active_context->reactions) > 0) {
      foreach ($active_context->reactions as $reaction_type => $current_reaction) {
        if ($reaction_type == 'newsroom_agenda_block') {
          $social_media_settings = $current_reaction;
          if (isset($current_reaction['type_id'])) {
            $type = NewsroomHelper::getNewsroomType($current_reaction['type_id']);
          }
        }
      }
    }
  }
  return $type;
}

/**
 * Gets summary of the blocks.
 *
 * @return string
 *   Summary block content.
 */
function _nexteuropa_nexteuropa_get_summary_blocks() {
  $summary_block = new NewsroomSummaryBlock();
  return $summary_block->generateContent();
}

/**
 * Gets related content tree.
 *
 * @return string
 *   Content.
 */
function _nexteuropa_nexteuropa_related_content() {
  $node = menu_get_object();
  $content = '';
  if ($node) {
    $children_related_items = _nexteuropa_nexteuropa_get_related_content('field_newsroom_related_content', $node);
    $parent_related_items = _nexteuropa_nexteuropa_get_related_content('field_newsroom_parent_content', $node);
    $brother_items = array();
    $parent_item = NULL;
    if (count($parent_related_items) > 0) {
      $parent_item = $parent_related_items[0];
      $brother_items = _nexteuropa_newsroom_get_related_children('field_newsroom_parent_content', $parent_item->id, $node->nid);
    }

    if ($parent_item || count($brother_items) > 0 || count($children_related_items) > 0) {
      $content = theme('newsroom_related_content', array(
        'parent_item' => $parent_item,
        'current_item' => $node,
        'brother_items' => $brother_items,
        'children_items' => $children_related_items,
      ));
    }
  }
  return $content;
}

/**
 * Tries to resolve each taxonomy term with a corresponding ID to map.
 *
 * @param string $field_name
 *   The mapping field.
 * @param int $parent_nid
 *   The parent node id.
 * @param int $current_nid
 *   The curent node id.
 *
 * @return array
 *   Taxonomy ids.
 */
function _nexteuropa_newsroom_get_related_children($field_name, $parent_nid, $current_nid) {
  // Let's initiate term_ids to field value, in case we can't map it.
  $items = array();
  if ($parent_nid) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
      ->fieldCondition($field_name, 'target_id', $parent_nid)
      ->execute();
    $result = $query->execute();
    if (isset($result['node'])) {
      $ids = array_keys($result['node']);

      foreach ($ids as $id) {
        // We exclude the current item.
        if ($id != $current_nid) {
          $std = new stdClass();
          $std->id = $id;
          $std->title = NewsroomHelper::getNodeTitle($id);
          $items[] = $std;
        }
      }
    }
  }
  return $items;
}

/**
 * Gets related content from node.
 *
 * @param string $field_name
 *   Field name.
 * @param object $node
 *   Current node.
 *
 * @return array
 *   Related nodes.
 */
function _nexteuropa_nexteuropa_get_related_content($field_name, $node) {
  $items = array();
  $node_ids = NewsroomHelper::getFieldValue($node, $field_name, 'target_id');
  if ($node_ids) {
    $node_ids = is_array($node_ids) ? $node_ids : array($node_ids);
    foreach ($node_ids as $nid) {
      $std = new stdClass();
      $std->id = $nid;
      $std->title = NewsroomHelper::getNodeTitle($nid);
      $items[] = $std;
    }
  }
  return $items;
}

/**
 * Returns buttons to manage newsroom items. Edit in newsroom, re-import etc.
 *
 * @return string
 *   Content.
 */
function _nexteuropa_newsroom_tools() {
  $content = '';
  $newsroom_item = menu_get_object();
  if ($newsroom_item->type == NEXTEUROPA_NEWSROOM_CONTENT_TYPE) {
    $newsroom_id_field = field_get_items('node', $newsroom_item, 'field_newsroom_item_id');
    $newsroom_id = $newsroom_id_field[0]['value'];
    $links = array();
    if (user_access(NEXTEUROPA_NEWSROOM_EDIT_ACCESS)) {
      $links['edit'] = array(
        'text' => '<span class="glyphicon glyphicon-edit"></span> Edit item in the Newsroom',
        'path' => NewsroomHelper::getNewsroomUrl(variable_get('newsroom_single_item_edit_segment', NEXTEUROPA_NEWSROOM_ITEM_EDIT_SEGMENT) . $newsroom_id),
        'options' => array(
          'external' => TRUE,
          'html' => TRUE,
          'attributes' => array('class' => 'btn btn-success'),
        ),
      );
    }
    if (user_access(NEXTEUROPA_NEWSROOM_IMPORT_ACCESS)) {
      $links['reimport'] = array(
        'text' => '<span class="glyphicon glyphicon-refresh"></span> Re-import from the Newsroom',
        'path' => 'newsroom-import/item/' . $newsroom_id,
        'options' => array(
          'html' => TRUE,
          'attributes' => array('class' => 'btn btn-danger'),
        ),
      );
    }

    foreach ($links as $link) {
      $content .= '<div class="btn-group-sm btn-group">' . l($link['text'], $link['path'], $link['options']) . '</div>';
    }

    if (!empty($content)) {
      $content = '<div class="btn-toolbar">' . $content . '</div>';
    }
  }
  return $content;
}

/**
 * Newsletter subscription block.
 *
 * @return array
 *   Form array.
 */
function _nexteuropa_newsroom_newsletter_subscription() {
  $content = array();
  $view = views_get_view('newsletter_subscription');

  if ($view) {
    $view->set_display('block');
    $view->pre_execute();
    $view->execute();
    if (!empty($view->result)) {
      $service = array_shift($view->result);
      $content = drupal_get_form('nexteuropa_newsroom_newsletter_subscription_form', array(
        'tid' => $service->field_field_newsroom_service_id[0]['raw']['safe_value'],
        'name' => $service->taxonomy_term_data_name,
      ));
    }
  }

  return $content;
}

/**
 * Returns block with the link to newsroom proposal form.
 *
 * @return string
 *   Block content.
 */
function _nexteuropa_newsroom_block_news_proposal() {

  if (!user_access(NEXTEUROPA_NEWSROOM_PROPOSAL_ACCESS)) {
    return NULL;
  }

  $topic_id = NULL;
  $output = NULL;
  // Try to get Topic ID from the entity.
  $node = menu_get_object();

  if ($node) {
    // First try to get topic from the current node.
    if ($associated_topic_id = NewsroomHelper::getFieldValue($node, 'field_newsroom_associated_topic', 'tid')) {
      $topic_id = $associated_topic_id;
    }
    else {
      // Try get topic from Organic group, if it exists.
      if ($group_id = NewsroomHelper::getFieldValue($node, 'og_group_ref', 'target_id')) {
        $group_id = is_array($group_id) ? $group_id[0] : $group_id;
        $group = node_load($group_id);

        if ($group_associated_topic_id = NewsroomHelper::getFieldValue($group, 'field_newsroom_associated_topic', 'tid')) {
          $topic_id = $group_associated_topic_id;
        }
      }
    }
  }
  else {
    // Taxonomy term override.
    $taxonomy_term = NULL;
    $current_page_path = current_path();

    if (strpos($current_page_path, 'taxonomy/term') !== FALSE) {
      // Never sure what menu_callback will get you with.
      // A view overridding a taxo page.
      $url_tokens = explode('/', $current_page_path);
      if (isset($url_tokens[2]) && is_numeric($url_tokens[2])) {
        $taxonomy_term = taxonomy_term_load($url_tokens[2]);
        // First try to get topic from the current taxonomy term.
        if ($associated_topic_id = NewsroomHelper::getFieldValue($taxonomy_term, 'field_newsroom_associated_topic', 'tid')) {
          $topic_id = $associated_topic_id;
        }
      }
    }
  }

  if (!empty($topic_id)) {
    $output = '<div class="communityTools">';
    $output .= '<div class="RSSButton">' . l(t('Propose newsroom item'), '/news-proposal', array('query' => array('topic_id' => $topic_id))) . '</div>';
    $output .= '</div>';
  }
  return $output;
}
