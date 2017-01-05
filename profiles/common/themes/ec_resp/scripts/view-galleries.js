/**
 * @file
 * Javascripts for gallery views.
 */

(function ($) {
  Drupal.behaviors.ec_resp_view_galleries = {
    attach: function (context) {
      $row = $('div.galleries-item-wrapper');
      // Hide the video thumbnails in galleries with pictur thumbnails.
      $row.each(function () {
        if ($(this).find('a').size() > 1) {
          $(this).find('a:last').hide();
        }
      });
    }
  }
})(jQuery);
