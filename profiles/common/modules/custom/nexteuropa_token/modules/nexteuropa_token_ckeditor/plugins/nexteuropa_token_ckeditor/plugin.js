/**
 * @file
 * CKEDITOR plugin file.
 */

(function($) {

  /**
   * NextEuropa Token CKEditor behavior.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.nexteuropa_token_ckeditor = {
    attach: function (context) {
      Drupal.nexteuropa_token_ckeditor = Drupal.nexteuropa_token_ckeditor || {};
      var editor_id = Drupal.nexteuropa_token_ckeditor.current_editor_id || '';

      if (editor_id in Drupal.nexteuropa_token_ckeditor) {
        var editor = Drupal.nexteuropa_token_ckeditor[editor_id];
        var content = context[0];

        $(content).find('.token-ckeditor-tips-toggle').once('token-ckeditor-tips-toggle', function() {
          $(this).click(function (e) {
            e.preventDefault();
            $('.token-ckeditor-tips-container').toggle();
          });
        });

        $(content).find('.token-ckeditor-selection').once('token-ckeditor-selection', function() {
          $(this).click(function (e) {
            e.preventDefault();
            var token = $(this).attr('token-ckeditor-token');
            var type = $(this).attr('token-ckeditor-type');
            if (type != 'url') {
              token = token + '{' + Drupal.t('@label as @mode', {'@label': $(this).attr('token-ckeditor-label'), '@mode': $(this).text()}) + '}';

              if (!Drupal.nexteuropa_token_ckeditor.filter.isBrowserSpaceSafe()) {
                token = '&nbsp;' + token + '&nbsp;';
              }
            }
            editor.insertHtml(token);
            CKEDITOR.dialog.getCurrent().hide();
          });
        });
      }
    }
  };

  CKEDITOR.plugins.add('nexteuropa_token_ckeditor', {
    init: function(editor) {

      CKEDITOR.dialog.add('nexteuropa_token_ckeditor_dialog', function() {
        return {
          title: Drupal.t('Insert internal content'),
          minWidth: 750,
          minHeight: 300,
          contents: [
            {
              id: 'info',
              label: Drupal.t('Insert internal links'),
              title: Drupal.t('Insert internal links'),
              elements: [
                {
                  id: 'nexteuropa_token_ckeditor',
                  type: 'html',
                  html: '<div class="nexteuropa-token-dialog-container"></div>'
                }
              ]
            },
            {
              id: 'info-bean',
              label: Drupal.t('Insert internal blocks'),
              title: Drupal.t('Insert internal blocks'),
              elements: [
                {
                  id: 'nexteuropa_token_bean_ckeditor',
                  type: 'html',
                  html: '<div class="nexteuropa-token-bean-dialog-container"></div>'
                }
              ]
            }
          ],
          onShow:function () {
            $('a.cke_dialog_tab').removeClass('cke_dialog_tab_disabled');
          },
          onLoad: function() {
            // Get CKEditor object.
            var editor = this.getParentEditor();

            // Store current editor id. It will be refreshed every time a new dialog is open.
            Drupal.nexteuropa_token_ckeditor = Drupal.nexteuropa_token_ckeditor || {};
            Drupal.nexteuropa_token_ckeditor.current_editor_id = editor.id;

            if (!(editor.id in Drupal.nexteuropa_token_ckeditor)) {
              // Store editor reference in global Drupal object since it will be accessed from within
              // Drupal.behaviors.nexteuropa_token_ckeditor defined in nexteuropa_token_ckeditor.js.
              Drupal.nexteuropa_token_ckeditor[editor.id] = editor;

              // Get dialog container ID.
              var id = 'nexteuropa-token-' + editor.id + '-dialog-container';

              // Get dialog DOM object.
              var content = $(this.getElement('info', 'nexteuropa_token_ckeditor').$);
              $('.nexteuropa-token-dialog-container', content).attr('id', id);

              var ajax_settings = {
                url: Drupal.settings.basePath + 'nexteuropa/token-ckeditor/' + id,
                event: 'dialog.nexteuropa-token-ckeditor',
                method: 'html'
              };
              Drupal.ajax[id] = new Drupal.ajax(id, content[0], ajax_settings);
              content.trigger(ajax_settings.event);

              // Get dialog container ID.
              var id = 'nexteuropa-token-bean-' + editor.id + '-dialog-container';

              // Get dialog DOM object.
              var content = $(this.getElement('info', 'nexteuropa_token_bean_ckeditor').$);
              $('.nexteuropa-token-bean-dialog-container', content).attr('id', id);

              var ajax_settings = {
                url: Drupal.settings.basePath + 'nexteuropa/token-bean-ckeditor/' + id,
                event: 'dialog.nexteuropa-token-bean-ckeditor',
                method: 'html'
              };
              Drupal.ajax[id] = new Drupal.ajax(id, content[0], ajax_settings);
              content.trigger(ajax_settings.event);
            }
          },
          buttons: [CKEDITOR.dialog.okButton]
        };
      });

      // Register a command with CKeditor to launch the dialog box.
      editor.addCommand('NextEuropaTokenInsert', new CKEDITOR.dialogCommand('nexteuropa_token_ckeditor_dialog'));

      // Add a button to the CKeditor that executes a CKeditor command.
      editor.ui.addButton('NextEuropaToken', {
        label: Drupal.t('Insert internal content'),
        command: 'NextEuropaTokenInsert',
        icon: this.path + 'plugin.png'
      });

      // Add plugin CSS.
      editor.addContentsCss(this.path + 'plugin.css');

      // Define DTD rules for placeholder tag "nexteuropatoken".
      CKEDITOR.dtd.$blockLimit['nexteuropatoken'] = 1;
      CKEDITOR.dtd.$inline['nexteuropatoken'] = 1;
      CKEDITOR.dtd.$nonEditable['nexteuropatoken'] = 1;
      // Set tags in which the placeholder tag can be included.
      // Note that CKEditor sets already some of them by default like for
      // "p", "div".
      CKEDITOR.dtd['td']['nexteuropatoken'] = 1;
      CKEDITOR.dtd['li']['nexteuropatoken'] = 1;
      if (parseFloat(CKEDITOR.version) >= 4.1) {
        // Register allowed tag for advanced filtering.
        editor.filter.allow('nexteuropatoken[!*]', 'nexteuropatoken', true);
        // Objects should be selected as a whole in the editor.
        CKEDITOR.dtd.$object['nexteuropatoken'] = 1;
      }

      // Ensure tokens instead the html element is saved.
      editor.on('setData', function(event) {
        var content = event.data.dataValue;
        event.data.dataValue = Drupal.nexteuropa_token_ckeditor.filter.replaceTokenWithPlaceholder(content, false);
      });

      // Replace tokens with WYSIWYG placeholders.
      editor.on('getData', function(event) {
        var content = event.data.dataValue;
        event.data.dataValue = Drupal.nexteuropa_token_ckeditor.filter.replacePlaceholderWithToken(content);
      });

      // Replace tokens with WYSIWYG placeholders.
      editor.on('insertHtml', function(event) {
        var content = event.data.dataValue;
        event.data.dataValue = Drupal.nexteuropa_token_ckeditor.filter.replaceTokenWithPlaceholder(content, true);
      });
    }
  });

  // Utility class.
  Drupal.nexteuropa_token_ckeditor = Drupal.nexteuropa_token_ckeditor || {};
  Drupal.nexteuropa_token_ckeditor.filter = {

    /**
     * Regular expressions matching tokens exposed by NextEuropa Token module.
     */
    regex: {
      parse_token: /\[(\w*\:\d*\:(view-mode\:\w*|link))\]\{(.*)\}/,
      parse_placeholder: /<nexteuropatoken.*token="(.*?)".*>(.*)<\/nexteuropatoken>/,
      get_tokens: /\[\w*\:\d*\:(view-mode\:\w*|link)\]{.*?}/g,
      get_placeholders: /<nexteuropatoken.*?<\/nexteuropatoken>/g
    },

    /**
     * Get HTML placeholder give a token and a label.
     *
     * @param token
     *    Token string, followed by its label enclosed in curly brackets.
     *    For example: [node:1:view-mode:full]{Title}.
     *
     * @returns {string}
     */
    getPlaceholderFromToken: function(token) {
      var matches = token.match(this.regex.parse_token);
      return (matches) ? '<nexteuropatoken contenteditable="false" token="' + matches[1] + '">' + matches[3] + '</nexteuropatoken>' : '';
    },

    /**
     * Get token given an HTML placeholder.
     *
     * @param placeholder
     *    Placeholder string.
     *
     * @returns {string}
     */
    getTokenFromPlaceholder: function(placeholder) {
      var matches = placeholder.match(this.regex.parse_placeholder);
      return (matches) ? '[' + matches[1] + ']{' + matches[2] + '}' : '';
    },

    /**
     * Replaces tokens with placeholders.
     *
     * @param content
     *    Text coming from WYSIWYG.
     * @param insertHtml
     *    Check if the calling event is insertHtml (true) or not (false).
     *
     * @returns {string}
     *   Text with placeholders.
     */
    replaceTokenWithPlaceholder: function(content, isInsertHtml) {
      var matches = content.match(this.regex.get_tokens);
      if (matches) {
        for (var i = 0; i < matches.length; i++) {
          var token = matches[i];
          // Let's replace the ' ' by &nbsp; for placeholder display.
          // We avoid to do that during the insertHtml event because the
          // "content" only contains the just inserted tag.
          // Then, we leave this process while saving the ckeditor data.
          if (!this.isBrowserSpaceSafe() && !isInsertHtml) {
            content = content.replace(token + ' ', token + '&nbsp;');
            content = content.replace(' ' + token, '&nbsp;' + token);
          }
          content = content.replace(token, this.getPlaceholderFromToken(token));
        }
      }
      return content;
    },

    /**
     * Replaces placeholders with tokens.
     *
     * @param content
     *    Text coming from WYSIWYG.
     *
     * @returns {string}
     *   Text with tokens.
     */
    replacePlaceholderWithToken: function(content) {
      if (!this.isBrowserSpaceSafe()) {
        // If the browser does manage very well the white space, clean them
        // before continuing the process.
        content = Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInPlaceholders(content);
      }
      var matches = content.match(this.regex.get_placeholders);
      if (matches) {
        for (var i = 0; i < matches.length; i++) {
          var placeholder = matches[i];
          content = content.replace(placeholder, this.getTokenFromPlaceholder(placeholder));
        }
      }
      return content;
    },

    /**
     * Check if the used browser managed correctly the white space.
     *
     * For more information, see https://dev.ckeditor.com/ticket/12199.
     *
     * @return {boolean}
     *   true if space safe.
     */
    isBrowserSpaceSafe: function () {
      return (!CKEDITOR.env.gecko && !CKEDITOR.env.ie);
    },
  };

  // Utility class allowing to clean HTML code before saving WYSIWYG content.
  // It is used when the used browser does not support space correctly.
  // See https://dev.ckeditor.com/ticket/12199.
  Drupal.nexteuropa_token_ckeditor.parser = {
    /**
     * Clean a HTML element of extra spaces around "nexteuropatoken" tags.
     *
     * @param element
     *   The HTML element to clean
     *
     * @return {CKEDITOR.htmlParser.element}
     *   The cleaned element.
     */
    cleanExtraSpaceInElement: function(element) {
      if ((typeof element.children == 'undefined') || (element.children.length == 0)) {
        return element;
      }

      // Clean first extra space of the HTML block.
      if (this.isWhiteSpace(element.children[0])) {
        element.children.splice(0, 1);
      }
      // Clean last extra space of the HTML block.
      if (this.isWhiteSpace(element.children[element.children.length - 1])) {
        element.children.splice((element.children.length - 1), 1);
      }

      // Clean extra spaces around "nexteuropatoken" tags in the rest of the element.
      var i = element.children.length;
      while (i--) {
        if (element.children[i]['name'] != 'nexteuropatoken') {
          continue;
        }
        // If the "nexteuropatoken" tag is alnone, no space has been detected.
        // The loop can stop.
        if ((typeof element.children[i - 1] == 'undefined') && (typeof element.children[i + 1] == 'undefined')) {
          break;
        }

        // Clean potential extra space after the "nexteuropatoken" tag.
        if ((typeof element.children[i + 1] != 'undefined')) {
          var secondElementAfterTag = (typeof element.children[i + 2] != 'undefined') ? element.children[i + 2] : '';
          var cleanedAfterTagElement = this.cleanExtraWhiteSpaceAfterTag(element.children[i + 1], secondElementAfterTag);

          if (cleanedAfterTagElement.length != 0) {
            element.children[i + 1] = cleanedAfterTagElement;
          }
          else {
            element.children.splice((i + 1), 2, ' ');
          }
        }

        // Clean potential extra space before the internal link tag.
        if ((typeof element.children[i - 1] != 'undefined')) {
          var secondElementBeforeTag = (typeof element.children[i + 2] != 'undefined') ? element.children[i + 2] : '';
          var cleanedBeforeTagElement = this.cleanExtraWhiteSpaceBeforeTag(element.children[i - 1], secondElementBeforeTag);

          if (cleanedBeforeTagElement.length != 0) {
            element.children[i - 1] = cleanedBeforeTagElement;
          }
          else {
            element.children.splice((i - 1), 2, ' ');
          }
        }
      }
      return element;
    },

    /**
     * Cleans a HTML content containing "nexteuropatoken" from extra space.
     *
     * @param content
     *   The HMTL content to clean.
     *
     * @return {string}
     *   The cleaned content.
     */
    cleanExtraSpaceInPlaceholders: function(content) {
      var filter = new CKEDITOR.htmlParser.filter({
        elements: {
          address: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          article: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          aside: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          blockquote: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          dd: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          div: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          dt: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          fieldset: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          figcaption: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          footer: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          form: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          h1: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          h2: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          h3: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          h4: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          h5: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          h6: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          header: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          li: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          main: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          nav: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          ol: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          p: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          pre: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          section: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          td: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
          th: function(element) {
            return Drupal.nexteuropa_token_ckeditor.parser.cleanExtraSpaceInElement(element);
          },
        }
      });

      var fragment = CKEDITOR.htmlParser.fragment.fromHtml(content),
        writer = new CKEDITOR.htmlParser.basicWriter();
      filter.applyTo(fragment);
      fragment.writeHtml(writer);
      return writer.getHtml();
    },

    /**
     * Cleans the element before a HTML tag from extra white space.
     *
     * @param elementBeforeTag
     *   CKEDITOR.htmlParser.element appearing directly before the tag.
     * @param secondElementBeforeTag
     *   the second CKEDITOR.htmlParser.element appearing directly before
     *   the tag.
     *
     * @return {CKEDITOR.htmlParser.element|string}
     *   The tag element cleaned from any extra white space; or an empty string
     *   if the whole element must be removed.
     */
    cleanExtraWhiteSpaceBeforeTag: function(elementBeforeTag, secondElementBeforeTag) {
      // If the element just before the tag is not a text (value is
      // "undefined"), there is no extra space before it.
      if ((typeof elementBeforeTag == 'undefined') && (typeof elementBeforeTag['value'] == 'undefined')) {
        return '';
      }

      var firstValue = elementBeforeTag;
      var secondValue = (typeof secondElementBeforeTag != 'undefined') ? secondElementBeforeTag : '';
      if (this.isWhiteSpace(firstValue) && this.isWhiteSpace(secondValue)) {
        return '';
      }

      // Working on both element did not return results, lt's focus on the first one.
      elementBeforeTag['value'] = firstValue['value'].replace(/(\s&nbsp;|\s\s|&nbsp;\s)$/, ' ');
      return elementBeforeTag;
    },

    /**
     * Cleans the element after a HTML tag from extra white space.
     *
     * @param elementAfterTag
     *   CKEDITOR.htmlParser.element appearing directly after the tag.
     * @param secondElementAfterTag
     *   the second CKEDITOR.htmlParser.element appearing directly after
     *   the tag.
     *
     * @return {CKEDITOR.htmlParser.element|string}
     *   The tag element cleaned from any extra white space; or an empty string
     *   if the whole element must be removed.
     */
    cleanExtraWhiteSpaceAfterTag: function(elementAfterTag, secondElementAfterTag) {
      // If the element just after the tag is not a text (value is
      // "undefined"), there is no extra space before it.
      if ((typeof elementAfterTag == 'undefined') && (typeof elementAfterTag['value'] == 'undefined')) {
        return '';
      }

      var firstValue = elementAfterTag;
      var secondValue = (typeof secondElementAfterTag != 'undefined') ? secondElementAfterTag : '';
      if (this.isWhiteSpace(firstValue) && this.isWhiteSpace(secondValue)) {
        return '';
      }

      // Working on both element did not return results, lt's focus on the first one.
      elementAfterTag['value'] = firstValue['value'].replace(/^(\s&nbsp;|\s\s|&nbsp;\s)/, ' ');
      return elementAfterTag;
    },

    /**
     * Check if a CKEDITOR.htmlParser.element is a white space.
     *
     * @param element
     *   The CKEDITOR.htmlParser.element to check.
     *
     * @return {boolean}
     *   true if the element has a ' ' or '&nbsps' value.
     */
    isWhiteSpace: function(element) {
      if (typeof element == 'undefined') {
        return false;
      }
      var value = element['value'];
      return ((value === ' ' || value == '&nbsp;'))
    },

  }
})(jQuery);
