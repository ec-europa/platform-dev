<?php
/**
 * @file
 * Code for the NextEuropa Metatags module.
 */

/**
 * Custom helper function.
 *
 * @return array
 *   Returns the error message if the config of metatags does not comply.
 */
function _nexteuropa_metatags_check_metatag_config() {
  $messages = array();

  if ($config = metatag_config_load('global')) {
    $meta_to_check = array('X-UA-Compatible', 'viewport');

    foreach ($meta_to_check as $meta) {
      if (!isset($config->config[$meta]) || (isset($config->config[$meta]) && empty($config->config[$meta]['value']))) {
        $messages[$meta] = t('The <em>@meta</em> global meta is empty, please <a href="@link">configure it</a> properly.', array('@meta' => $meta, '@link' => url('admin/config/search/metatags/config/global')));
      }
    }
  }

  return $messages;
}
