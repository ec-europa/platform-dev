/**
 * @file
 * Javascript functionality for the NextEuropa Multilingual feature.
 */

(function ($) {
  Drupal.behaviors.nexteuropa_multilingual = {
    attach: function (context, settings) {

      var secondLanguageParam = '2nd-language';

      var secondLanguageValue = getParameter(secondLanguageParam, window.location.search);
      if (secondLanguageValue) {
        addSecondLanguage(secondLanguageParam, secondLanguageValue);
      }

      /**
       * Add second preferred language to every link.
       */
      function addSecondLanguage(paramName, paramValue) {
        $('a[href]').each(function () {
          if (!getParameter(paramName, this.href) && isCurrentDomain(this.href)) {
            var sep = (this.href.indexOf('?') != -1) ? '&' : '?';
             $(this).attr('href', this.href + sep + paramName + '=' + paramValue);
          }
        });
        $('form').each(function () {
          if (!getParameter(paramName, this.action) && isCurrentDomain(this.action)) {
            var sep = (this.action.indexOf('?') != -1) ? '&' : '?';
            $(this).attr('action', this.action + sep + paramName + '=' + paramValue);
          }
        });
      }

      /**
       * Check if link leads to current domain or not.
       *
       * Returns true if link leads to current domain, and false if not.
       */
      function isCurrentDomain(linkUrl) {
        if (linkUrl.indexOf(document.domain) == -1) {
          return false;
        }
        else {
          return true;
        }
      }

      /**
       * Helper function to get parameter.
       *
       * Returns parameter value, or false if not found.
       */
      function getParameter(paramName, location) {
        var params = location.split('?');
        if (params[1]) {
          var paramsList = params[1].split('&');
          for (var i = 0; i < paramsList.length; i++) {
            var param = paramsList[i].split('=');
            if (param[0] == paramName) {
              return param[1];
            }
          }
        }
        return false;
      }
    }
  };
})(jQuery);
