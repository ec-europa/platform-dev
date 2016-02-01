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
  public function __construct($type, $topics) {
    $this->setIsAgenda(TRUE);
    parent::__construct($type, $topics);
  }

  /**
   * Getter.
   */
  public function getTitle() {
    return t('Agenda');
  }

  public function generateContent() {
//    $path = md5(current_path());
//    $cache_key = 'newsroom:summary_block_agenda:' . $path;
//    $cache = cache_get($cache_key, NEWSROOM_CACHE_TABLE);
//    if ($cache) {
//      $content = $cache->data;
//    } else {
      $factory = new NewsroomAgendaFactory();
      $agenda = $factory->build('schedule', $this->getType(), $this->getTopics(), new DateTime());
      $content = $agenda->getBlockAgenda();
//
//      cache_set($cache_key, $content, NEWSROOM_CACHE_TABLE, time() + 3600);
//    }

    return $content;
  }
}
