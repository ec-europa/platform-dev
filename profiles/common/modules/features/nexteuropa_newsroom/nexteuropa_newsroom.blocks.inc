<?php

/**
 * @file
 * To change this license header, choose License Headers in Project Properties.
 *
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Implements hook_block_info().
 */
function nexteuropa_newsroom_block_info() {
  $blocks = array();
  $blocks['newsroom_summary_blocks'] = array(
    'info' => t('Newsroom Summary Blocks'),
  );
  $blocks['newsroom_related_content'] = array(
    'info' => t('Newsroom Related Content'),
  );
  $blocks['newsroom_topic_summary'] = array(
    'info' => t('Newsroom Topic Summary'),
  );
  $blocks['newsroom_admin_tools'] = array(
    'info' => t('Newsroom administration buttons'),
  );
  $blocks['newsroom_newsletter_subscription'] = array(
    'info' => t('Newsroom Newsletter Subscription'),
  );
  $blocks['newsroom_list_filter'] = array(
    'info' => t('Newsroom List Filter'),
  );
  $blocks['newsroom_proposal'] = array(
    'info' => t('News proposal'),
  );
  $blocks['newsroom_agenda_block'] = array(
    'info' => t('Newsroom agenda block'),
  );
  return $blocks;
}

/**
 * Implements hook_block_view().
 */
function nexteuropa_newsroom_block_view($delta = '') {
  switch ($delta) {
    case 'newsroom_summary_blocks':
      $block['subject'] = _nexteuropa_newsroom_subject();
      $block['content'] = _nexteuropa_nexteuropa_get_summary_blocks();
      break;

    case 'newsroom_related_content':
      $block['subject'] = t('Related content');
      $block['content'] = _nexteuropa_nexteuropa_related_content();
      break;

    case 'newsroom_topic_summary':
      $block['subject'] = _nexteuropa_newsroom_subject();
      $block['content'] = _nexteuropa_nexteuropa_newsroom_contents();
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
  module_load_include('inc', 'nexteuropa_newsroom', 'classes/NewsroomAgendaFactory');
  module_load_include('inc', 'nexteuropa_newsroom', 'classes/NewsroomBlockBase');
  module_load_include('inc', 'nexteuropa_newsroom', 'classes/NewsroomBlockAgenda');
  module_load_include('inc', 'nexteuropa_newsroom', 'classes/NewsroomAgendaBlockSchedule');

  $type = _nexteuropa_nexteuropa_agenda_block_reaction();
  $agenda_block = new NewsroomBlockAgenda($type, array());
  return $agenda_block->generateContent();
}

/**
 * Implements hook_detect_social_media_reaction().
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
            $type = taxonomy_term_load($current_reaction['type_id']);
          }
        }
      }
    }
  }
  return $type;
}

/**
 * Helper function to get summary of the blocks.
 */
function _nexteuropa_nexteuropa_get_summary_blocks() {
  module_load_include('inc', 'nexteuropa_newsroom', 'classes/NewsroomAgendaFactory');
  module_load_include('inc', 'nexteuropa_newsroom', 'classes/NewsroomBlockBase');
  module_load_include('inc', 'nexteuropa_newsroom', 'classes/NewsroomSummaryBlock');
  module_load_include('inc', 'nexteuropa_newsroom', 'classes/NewsroomBlock');
  module_load_include('inc', 'nexteuropa_newsroom', 'classes/NewsroomBlockAgenda');
  module_load_include('inc', 'nexteuropa_newsroom', 'classes/NewsroomAgendaBlockSchedule');

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
    $children_related_items = _nexteuropa_nexteuropa_get_related_content('field_related_content', $node);
    $parent_related_items = _nexteuropa_nexteuropa_get_related_content('field_newsroom_parent_content', $node);
    $parent_nid = count($parent_related_items) > 0 ? key($parent_related_items) : NULL;
    if ($parent_related_items || $children_related_items) {
      $content = theme('newsroom_related_content', array(
        'parent_items' => $parent_related_items,
        'current_item' => $node,
        'brother_items' => _nexteuropa_newsroom_get_related_children('field_newsroom_parent_content', $parent_nid),
        'children_items' => $children_related_items,
      ));
    }
  }
  return $content;
}

/**
 * Try to resolve each taxonomy term with a corresponding ID to map.
 *
 * @param string $field_name
 *   The mapping field.
 * @param string $nid
 *   The node id.
 *
 * @return array
 *   Taxonomy ids.
 */
