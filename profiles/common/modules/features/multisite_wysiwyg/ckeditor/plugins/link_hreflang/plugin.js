/**
 * @file
 * CKEditor Link hreflang code.
 */

(function ($) {
  CKEDITOR.plugins.add("multisite_wysiwyg_link_hreflang", {
    init: function (editor) {
      CKEDITOR.on("dialogDefinition", function (e) {
        if ((e.editor != editor) || (e.data.name != 'link')) {
          return;
        }

        // Overrides definition.
        var definition = e.data.definition;

        // Removing the "lang" input and adding the "hreflang" one
        // in the advanced tab.
        var advancedTab = definition.getContents("advanced");
        if ((advancedTab != null) && (typeof advancedTab.add == 'function')) {
          // Removing "lang" input.
          advancedTab.remove("advLangCode");

          // Adding "hreflang" input.
          advancedTab.add({
            type: "text",
            id: "multisite_wysiwyg_link_hreflang",
            label: Drupal.t("Language code (hreflang)"),
            title: Drupal.t("The language of the linked document (2 characters code, e.g. 'en')"),
            width: "100px",
            setup: function () {
              // Gets "hreflang" attribute from the selected hyperlink value and initialise the
              // input field.
              var definedLink = CKEDITOR.plugins.link.getSelectedLink(editor);
              var setHreflang = '';
              if (definedLink) {
                setHreflang = definedLink.getAttribute("hreflang");
              }
              this.setValue(setHreflang || '');
            },
          });

          // Override the onOk event to display custom elements like the
          // "hreflang" attribute.
          definition.onOk = CKEDITOR.tools.override(definition.onOk, function (original) {
            return function () {
              original.call(this);
              var hrefLangValue = this.getValueOf("advanced", "multisite_wysiwyg_link_hreflang");
              if (hrefLangValue) {
                CKEDITOR.plugins.link.getSelectedLink(editor).setAttribute("hreflang", hrefLangValue);
              }
              else {
                CKEDITOR.plugins.link.getSelectedLink(editor).removeAttribute("hreflang");
              }
            };
          });
        }
      });
    }
  });
})(jQuery);
