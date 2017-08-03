/**
 * @file
 * Javascript for autosave.
 */

(function ($) {

  var showingRestoreCommand;

  Drupal.behaviors.autosave = {};
  Drupal.behaviors.autosave.attach = function (context, settings) {
    var autosaveSettings;

    if ($('#autosave-status').size() == 0) {
      // Add a div for us to put messages in.
      $('body').append('<div id="autosave-status"><span id="status"></span></div>');
    }

    autosaveSettings = settings.autosave;

    $('#' + autosaveSettings.formid).not('.autosave-processed').addClass('autosave-processed').autosave({
      interval: autosaveSettings.period * 1000,
      // Time in ms.
      url: autosaveSettings.url,
      setup: function (e, o) {
        var ignoreLink, restoreLink, callbackPath;

        // If there is a saved form for this user, let him know so he can reload it
        // if desired.
        if (autosaveSettings.savedTimestamp) {
          showingRestoreCommand = true;

          ignoreLink = $('<a>').attr('href', '#').attr('title', Drupal.t('Ignore/Delete saved form')).html(Drupal.t('Ignore')).click(function (e) {
            Drupal.behaviors.autosave.hideMessage();
            return false;
          });

          callbackPath = Drupal.settings.basePath + 'autosave/restore/' + autosaveSettings.formid + '/' + autosaveSettings.savedTimestamp + '/' + autosaveSettings.formToken + '/' + autosaveSettings.theme;
          restoreLink = $('<a>').attr('href', callbackPath).addClass('use-ajax').attr('title', Drupal.t('Restore saved form')).html(Drupal.t('Restore')).click(function (e) {
            Drupal.behaviors.autosave.hideMessage();
          });

          Drupal.behaviors.autosave.displayMessage(Drupal.t('This form was autosaved on ' + autosaveSettings.savedDate), {
            // Show the message for 30 seconds, or hide it when the user starts
            // editing the form.
            timeout: 30000,
            operations: '<span id="operations">',
            ignore: ignoreLink,
            restore: restoreLink
          });
        }

        // Wire up TinyMCE to autosave.
        if (typeof(tinymce) !== 'undefined') {
          setInterval(function () {
            // Save text data from the tinymce area back to the original form element.
            // Once it's in the original form element, autosave will notice it
            // and do what it needs to do.
            // Note: There seems to be a bug where after a form is restored,
            // everything works fine but tinyMCE keeps reporting an undefined
            // error internally.  As its code is compressed I have absolutely no
            // way to debug this.  If you can figure it out, please file a patch.
            var triggers = Drupal.settings.wysiwyg.triggers;
            var id;
            var field;
            for (id in triggers) {
              field = triggers[id].field;
              $('#' + field).val(tinymce.get(field).getContent());
            }
          }, autosaveSettings.period * 1000);
        }

        // Code added for support the CKEDITOR.
        if (typeof(CKEDITOR) !== 'undefined') {
          setInterval(function () {
            var id;
            for (id in CKEDITOR.instances) {
              var instance = CKEDITOR.instances[id];
              instance.updateElement();
            }
          }, autosaveSettings.period * 1000);
        }

      },
      save: function (e, o) {
        if (!autosaveSettings.hidden) {
          Drupal.behaviors.autosave.displayMessage(Drupal.t('Form autosaved.'));
        }
      },
      dirty: function (e, o) {
        if (showingRestoreCommand) {
          Drupal.behaviors.autosave.hideMessage();
        }
      }
    });
  };

  Drupal.behaviors.autosave.hideMessage = function () {
    $('#autosave-status').fadeOut('slow');
  };

  Drupal.behaviors.autosave.displayMessage = function (message, settings) {
    settings = settings || {};
    settings.timeout = settings.timeout || 3000;
    // Settings = $.extend({}, {timeout: 3000, extra: ''}, settings);.
    var status = $('#autosave-status');
    status.empty().append('<span id="status">' + message + '</span>');
    if (settings.operations) {
      status.append(settings.operations).append(settings.ignore).append(settings.restore);
    }
    Drupal.attachBehaviors(status);

    $('#autosave-status').slideDown();
    setTimeout(Drupal.behaviors.autosave.hideMessage, settings.timeout);
  };

})(jQuery);
