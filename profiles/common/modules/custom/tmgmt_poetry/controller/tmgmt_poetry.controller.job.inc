<?php

/**
 * @file
 * Contains the job entity controller class.
 */

/**
 * Controller class for the job entity.
 *
 * @ingroup tmgmt_job
 */
class TMGMTPoetryJobController extends TMGMTJobController {

  /**
   * {@inheritdoc}
   */
  public function save($origin_job, DatabaseTransaction $transaction = NULL) {

    $translator = $origin_job->getTranslator();
    $origin_job_items = $origin_job->jobItemSessionGetSaveAndUnset();

    if ($origin_job->reference === NULL && isset($origin_job->settings['languages']) && $translator->plugin == 'poetry') {
      $origin_job->reference = 'MAIN_' . $origin_job->tjid;
      $origin_job_item = array_shift($origin_job_items);
      if (empty($origin_job_item)) {
        drupal_set_message('The selected job cannot be used. Please make a new translation request.', 'warning');
        drupal_goto('admin/tmgmt');
        return;
      }
      _tmgmt_poetry_insert_item_status($origin_job_item->tjiid, $origin_job->target_language, "Pending", date('d/m/Y', strtotime($origin_job->settings['delai'])));
    }

    if ((count($origin_job_items) > 0) && isset($origin_job->settings['languages']) && $translator->plugin == 'poetry') {
      $origin_job_item = array_shift($origin_job_items);
      $languages = language_list('language');
      $requested_languages = $origin_job->settings['languages'];
      foreach ($requested_languages as $key_requested_language => $requested_language) {
        if ($key_requested_language != $origin_job->target_language) {
          if (empty($requested_language)) {
            // Remove a job if it was unchecked.
            $job_ids_remove = _tmgmt_poetry_obtain_related_translation_jobs(array($key_requested_language), 'SUB_' . $origin_job->tjid)->fetchAll();
            if (count($job_ids_remove) > 0) {
              $job_id_remove = array_shift($job_ids_remove);
              $job_remove = tmgmt_job_load($job_id_remove->tjid);
              $job_remove->delete();
            }
            continue;
          }

          // Check if job is already created
          // and in that case don't create it again.
          if (_tmgmt_poetry_obtain_related_translation_jobs(array($requested_language), 'SUB_' . $origin_job->tjid)->rowCount() > 0) {
            continue;
          }

          $job = tmgmt_job_create($origin_job->source_language, $requested_language, $origin_job->uid);
          $job->translator = $origin_job->translator;
          $job->reference = 'SUB_' . $origin_job->tjid;
          $job->label = $origin_job->label . ' ' . $languages[$requested_language]->name;
          $job->save();

          $job_item = tmgmt_job_item_create($origin_job_item->plugin, $origin_job_item->item_type, $origin_job_item->item_id);
          $job_item->tjid = $job->tjid;
          $job_item->count_pending = $origin_job_item->count_pending;
          $job_item->count_translated = $origin_job_item->count_translated;
          $job_item->count_accepted = $origin_job_item->count_accepted;
          $job_item->count_reviewed = $origin_job_item->count_reviewed;
          $job_item->word_count = $origin_job_item->word_count;
          $job_item->save();
          _tmgmt_poetry_insert_item_status($job_item->tjiid, $job->target_language, "Pending", date('d/m/Y', strtotime($origin_job->settings['delai'])));
        }
      }
    }

    // If a poetry translation has accepted a translation request
    // we should update the related additional sub translation jobs
    // with a reference returned by poetry.
    if ($origin_job->state == TMGMT_JOB_STATE_ACTIVE && (strpos($origin_job->reference, 'MAIN_' . $origin_job->tjid . '_POETRY') !== FALSE)) {
      $jobs = _tmgmt_poetry_obtain_related_translation_jobs(array(), 'SUB_' . $origin_job->tjid, TRUE);
      foreach ($jobs as $ids) {
        $job = tmgmt_job_load($ids->tjid);
        $job->reference = str_replace(
          'MAIN_' . $origin_job->tjid . '_POETRY_',
          'SUB_' . $origin_job->tjid . '_POETRY_',
          $origin_job->reference
        );
        $job->state = TMGMT_JOB_STATE_ACTIVE;
        $job->save();
      }
    }

    return parent::save($origin_job, $transaction);
  }

  /**
   * Remove unused Jobs.
   */
  public function removeUnusedJobs() {
    // Remove Jobs that don't have an associated Job Item.
    db_query('DELETE {tmgmt_job}.* FROM {tmgmt_job} LEFT JOIN {tmgmt_job_item} ON {tmgmt_job}.tjid={tmgmt_job_item}.tjid WHERE {tmgmt_job_item}.tjid IS NULL');
  }

}
