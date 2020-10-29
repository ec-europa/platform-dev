/**
 * @file
 * CKEditor Link target alter.
 */

// Alter the options of the link dialog plugin.
(function () {
    CKEDITOR.on('dialogDefinition', function (ev) {
        // Take the dialog name and its definition from the event data.
        var dialogName = ev.data.name;
        var dialogDefinition = ev.data.definition;
        // Check the it is the link definition.
        if (dialogName == 'link') {
          var targetTab = dialogDefinition.getContents("target");
          /*
            Remove options from the default list defined on the link plugin.
            var removeOptions = ["frame", "popup", "notSet", "_blank", "_top", "_self", "_parent"];
            */
          var removeOptions = ["popup"];
          var i;
          var optionsToKeep = [];
          for (i = targetTab.elements[0].children[0].items.length - 1; i >= 0; i--) {
              // Remove options from the target select.
              if (removeOptions.indexOf(targetTab.elements[0].children[0].items[i][1]) !== -1) {
                delete targetTab.elements[0].children[0].items[i];
              }
              else {
                optionsToKeep.unshift(targetTab.elements[0].children[0].items[i]);
              }
          }
          targetTab.elements[0].children[0].items = optionsToKeep;
          // NEPT-2613: Block FTP protocol from the wysiwyg filters.
          // The blocking is also added on the server side using variable "filter_allowed_protocols".
          var ftpIndex = false;
          for (i = dialogDefinition.getContents('info').get('protocol')['items'].length - 1; i >= 0; i--) {
            ftpIndex = dialogDefinition.getContents('info').get('protocol')['items'][i].indexOf("ftp://");

            if (ftpIndex !== -1) {
              dialogDefinition.getContents('info').get('protocol')['items'].splice(i, 1);
            }
          }
        }
    });
})();
