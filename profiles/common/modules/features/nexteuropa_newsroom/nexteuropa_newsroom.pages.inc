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
function _nexteuropa_newsroom_agenda($view = 'schedule', $type = NULL, $topic = NULL, $arg1 = NULL, $arg2 = NULL, $arg3 = NULL) {
  module_load_include('inc', 'nexteuropa_newsroom', 'classes/NewsroomAgendaFactory');

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
          'items' => $central_newsletters,
          'title' => $central_newsletters_title,
          'css_class' => $central_display,
        )),
      'basic_items' => theme('newsroom_services_items',
        array(
          'items' => $basic_newsletters,
          'title' => $basic_newsletters_title,
          'css_class' => $basic_display,
        )),
      'privacy_text' => variable_get('newsroom_newsletter_privacy', NULL),
    ));
    $build['#markup'] = $content;
  }

  return $build;
}
