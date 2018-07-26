/**
 * @file
 * Scripts for TMGMT Poetry module.
 */

(function ($) {
  Drupal.behaviors.tmgmtPoetryDisableTranslator = {
    attach: function (context, settings) {
      /**
       * Prevent users from leaving the page without selecting one option.
       */
      $(document).ready(function () {
        window.needToConfirm = true;
      });
      $(window).on('beforeunload', function () {
        if (window.needToConfirm) {
          return "Please send or delete the job before leaving the page";
        }
      });

      /**
       * Small script for making Translator select field disabled on /admin/tmgmt/jobs/% path.
       */
      if ($("#edit-translator").val() === "poetry" || $("#edit-translator").val() === "tmgmt_poetry_test_translator") {
        $("#edit-translator").attr('disabled', 'disabled');
        $("#edit-translator").parent().addClass("form-disabled");

        if (!$("#unblock-translator").length) {
          $("#edit-translator").parent().append('<a href="#" id="unblock-translator">' + Drupal.t("Change translator") + "</a>");
        }

        $("#unblock-translator").click(function (e) {
          $("#edit-translator").removeAttr("disabled");
          $("#edit-translator").parent().removeClass("form-disabled");
          e.preventDefault();
        });
      }
    }
  };

})(jQuery);
