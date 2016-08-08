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
   * Gets block title.
   *
   * @return string
   *   Block title.
   */
  public function getTitle() {
    return t('Agenda');
  }

  /**
   * Generates Agenda block content.
   *
   * @return string
   *   Agenda block content.
   */
  public function generateContent() {
    $builder = new NewsroomBuilder();
    $agenda = $builder->buildAgenda(NewsroomAgenda::AGENDA_VIEW_SCHEDULE_BLOCK, $this->getType(), $this->getTopics(), new DateTime(), $this->getOperator());
    $content = theme('newsroom_summary_block_wrapper', array(
      'content' => $agenda->getBlockAgenda(),
      'css_classes' => $this->getCssClasses(),
      'title' => $this->getTitle(),
      'type_url' => 'agenda',
      'url' => 'newsroom-agenda/' . NewsroomAgenda::AGENDA_VIEW_SCHEDULE . '/' . $this->getTypeUrl() . '/' . $this->getTopicUrl(),
    ));
    return $content;
  }

}