function _nexteuropa_newsroom_get_related_children($field_name, $nid) {
  // Let's initiate term_ids to field value, in case we can't map it.
  $items = array();
  if ($nid) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
        ->fieldCondition($field_name, 'target_id', $nid)
        ->execute();
    $result = $query->execute();
    if (isset($result['node'])) {
      $ids = array_keys($result['node']);

      foreach ($ids as $id) {
        $items[$id] = _nexteuropa_newsroom_get_node_title($id);
      }
    }
  }
  return $items;
}

/**
 * Get related content from node.
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
      $items[$item['target_id']] = isset($item['entity']) ? $item['entity']->title : _nexteuropa_newsroom_get_node_title($item['target_id']);
    }
  }
  return $items;
}

/**
 * Helper function to get the node title without loading the whole node object.
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
    cache_set($cache_key, $node_title, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + 3600);
  }
  return $node_title;
}

/**
 * Returns the Newsroom title and link depending by taxonomy terms.
 *
 * @return string
 *   Subject.
 */
function _nexteuropa_newsroom_subject() {
  return l(t('Newsroom'), NewsroomHelper::getNewsroomUrl('all'));
}

/**
 * Returns a block content.
 *
 * Loops through newsroom type at top level and display the corresponding
 * content and link for each newsroom type.
 *
 * @return string
 *   Content.
 */
function _nexteuropa_nexteuropa_newsroom_contents() {
  $block_settings = _nexteuropa_newsroom_get_summary_block_tid();

  $topic_tids = array();
  $topic_name = array();
  // Sticky items (Centrally published).
  $sticky = TRUE;
  if (!drupal_is_front_page()) {
    if (!$block_settings['display']) {
      return '';
    }
    $sticky = FALSE;
    if (!empty($block_settings['topic'])) {
      foreach ($block_settings['topic'] as $topic) {
        $topic_tids[] = $topic->tid;
        $topic_name[] = $topic->name;
      }
    }
  }

  $newsroom_content = _nexteuropa_newsroom_content($block_settings['type'], FALSE, implode('+', $topic_tids), $sticky, $block_settings['topic'], $block_settings['topic_operator']);

  // Prepend RSS link if there is content.
  if (!empty($newsroom_content)) {
    $newsroom_content = _nexteuropa_newsroom_build_rss_link($topic_tids, $topic_name) . $newsroom_content;
  }

  return $newsroom_content;
}

/**
 * Returns block content.
 *
 * Buttons to easily manage newsroom items. Edit in newsroom, re-import etc.
 *
 * @return string
 *   Content
 */
