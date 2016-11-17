/**
 * @file
 * Notifications javascript file.
 */

(function ($) {
  Drupal.behaviors.nexteuropa_subscriptions = {
    attach: function (context, settings) {

    }
  };
})(jQuery);

// Use jQuery 1.4.4
// MOVE HERE ALL THE CODE THAT NEEDS TO BE EXECUTED AS LAST.
// YOU GOT TO MOVE IT MOVE IT.
jQuery(function ($) {
  // Once the page elements are fully loaded.
  $(document).ready(function () {
    var Input = $('#nexteuropa-subscriptions-form input[name=mail]');
    var default_value = Input.val();

    $(Input).focus(function () {
      if ($(this).val() == default_value) {
        $(this).val("");
      }
    }).blur(function () {
        // Small update.
      if ($(this).val().length == 0) {
        $(this).val(default_value);
      }
    });
  });
});
