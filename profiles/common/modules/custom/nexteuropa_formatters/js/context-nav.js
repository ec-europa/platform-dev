/**
 * @file
 * Contextual navigation related behaviors.
 */

(function ($) {
  Drupal.behaviors.contextual_nav = {
    attach: function (context) {
      // Define our dropdown button.
      var dropDown = '<span class="context-nav__more-button">' + Drupal.t('More') + '<span class="caret"></span></span>';

      // Loop all our contextual navigation items. We should only do this for
      // the wrappers that have the class .has-expander.
      $.each($('.context-nav__items.has-expander'), function () {

        // Cache our variables.
        var $item = $(this),
            contextNavItems = $item.children(),
            contextNavItemCount = contextNavItems.length,
            contextNavTrimAt = $item.attr('data-trimat') ? $item.attr('data-trimat') : FALSE,
            contextNavTrimTo = $item.attr('data-trimto') ? $item.attr('data-trimto') : FALSE;

        // If there are more then 5 we create our dropdown.
        if (contextNavTrimAt && contextNavTrimTo && contextNavItemCount > contextNavTrimAt) {
          // Wrap the other elements.
          contextNavItems.slice(contextNavTrimTo).wrapAll('<div class="context-nav__expander"><div class="context-nav__hidden"></div></div>');
          // Add the button.
          $item.children('.context-nav__expander').prepend(dropDown);
        }

      });

      // Add the button onclick event.
      $('.context-nav__expander').click('.context-nav__more-button', function () {
        var $button = $(this),
            $elements = $button.closest('.has-expander').find('.context-nav__item').detach();
        // Replace the content with our elements.
        $button.closest('.has-expander').html($elements);
      });

    }
  }
})(jQuery);
