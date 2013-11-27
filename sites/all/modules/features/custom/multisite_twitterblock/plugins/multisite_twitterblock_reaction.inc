<?php

/**
 * @file
 * context reaction
 */

class H2020SocialReaction extends context_reaction {

  /**
   * Returns form options.
   * 
   * @param string $context
   *   Context name
   * 
   * @return array
   *   array form
   */
  public function options_form($context) {
    $values = $this->fetch_from_context($context);
    if (empty($values)) {
      // Load defaults.
      $default_values = _h2020_social_load_twitter_config();
    }
    else {
      // Load previous values.
      $default_values = _h2020_social_load_twitter_config($values['config']);
    }

    $form['enabled'] = array(
      '#type' => 'checkbox',
      '#title' => t('Override Twitter widget in this context'),
      '#default_value' => isset($values['enabled']) ? $values['enabled'] : FALSE,
    );

    $form['config'] = _h2020_twitter_settings_form($default_values, 'override', '', "reactions[plugins][h2020_social][config]");
    $form['config'] += array(
      '#type' => 'container',
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
      '#states' => array(
        'visible' => array(
          ':input[name="reactions[plugins][h2020_social][enabled]"]' => array('checked' => TRUE),
        ),
      ),
    );
    return $form;
  }

  /**
   * We need a definition for this function but is not required.
   */
  protected function execute() {

  }
}
