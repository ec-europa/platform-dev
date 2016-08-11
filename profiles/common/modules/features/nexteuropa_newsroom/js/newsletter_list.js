/**
 * @file
 * Newsroom newsletter list.
 */

(function ($) {
  Drupal.behaviors.nexteuropa_newsroom = {
    attach: function (context, settings) {
      $('.serviceItemContainer input[type="submit"]').each(function () {
        $(this).prop('disabled', !Drupal.settings.nexteuropa_newsroom.user_is_logged_in);
      });

      $('#newsroom-service-email').change(function () {
        var regex = /^([a-zA-Z0-9_.+-])+\@(([a-zA-Z0-9-])+\.)+([a-zA-Z0-9]{2,4})+$/;
        var email = $(this).val();
        if (regex.test($(this).val())) {
          $('.serviceItemContainer input[name="email"]').each(function () {
            $(this).val(email);
          });

          $('.serviceItemContainer input[type="submit"]').each(function () {
            $(this).prop('disabled', false);
          });
        }
        else {
          alert(Drupal.settings.nexteuropa_newsroom.error_message);
        }
      });
    }
  };
})(jQuery);
