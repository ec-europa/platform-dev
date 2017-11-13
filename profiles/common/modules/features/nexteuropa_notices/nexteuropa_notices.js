/**
 * @file
 * Javascripts for notices.
 */

(function ($) {

  Drupal.behaviors.notices = {
    attach: function (context, settings) {
      var cookieName = "hide_notices";
      var cookieValue = getCookie(cookieName);

      // Manage display of notices.
      $('.notice').each(function () {
        // Check if cookie exists.
        if (cookieValue != "") {
          if (jQuery.inArray($(this).attr('id'), JSON.parse(cookieValue)) == -1) {
            // Notice hasn't been hidden before.
            $(this).addClass('is-open');
          }
          else {
            // Notice has been hidden.
            $(this).addClass('is-close');
          }
        }
        else {
          $(this).addClass('is-open');
        }
      });

      // Manage close button.
      $('.notice__btn-close').click({name:cookieName}, function (e) {
        var notice = $(this).closest('.notice');
        var noticeId = notice.attr('id');

        // Check if cookie exists.
        var cookieValue = getCookie(e.data.name);
        if (cookieValue != "") {
          // Cookie exists, update it.
          var newValue = JSON.parse(cookieValue);
          newValue.push(noticeId);
          document.cookie = e.data.name + "=" + JSON.stringify(newValue) + "; path=/";
        }
        else {
          // Cookie doesn't exist, create it.
          var newValue = [noticeId];
          document.cookie = e.data.name + "=" + JSON.stringify(newValue) + "; path=/";
        }

        // Close notice.
        notice.fadeOut(400, function () {
          notice.addClass('is-close');
          notice.removeClass('is-open');
        });
      });

      // Get value of cookie.
      function getCookie(cname) {
        var name = cname + "=";
        var ca = document.cookie.split(';');
        for (var i = 0; i < ca.length; i++) {
          var c = ca[i];
          while (c.charAt(0) == ' ') {
            c = c.substring(1);
          }
          if (c.indexOf(name) == 0) {
            return c.substring(name.length,c.length);
          }
        }
        return "";
      }
    }
  }
})(jQuery);
