<?php
/**
 * @file
 * Code for the NewsroomBuilder class.
 */

/**
 * NewsroomBuilder class.
 */
class NewsroomBuilder {

  /**
   * Builds agenda base on url params.
   *
   * @param string $view
   *   View (presentation type): schedule, month, week, day.
   * @param string $type_name
   *   Type url name.
   * @param string $topic_name
   *   Topic url name.
   * @param string $arg1
   *   Date param.
   * @param string $arg2
   *   Date param.
   * @param string $arg3
   *   Date param.
   *
   * @return object
   *   Agenda item.
   */
  public function buildPageAgenda($view = NewsroomAgenda::AGENDA_VIEW_SCHEDULE, $type_name = 'all', $topic_name = 'all', $arg1 = NULL, $arg2 = NULL, $arg3 = NULL) {
    $agenda = NULL;
    $current_date = new DateTime();
    $type = $this->getType($type_name);
    $topic = $this->getTopic($topic_name);
    switch ($view) {
      case NewsroomAgenda::AGENDA_VIEW_MONTH:
        $month = $this->getMonth($arg1);
        $year = $this->getYear($arg2);
        $current_date->setDate($year, $month, 1);

        $agenda = new NewsroomAgendaMonth($type, $topic, $current_date);
        break;

      case NewsroomAgenda::AGENDA_VIEW_WEEK:
        $week = $this->getWeek($arg1);
        $year = $this->getYear($arg2);
        $current_date->setISODate($year, $week);

        $agenda = new NewsroomAgendaWeek($type, $topic, $current_date);
        break;

      case NewsroomAgenda::AGENDA_VIEW_DAY:
        $day = $this->getDay($arg1);
        $month = $this->getMonth($arg2);
        $year = $this->getYear($arg3);
        $current_date->setDate($year, $month, $day);

        $agenda = new NewsroomAgendaDay($type, $topic, $current_date);
        break;

      default:
        $day = $this->getDay($arg1);
        $month = $this->getMonth($arg2);
        $year = $this->getYear($arg3);

        $current_date->setDate($year, $month, $day);
        $agenda = new NewsroomAgendaSchedule($type, $topic, $current_date);

    }

    return $agenda;
  }

  /**
   * Builds Agenda item based on the current date.
   *
   * @param string $view
   *   View (presentation type): schedule, month, week, day.
   * @param string $type
   *   Newsroom type.
   * @param array $topics
   *   Newsroom topic.
   * @param object $date
   *   Current date.
   *
   * @return object
   *   Agenda item.
   */
  public function buildAgenda($view, $type, $topics, $date, $operator = NEXTEUROPA_NEWSROOM_TOPIC_OPERATOR_OR) {
    $agenda = NULL;
    switch ($view) {
      case NewsroomAgenda::AGENDA_VIEW_MONTH:
        $agenda = new NewsroomAgendaMonth($type, $topics, $date);
        break;

      case NewsroomAgenda::AGENDA_VIEW_WEEK:
        $agenda = new NewsroomAgendaWeek($type, $topics, $date);
        break;

      case NewsroomAgenda::AGENDA_VIEW_DAY:
        $agenda = new NewsroomAgendaDay($type, $topics, $date);
        break;

      case NewsroomAgenda::AGENDA_VIEW_SCHEDULE_BLOCK:
        $agenda = new NewsroomAgendaBlockSchedule($type, $topics, $date, $operator);
        break;

      default:
        $agenda = new NewsroomAgendaSchedule($type, $topics, $date);

    }

    return $agenda;
  }

  /**
   * Validates and returns day number.
   *
   * @param string $value
   *   Day number.
   *
   * @return int
   *   Day number.
   */
  protected function getDay($value) {
    return preg_match('/^\d{1,2}$/', $value) ? (int) $value : NewsroomHelper::getFormatedDate('d');
  }

  /**
   * Validates and returns week number.
   *
   * @param string $value
   *   Day number.
   *
   * @return int
   *   Week number.
   */
  protected function getWeek($value) {
    return preg_match('/^\d{1,2}$/', $value) ? (int) $value : NewsroomHelper::getFormatedDate('W');
  }

  /**
   * Validates and returns month number.
   *
   * @param string $value
   *   Month number.
   *
   * @return int
   *   Month number.
   */
  protected function getMonth($value) {
    return preg_match('/^\d{1,2}$/', $value) ? (int) $value : NewsroomHelper::getFormatedDate('n');
  }

  /**
   * Validates and returns year number.
   *
   * @param string $value
   *   Year number.
   *
   * @return int
   *   Year number.
   */
  protected function getYear($value) {
    return preg_match('/^\d{4}$/', $value) ? (int) $value : NewsroomHelper::getFormatedDate('Y');
  }

  /**
   * Gets taxonomy term topic from url name.
   *
   * @param string $topic
   *   Topic taxonomy term name.
   *
   * @return object
   *   Taxonomy term object.
   */
  protected function getTopic($topic) {
    return $this->getTaxonomyTerm($topic, 'newsroom_topic');
  }

  /**
   * Validates date.
   *
   * @param string $value
   *   Date string.
   *
   * @return string|null
   *   Date string.
   */
  protected function getDate($value) {
    return preg_match('/^\d{2}-d{2}-d{4}$/', $value) ? (int) $value : NULL;
  }

  /**
   * Gets taxonomy term type from url name.
   *
   * @param string $type
   *   Type taxonomy term name.
   *
   * @return object
   *   Taxonomy term object.
   */
  protected function getType($type) {
    return $this->getTaxonomyTerm($type, 'newsroom_item_type');
  }

  /**
   * Gets taxonomy term from url name.
   *
   * @param string $value
   *   Taxonomy term url name.
   * @param string $vocabulary
   *   Vocabulary name.
   *
   * @return object
   *   Taxonomy term object.
   */
  protected function getTaxonomyTerm($value, $vocabulary) {
    return $value == 'all' ? NULL : NewsroomHelper::getTermFromRequest($value, array($vocabulary));
  }
  
  public function buildNewsroomPage($type_url, $topic_url, $start_date = NULL, $end_date = NULL) {
    $type = $this->getType($type_url);
    $topic = $this->getType($topic_url);
    $start_date = $this->getDate($start_date);
    $end_date = $this->getDate($end_date);
    $page = new NewsroomPage($type, $topic, $start_date, $end_date);
    return $page;
  }

}
