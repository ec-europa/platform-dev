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
  Drupal.behaviors.nexteuropa_token_ckeditor = {
    attach: function (context) {
      Drupal.nexteuropa_token_ckeditor = Drupal.nexteuropa_token_ckeditor || {};
      var editor_id = Drupal.nexteuropa_token_ckeditor.current_editor_id || '';

      if (editor_id in Drupal.nexteuropa_token_ckeditor) {
        var editor = Drupal.nexteuropa_token_ckeditor[editor_id];
        var content = context[0];

        $(content).find('.token-ckeditor-tips-toggle').once('token-ckeditor-tips-toggle', function() {
          $(this).click(function (e) {
            e.preventDefault();
            $('.token-ckeditor-tips-container').toggle();
          });
        });

        $(content).find('.token-ckeditor-selection').once('token-ckeditor-selection', function() {
          $(this).click(function (e) {
            e.preventDefault();
            var token = $(this).attr('token-ckeditor-token');
            var type = $(this).attr('token-ckeditor-type');
            if (type != 'url') {
              token = token + '{' + Drupal.t('@label as @mode', {'@label': $(this).attr('token-ckeditor-label'), '@mode': $(this).text()}) + '}';
            }
            editor.insertHtml(token);
            CKEDITOR.dialog.getCurrent().hide();
          });
        });
      }

      Drupal.nexteuropa_token_ckeditor = Drupal.nexteuropa_token_ckeditor || {};
      var editor_id = Drupal.nexteuropa_token_ckeditor.current_editor_id || '';

      if (editor_id in Drupal.nexteuropa_token_ckeditor) {
        var editor = Drupal.nexteuropa_token_ckeditor[editor_id];
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
