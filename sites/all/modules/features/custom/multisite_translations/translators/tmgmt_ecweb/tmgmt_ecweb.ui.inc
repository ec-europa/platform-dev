<?php

/**
 * @file
 * Provides Ecweb Translator ui controller.
 */

/**
 * Ecweb translator ui controller.
 */

class TMGMTEcwebTranslatorUIController extends TMGMTDefaultTranslatorUIController {
  /**
   * Overrides TMGMTDefaultTranslatorUIController::pluginSettingsForm().
   */
  public function pluginSettingsForm($form, &$form_state, TMGMTTranslator $translator, $busy = FALSE) {
    return parent::pluginSettingsForm($form, $form_state, $translator);
  }

}
