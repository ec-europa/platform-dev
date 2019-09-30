<?php

/**
 * Implement hook_rules_action_info().
 */
function nexteuropa_varnish_rules_action_info() {
  return array(
    'nexteuropa_varnish_rules_action_flush' => array(
      'label' => t('Varnish flush'),
      'group' => t('Entity'),
      'parameter' => array(
        'entity' => array(
          'type' => 'entity',
          'label' => t("Entity"),
        ),
        'string' => array(
          'type' => 'text',
          'label' => t('Regexp'),
          'description' => t('Enter a value for a string that will be hashed using the md5 hash-algorithm.'),
        ),
      ),
    ),
  );
}

function nexteuropa_varnish_rules_action_flush($wrapper, $string) {
  module_load_include('inc', 'nexteuropa_varnish', 'nexteuropa_varnish.rules.admin');
  $regex = _nexteuropa_varnish_gather_expressions($string);
  _nexteuropa_varnish_purge_paths(array($regex));
}
