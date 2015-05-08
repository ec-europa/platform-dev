(function ($) {
  Drupal.media_crop = Drupal.media_crop || {};

  Drupal.media_crop.replaceImage = function (replaceData) {
    var id = replaceData.id;
    var options = replaceData.options;
    var token = replaceData.token;
    var fid = replaceData.fid;

    $.ajax({
      cache: false,
      success: function (data) {
        var mciid = '%7BMCIID%7D';
        var img = $('#' + id);
        if (img.length === 0) {
          $('iframe').each(function () {
            var iimg = $(this).contents().find('#' + id);
            if (iimg.length > 0) {
              img = iimg;
            }
          });
        }
        var src = (img.attr('src') || '');
        var dataCkeSavedSrc = (img.attr('data-cke-saved-src') || '');
        var cls = (img.attr('class') || '');
        img.attr('src', src.replace(mciid, data));
        img.attr('data-cke-saved-src', dataCkeSavedSrc.replace(mciid, data));
        img.attr('class', cls.replace(mciid, data));
        img.addClass('mciid-' + data);
      },
      error: function (jqXHR, textStatus, errorThrown) {
        if (parent.console && parent.console.log) {
          parent.console.log(jqXHR, textStatus, errorThrown);
        }
      },
      type: 'POST',
      url: Drupal.settings.basePath + 'media_crop/' +
           options.media_crop_image_style + '/' +
           fid + '/' +
           token,
      data: {
        media_crop: {
          angle: options.media_crop_rotate,
          w: options.media_crop_w,
          h: options.media_crop_h,
          x: options.media_crop_x,
          y: options.media_crop_y,
          scale_w: options.media_crop_scale_w,
          scale_h: options.media_crop_scale_h,
        }
      }
    });
  };


  /* PATCHING THE MODULE media-7.x-2.0-alpha2 */
  /**
   * Replaces media tokens with the placeholders for html editing.
   * @param content
   */
  Drupal.media.filter.replaceTokenWithPlaceholder= function(content) {
    var tagmap = Drupal.media.filter.ensure_tagmap(),
      matches = content.match(/\[\[.*?\]\]/g),
      media_definition;

    if (matches) {
      var i = 1;
      for (var index in matches) {
        var macro = matches[index];

        if (tagmap[macro]) {
          var media_json = macro.replace('[[', '').replace(']]', '');
          // Make sure that the media JSON is valid.
          try {
            media_definition = JSON.parse(media_json);
          }
          catch (err) {
            media_definition = null;
          }
          if (media_definition) {
            // Apply attributes.
            var element = Drupal.media.filter.create_element(tagmap[macro], media_definition);
            var markup = Drupal.media.filter.outerHTML(element);

            content = content.replace(macro, Drupal.media.filter.getWrapperStart(i) + markup + Drupal.media.filter.getWrapperEnd(i));
          }
        }
        i++;
      }
    }
    return content;
  };

  /**
   * Replaces the placeholders for html editing with the media tokens to store.
   * @param content
   */
  Drupal.media.filter.replacePlaceholderWithToken= function(content) {
    var tagmap =  Drupal.media.filter.ensure_tagmap(),
      markup,
      macro;

    // Finds the media-element class.
    var classRegex = 'class=[\'"][^\'"]*?media-element';
    // Image tag with the media-element class.
    var regex = '<img[^>]+' + classRegex + '[^>]*?>';
    // Or a span with the media-element class (used for documents).
    // \S\s catches any character, including a linebreak; JavaScript does not
    // have a dotall flag.
    regex += '|<span[^>]+' + classRegex + '[^>]*?>[\\S\\s]+?</span>';
    var matches = content.match(RegExp(regex, 'gi'));

    if (matches) {
      for (i = 0; i < matches.length; i++) {
        markup = matches[i];
        macro = Drupal.media.filter.create_macro($(markup));
        tagmap[macro] = markup;
        content = content.replace(markup, macro);
      }
    }
    return content;
  };
})(jQuery);
