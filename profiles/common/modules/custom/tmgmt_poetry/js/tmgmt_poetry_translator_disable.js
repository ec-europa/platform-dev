/**
 * @file
 * Scripts for TMGMT Poetry module.
 */

(function ($) {

  /**
   * Small script for making Translator select field disabled on /admin/tmgmt/jobs/% path.
   */
  Drupal.behaviors.tmgmtPoetryDisableTranslator = {
    attach: function (context, settings) {
      $('#edit-translator').attr('disabled', 'disabled');
      $('#edit-translator').parent().addClass('form-disabled');

      if (!$('#unblock-translator').length) {
        $('#edit-translator').parent().append('<a href="#" id="unblock-translator">' + Drupal.t('Change translator') + '</a>');
      }

      $('#unblock-translator').click(function (e) {
        $('#edit-translator').removeAttr('disabled', 'disabled');
        $('#edit-translator').parent().removeClass('form-disabled');
        $(this).remove();
      });
    }
  };

})(jQuery);
