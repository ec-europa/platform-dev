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
   * @param $plugin
   *   The plugin name.
   * @param $item_type
   *   The source item type.
   * @param $item_id
   *   The source item id.
   *
   * @return TMGMTJobItem
   *   The job item that was added to the job or FALSE if it couldn't be saved.
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

    $item = tmgmt_job_item_create($plugin, $item_type, $item_id,
      array('tjid' => $this->tjid, 'state' => TMGMT_JOB_ITEM_STATE_CREATED));
    $item->save();

    if ($item->getWordCount() == 0) {
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

}
