<?php

/**
 * @file
 * Contains job entity class.
 */

/**
 * Entity class for the tmgmt_job entity.
 *
 * @ingroup tmgmt_job
 */
class TMGMTPoetryJob extends TMGMTJob {

  /**
   * Checks whether a job is abortable.
   *
   * @return bools
   *   TRUE if the job can be aborted, FALSE otherwise.
   */
  public function isAbortable() {
    $translator = $this->getTranslator();
    if ($translator) {
      if ($translator->plugin == 'poetry' && $this->state != TMGMT_JOB_STATE_UNPROCESSED) {
        return FALSE;
      }
    }
    return parent::isAbortable();
  }

  /**
   * Checks whether a job is deletable.
   *
   * @return bool
   *   TRUE if the job can be deleted, FALSE otherwise.
   */
  public function isDeletable() {
    $translator = $this->getTranslator();
    if ($translator) {
      if ($translator->plugin == 'poetry' && $this->state != TMGMT_JOB_STATE_UNPROCESSED) {
        return FALSE;
      }
    }
    return parent::isDeletable();
  }

  /**
   * Adds an item to the translation job.
   *
   * @param string $plugin
   *   The plugin name.
   * @param string $item_type
   *   The source item type.
   * @param int $item_id
   *   The source item id.
   *
   * @return TMGMTJobItem
   *   The job item that was added to the job or FALSE if it couldn't be saved.
   *
   * @throws TMGMTException
   *   On zero item word count.
   */
  public function addItem($plugin, $item_type, $item_id) {

    $transaction = db_transaction();
    $is_new = FALSE;

    if (empty($this->tjid)) {
      $this->save();
      $is_new = TRUE;
    }

    $item = tmgmt_job_item_create($plugin, $item_type, $item_id, array('tjid' => $this->tjid));

    // We will save this job item only when submitting the translation
    // We want to keep this Job Item because later we don't have the item_id
    // $item->save();
    $this->jobItemSessionCreate($item);

    if ($this->getItemWordCount($item) == 0) {
      $transaction->rollback();

      // In case we got word count 0 for the first job item, NULL tjid so that
      // if there is another addItem() call the rolled back job object will get
      // persisted.
      if ($is_new) {
        $this->tjid = NULL;
      }

      throw new TMGMTException('Job item @label (@type) has no translatable content.',
          array('@label' => $item->label(), '@type' => $item->getSourceType()));
    }

    return $item;
  }

  /**
   * Returns all job items attached to this job.
   *
   * If no items are returned, look in SESSION for previously saved job items.
   *
   * @param array $conditions
   *   Additional conditions to pass into EFQ.
   *
   * @return TMGMTJobItem[]
   *   An array of translation job items.
   */
  public function getItems($conditions = array()) {
    $items = parent::getItems($conditions);

    if (empty($items)) {
      $item = $this->jobItemSessionGet();
      if ($item && $item->tjid == $this->tjid) {
        return array($item);
      }
    }

    return $items;
  }

  /**
   * Returns a job item previously saved in SESSION.
   *
   * @return bool|TMGMTJobItem
   *   Return the job item in SESSION or FALSE.
   */
  public function jobItemSessionGet() {
    return isset($_SESSION['tmgmt_ui']['poetry_item']) ? unserialize($_SESSION['tmgmt_ui']['poetry_item']) : FALSE;
  }

  /**
   * Saves a job item in SESSION.
   *
   * @param TMGMTJobItem $item
   *   The job item to save.
   */
  public function jobItemSessionCreate(TMGMTJobItem $item) {
    $_SESSION['tmgmt_ui']['poetry_item'] = serialize($item);
  }

  /**
   * Returns all job items attached to this job.
   *
   * If there are none in the database, search in SESSION and if found then
   * save it in database, then remove it from SESSION.
   *
   * @return array|TMGMTJobItem[]
   *   An array with the job items.
   */
  public function jobItemSessionGetSaveAndUnset() {

    if ($items = parent::getItems()) {
      return $items;
    }
    elseif (($item = $this->jobItemSessionGet()) && $item->tjid == $this->tjid) {
      $item->save();
      unset($_SESSION['tmgmt_ui']['poetry_item']);
      return array($item);
    }

    return array();
  }

  /**
   * Count of all accepted data items.
   *
   * @return int
   *   Translated count
   */
  public function getCountAccepted() {
    return tmgmt_poetry_job_statistics($this, 'count_accepted');
  }

  /**
   * Count of all reviewed data items.
   *
   * @return int
   *   Translated count
   */
  public function getCountReviewed() {
    return tmgmt_poetry_job_statistics($this, 'count_reviewed');
  }

  /**
   * Count of all translated data items.
   *
   * @return int
   *   Translated count
   */
  public function getCountTranslated() {
    return tmgmt_poetry_job_statistics($this, 'count_translated');
  }

  /**
   * Count of all pending data items.
   *
   * @return int
   *   Translated count
   */
  public function getCountPending() {
    return tmgmt_poetry_job_statistics($this, 'count_pending');
  }

  /**
   * Sums up all word counts of this task job items.
   *
   * @return int
   *   The sum of all accepted counts
   */
  public function getWordCount() {
    return tmgmt_poetry_job_statistics($this, 'word_count');
  }

  /**
   * Get word count for TMGMTJobItem.
   *
   * Returns the same result as TMGMTJob::getWordCount but without side impacts.
   *
   * @param TMGMTJobItem|array $item
   *   The job item or its data.
   *
   * @return int
   *   Number of words
   */
  protected function getItemWordCount($item) {

    if (is_object($item)) {
      $item = $item->getSourceData();
    }

    if (!empty($item['#text'])) {
      if (_tmgmt_filter_data($item)) {

        // Count words of the data item.
        return tmgmt_word_count($item['#text']);
      }
    }
    elseif (is_array($item)) {
      $counter = 0;
      foreach (element_children($item) as $key) {
        $counter += $this->getItemWordCount($item[$key]);
      }
      return $counter;
    }
  }

}
