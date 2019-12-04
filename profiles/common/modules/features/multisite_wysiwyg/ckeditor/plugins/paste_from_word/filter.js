/**
 * @file
 * AfterPasteFromWord.
 */

(function ($) {
  Drupal.behaviors.multisite_wysiwyg_paste_from_word = {
    attach: function () {
      $(function () {
        var activeFilter = [];

        for (var i in CKEDITOR.instances) {
          CKEDITOR.instances[i].on('paste', function (evt) {
            if (activeFilter[i] !== true) {
              return;
            }

            // Create a standalone filter.
            var rules = 'h2 h3 h4 h5 h6 em strong abrr cite blockquote code ul ol li dl dt table tr td br; a[href]; img[src, alt]; p[align]';
            var filter = new CKEDITOR.filter(rules),
            // Parse the HTML string to a pseudo-DOM structure.
            fragment = CKEDITOR.htmlParser.fragment.fromHtml(evt.data.dataValue),
            writer = new CKEDITOR.htmlParser.basicWriter();
            // Some needed transformations.
            filter.addTransformations([
              [
                {
                  element: 'b',
                  right: function (el, tools) {
                    tools.transform(el, 'strong');
                  }
                }
              ],
              [
                {
                  element: 'i',
                  right: function (el, tools) {
                    tools.transform(el, 'em');
                  }
                }
              ]
            ]);

            filter.applyTo(fragment);
            fragment.writeHtml(writer);
            evt.data.dataValue = writer.getHtml();
            activeFilter[i] = false;
          });

          // Enable filer when button is pressed.
          CKEDITOR.instances[i].on('beforeCommandExec', function (event) {
            if (event.data.name === 'pastefromword') {
              activeFilter[i] = true;
            }
          });

          // Remove browser incompatibility notice.
          CKEDITOR.instances[i].on('instanceReady', function (ev) {
            ev.editor.lang.clipboard.pasteNotification = "Press %1 to paste.";
          });
        }
      });
    }

  }
})(jQuery);
