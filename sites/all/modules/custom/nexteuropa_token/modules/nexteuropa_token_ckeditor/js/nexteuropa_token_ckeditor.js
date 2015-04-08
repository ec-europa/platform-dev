(function ($) {
  Drupal.behaviors.nexteuropa_token_ckeditor = {
    attach: function (context) {
      Drupal.nexteuropa_token_ckeditor = Drupal.nexteuropa_token_ckeditor || {};
      var editor_id = Drupal.nexteuropa_token_ckeditor.current_editor_id || '';

      if (editor_id in Drupal.nexteuropa_token_ckeditor) {
        var editor = Drupal.nexteuropa_token_ckeditor[editor_id];
        var content = context[0];

        $(content).find('.token-ckeditor-selection').once('token-ckeditor-selection', function() {
          $(this).click(function (e) {
            var entity_id = $(this).attr('token-ckeditor-token');
            editor.insertText(entity_id);
            e.preventDefault();
          });
        });
      }
    }
  };
})(jQuery);
