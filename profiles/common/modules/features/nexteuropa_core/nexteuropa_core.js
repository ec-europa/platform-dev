/**
 * @file
 * Javascript functionality for the NextEuropa Core feature.
 */

(function ($) {
  Drupal.behaviors.nexteuropaCore = {
    attach: function (context) {

      /**
       * Set the "URL settings" vertical tab.
       */
      $('fieldset.path-form', context).drupalSetSummary(function (context) {
        return Drupal.t('Automatic alias');
      });
    }
  };
})(jQuery);
