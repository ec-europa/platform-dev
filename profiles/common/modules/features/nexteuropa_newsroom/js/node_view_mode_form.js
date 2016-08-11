/**
 * @file
 * Newsroom view mode form.
 */

(function ($) {
  Drupal.behaviors.nexteuropa_newsroom = {
    attach: function (context, settings) {
      $("#edit-reveal-modes").click(function (event) {
        event.preventDefault();
        jQuery('#newsroom-import-code').css('display', 'block');
        jQuery('#newsroom-export-code').css('display', 'block');
        jQuery('#newsroom_import_submit').css('display', 'block');
        jQuery('#newsroom_import_backup').css('display', 'block');
        jQuery(this).parent().parent().css('display', 'none');
        jQuery('#newsroom-backup-submit').css('display', 'block');
      });
    }
  };
})(jQuery);
