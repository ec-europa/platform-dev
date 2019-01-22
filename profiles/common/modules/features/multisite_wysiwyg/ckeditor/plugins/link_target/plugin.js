/**
 * @file
 * CKEditor Link Target code.
 */

(function ($) {
  CKEDITOR.plugins.add("multisite_wysiwyg_link_target", {
    init: function (editor) {
      CKEDITOR.on("dialogDefinition", function (e) {
        if ((e.editor != editor) || (e.data.name != 'link')) {
          return;
        }

        // Overrides definition.
        var definition = e.data.definition;

        // Removing the "popup window" option of target select
        // in the target tab.
        var targetTab = definition.getContents("target");
        if ((targetTab != null) && (typeof targetTab.add == 'function')) {
          var linkTypeItems = targetTab.get('linkTargetType').items;
          if (linkTypeItems.length > 0) {
            var itemsToRemove = ["<popup window>", "<frame>"];
            var finalArray = linkTypeItems.filter(item => !itemsToRemove.includes(item[0]));
            targetTab.get('linkTargetType').items = finalArray;
           }

          // Override the onOk event to display custom elements like the
          // "hreflang" attribute.
          definition.onOk = CKEDITOR.tools.override(definition.onOk, function (original) {
            return function () {
              original.call(this);
              var targetValue = this.getValueOf("advanced", "multisite_wysiwyg_link_target");
            };
          });
        }
      });
    }
  });
})(jQuery);
