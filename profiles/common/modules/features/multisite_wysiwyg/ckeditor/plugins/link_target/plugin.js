/**
 * @file
 * CKEditor Link hreflang code.
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
          var linkTypeItems = targetTab.get( 'linkTargetType' ).items;
          console.log(linkTypeItems);
          if ( linkTypeItems.length > 0 ) {
            for (var i = 0; i < linkTypeItems.length; i++) {
               if (linkTypeItems[i][0] == "<popup window>") {
                 linkTypeItems.splice(i, 1);
                 break;
               }
             }
           }
        }
       
      });
    }
  });
})(jQuery);
