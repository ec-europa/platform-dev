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
                      id: 'nexteuropa_webtools_block_content',
                      type: 'html',
                      html: '<div class="nexteuropa-webtools-block-container"></div>'
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
                  Drupal.nexteuropa_webtools_block_content = Drupal.nexteuropa_webtools_block_content || {};
                  Drupal.nexteuropa_webtools_block_content.current_editor_id = editor.id;

                if (!(editor.id in Drupal.nexteuropa_webtools_block_content)) {
                    // Store editor reference in global Drupal object since it will be accessed from within
                    // Drupal.behaviors.nexteuropa_webtools_block_content defined in nexteuropa_webtools_block_content.js.
                    Drupal.nexteuropa_webtools_block_content[editor.id] = editor;

                    // Get dialog container ID.
                    var id = 'nexteuropa-webtools-' + editor.id + '-block-container';

                    // Get dialog DOM object.
                    var content = $(this.getElement('info', 'nexteuropa_webtools_block_content').$);
                    $('.nexteuropa-webtools-block-container', content).attr('id', id);

                    var ajax_settings = {
                        url: Drupal.settings.basePath + 'nexteuropa/webtools-ckeditor/' + id,
                        event: 'dialog.nexteuropa_webtools_block_content',
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
