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
        }
      });
    }
  });
})(jQuery);
