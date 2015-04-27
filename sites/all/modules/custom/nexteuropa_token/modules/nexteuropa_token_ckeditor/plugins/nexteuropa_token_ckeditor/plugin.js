(function($) {
  CKEDITOR.plugins.add('nexteuropa_token_ckeditor', {
    init: function(editor) {
      CKEDITOR.dialog.add('nexteuropa_token_ckeditor_dialog', function() {
        return {
          title: Drupal.t('Insert token'),
          minWidth: 750,
          minHeight: 300,
          contents: [
            {
              id: 'info',
              label: Drupal.t('Insert a token'),
              title: Drupal.t('Insert a token'),
              elements: [
                {
                  id: 'nexteuropa_token_ckeditor',
                  type: 'html',
                  html: '<div class="nexteuropa-token-dialog-container"></div>'
                }
              ]
            }
          ],
          onShow: function () {
            // Get CKEditor object.
            var editor = this.getParentEditor();

            // Store current editor id. It will be refreshed every time a new dialog is open.
            Drupal.nexteuropa_token_ckeditor = Drupal.nexteuropa_token_ckeditor || {};
            Drupal.nexteuropa_token_ckeditor.current_editor_id = editor.id;

            if (!(editor.id in Drupal.nexteuropa_token_ckeditor)) {
              // Store editor reference in global Drupal object since it will be accessed from within
              // Drupal.behaviors.nexteuropa_token_ckeditor defined in nexteuropa_token_ckeditor.js
              Drupal.nexteuropa_token_ckeditor[editor.id] = editor;

              // Get dialog container ID.
              var id = 'nexteuropa-token-' + editor.id + '-dialog-container';

              // Get dialog DOM object.
              var content = $(this.getElement('info', 'nexteuropa_token_ckeditor').$);
              $('.nexteuropa-token-dialog-container', content).attr('id', id);

              var ajax_settings = {
                url: Drupal.settings.basePath + 'nexteuropa/token-ckeditor/' + id,
                event: 'dialog.nexteuropa-token-ckeditor',
                method: 'html'
              };

              new Drupal.ajax(id, content[0], ajax_settings);
              content.trigger(ajax_settings.event);
            }
          },
          buttons: [CKEDITOR.dialog.okButton]
        };
      });

      // Register a command with CKeditor to launch the dialog box.
      editor.addCommand('NextEuropaTokenInsert', new CKEDITOR.dialogCommand('nexteuropa_token_ckeditor_dialog'));

      // Add a button to the CKeditor that executes a CKeditor command.
      editor.ui.addButton('NextEuropaToken', {
        label: Drupal.t('Insert a token'),
        command: 'NextEuropaTokenInsert',
        icon: this.path + 'icons/nexteuropa_token_ckeditor.png'
      });
    }
  });
})(jQuery);

