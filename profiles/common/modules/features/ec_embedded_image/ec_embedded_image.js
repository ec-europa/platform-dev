/**
 * @file
 * Javascript file for embedded images (flickr).
 */

(function ($) {
  Drupal.behaviors.embeddedImage = {
    attach: function(context, settings) {
      $("a[href^='http://www.flickr.com']").attr({
        target : "_blank"
      })
    }
  }

})(jQuery);
