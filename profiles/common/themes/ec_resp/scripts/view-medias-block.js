/**
 * @file
 * Javascripts for media block views.
 */

(function ($) {
  Drupal.behaviors.ec_resp_view_medias_block = {
    attach: function (context) {
      $row = $('div.carousel-inner div.views-row');
      // Hide the video thumbnails in galleries with pictur thumbnails.
      $row.each(function () {
        if ($(this).find('a').size() > 2) {
          $(this).find('a:last').hide();
        }
      });
    }
  }
})(jQuery);
