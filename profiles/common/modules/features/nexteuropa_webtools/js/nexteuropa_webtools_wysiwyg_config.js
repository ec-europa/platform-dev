/**
 * @file
 * Wysiwyg configuration file.
 */

(function($) {
    CKEDITOR.on('dialogDefinition', function(ev) {
        // Take the dialog name and its definition from the event data.
        var dialogName = ev.data.name;
        var dialogDefinition = ev.data.definition;
        var dialog = CKEDITOR.dialog.getCurrent();

      if (dialogName == 'nexteuropa_token_ckeditor_dialog') {
          dialogDefinition.addContents({
              id: 'info-block',
              label: Drupal.t('Insert internal blocks'),
              title: Drupal.t('Insert internal blocks'),
              elements: [
                  {
                      id: 'nexteuropa_token_block_content',
                      type: 'html',
                      html: '<div id="nexteuropa-token-block-container"></div>'
                    }
              ]
            });

          // Override the onShow event.
          dialogDefinition.onShow = CKEDITOR.tools.override(dialogDefinition.onShow, function(original) {
              return function() {
                  original.call(this);

                  // Get CKEditor object.
                  var dialog = CKEDITOR.dialog.getCurrent();
                  var editor = dialog.getParentEditor();

                  // Store current editor id. It will be refreshed every time a new dialog is open.
                  Drupal.nexteuropa_block_ckeditor = Drupal.nexteuropa_block_ckeditor || {};
                  Drupal.nexteuropa_block_ckeditor.current_editor_id = editor.id;

                  console.log("Drupal.nexteuropa_block_ckeditor: " + Drupal.nexteuropa_block_ckeditor);
                  console.log("Drupal.nexteuropa_block_ckeditor.current_editor_id: " + Drupal.nexteuropa_block_ckeditor.current_editor_id);

                if (!(editor.id in Drupal.nexteuropa_block_ckeditor)) {
                    // Store editor reference in global Drupal object since it will be accessed from within
                    // Drupal.behaviors.nexteuropa_block_ckeditor defined in nexteuropa_block_ckeditor.js.
                    Drupal.nexteuropa_block_ckeditor[editor.id] = editor;

                    // Get dialog container ID.
                    var id = 'nexteuropa-token-' + editor.id + '-block-container';

                    // Get dialog DOM object.
                    var content = $(this.getElement('info', 'nexteuropa_block_ckeditor').$);
                    $('.nexteuropa-token-block-container', content).attr('id', id);

                    var ajax_settings = {
                        url: Drupal.settings.basePath + 'nexteuropa/token-ckeditor/' + id,
                        event: 'dialog.nexteuropa_block_ckeditor',
                        method: 'html'
                      };

                    new Drupal.ajax(id, content[0], ajax_settings);
                    content.trigger(ajax_settings.event);
                }

                  $('a.cke_dialog_tab').removeClass('cke_dialog_tab_disabled');
              };
          });

      }
    });

})(jQuery);
