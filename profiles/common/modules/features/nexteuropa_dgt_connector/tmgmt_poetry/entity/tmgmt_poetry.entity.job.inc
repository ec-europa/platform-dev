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
    if ($this->hasPoetryTranslator() && $this->state != TMGMT_JOB_STATE_UNPROCESSED) {
      return FALSE;
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
    if ($this->hasPoetryTranslator() && $this->state != TMGMT_JOB_STATE_UNPROCESSED) {
      return FALSE;
    }
    return parent::isDeletable();
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
   * Checks if job has a translator with a poetry plugin.
   *
   * @return bool
   *   TRUE if translator has a poetry plugin, FALSE otherwise.
   */
  public function hasPoetryTranslator() {
    $translator = $this->getTranslator();
    if (!empty($translator)) {
      return in_array($translator->plugin, ['poetry', 'tmgmt_dgt_connector']);
    }
    return FALSE;
  }

}
