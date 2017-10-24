/**
 * @file
 * Displays fields to add parameters in case the selected options before need those parameters.
 */

(function (jQuery) {
  jQuery(document).ready(function() {
    show_hide_field(jQuery('#edit-language-socialbar-language-specified'), jQuery('.form-item-language-selector-socialbar'));

    jQuery('#edit-language-socialbar').live('change',function() {
      show_hide_field(jQuery('#edit-language-socialbar-language-specified'), jQuery('.form-item-language-selector-socialbar'));
    });

    show_hide_field(jQuery('#edit-language-socialbookmark-language-specified'), jQuery('.form-item-language-selector-socialbookmark'));

    jQuery('#edit-language-socialbookmark').live('change',function() {
      show_hide_field(jQuery('#edit-language-socialbookmark-language-specified'), jQuery('.form-item-language-selector-socialbookmark'));
    });

    show_hide_field(jQuery('#edit-type-socialbookmark-icon'), jQuery('.form-item-icon-size-socialbookmark'));

    jQuery('#edit-type-socialbookmark').live('change',function() {
      show_hide_field(jQuery('#edit-type-socialbookmark-icon'), jQuery('.form-item-icon-size-socialbookmark'));
    });

    show_hide_field(jQuery('#edit-override-socialbookmark'), jQuery('.form-item-label-socialbookmark'));

    jQuery('#edit-override-socialbookmark').live('change',function() {
      show_hide_field(jQuery('#edit-override-socialbookmark'), jQuery('.form-item-label-socialbookmark'));
    });

    show_hide_field(jQuery('#edit-display-socialbookmark'), jQuery('.form-item-least-socialbookmark'));

    jQuery('#edit-display-socialbookmark').live('change',function() {
      show_hide_field(jQuery('#edit-display-socialbookmark'), jQuery('.form-item-least-socialbookmark'));
    });

    show_hide_field(jQuery('#edit-display-socialbookmark'), jQuery('.form-item-orientation-socialbookmark'));

    jQuery('#edit-display-socialbookmark').live('change',function() {
      show_hide_field(jQuery('#edit-display-socialbookmark'), jQuery('.form-item-orientation-socialbookmark'));
    });

  });

  function show_hide_field(trigger, field) {
    if (trigger.is(':checked')) {
      field.css('display', 'block');
    }
    else {
      field.css('display', 'none');
    }
  }
})(jQuery);
