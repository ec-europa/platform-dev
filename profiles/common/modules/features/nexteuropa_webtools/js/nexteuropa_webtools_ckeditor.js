/**
 * @file
 * NextEuropa Token CKEditor behavior.
 */

(function ($) {
  /**
   * NextEuropa Token CKEditor behavior.
   *
   * @type {{attach: Function}}
   */
    Drupal.behaviors.nexteuropa_webtools_block_content = {
        attach: function (context) {
            Drupal.nexteuropa_webtools_block_content = Drupal.nexteuropa_webtools_block_content || {};
            var editor_id = Drupal.nexteuropa_webtools_block_content.current_editor_id || '';

          if (editor_id in Drupal.nexteuropa_webtools_block_content) {
                var editor = Drupal.nexteuropa_webtools_block_content[editor_id];
                var content = context[0];
                $(content).find('.token-ckeditor-selection').once('token-ckeditor-selection', function() {
                    $(this).click(function (e) {
                        e.preventDefault();
                        var token = $(this).attr('token-ckeditor-token');
                        var type = $(this).attr('token-ckeditor-type');
                      if (type != 'url') {
                            token = token + "{" + Drupal.t('@label as @mode', {'@label': $(this).attr('token-ckeditor-label'), '@mode': $(this).text()}) + "}";
                      }
                        editor.insertHtml(token);
                        CKEDITOR.dialog.getCurrent().hide();
                    });
                });
          }
        }
  };
})(jQuery);
