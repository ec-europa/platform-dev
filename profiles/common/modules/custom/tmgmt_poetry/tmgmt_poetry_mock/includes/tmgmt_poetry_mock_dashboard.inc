<?php
/**
 * @file
 * tmgmt_poetry_mock_dashboard.inc
 */

use Drupal\tmgmt_poetry_mock\Mock\PoetryMock;

/**
 * POETRY Service Mock dashboard callback function.
 */
function tmgmt_poetry_mock_dashboard() {
  $data_set = _poetry_mock_prepare_request_data_set();
  $table = _poetry_mock_render_table($data_set);

  return $table;
}

/**
 * Creating data set for the theme function.
 */
function _poetry_mock_prepare_request_data_set() {
  $request_files = PoetryMock::getAllRequestTranslationFiles();
  $data_set = [];
  if (!empty($request_files)) {
    foreach ($request_files as $request_file) {
      $file_object = file_load($request_file->fid);
      $message = file_get_contents($file_object->uri);
      $request_data = PoetryMock::getDataFromRequest($message);
      if (isset($request_data['demande_id']['sequence'])) {
        $request_data['demande_id']['numero'] = PoetryMock::COUNTER_VALUE;
      }
      $entity_details = PoetryMock::getEntityDetailsByDemandeId($request_data['demande_id']);
      $jobs = PoetryMock::getActiveTranslationJobsByEntityId($entity_details['entity_id']);
      if ($entity_details && !empty($jobs)) {
        foreach ($jobs as $job) {
          $data_set[$job->tjid] = [
            'reference' => $job->reference,
            'tjid' => $job->tjid,
            'tjiid' => $job->tjiid,
            'source_lg' => $job->source_language,
            'target_lg' => $job->target_language,
            'date' => format_date($job->changed, 'short'),
            'entity_id' => $entity_details['entity_id'],
            'entity_type' => $entity_details['entity_type'],
            'file_id' => $request_file->fid,
          ];
        }
      }
    }
  }

  return $data_set;
}

/**
 * Helper function which renders table with job translations.
 *
 * @param array $data_set
 *    Data set with translation job requests.
 *
 * @return string
 *    Rendered markup for the table with translation job requests.
 */
function _poetry_mock_render_table($data_set) {
  if (count($data_set) > 0) {
    // Setting up table header.
    $header = [
      ['data' => t('Reference')],
      ['data' => t('Job ID')],
      ['data' => t('Job item ID')],
      ['data' => t('Translation')],
      ['data' => t('Change')],
      ['data' => t('Entity type')],
      ['data' => t('Entity ID')],
      ['data' => t('File ID')],
      ['data' => t('Actions')],
    ];

    // Setting up table rows.
    foreach ($data_set as $data_row) {
      $row = [
        $data_row['reference'],
        l($data_row['tjid'], 'admin/tmgmt/jobs/' . $data_row['tjid']),
        l($data_row['tjiid'], 'admin/tmgmt/items/' . $data_row['tjiid'],
          ['query' => ['destination' => 'admin/tmgmt/jobs/' . $data_row['tjid']]]
        ),
        $data_row['source_lg'] . '->' . $data_row['target_lg'],
        $data_row['date'],
        $data_row['entity_type'],
        l($data_row['entity_id'], _tmgmt_poetry_mock_get_job_item_entity_path($data_row['tjiid'])),
        l($data_row['file_id'], 'file/' . $data_row['file_id']),
        _poetry_mock_get_data_row_action_links($data_row),
      ];
      $rows[] = $row;
    }

    // Initialize the pager.
    $current_page = pager_default_initialize(count($rows), 25);
    // Split list into page sized chunks.
    $chunks = array_chunk($rows, 25, TRUE);

    // Render table.
    $rendered_table = theme('table',
      [
        'header' => $header,
        'rows' => $chunks[$current_page],
        'attributes' => ['class' => ['table', 'table-striped']],
        'caption' => '',
        'colgroups' => [],
        'sticky' => FALSE,
        'empty' => FALSE,
      ]
    );

    // Add rendered pager to the table.
    $rendered_table .= theme('pager', ['quantity', count($rows)]);
  }
  else {
    $rendered_table = '<p>There are no active translation job requests.</p>';
  }

  return $rendered_table;
}

/**
 * Helper function for rendering actions for each translation job.
 *
 * @param array $data_row
 *    Translation job data array.
 *
 * @return string
 *    Rendered markup with action list links.
 */
function _poetry_mock_get_data_row_action_links($data_row) {
  $action_list = [
    'see' => [
      'title' => 'See',
      'href' => _tmgmt_poetry_mock_get_job_item_entity_path($data_row['tjiid'], true),
    ],
    'translate' => [
      'title' => 'Translate',
      'href' => 'tmgmt_poetry_mock/translate/'
      . $data_row['target_lg'] . '/'
      . $data_row['file_id'] . '/'
      . $data_row['tjiid'],
      'query' => array('destination' => current_path()),
    ],
    'refuse' => [
      'title' => 'Refuse',
      'href' => 'tmgmt_poetry_mock/refuse/'
      . $data_row['file_id'] . '/'
      . $data_row['tjiid'],
      'query' => array('destination' => current_path()),
    ],
  ];

  return theme('links', ['links' => $action_list]);
}
