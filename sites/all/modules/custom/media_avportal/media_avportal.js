/**
 * @file Jquery module file.
 */
(function($) {
  Drupal.behaviors.media_avportal = {
    attach : function(context, settings) {

      $('div.language-switcher li a').click(
        function(e) {
          e.preventDefault();
          $(this).parents('ul').find('a.current').removeClass('current');
          $(this).addClass('current');
          var iframe = $(this).parents('div.language-switcher').prev('p')
                .find('iframe');
          if(!iframe.length) {
            iframe = $(this).parents('div.language-switcher').prev('iframe')
          }
          var lng = $(this).text().replace('+', ' ');
          var new_src = iframe.attr('src').replace(
                new RegExp("videolang=(.+)", "g"), 'videolang=' + lng);
          iframe.attr('src', new_src);
        })
    }
  }
})(jQuery);
