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

}