function _nexteuropa_newsroom_tools() {
  $content = '';
  $newsroom_item = menu_get_object();
  if ($newsroom_item->type == 'newsroom_item') {
    $newsroom_id_field = field_get_items('node', $newsroom_item, 'field_newsroom_item_id');
    $newsroom_id = $newsroom_id_field[0]['value'];
    $links = array();
    if (user_access(NEXTEUROPA_NEWSROOM_EDIT_ACCESS)) {
      global $_newsroom_universe_url;
      $links['edit'] = array(
        'text' => '<span class="glyphicon glyphicon-edit"></span> Edit item in the Newsroom',
        'path' => $_newsroom_universe_url . variable_get('newsroom_single_item_edit_segment', 'item.cfm?item_id=') . $newsroom_id,
        'options' => array(
          'html' => TRUE,
          'attributes' => array('class' => 'btn btn-success'),
        ),
      );
    }
    if (user_access(NEXTEUROPA_NEWSROOM_IMPORT_ACCESS)) {
      $links['reimport'] = array(
        'text' => '<span class="glyphicon glyphicon-refresh"></span> Re-import from the Newsroom',
        'path' => 'news-import/' . $newsroom_id . '/reimport',
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
 * Builds rss link.
 *
 * @param array $topic_tids
 *   Topics ids.
 * @param string $topic_name
 *   Topic name.
 *
 * @return string
 *   RSS.
 */
function _nexteuropa_newsroom_build_rss_link(array $topic_tids, $topic_name) {
  $topic_url = count($topic_tids) > 0 ? implode('+', $topic_tids) : 'all';
  $rss_path = NewsroomHelper::getNewsroomUrl('all', $topic_url, 'feed');
  $rss_title = count($topic_name) > 0 ? 'RSS feed : ' . implode(', ', $topic_name) : 'RSS feed';
  $rss = '<div class="newsroom_rss">';
  $rss .= theme('feed_icon', array(
    'url' => $rss_path,
    'title' => $rss_title,
  ));
  $rss .= l($rss_title, $rss_path);
  $rss .= '</div>';

  return $rss;
}

/**
 * Returns the newsroom list filter form.
 */
function _nexteuropa_newsroom_list_filter() {
  $topics_vocanulary = taxonomy_vocabulary_machine_name_load(NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY);

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
    $query->condition('t.vid', $topics_vocanulary->vid);
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
    $field_instance = field_info_instance('node', 'field_newsroom_topics', 'newsroom_item');
    $field = field_info_field('field_newsroom_topics');
    $temp = new stdClass();
    $temp->type = 'newsroom_item';
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

  return '';
}

/**
 * Converts an option array from tid based to name based.
 *
 * @return array
 *   List of options.
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
 * @global object $user
 *   Global user object.
 * @global string $base_url
 *   Global URL.
 *
 * @return string
 *   Block content.
 */
function _nexteuropa_newsroom_block_news_proposal() {

  if (!user_access(NEXTEUROPA_NEWSROOM_PROPOSAL_ACCESS)) {
    return NULL;
  }

  global $base_url;

  $topic_id = NULL;

  // Try to get Topic ID from the entity.
  $node = menu_get_object();

  if ($node) {
    if (isset($node->field_associated_newsroom_topic[LANGUAGE_NONE][0]['tid']) && !empty($node->field_associated_newsroom_topic[LANGUAGE_NONE][0]['tid'])) {
      $topic_id = $node->field_associated_newsroom_topic[LANGUAGE_NONE][0]['tid'];
    }
    elseif (isset($node->og_group_ref[LANGUAGE_NONE][0]['target_id']) && !empty($node->og_group_ref[LANGUAGE_NONE][0]['target_id'])) {
      $group = node_load($node->og_group_ref[LANGUAGE_NONE][0]['target_id']);
      if (isset($group->field_associated_newsroom_topic[LANGUAGE_NONE][0]['tid']) && !empty($group->field_associated_newsroom_topic[LANGUAGE_NONE][0]['tid'])) {
        $topic_id = $group->field_associated_newsroom_topic[LANGUAGE_NONE][0]['tid'];
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

        if (isset($taxonomy_term->field_associated_newsroom_topic[LANGUAGE_NONE][0]['tid']) && !empty($taxonomy_term->field_associated_newsroom_topic[LANGUAGE_NONE][0]['tid'])) {
          $topic_id = $taxonomy_term->field_associated_newsroom_topic[LANGUAGE_NONE][0]['tid'];
        }
      }
    }
  }

  $output = '<div class="communityTools">';
  $output .= '<div class="RSSButton"><a href="' . $base_url . '/news-proposal/?topic_id=' . $topic_id . '">' . t('Propose newsroom item') . '</a></div>';
  $output .= '</div>';

  return $output;
}

/**
 * Calculates the tid to use to filter the newsroom_topic_summary block content.
 *
 * @return array
 *   NR Topic tid
 */
function _nexteuropa_newsroom_get_summary_block_tid() {

  $current_path = menu_get_item();
  $topic_operator = NEXTEUROPA_NEWSROOM_TOPIC_OPERATOR_OR;
  $selected_topics = array();
  $selected_types = array();
  $config['display'] = FALSE;
  $newsroom_selection_node = FALSE;

  // We are on a view object, it's a term argument,
  // let's use to filter results.
  if ($current_path['page_callback'] === 'views_page' && $current_path['path'] === 'taxonomy/term/%') {
    $argument_values = array_values($current_path['page_arguments']);
    $last_argument_element = end($argument_values);
    // We may have a term page, let's try to load it.
    if (is_numeric($last_argument_element)) {
      $entity = taxonomy_term_load($last_argument_element);
      $selected_topics[] = $entity->tid;
    }
  }
  elseif ($current_path['page_callback'] === 'node_page_view') {
    // It is a node page take node entity from request.
    $entity = $current_path['map'][1];

    // If newsroom selection type, load same entity as selection.
    $newsroom_selection_node = $entity->type == 'newsroom_selection' ? $entity : FALSE;
  }
  elseif (isset($current_path['page_arguments'][0]->tid)) {
    // It's taxonomy term without views.
    $entity = $current_path['page_arguments'][0];
    $selected_topics[] = $entity->tid;
  }

  // Check if selection config is set.
  if (isset($entity->field_associated_newsroom_select) && !empty($entity->field_associated_newsroom_select)) {
    // If it has the selection field, try to load config.
    $newsroom_selection_node = node_load($entity->field_associated_newsroom_select['und'][0]['target_id']);
  }

  if ($newsroom_selection_node) {

    if (!empty($newsroom_selection_node->field_newsroom_topic_operator)) {
      $topic_operator = $newsroom_selection_node->field_newsroom_topic_operator['und'][0]['value'];
    }

    $topic_config = field_get_items('node', $newsroom_selection_node, 'field_selected_topics');
    $selected_topics = array();
    if ($topic_config) {
      foreach ($topic_config as $term_ref) {
        $selected_topics[] = $term_ref['target_id'];
      }
    }

    $type_config = field_get_items('node', $newsroom_selection_node, 'field_selected_types');
    if ($type_config) {
      foreach ($type_config as $term_ref) {
        $selected_types[] = $term_ref['tid'];
      }
    }
    $config['display'] = TRUE;
  }
  elseif (isset($entity->field_associated_newsroom_topic) && !empty($entity->field_associated_newsroom_topic)) {
    // If it has the associated field, try to load topic.
    $selected_topics = array($entity->field_associated_newsroom_topic['und'][0]['tid']);
    $config['display'] = TRUE;
  }

  $config['topic'] = count($selected_topics) > 0 ? taxonomy_term_load_multiple($selected_topics) : array();
  $config['topic_operator'] = $topic_operator;
  $config['type'] = NewsroomHelper::getGroupTypeTerms($selected_types);

  return $config;
}

/**
 * Call to the content view, set up the argument vocabulary by vocabulary.
 *
 * @param array $newsroom_grouping_terms
 *   Newroom type terms.
 * @param bool $full_display
 *   Show full display.
 * @param int $newsroom_topic_tids
 *   Main tid.
 * @param bool $sticky
 *   Centrally published.
 *
 * @return string
 *   Content.
 */
function _nexteuropa_newsroom_content(array $newsroom_grouping_terms, $full_display = FALSE, $newsroom_topic_tids = 'all', $sticky = NULL, $topics = array(), $topic_operator = NEXTEUROPA_NEWSROOM_TOPIC_OPERATOR_OR) {
  $newsroom_boxes = array();

  // We skip the newsroom topic param if it is empty string.
  if (!empty($newsroom_topic_tids)) {
    $view_arguments[1] = $newsroom_topic_tids;
  }

  // Custom Agenda block if needed.
  if (variable_get('newsroom_display_agenda', 1) && $agenda_types = NewsroomHelper::getEventsTermsIds()) {
    $view_arguments[0] = implode('+', $agenda_types);
    $agenda_box = _nexteuropa_newsroom_fetch_content_view($view_arguments, NEXTEUROPA_NEWSROOM_CALENDAR_BLOCK, 'agenda', $sticky, $full_display, $topic_operator);

    if ($agenda_box && $agenda_box['block']['content'] != '') {
      $full_list_url = NewsroomHelper::getNewsroomUrl('calendar');
      $newsroom_boxes[] = array_merge($agenda_box, array(
        'title' => l(t('Calendar'), $full_list_url),
        'list_link' => l(t('<span class="more">%1</span>', array('%1' => t('More ongoing activities'))), $full_list_url, array('html' => TRUE)),
        'classes' => array('agenda', 'highlighted'),
        'id' => 'newsroom-agenda-block',
        'highlight' => TRUE,
        'agenda' => TRUE,
        'weight' => '0',
      ));
    }
  }

  if (count($newsroom_grouping_terms) > 0) {
    foreach ($newsroom_grouping_terms as $newsroom_grouping_term) {
      $default_view_display = 'default_newsroom';
      $classes = array('term-' . $newsroom_grouping_term->tid);
      $newsroom_block_id = '';
      $view_arguments[0] = implode('+', NewsroomHelper::getTermChildren($newsroom_grouping_term->tid, $newsroom_grouping_term->vid));
      $newsroom_type_display = field_get_items('taxonomy_term', $newsroom_grouping_term, 'field_newsroom_type');

      // Some newsroom type are not using the normal sorting.
      // This is machine-name defined by newsroom type.
      if ($newsroom_type_display) {
        switch ($newsroom_type_display[0]['value']) {
          case 'events':
            $default_view_display = 'events';
            break;

          case 'agenda':
            $default_view_display = 'agenda';
            break;

          case 'consultation_funding':
            $default_view_display = 'consultation_funding';
            break;
        }
      }

      $newsroom_view_exec = _nexteuropa_newsroom_fetch_content_view($view_arguments, $newsroom_grouping_term, $default_view_display, $sticky, $full_display, $topic_operator);

      // If we have some content, let's add a title.
      if ($newsroom_view_exec && $newsroom_view_exec['block']['content'] != '') {

        $topic_is_highlighted = _nexteuropa_newsroom_type_is_highlighted($newsroom_grouping_term);

        if ($topic_is_highlighted) {
          // Controls width.
          $classes[] = 'featured';
          // Controls border.
          $classes[] = 'highlighted';
        }

        $clean_url_type_name = pathauto_cleanstring($newsroom_grouping_term->name);
        $newsroom_block_id = 'newsroom-block-' . $clean_url_type_name;
        if (count($topics) == 1) {
          $topics_segment = pathauto_cleanstring($topics[key($topics)]->name);
        }
        else {
          $topics_segment = $newsroom_topic_tids;
        }

        $full_list_url = NewsroomHelper::getNewsroomUrl($clean_url_type_name, $topics_segment);

        // Check latest item in box.
        $created = 0;

        foreach ($newsroom_view_exec['view']->result as $row) {
          $created = $row->node_created > $created ? $row->node_created : $created;
        }

        $newsroom_boxes[] = array_merge($newsroom_view_exec, array(
          'title' => l($newsroom_grouping_term->name, $full_list_url),
          'list_link' => l(t('<span class="more">More</span> <span class="more_type">%1</span>', array('%1' => $newsroom_grouping_term->name)), $full_list_url, array('html' => TRUE)),
          'classes' => $classes,
          'id' => $newsroom_block_id,
          'highlight' => $topic_is_highlighted,
          'agenda' => FALSE,
          'last_update' => $created,
          'weight' => $newsroom_grouping_term->weight,
        ));
      }
    }
  }

  return !empty($newsroom_boxes) ? _nexteuropa_newsroom_render_boxes($newsroom_boxes) : '';
}

/**
 * Render the boxes for the block.
 *
 * @return string
 *   markup
 */
function _nexteuropa_newsroom_render_boxes($boxes) {
  $newsroom_content = '';
  $columns_newsroom = array(
    1 => array(
      'visible' => FALSE,
      'content' => '',
    ),
    2 => array(
      'visible' => FALSE,
      'content' => '',
    ),
  );
  $num_columns = variable_get('newsroom_summary_block_columns', 1);

  // Sort boxes based on configuration.
  uasort($boxes, '_nexteuropa_newsroom_sort_newsroom_boxes');

  $newsroom_row_number = 1;
  foreach ($boxes as $box) {
    $active_column = 1;
    $box['classes'][] = 'newsroom_item_container';
    // Get active column.
    if ($num_columns == 2 && $newsroom_row_number % 2 == 0) {
      $active_column = 2;
    }

    $columns_newsroom[$active_column]['visible'] = TRUE;
    $columns_newsroom[$active_column]['content'] .= '<div id="' . $box['id'] . '" class="' . implode(' ', $box['classes']) . '">'; /* add "highlighted" classname to display that block as highlighted (ie press releases, speeches) */
    $columns_newsroom[$active_column]['content'] .= '<a name="' . $box['id'] . '"></a>';
    $columns_newsroom[$active_column]['content'] .= '<h3 class="newsroom_title">' . $box['title'] . '</h3>';
    $columns_newsroom[$active_column]['content'] .= $box['block']['content'];
    $columns_newsroom[$active_column]['content'] .= '<div class="newsroom_more">' . $box['list_link'] . '</div>';
    $columns_newsroom[$active_column]['content'] .= "</div>";

    $newsroom_row_number++;
  }

  // 2 columns so display both.
  if ($columns_newsroom[2]['visible'] === TRUE) {
    $newsroom_content .= '<div class="nr_column_1 nr_column">' . $columns_newsroom[1]['content'] . '</div>';
    $newsroom_content .= '<div class="nr_column_2 nr_column">' . $columns_newsroom[2]['content'] . '</div>';
  }
  // 1 column only.
  else {
    $newsroom_content .= '<div class="nr_column_single">' . $columns_newsroom[1]['content'] . '</div>';
  }
  return $newsroom_content;
}

/**
 * Sort newsroom boxes.
 *
 * @param array $a
 *   Newsroom box.
 * @param array $b
 *   Newsroom box.
 *
 * @return bool
 *   Value.
 */
function _nexteuropa_newsroom_sort_newsroom_boxes(array $a, array $b) {
  // Highligths at begining or end - based on setting.
  if ($a['highlight'] !== $b['highlight']) {
    return variable_get('newsroom_display_highlights_begin', 0) ? $a['highlight'] == FALSE : $a['highlight'] == TRUE;
  }
  // Sort Agenda before or after highlighted  - based on setting.
  if ($a['highlight'] && ($a['agenda'] !== $b['agenda'])) {
    return variable_get('newsroom_agenda_after_highlights', 0) ? $a['agenda'] == TRUE : $a['agenda'] == FALSE;
  }
  // Sort based on last update  - based on setting.
  if (variable_get('newsroom_order_by_last_update', 0)) {
    return $a['last_update'] < $b['last_update'];
  }
  else {
    return $a['weight'] > $b['weight'];
  }
}

/**
 * Helper to check if topic is highlighted.
 *
 * @return bool
 *   is highlighted or not
 */
function _nexteuropa_newsroom_type_is_highlighted($term) {
  if ($term === NEXTEUROPA_NEWSROOM_CALENDAR_BLOCK) {
    return FALSE;
  }
  $item_wrapper = entity_metadata_wrapper('taxonomy_term', $term);
  return $item_wrapper->__isset('field_newsroom_highlighted') ? $item_wrapper->field_newsroom_highlighted->value() : FALSE;
}

/**
 * Fetch the contents of a newsroom box.
 *
 * @return array
 *   view
 */
function _nexteuropa_newsroom_fetch_content_view($view_arguments, $newsroom_grouping_term_name, $default_view_display, $sticky, $full_display, $topic_operator) {
  $view = views_get_view('newsroom_page_content');
  if (!is_object($view)) {
    return FALSE;
  }

  $view->newsroom_display_type = FALSE;
  $view->newsroom_type_name = $newsroom_grouping_term_name === NEXTEUROPA_NEWSROOM_CALENDAR_BLOCK ? t('Calendar') : $newsroom_grouping_term_name->name;
  $view->set_arguments($view_arguments);
  $view->set_display($default_view_display);
  $view->sticky = $sticky;

  // Use topic operator from newsroom selection for topic context filter.
  $arguments_settings = $view->display[$view->current_display]->handler->get_option('arguments');
  if ($topic_operator != NEXTEUROPA_NEWSROOM_TOPIC_OPERATOR_OR && isset($arguments_settings['newsroom_term_node_tid_depth']['use_and'])) {
    $arguments_settings['newsroom_term_node_tid_depth']['use_and'] = 1;
    $view->display[$view->current_display]->handler->set_option('arguments', $arguments_settings);
  }

  $pager = $view->display_handler->get_option('pager');
  if ($full_display == TRUE) {
    $pager['type'] = 'full';
    $pager['options']['items_per_page'] = '15';
    $pager['options']['offset'] = '0';
    $pager['options']['id'] = '0';
  }
  elseif ($default_view_display !== 'agenda') {
    // Customizeable item number for non agenda displays.
    $variable_name = '';
    // Number of items per block.
    if (_nexteuropa_newsroom_type_is_highlighted($newsroom_grouping_term_name)) {
      // Highlighted type, home | not home.
      $variable_name = $sticky ? 'newsroom_summary_home_block_num_highlighted_items' : 'newsroom_summary_block_num_highlighted_items';
    }
    else {
      // Not highlighted type, home | not home.
      $variable_name = $sticky ? 'newsroom_summary_home_block_num_items' : 'newsroom_summary_block_num_items';
    }

    $pager['options']['items_per_page'] = variable_get($variable_name, 3);
  }

  $view->display_handler->set_option('pager', $pager);
  $view->execute_display($default_view_display);

  return array('block' => $view->execute_display($default_view_display), 'view' => $view);
}
