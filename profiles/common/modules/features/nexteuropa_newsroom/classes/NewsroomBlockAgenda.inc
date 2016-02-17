<?php

/**
 * @file
 * Code for the NewsroomBlockAgenda class.
 */

/**
 * NewsroomBlockAgenda class base class.
 */
class NewsroomBlockAgenda extends NewsroomBlockBase {

  /**
   * NewsroomBlockAgenda constructor.
   */
  public function __construct($type, $topics, $operator) {
    $this->setIsAgenda(TRUE);
    parent::__construct($type, $topics, $operator);
  }

  /**
   * Getter.
   */
  public function getTitle() {
    return t('Agenda');
  }

  /**
   * Generates Agenda block content.
   */
  public function generateContent() {
    $path = md5(current_path());
    $cache_key = 'newsroom:summary_block_agenda:' . $path;
    $cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    if ($cache) {
      $content = $cache->data;
    }
    else {
      $factory = new NewsroomAgendaFactory();
      $agenda = $factory->build(NewsroomAgenda::AGENDA_VIEW_SCHEDULE_BLOCK, $this->getType(), $this->getTopics(), new DateTime(), $this->getOperator());
      $content = theme('newsroom_summary_block', array(
        'content' => $agenda->getBlockAgenda(),
        'css_classes' => $this->getCssClasses(),
        'title' => $this->getTitle(),
        'type_url' => 'agenda',
        'url' => NewsroomHelper::getNewsroomAgendaUrl(NewsroomAgenda::AGENDA_VIEW_SCHEDULE, $this->getTypeUrl(), $this->getTopicUrl()),
      ));
      cache_set($cache_key, $content, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + 3600);
    }
    return $content;
  }

}
