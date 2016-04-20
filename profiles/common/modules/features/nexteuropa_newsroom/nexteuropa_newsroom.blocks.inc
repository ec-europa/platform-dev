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
  $blocks['newsroom_list_filter'] = array(
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
      $block['subject'] = l(t('Newsroom'), NewsroomHelper::getNewsroomPageUrl('all'));
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

    case 'newsroom_list_filter':
      $block['subject'] = NULL;
      $block['content'] = _nexteuropa_newsroom_list_filter();
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
          $std->title = _nexteuropa_newsroom_get_node_title($id);
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
  $field = isset($node->$field_name) ? $node->$field_name : NULL;
  if ($field && isset($field[LANGUAGE_NONE])) {
    foreach ($field[LANGUAGE_NONE] as $item) {
      $std = new stdClass();
      $std->id = $item['target_id'];
      $std->title = _nexteuropa_newsroom_get_node_title($item['target_id']);
      $items[] = $std;
    }
  }
  return $items;
}

/**
 * Gets the node title without loading the whole node object.
 *
 * @param int $nid
 *   Node nid.
 *
 * @return string
 *   Node title.
 */
function _nexteuropa_newsroom_get_node_title($nid) {
  $cache_key = 'newsroom:node_title:' . $nid;
  $cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
  if ($cache) {
    $node_title = $cache->data;
  }
  else {
    $node_title = db_query('SELECT title_field_value FROM {field_data_title_field} WHERE entity_id = :nid', array(':nid' => $nid))->fetchField();
    if (empty($node_title)) {
      $node_title = db_query('SELECT title FROM {node} WHERE nid = :nid', array(':nid' => $nid))->fetchField();
    }
    cache_set($cache_key, $node_title, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('newsroom_ct_node_title', 3600));
  }
  return $node_title;
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
      $content .= '<div class="btn-group-sm btn-group">' . theme('link', $link) . '</div>';
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
      $content = drupal_get_form('nexteuropa_newsroom_newsletter_subscription_form', array('tid' => $service->field_field_newsroom_service_id[0]['raw']['safe_value'], 'name' => $service->taxonomy_term_data_name));
    }
  }

  return $content;
}

/**
 * Returns the newsroom list filter form.
 *
 * @return array|null
 *   Newsroom page filter form array or NULL.
 */
function _nexteuropa_newsroom_list_filter() {
  $topics_vocabulary = NewsroomHelper::getNewsroomTopicVocabulary();

  // Load all relevant nids by loading the same view without pager.
  $menu_object = menu_get_item();
  if ($menu_object['page_callback'] == 'views_page' && !empty($menu_object['page_arguments']) && $menu_object['page_arguments'][0] == 'newsroom') {
    $nids = array();
    $arguments = $menu_object['theme_arguments'];
    $fields = array(
      'nid' => array(
        'id' => 'nid',
        'table' => 'node',
        'field' => 'nid',
        'label' => '',
        'exlude' => TRUE,
        'element_label_colon' => FALSE,
      ),
    );
    $view = views_get_view('newsroom');
    $view->set_display($menu_object['page_arguments'][1]);
    $view->set_arguments($arguments);
    $view->display[$view->current_display]->handler->set_option('fields', $fields);
    $view->display[$view->current_display]->handler->set_option('pager', array('type' => 'none', 'options' => array()));
    $view->pre_execute();
    $view->execute();

    foreach ($view->result as $node) {
      $nids[] = $node->nid;
    }

    $query = db_select('taxonomy_index', 'ti');
    $query->fields('ti', array('tid'));
    $query->join('taxonomy_term_data', 't', 't.tid = ti.tid');
    $query->fields('t', array('name'));
    $query->join('field_data_field_newsroom_category_domain', 'd', 'd.entity_id = ti.tid');
    $query->fields('d', array('field_newsroom_category_domain_value'));
    $query->condition('t.vid', $topics_vocabulary->vid);
    if (!empty($nids)) {
      $query->condition('ti.nid', $nids);
    }
    $query->condition('d.entity_type', 'taxonomy_term');
    $result = $query->execute();

    $countries = array();
    $topics = array();
    while ($record = $result->fetchAssoc()) {
      if ($record['field_newsroom_category_domain_value'] == 'Country') {
        $countries[$record['tid']] = $record['name'];
      }
      else {
        $topics[$record['tid']] = $record['name'];
      }
    }

    // Load full otpion list based on field_newsroom_topics values.
    $field_instance = field_info_instance('node', 'field_newsroom_topics', NEXTEUROPA_NEWSROOM_CONTENT_TYPE);
    $field = field_info_field('field_newsroom_topics');
    $temp = new stdClass();
    $temp->type = NEXTEUROPA_NEWSROOM_CONTENT_TYPE;
    node_object_prepare($temp);
    $options = taxonomy_options_list($field, $field_instance, 'node', $temp);

    // Reduce options to existing values only.
    $countries = array_intersect_key($options, $countries);
    $topics = array_intersect_key($options, $topics);
    // Change values from tid keys term name based.
    $countries = _nexteuropa_newsroom_options_tid_to_name($countries);
    $topics = _nexteuropa_newsroom_options_tid_to_name($topics);

    // Add - None - option.
    $none = array('0' => t('- None -'));
    $countries = $none + $countries;
    $topics = $none + $topics;

    return drupal_get_form('nexteuropa_newsroom_list_filter_form', $countries, $topics, $arguments);
  }

  return NULL;
}

/**
 * Converts an option array from tid based to name based.
 *
 * @param array $options
 *   Options list.
 *
 * @return array
 *   Normalized option list.
 */
function _nexteuropa_newsroom_options_tid_to_name($options) {
  $options_names = array();
  foreach ($options as $option) {
    $options_names[drupal_strtolower(str_replace(' ', '-', trim($option, ' -')))] = $option;
  }
  return $options_names;
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
    if (isset($node->field_newsroom_associated_topic[LANGUAGE_NONE][0]['tid']) && !empty($node->field_newsroom_associated_topic[LANGUAGE_NONE][0]['tid'])) {
      $topic_id = $node->field_newsroom_associated_topic[LANGUAGE_NONE][0]['tid'];
    }
    elseif (isset($node->og_group_ref[LANGUAGE_NONE][0]['target_id']) && !empty($node->og_group_ref[LANGUAGE_NONE][0]['target_id'])) {
      $group = node_load($node->og_group_ref[LANGUAGE_NONE][0]['target_id']);
      if (isset($group->field_newsroom_associated_topic[LANGUAGE_NONE][0]['tid']) && !empty($group->field_newsroom_associated_topic[LANGUAGE_NONE][0]['tid'])) {
        $topic_id = $group->field_newsroom_associated_topic[LANGUAGE_NONE][0]['tid'];
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

        if (isset($taxonomy_term->field_newsroom_associated_topic[LANGUAGE_NONE][0]['tid']) && !empty($taxonomy_term->field_newsroom_associated_topic[LANGUAGE_NONE][0]['tid'])) {
          $topic_id = $taxonomy_term->field_newsroom_associated_topic[LANGUAGE_NONE][0]['tid'];
        }
      }
    }
  }

  if (!empty($topic_id)) {
    $output = '<div class="communityTools">'; ;
    $output .= '<div class="RSSButton">' . l(t('Propose newsroom item'), '/news-proposal', array('query' => array('topic_id' => $topic_id))) . '</div>';
    $output .= '</div>';
  }
  return $output;
}
