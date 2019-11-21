
/**
 * @file
 * afterPasteFromWord
 */
        
(function ($) {
  Drupal.behaviors.multisite_wysiwyg_paste_from_word = {
    attach: function () {
      $(function () {
        for (var i in CKEDITOR.instances) {
          CKEDITOR.instances[i].on('paste', function(evt) {
            // Create a standalone filter
            var rules = 'em strong abrr img cite blockquote code ul ol li dl dt td br p; a[href]';
            var filter = new CKEDITOR.filter(rules),
            // Parse the HTML string to a pseudo-DOM structure.
            fragment = CKEDITOR.htmlParser.fragment.fromHtml(evt.data.dataValue),
            writer = new CKEDITOR.htmlParser.basicWriter();
            filter.applyTo(fragment);
            fragment.writeHtml(writer);
            evt.data.dataValue = writer.getHtml();
        });
          
          CKEDITOR.instances[i].on('afterCommandExec', function (event) {
            //console.log(event.data.name);
            //this.filter.disabled = true;
          });
        }
      });
    }

  }
})(jQuery);

