/**
* @file
* JS code customizing CKEditor LITE plugin
*/
(function ($) {
  Drupal.behaviors.nexteuropa_trackedchanges = {
    attach: function () {
      $(function() {
        for(var i in CKEDITOR.instances) {
          CKEDITOR.instances[i].on('configLoaded', function(event) {
            var editor = event.editor;
            var editorContent = editor.getData();
            var trackedChanges = editorContent.search('(<span[^>]+class\s*=\s*(")ice-[^>]*>)[^<]*(</span>)');
            if (trackedChanges >= 0) {
              editor.config.lite.isTracking = true;
            }
          });
        }
      });
    }

  }
})(jQuery);
