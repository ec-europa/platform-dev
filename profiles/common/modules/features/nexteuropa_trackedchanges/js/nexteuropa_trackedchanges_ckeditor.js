/**
 * @file
 * JS code customizing CKEditor LITE plugin.
 */

(function ($) {
  Drupal.behaviors.nexteuropa_trackedchanges_ckeditor = {
    attach: function () {
      $(function () {
        for (var i in CKEDITOR.instances) {
          CKEDITOR.instances[i].on('configLoaded', function (event) {
            var editor = event.editor;
            var editorContent = editor.getData();
            var trackedChanges = editorContent.search('(<span[^>]+class\s*=\s*(")ice-[^>]*>)[^<]*(</span>)');
            if (trackedChanges >= 0) {
              $('select.filter-list').prop('disabled', 'disabled');
            }
          });

          CKEDITOR.instances[i].on('change', function (event) {
            var editor = event.editor;
            var editorContent = editor.getData();
            var trackedChanges = editorContent.search('(<span[^>]+class\s*=\s*(")ice-[^>]*>)[^<]*(</span>)');
            if (trackedChanges >= 0) {
              $('select.filter-list').prop('disabled', 'disabled');
            }
          });

          CKEDITOR.instances[i].on('afterCommandExec', function (event) {
            var editor = event.editor;
            var editorContent = editor.getData();
            var trackedChanges = editorContent.search('(<span[^>]+class\s*=\s*(")ice-[^>]*>)[^<]*(</span>)');
            if (trackedChanges === -1) {
              $('select.filter-list').removeProp('disabled');
            }
          });
        }
      });
    }

  }
})(jQuery);
