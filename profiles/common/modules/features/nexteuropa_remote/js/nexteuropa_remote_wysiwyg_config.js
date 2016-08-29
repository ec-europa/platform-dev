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
        id: 'info-remote',
        label: Drupal.t('Remote contents'),
        title: Drupal.t('Remote contents'),
        elements: [
          {
            type: 'text',
            id: 'remote_content_url',
            label: Drupal.t('Url of the remote content')
          },
          {
            type: 'button',
            id: 'get_remote_content_btn',
            label: Drupal.t('Get content'),
            title: Drupal.t('Get content'),
            onClick: function() {
              var dialog = this.getDialog();
              var url = dialog.getContentElement('info-remote','remote_content_url').getValue();
              var remote_browser_endpoint = Drupal.settings.nexteuropa_remote.remote_browser_endpoint;
              $('#url_check_msg').html('Checking url... <img src="' + Drupal.settings.basePath + 'misc/throbber-active.gif"/>');
              $('#nexteuropa-token-remote-content-preview').load(Drupal.settings.basePath + 'remote-entity/get/render?url=' + url, function(response, status, xhr){
                $('#url_check_msg').html('');
                if (status == "error") {
                  $(this).css({ 'color': 'red', 'font-weight': 'bold' });
                  $(this).html('Content not found');
                }
                else {
                  $(this).show();
                  $(this).css({"border" :"1px solid #ddd", "padding": "10px", "margin": "5px"});
                  dialog.getContentElement('info-remote','insert_remote_content_token').getElement().show();
                  // dialog.getContentElement('info-remote','nexteuropa_token_remote_view_mode').getElement().show();
                }
              });
            }
        },
          {
            id: 'nexteuropa_token_remote_content_preview',
            type: 'html',
            html: '<div id="nexteuropa-token-remote-content-preview"></div>'
          },
          {
            id : 'check_url_msg',
            type : 'html',
            html : '<div id="url_check_msg"></div>',
          },
          {
            type: 'button',
            id: 'insert_remote_content_token',
            label: Drupal.t('Insert link'),
            title: Drupal.t('Insert link'),
            onClick: function() {
              // Save entity locally.
              var dialog = this.getDialog();
              var editor = dialog.getParentEditor();
              var url = dialog.getContentElement('info-remote','remote_content_url').getValue();
              var remote_browser_endpoint = Drupal.settings.nexteuropa_remote.remote_browser_endpoint;
              $('#url_check_msg').html('Checking url... <img src="' + Drupal.settings.basePath + 'misc/throbber-active.gif"/>');
              $.get(Drupal.settings.basePath + 'remote-entity/get/save?url=' + url, function(data,status,xhr) {
                $('#url_check_msg').html('');
                $('#url_check_msg').css({ 'color': 'green', 'font-weight': 'bold' });
                $('#url_check_msg').html('Link added');
                // Insert token in wysiwyg.
                editor.insertHtml(data);
              });
            }
        }
        ]
      });

      // Override the onShow event.
      dialogDefinition.onShow = CKEDITOR.tools.override(dialogDefinition.onShow, function(original) {
        return function() {
          original.call(this);
          var dialog = CKEDITOR.dialog.getCurrent();
          var editor = dialog.getParentEditor();
          dialog.getContentElement('info-remote','insert_remote_content_token').getElement().hide();
          // dialog.getContentElement('info-remote','nexteuropa_token_remote_view_mode').getElement().hide();
          $('#nexteuropa-token-remote-content-preview').hide();
          $('#nexteuropa-token-remote-view-mode').hide();
          $('#nexteuropa-token-remote-content-preview').html('');
          $('#url_check_msg').html('');
          $('a.cke_dialog_tab').removeClass('cke_dialog_tab_disabled');
        };
      });

    }
  });

})(jQuery);
