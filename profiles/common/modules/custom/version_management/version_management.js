/**
 * @file
 * Contains javascript code for the Version Management module.
 *
 * Code to manage events triggered on the version management checkbox.
 */

jQuery.noConflict();

(function ($) {
  Drupal.behaviors.myBehavior = {
    attach: function (context, settings) {
      $('#edit-minor-version').on('click', function (e) {
        $('#edit-submit').toggleClass('major_version_mark_bg');
        $('#edit-minor-version').toggleClass('major_version_mark_color');
        $('.form-item-minor-version label').toggleClass('major_version_mark_color');
        $('#edit-submit').toggleClass('btn-default');
      });
    }
  };
})(jQuery);
