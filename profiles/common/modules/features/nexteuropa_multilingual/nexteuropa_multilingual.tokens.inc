<?php

/**
 * @file
 * Code for the NextEuropa Multilingual feature.
 */

/**
 * Implements hook_token_info().
 */
function nexteuropa_multilingual_token_info() {
  $info['tokens']['node']['entity-translation-languages'] = array(
    'name' => t('Node translation languages'),
    'description' => t('Display all the translation languages.'),
  );
  return $info;
}

/**
 * Implements hook_tokens().
 */
function nexteuropa_multilingual_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();

  if ($type == 'node' && !empty($data['node'])) {
    $node = $data['node'];
    foreach ($tokens as $name => $original) {
      if ($name == 'entity-translation-languages') {
        $handler = entity_translation_get_handler('node', $node);
        $translations = $handler->getTranslations();
        $entity_languages = array_keys($translations->data);
        $language_list = language_list();
        $languages = array();
        foreach ($entity_languages as $language) {
          if (isset($language_list[$language]) && isset($language_list[$language]->name)) {
            $languages[] = $language_list[$language]->name;
          }
        }

        $replacements[$original] = implode(" ", $languages);
      }
    }
  }
  return $replacements;
}
