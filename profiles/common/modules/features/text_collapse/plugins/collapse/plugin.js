/**
 * @file
 * Javascript file for text collapse.
 */

CKEDITOR.plugins.add('collapse',
{
  init: function(editor) {
    /* COMMAND */
    editor.addCommand('cmdCollapseDialog', new CKEDITOR.dialogCommand('collapseDialog'));

    /* BUTTON */
    editor.ui.addButton('collapse',
    {
      label: 'Insert collapsible block',
      command: 'cmdCollapseDialog',
      icon: this.path + 'button.png'
    });

    /* DIALOG */
    CKEDITOR.dialog.add('collapseDialog', function (editor) {
      return {
        title : 'Collapsible block settings',
        minWidth : 300,
        minHeight : 200,
        contents :
        [{
          id : 'tab1',
          label : 'Settings',
          elements :
          [{
            type : 'text',
            id : 'title',
            label : 'Block title',
            onShow : function() { this.setValue('Hidden text');
            },
            validate : CKEDITOR.dialog.validate.notEmpty("Block title should be provided")
          }]
        }],
        onOk : function() {
          var dialog = this;
          var title = dialog.getValueOf('tab1', 'title');

          var openTag = '[collapsed title=' + title + ']';
          var closeTag = '[/collapsed]';
          var inplaceTag = ' ' + openTag + ' text ' + closeTag + ' ';

          var S = editor.getSelection();

          if (S == null) {
            editor.insertHtml(inplaceTag);
            return;
          }

          var R = S.getRanges();
          R = R[0];

          if (R == null) {
            editor.insertHtml(inplaceTag);
            return;
          }

          var startPos = Math.min(R.startOffset, R.endOffset);
          var endPos = Math.max(R.startOffset, R.endOffset);

          if (startPos == endPos) {
            editor.insertHtml(inplaceTag);
            return;
          }

          var container = new CKEDITOR.dom.element('p');
          var fragment = R.extractContents();

          container.appendText(openTag);
          fragment.appendTo(container);
          container.appendText(closeTag);

                editor.insertElement(container);
        }
      };
      // dialog.add.
    });
    // init:
  }
  // plugin.add.
});
