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

      var placeholder_tag = Drupal.nexteuropa_token_ckeditor.filter.placeholder_tag;
      CKEDITOR.dtd[placeholder_tag] = CKEDITOR.dtd;
      CKEDITOR.dtd.$blockLimit[placeholder_tag] = 1;
      CKEDITOR.dtd.$inline[placeholder_tag] = 1;
      CKEDITOR.dtd.$nonEditable[placeholder_tag] = 1;
      if (parseFloat(CKEDITOR.version) >= 4.1) {
        // Ensure token tags accept all kinds of attributes.
        editor.filter.allow( placeholder_tag + '[*]{*}(*)', placeholder_tag, true);
        // Objects should be selected as a whole in the editor.
        CKEDITOR.dtd.$object[placeholder_tag] = 1;
      }

      // Ensure tokens instead the html element is saved.
      editor.on('setData', function(event) {
        console.log(event.name, event.editor.name);
        event.data.dataValue = Drupal.nexteuropa_token_ckeditor.filter.replaceTokenWithPlaceholder(event.data.dataValue);
      });

      // Replace tokens with WYSIWYG placeholders.
      editor.on('getData', function(event) {
        console.log(event.name, event.editor.name);
        event.data.dataValue = Drupal.nexteuropa_token_ckeditor.filter.replaceTokenWithPlaceholder(event.data.dataValue);
      });

      // Replace tokens with WYSIWYG placeholders.
      editor.on('insertHtml', function(event) {
        console.log(event.name, event.editor.name);
        event.data.dataValue = Drupal.nexteuropa_token_ckeditor.filter.replaceTokenWithPlaceholder(event.data.dataValue);
      });
    }
  });

  /**
   * Utility class.
   *
   * @type {*|Drupal.nexteuropa_token_ckeditor|{}}
   */
  Drupal.nexteuropa_token_ckeditor = Drupal.nexteuropa_token_ckeditor || {};
  Drupal.nexteuropa_token_ckeditor.filter = {

    /**
     * Placeholder tag.
     */
    placeholder_tag: 'nexteuropa_token',

    /**
     * Regular expressions matching tokens exposed by NextEuropa Token module.
     */
    regex: /\[(\w*)\:(\d*)\:view-mode\:(\w*)\]/,
    regex_global: /\[\w*\:\d*\:view-mode\:\w*\]/g,

    /**
     * Get HTML placeholder give a token and a label.
     *
     * @param token
     *    Token string.
     * @param label
     *    Entity label the token refers to.
     *
     * @returns {string}
     */
    getPlaceholderFromToken: function(token, label) {
      var matches = token.match(this.regex);
      console.log(matches);
      return '<' + this.placeholder_tag + ' type="' + matches[1] + '" id="' + matches[2] + '" mode="' + matches[3] + '">' + label + '</' + this.placeholder_tag + '>';
    },

    /**
     * Replaces tokens with placeholders.
     *
     * @param content
     *    Content coming from WYSIWYG.
     *
     * @returns {*}
     */
    replaceTokenWithPlaceholder: function(content) {

      var matches = content.match(this.regex_global);
      if (matches) {
        for (var i = 0; i < matches.length; i++) {
          var token = matches[i];
          content = content.replace(token, this.getPlaceholderFromToken(token, 'title '));
        }
      }
      return content;
    },

    /**
     * Replaces placeholders with tokens.
     *
     * @param content
     */
    replacePlaceholderWithToken: function(content) {

      return content;
    }
  };
  
})(jQuery);

