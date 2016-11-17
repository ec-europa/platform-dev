/**
 * @file
 * Javascript functionality for the NextEuropa IEF Views Widget.
 */

(function ($) {
    Drupal.behaviors.nexteuropa_ief_views_widget = {
        attach: function (context) {
            $('.ief-selection-link', context).each(function () {
                $(this).click(function (e) {
                    e.preventDefault();
                    var autocomplete_id = $(this).attr('autocomplete-id');
                    var entity_id = $(this).attr('entity-id');
                    var field_id = '#' + autocomplete_id;
                    $('html,body').animate({scrollTop: $(field_id).offset().top - 150}, 500);
                    $(field_id).val(entity_id);
                });
            });
        }
  }
})(jQuery);
