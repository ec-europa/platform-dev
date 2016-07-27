<?php

/**
 * @file
 * Pages content for menu callbacks.
 */

/**
 * Agenda menu callback.
 *
 * @param string $view
 *   View: schedule, month, week, day.
 * @param string $type
 *   Type name.
 * @param string $topic
 *   Topic name.
 * @param string $arg1
 *   Date param.
 * @param string $arg2
 *   Date param.
 * @param string $arg3
 *   Date param.
 *
 * @return string
 *   Agenda content,
 */
function _nexteuropa_newsroom_agenda($view = NewsroomAgenda::AGENDA_VIEW_SCHEDULE, $type = NULL, $topic = NULL, $arg1 = NULL, $arg2 = NULL, $arg3 = NULL) {
  $builder = new NewsroomBuilder();
  return $builder->buildPageAgenda($view, $type, $topic, $arg1, $arg2, $arg3)->getAgenda();
}

/**
 * Newsroom page menu callback.
 *
 * @param string $type_url
 *   Type url part.
 * @param string $topic_url
 *   Topic url part.
 * @param string $start_date
 *   Start date.
 * @param string $end_date
 *   End date.
 */
function _nexteuropa_newsroom_newsroom_page($type_url = NULL, $topic_url = NULL, $start_date = NULL, $end_date = NULL) {
  $builder = new NewsroomBuilder();
  $newsroom_page = $builder->buildPageNewsroomPage($type_url, $topic_url, $start_date, $end_date);
  $output = $newsroom_page->getContent();
  $output .= theme('pager');
  $build['#markup'] = $output;
  return $build;
}

/**
 * Newsroom page menu callback.
 *
 * @param string $type_url
 *   Type url part.
 * @param string $topic_url
 *   Topic url part.
 */
function _nexteuropa_newsroom_newsroom_rss($type_url = NULL, $topic_url = NULL) {
  $builder = new NewsroomBuilder();
  $newsroom_page = $builder->buildPageNewsroomPage($type_url, $topic_url);
  drupal_add_http_header('Content-Type', 'application/rss+xml; charset=utf-8');
  echo $newsroom_page->getRssContent();
  module_invoke_all('exit');
  exit();
}

/**
 * Returns render array for the access newsletters page.
 *
 * @return array
 *   Array of markup.
 */
function _nexteuropa_newsroom_newsletters_page() {
  $view = views_get_view('newsroom_services');
  $build = array();
  $basic_display = 'basic';
  $central_display = 'central';

  if ($view) {
    $subscriptions = _nexteuropa_newsroom_get_user_subscriptions();
    global $user;

    if (user_access(NEXTEUROPA_NEWSROOM_ADVANCED_SETTINGS_ACCESS, $user) && (empty(variable_get('newsroom_subscription_url')) || empty(variable_get('newsroom_app')) || empty(variable_get('newsroom_app_key')))) {
      drupal_set_message(t('Please setup newsroom settings: app, key and subscription URL. !url', array('!url' => l(t('Newsroom settings'), 'admin/config/content/newsroom'))), 'warning');
    }

    $view->set_display($basic_display);
    $view->pre_execute();
    $view->execute();
    $basic_newsletters = $view->result;

    $view->destroy();

    $view = views_get_view('newsroom_services');
    $view->set_display($central_display);
    $view->pre_execute();
    $view->execute();
    $central_newsletters = $view->result;
    $content = theme('newsroom_services_page', array(
      'central_items' => theme('newsroom_services_items',
        array(
          'items' => _nexteuropa_newsroom_prepare_newsletters($central_newsletters, $subscriptions),
          'title' => variable_get('newsroom_central_newsletter_title', t('Central newsletters')),
          'css_class' => $central_display,
          'universe_id' => $universe_id = NewsroomHelper::getUniverseId(),
        )),
      'basic_items' => theme('newsroom_services_items',
        array(
          'items' => _nexteuropa_newsroom_prepare_newsletters($basic_newsletters, $subscriptions),
          'title' => variable_get('newsroom_other_newsletter_title', t('Other newsletters')),
          'css_class' => $basic_display,
          'universe_id' => $universe_id = NewsroomHelper::getUniverseId(),
        )),
      'privacy_text' => variable_get('newsroom_newsletter_privacy', NULL),
    ));
    $build['#markup'] = $content;
    $build['#attached']['js'][] = array(
      'type' => 'setting',
      'data' => array('nexteuropa_newsroom' => array('error_message' => t('Wrong e-mail address'), 'user_is_logged_in' => user_is_logged_in())),
    );
    $build['#attached']['js'][] = array(
      'type' => 'file',
      'data' => drupal_get_path('module', 'nexteuropa_newsroom') . '/js/newsletter_list.js',
    );
  }

  return $build;
}

/**
 * Prepares newsletters for presentation.
 *
 * @param array $newsletters
 *   Items from view.
 * @param array $subscriptions
 *   Current user subscriptions.
 *
 * @return array
 *   Newsletter items prepared for output.
 */
function _nexteuropa_newsroom_prepare_newsletters($newsletters = array(), $subscriptions = array()) {
  $output = array();
  foreach ($newsletters as $newsletter) {
    $item = new stdClass();
    $item->title = $newsletter->taxonomy_term_data_name;
    $item->description = $newsletter->taxonomy_term_data_description;
    $item->service_id = isset($newsletter->field_field_newsroom_service_id[0]) ? $newsletter->field_field_newsroom_service_id[0]['raw']['value'] : NULL;
    $item->image = isset($newsletter->field_field_newsroom_service_image[0]) ? drupal_render($newsletter->field_field_newsroom_service_image[0]['rendered']) : NULL;
    $item->form = NULL;
    if (!empty($item->service_id)) {
      $subscription_url = NULL;
      foreach ($subscriptions as $user_subscription) {
        if ($user_subscription['NEWSLETTERID'] == $item->service_id) {
          $subscription_url = $user_subscription['UNSUBSCRIPTIONLINK'];
          break;
        }
      }
      if ($subscription_url) {
        $form = drupal_get_form('nexteuropa_newsroom_unsubscription_newsletter_form', $subscription_url);
      }
      else {
        $form = drupal_get_form('nexteuropa_newsroom_subscription_newsletter_form', $item->service_id);
      }

      $item->form = drupal_render($form);
    }
    $output[] = $item;
  }
  return $output;
}

/**
 * Returns user subscriptions from the newsroom side.
 *
 * @return array
 *   User subscriptions response.
 */
function _nexteuropa_newsroom_get_user_subscriptions() {
  $subscriptions = array();
  if (user_is_logged_in()) {
    global $user;
    $input = array(
      'user_email' => $user->mail,
      'universe_acronym' => NewsroomHelper::getUniverseId(),
      'app' => variable_get('newsroom_app'),
      'key' => NewsroomHelper::getEmailHash($user->mail),
      'response_type' => 'json',
    );
    $url = variable_get('newsroom_subscription_url');
    if ($url) {
      $request = drupal_http_request($url . '?' . drupal_http_build_query($input));
      if (isset($request->data)) {
        $subscriptions = drupal_json_decode($request->data);
      }
    }
  }

  return $subscriptions;
}
