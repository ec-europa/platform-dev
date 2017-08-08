/**
 * @file
 * This file provides a small modification to the autocomplete url paths.
 */

(function($){
  Drupal.behaviors.language_selector_page = {
    attach: function (context, settings) {

      var secondLanguageParam = '2nd-language';

      var secondLanguageValue = getParameter(secondLanguageParam, window.location.search);
      if (secondLanguageValue) {
        addSecondLanguage(secondLanguageParam, secondLanguageValue);
      }

      /**
       * Add second preferred language to autocomplete urls.
       *
       * Instead of suffixing, we prefix it as the autocomplete javascript is
       * already using the suffix method.
       */
      function addSecondLanguage(paramName, paramValue) {
        // Only apply this to autocomplete paths. All other urls are parsed by
        // using hook_url_outbound_alter.
        $('input.autocomplete').each(function() {
          // Lets ignore if the 2nd-language is somehow already set and if it is
          // an external url.
          if (!getParameter(paramName, this.value) && isCurrentDomain(this.value)) {
            // Get the base of our url.
            base_url = this.value.substring(0,this.value.indexOf("?"));
            // Build the new url.
            new_url = base_url + '?' + paramName + '=' + paramValue + '&q=' + getParameter('q', this.value);
            // Place back the new url in the form.
            $(this).attr('value', new_url);
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
