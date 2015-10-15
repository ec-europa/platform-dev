/**
 * @file
 * Displays fields to add parameters in case the selected options need those parameters.
 */

(function (jQuery) {
  jQuery(document).ready(function(){
    show_hide_url_field(jQuery('#edit-url-user-specified-url'));
    show_hide_lan_field(jQuery('#edit-language-language-specified'));

    jQuery('#edit-url').live('change',function(){
      show_hide_url_field(jQuery('#edit-url-user-specified-url'));
    });

    jQuery('#edit-language').live('change',function(){
      show_hide_lan_field(jQuery('#edit-language-language-specified'));
    });
  });

  function show_hide_url_field($radiobutton) {
    if ($radiobutton.is(':checked')) {
      jQuery('.form-item-url-address').css('display', 'block');
      jQuery('#edit-url-address').focus();
    }
    else {
      jQuery('.form-item-url-address').css('display', 'none');
      jQuery('#edit-url-address').val("");
    }
  }

  function show_hide_lan_field($radiobutton) {
    if ($radiobutton.is(':checked')) {
      jQuery('.form-item-language-selector').css('display', 'block');
      // jQuery('#edit-url-address').focus();.
    }
    else {
      jQuery('.form-item-language-selector').css('display', 'none');
      // jQuery('#edit-url-address').val("");.
    }
  }
})(jQuery);
