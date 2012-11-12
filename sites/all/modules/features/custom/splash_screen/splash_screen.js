(function($) {
  Drupal.behaviors.splash = {
    attach: function(context, settings) {

      $('ul.languages li a').hover(function() {
        $('#label_language').text($(this).attr('data-label'));
      });

    }
  }
})(jQuery);
