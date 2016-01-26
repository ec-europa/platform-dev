/**
 * @file
 * Provides JavaScript for mapeditor forms.
 */

(function ($) {

  /**
   * Provides a help text for the height field.
   *
   * Helps choosing the right height for a map.
   */
  Drupal.behaviors.dag_maxlength_title_field = {
    attach: function (context, settings) {
      var min_height = Drupal.settings.mapeditor.min_height;
      var label = Drupal.settings.mapeditor.label;
      var warning = Drupal.settings.mapeditor.warning;
      var displayed_label = label;
      var height_obj = jQuery('input[name=height]');
      jQuery('#min-height-label').html(displayed_label);
      jQuery('input[name=height]').keyup(function () {
        var height = jQuery(this).val();
        if (height < min_height) {
          var displayed_label = warning + ' ' + label;
          jQuery('#min-height-label').html(displayed_label);
        }
        else {
          var displayed_label = label;
          jQuery('#min-height-label').html(displayed_label);
        }
      });
    }
  }

})(jQuery);