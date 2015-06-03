(function ($) {

  /**
   * NextEuropa Token CKEditor behavior.
   *
   * @type {{attach: Function}}
   */
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
            var entity_label = $(this).attr('token-ckeditor-label');
            var token = (entity_label) ? entity_id + '{' + entity_label + '}' : entity_id;
            editor.insertHtml(token);
            e.preventDefault();
          });
        });
      }
    }
  };

})(jQuery);
