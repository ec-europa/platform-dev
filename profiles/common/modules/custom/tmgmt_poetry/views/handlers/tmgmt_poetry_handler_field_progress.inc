<?php
/**
 * @file
 * Contains tmgmt_poetry_handler_field_progress class.
 */

/**
 * Class tmgmt_poetry_handler_field_progress.
 */
class tmgmt_poetry_handler_field_progress extends views_handler_field_entity {

  /**
   * Prefetch statistics for all jobs.
   */
  public function pre_render(&$values) {
    parent::pre_render($values);

    // In case of tasks, pre-fetch the statistics in a single query and add them
    // to the static cache.
    if ($this->entity_type == 'tmgmt_job') {
      $tjids = array();
      foreach ($values as $value) {
        $tjids[] = $value->tjid;
      }
      tmgmt_poetry_job_statistics_load($tjids);
    }
  }

  /**
   * {@inheritdoc}
   */
  public function render($values) {
    /** @var TMGMTJobItem|TMGMTJob $object */
    $object = $this->get_value($values);
    // If job has been aborted the status info is not applicable.
    if ($object->isAborted()) {
      return t('N/A');
    }

    $counts = array(
      '@pending' => $object->getCountPending(),
      '@translated' => $object->getCountTranslated(),
      '@reviewed' => $object->getCountReviewed(),
      '@accepted' => $object->getCountAccepted(),
    );

    $id = $object->internalIdentifier();

    if (module_exists('google_chart_tools')) {
      draw_chart($this->build_progressbar_settings($id, $counts));
      return '<div id="progress' . $id . '"></div>';
    }
    $title = t('[P]ending: @pending, [T]ranslated: @translated, [R]eviewed: @reviewed, [A]ccepted: @accepted.', $counts);
    $output = theme('tmgmt_poetry_progress_field',
      [
        'stats' => $counts,
        'title' => $title,
      ]
    );

    return $output;
  }

  /**
   * Creates a settings array for the google chart tools.
   *
   * The settings are preset with values to display a progress bar for either
   * a job or job item.
   *
   * @param string $id
   *   The id of the chart.
   * @param array $counts
   *   Array with the counts for accepted, translated and pending.
   * @param string $prefix
   *   Prefix to id.
   *
   * @return array
   *   Settings array.
   */
  protected function build_progressbar_settings($id, $counts, $prefix = 'progress') {
    $settings['chart'][$prefix . $id] = array(
      'header' => array(
        t('Accepted'),
        t('Reviewed'),
        t('Translated'),
        t('Pending'),
      ),
      'rows' => array(
        array(
          $counts['@accepted'],
          $counts['@reviewed'],
          $counts['@translated'],
          $counts['@pending'],
        ),
      ),
      'columns' => array(''),
      'chartType' => 'PieChart',
      'containerId' => $prefix . $id,
      'options' => array(
        'backgroundColor' => 'transparent',
        'colors' => array('#00b600', '#60ff60', '#ffff00', '#6060ff'),
        'forceIFrame' => FALSE,
        'chartArea' => array(
          'left' => 0,
          'top' => 0,
          'width' => '50%',
          'height' => '100%',
        ),
        'fontSize' => 9,
        'title' => t('Progress'),
        'titlePosition' => 'none',
        'width' => 60,
        'height' => 50,
        'isStacked' => TRUE,
        'legend' => array('position' => 'none'),
        'pieSliceText' => 'none',
      ),
    );
    return $settings;
  }

}
