/**
 * @file
 * JS code customizing CKEditor LITE plugin.
 */

(function ($) {
  Drupal.behaviors.nexteuropa_trackedchanges_ckeditor = {
    attach: function () {
      $(function () {
        function filterTracked(event) {
          var editor = event.editor;
          var editorContent = editor.getData();
          var trackedChanges = editorContent.search('(<span[^>]+class\s*=\s*(")ice-[^>]*>)[^<]*(</span>)');

          if (trackedChanges >= 0) {
            $('select.filter-list option').each(function (index, option) {
              if (Drupal.settings.tracking_profiles.indexOf(option.value) === -1) {
                $('select.filter-list option').eq(index).prop('disabled', 'disabled');
              }
            });
          }
        }

        for (var i in CKEDITOR.instances) {
          CKEDITOR.instances[i].on('configLoaded', function (event) {
            filterTracked(event);
          });

          CKEDITOR.instances[i].on('change', function (event) {
            filterTracked(event);
          });

          CKEDITOR.instances[i].on('afterCommandExec', function (event) {
            filterTracked(event);
          });
        }
      });
    }

  }
})(jQuery);
