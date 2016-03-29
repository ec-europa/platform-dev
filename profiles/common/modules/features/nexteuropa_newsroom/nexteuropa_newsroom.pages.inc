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
  $factory = new NewsroomAgendaFactory();
  return $factory->buildAgenda($view, $type, $topic, $arg1, $arg2, $arg3)->getAgenda();
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
    $view->set_display($basic_display);
    $view->pre_execute();
    $view->execute();

    $basic_newsletters_title = $view->get_title();
    $basic_newsletters = $view->result;

    $view->destroy();

    $view = views_get_view('newsroom_services');
    $view->set_display($central_display);
    $view->pre_execute();
    $view->execute();

    $central_newsletters_title = $view->get_title();
    $central_newsletters = $view->result;
    $content = theme('newsroom_services_page', array(
      'central_items' => theme('newsroom_services_items',
        array(
          'items' => _nexteuropa_newsroom_prepare_newsletters($central_newsletters),
          'title' => $central_newsletters_title,
          'css_class' => $central_display,
          'universe_id' => $universe_id = NewsroomHelper::getUniverseId(),
        )),
      'basic_items' => theme('newsroom_services_items',
        array(
          'items' => _nexteuropa_newsroom_prepare_newsletters($basic_newsletters),
          'title' => $basic_newsletters_title,
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
 * Prepare newsletters for presentation.
 *
 * @param array $newsletters
 *   Items from view.
 *
 * @return array
 *   Newsletter items prepared for output.
 */
function _nexteuropa_newsroom_prepare_newsletters($newsletters) {
  $output = array();
  foreach ($newsletters as $newsletter) {
    $item = new stdClass();
    $item->title = $newsletter->taxonomy_term_data_name;
    $item->description = $newsletter->taxonomy_term_data_description;
    $item->service_id = isset($newsletter->field_field_newsroom_service_id[0]) ? $newsletter->field_field_newsroom_service_id[0]['raw']['value'] : NULL;
    $item->image = isset($newsletter->field_field_newsroom_service_image[0]) ? drupal_render($newsletter->field_field_newsroom_service_image[0]['rendered']) : NULL;
    $item->form = NULL;
    if (!empty($item->service_id)) {
      $form = drupal_get_form('nexteuropa_newsroom_newsletter_form', $item->service_id);
      $item->form = drupal_render($form);
    }
    $output[] = $item;
  }
  return $output;
}
