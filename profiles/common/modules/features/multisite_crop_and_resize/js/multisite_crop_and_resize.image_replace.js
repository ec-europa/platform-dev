/**
 * @file
 * Javascript file for image replacement.
 */

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
})(jQuery);
