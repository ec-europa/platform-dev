/**
 * @file
 * Javascript file for crop and resize.
 */

(function ($) {
  Drupal.media_crop = Drupal.media_crop || {};
  Drupal.media_crop.actions = Drupal.media_crop.actions || {};

  Drupal.behaviors.media_crop = {
    attach: function (context) {

      // Process special elements.
      Drupal.media_crop.processSpecialSelect(context);

      var freeze = false;

      var container = $('div.media-item', context);
      var jq = parent.jQuery;

      var origWidth;
      var origHeight;
      var imageScale;

      var cropWidth;
      var cropHeight;
      var cropEnabled = false;

      var activeCroppingInstance;

      var initialImageStyle = ($('select[name=image_style]', context).val());
      var imageStyleSafe = Boolean(Drupal.settings.media_crop.styles[($('select[name=image_style]', context).val())] && Drupal.settings.media_crop.styles[($('select[name=image_style]', context).val())].safe);
      var imageStyleHasCrop = (imageStyleSafe && (Drupal.settings.media_crop.styles[($('select[name=image_style]', context).val())].crop || false));
      var aspectRatioUnlocked = true;

      jq('iframe#mediaStyleSelector').height('900px');

      var toggleImageStyleWarning = function () {
        if (!imageStyleSafe) {
          $('.image-style-description').show();
        }
        else {
          $('.image-style-description').hide();
        }
      };

      toggleImageStyleWarning();

      var safeImageStyleCropSettings = {
        x: 0,
        y: 0,
        w: 0,
        h: 0
      };

      var getImageScale = Drupal.media_crop.actions.getImageScale;
      var recalculateScale = Drupal.media_crop.actions.recalculateScale;
      var setOrigWidth = Drupal.media_crop.actions.setOrigWidth;
      var setOrigHeight = Drupal.media_crop.actions.setOrigHeight;
      var setCropWidth = Drupal.media_crop.actions.setCropWidth;
      var setCropHeight = Drupal.media_crop.actions.setCropHeight;
      var setScaleWidth = Drupal.media_crop.actions.setScaleWidth;
      var setScaleHeight = Drupal.media_crop.actions.setScaleHeight;
      var resetScale = Drupal.media_crop.actions.resetScale;

      var calculateAnchors = function (anchor, orig, crop) {
        var ret = anchor;
        switch (anchor) {
          case "top":
          case "left":
            ret = 0;
            break;

          case "bottom":
          case "right":
            ret = orig - crop;
            break;

          case "center":
            ret = (orig / 2) - (crop / 2);
            break;
        }

        return ret;
      };

      var areaSelectOptions = {
        instance: true,
        handles: true,
        onSelectChange: function (img, selection) {
          recalculateScale(selection);
          $('input[name=x]', context).val(selection.x1);
          $('input[name=y]', context).val(selection.y1);
          setCropWidth(selection.width);
          setCropHeight(selection.height);
          updateUICropDimensions(selection.width, selection.height);
          toggleCropWarning();
        }
      };

      var normalizeImageDimensions = function (img) {
        var w = img.width();
        var h = img.height();

        // Resize the image if it is not in the correct size.
        if (w != 350 || h != 350) {
          var normalizer = Math.max(w, h);
          w = Math.round(w / normalizer * 350);
          h = Math.round(h / normalizer * 350);
          img.width(w);
          img.height(h);
        }
      };

      // This killSwitch is needed because of Internet Explorer.
      // For some weird reason, Internet Explorer's favourite hobby is to
      // run the onLoad event handler. This killSwitch makes sure that it
      // runs exactly once.
      var killSwitch = false;
      var img = $('div.media-item img');
      if (!killSwitch) {
        // Determining the original width and height of the image.
        $('<img/>')
          .load(function () {
            setOrigWidth(this.width);
            origWidth = this.width;
            setOrigHeight(this.height);
            origHeight = this.height;
            imageScale = getImageScale();
            resetDimensions();
            normalizeImageDimensions(img);
            updateRotation(0, function () {
            });
            killSwitch = true;
          })
          .attr('src', $(img).attr('src'));
      }

      $('div.rotated-images img.rotated')
        .load(function () {
          normalizeImageDimensions($(this));
        });

      $('input[name=crop_width]', context)
        .focus(function () {
          var rawWidth = Number($(this).val());
          $(this).data("oldVal", rawWidth);
        })
        .change(function () {
          var rawWidth = Number($(this).val());

          if (rawWidth && rawWidth <= origWidth) {
            var x = Number($('input[name=x]', context).val());
            var y = Number($('input[name=y]', context).val());
            var w = Math.round(rawWidth * imageScale);
            var h = Number($('input[name=height]', context).val()) || Math.round(origHeight * imageScale);
            setCropWidth(w);
            var selectionData = {
              x1: x,
              x2: x + w,
              y1: y,
              y2: y + h
            };
            activeCroppingInstance.setOptions($.extend({show: true}, selectionData));
            $(this).data("oldVal", rawWidth);
            resetScale();
          }
          else {
            var origCropWidth = $(this).data("oldVal");
            $('input[name=crop_width]', context).val(origCropWidth);
          }
        });

      $('input[name=crop_height]', context)
        .focus(function () {
          var rawHeight = Number($(this).val());
          $(this).data("oldVal", rawHeight);
        })
        .change(function () {
          var rawHeight = Number($(this).val());

          if (rawHeight && rawHeight <= origHeight) {
            var x = Number($('input[name=x]', context).val());
            var y = Number($('input[name=y]', context).val());
            var w = Number($('input[name=width]', context).val()) || Math.round(origWidth * imageScale);
            var h = Math.round(rawHeight * imageScale);
            setCropHeight(h);
            var selectionData = {
              x1: x,
              x2: x + w,
              y1: y,
              y2: y + h
            };
            activeCroppingInstance.setOptions(selectionData);
            $(this).data("oldVal", rawHeight);
            resetScale();
          }
          else {
            var origCropHeight = $(this).data("oldVal");
            $('input[name=crop_height]', context).val(origCropHeight);
          }
        });

      var resetDimensions = function () {
        $('input[name=x]', context).val('');
        $('input[name=y]', context).val('');
        $('input[name=width]', context).val('');
        $('input[name=scale_width]', context).focus();
        $('input[name=height]', context).val('');
        $('input[name=crop_width]', context).val(origWidth);
        $('input[name=crop_height]', context).val(origHeight);
        aspectRatioUnlocked = true;
        resetAspectRatioLock();
      };

      var resetAspectRatioLock = function () {
        $('.crop-aspect-ratio-unlock').hide();
        $('.crop-aspect-ratio-lock').show();
        if (activeCroppingInstance) {
          activeCroppingInstance.setOptions({aspectRatio: false});
          activeCroppingInstance.setOptions({aspectRatio: false});
        }
      };

      var updateUICropDimensions = function (width, height) {
        $('input[name=crop_width]', context).val(Math.round(width / imageScale));
        $('input[name=crop_height]', context).val(Math.round(height / imageScale));
      };

      var updateRotation = function (angle, finished) {
        freeze = true;
        var rotInput = $('input[name=rotate]', context);
        var rot = Number(rotInput.val());
        var oldRot = rot;
        var rotatedImage;

        rot = (rot + angle) % 360;
        if (rot < 0) {
          rot = 360 + rot;
        }

        rotInput.val(rot);

        var rotDiff = Math.abs(oldRot - rot);

        rotatedImage = $('img.rotated-' + rot, context);
        var currentImage = rotatedImage.length > 0 ? rotatedImage : img;

        var animationFinished = function () {
          img
            .show()
            .attr('class', img
              .attr('class')
              .replace(/\bimage-rotate-[-0-9]+-[-0-9]+\b/, ''))
            .addClass('image-rotate-' + oldRot + '-' + rot)
            .imgAreaSelect({hide: true, remove: true});
        };

        var animationOptions = {
          duration: 50,
          easing: 'linear',
          queue: false
        };

        normalizeImageDimensions(currentImage);
        var cih = currentImage.height();

        if (rotDiff) {
          // Resizing the container.
          currentImage.animate({
            'margin-top': (350 - cih) / 2
          }, $.extend({
            complete: function () {
              img.css('margin-top', (350 - img.height()) / 2);
            }
          }, animationOptions));
          container.animate({
            height: 350
          }, animationOptions);
          setTimeout(animationFinished, animationOptions.duration);
        }

        // Saves the selection.
        var x = Number($('input[name=x]', context).val());
        var y = Number($('input[name=y]', context).val());
        var w = Number($('input[name=width]', context).val());
        var h = Number($('input[name=height]', context).val());

        if (rotDiff) {
          // Moves back the rotated images.
          $('div.media-item img.rotated', context)
            .imgAreaSelect({hide: true, remove: true})
            .appendTo($('div.rotated-images'));
        }

        setTimeout(function () {
          if (rot != 0 && rotDiff) {
            // Replaces the original image with a rotated.
            img
              .hide()
              .after(rotatedImage);
          }

          var selectionData = {};
          var show = false;

          if (x > 0 || y > 0 || w > 0 || h > 0) {
            var iw = currentImage.width();
            var ih = currentImage.height();
            var k, x_, y_, w_, h_;
            switch (rotDiff) {
              case 270:
              case 90:
                // Restores the selection.
                // K will be either -1 or 1.
                k = angle / 90;
                if (rotDiff == 270) {
                  k /= 3;
                }
                x_ = k > 0 ? (iw - (h + y)) : y;
                y_ = k > 0 ? x : (ih - (w + x));
                w_ = h;
                h_ = w;
                break;

              case 0:
                x_ = x;
                y_ = y;
                w_ = w;
                h_ = h;
                break;
            }

            selectionData = {
              x1: x_,
              x2: x_ + w_,
              y1: y_,
              y2: y_ + h_
            };

            show = true;
          }

          if (!show) {
            freeze = false;
          }

          container.animate({
            height: cih
          }, animationOptions);
          currentImage.animate({
            'margin-top': 0
          }, animationOptions);

          if (x === 0 && y === 0 && w === 0 && h === 0 && rotDiff === 0) {
            selectionData = {
              hide: true
            };
          }

          setTimeout(function () {
            activeCroppingInstance = currentImage.imgAreaSelect(
              $.extend({}, areaSelectOptions,
                       {show: show, enable: cropEnabled}, selectionData));
            if (show) {
              $('input[name=x]').val(x_);
              $('input[name=y]').val(y_);
              setCropWidth(w_);
              setCropHeight(h_);
              updateUICropDimensions(w_, h_);
            }
            freeze = false;
            if (finished) {
              finished();
            }
          }, rotDiff ? 500 : 0);

        }, rotDiff ? 350 : 0);
      };

      Drupal.media_crop.actions.updateRotation = updateRotation;

      $('select[name=image_style]', context).change(function () {

        var selected = $(this).val();

        try {
          if (Drupal.settings.media_crop.styles[selected].safe) {
            imageStyleSafe = true;
            toggleImageStyleWarning();
            activeCroppingInstance.update();
            var props = Drupal.settings.media_crop.styles[selected];
            var oldRot = Number($('input[name=rotate]').val());
            var newRot = Number(props.rotation);
            var w = ((oldRot + newRot) / 90) & 1 ? img.height() : img.width();
            var h = ((oldRot + newRot) / 90) & 1 ? img.width() : img.height();

            resetDimensions();

            updateRotation(newRot, function () {
              if (props.crop) {
                var anchor = props.crop.anchor.split('-');

                imageStyleHasCrop = true;
                safeImageStyleCropSettings = {
                  x: Math.round(calculateAnchors(anchor[0], w, props.crop.width)),
                  y: Math.round(calculateAnchors(anchor[1], h, props.crop.height)),
                  w: Math.round(props.crop.width),
                  h: Math.round(props.crop.height)
                };

                $('input[name=x]', context).val(safeImageStyleCropSettings.x);
                $('input[name=y]', context).val(safeImageStyleCropSettings.y);
                setCropWidth(safeImageStyleCropSettings.w);
                setCropHeight(safeImageStyleCropSettings.h);

                updateRotation(0, toggleCropWarning());
              }
              else {
                imageStyleHasCrop = false;
              }
            });
          }
          else {
            imageStyleSafe = false;
            resetUI();
            toggleImageStyleWarning();
          }
        }
        catch (e) {
          imageStyleSafe = false;
          resetUI();
        }

        // Handle the hidden state of this element.
        if ($('a', $(this).parent()).length) {
          $('a', $(this).parent()).click();
          $(this).removeClass('processed');
          Drupal.media_crop.processSpecialSelect(context);
        }
      });

      $('body').delegate('div.imgareaselect-outer', 'click', function () {
        resetDimensions();
      });

      $('.rotate-left-button:not(.processed)')
        .addClass('processed')
        .click(function (ev) {
          if (!freeze) {
            updateRotation(-90, null);
          }
          ev.preventDefault();
        });

      $('.rotate-right-button:not(.processed)')
        .addClass('processed')
        .click(function (ev) {
          if (!freeze) {
            updateRotation(90, null);
          }
          ev.preventDefault();
        });

      $('input[name=scale_width]', context).change(function (ev) {
        var scaleWidth = Number($(this).val());
        if (scaleWidth) {
          setScaleWidth(scaleWidth);
          var cropWidth = Drupal.media_crop.cropWidth || origWidth;
          var cropHeight = Drupal.media_crop.cropHeight || origHeight;
          var aspectRatio = cropWidth / cropHeight;
          var scaleHeight = scaleWidth / aspectRatio;
          scaleHeight = Math.round(scaleHeight);
          Drupal.media_crop.actions.setScaleHeightUI(scaleHeight);
          toggleScaleWarning(scaleWidth, scaleHeight);
        }
        else {
          resetScale();
        }
      });

      $('input[name=scale_height]', context).change(function (ev) {
        var scaleHeight = Number($(this).val());
        if (scaleHeight) {
          setScaleHeight(scaleHeight);
          var cropWidth = Drupal.media_crop.cropWidth || origWidth;
          var cropHeight = Drupal.media_crop.cropHeight || origHeight;
          var aspectRatio = cropWidth / cropHeight;
          var scaleWidth = scaleHeight * aspectRatio;
          scaleWidth = Math.round(scaleWidth);
          Drupal.media_crop.actions.setScaleWidthUI(scaleWidth);
          toggleScaleWarning(scaleWidth, scaleHeight);
        }
        else {
          resetScale();
        }
      });

      $('.crop-aspect-ratio-lock:not(.processed)')
        .addClass('processed')
        .click(function () {
          var aspRatW = Number($('input[name=width]', context).val());
          var aspRatH = Number($('input[name=height]', context).val());

          if (aspRatW && aspRatH) {
            $(this).hide();
            aspectRatioUnlocked = false;
            $('.crop-aspect-ratio-unlock').show();
            var aspRat = aspRatW + ':' + aspRatH;
            activeCroppingInstance.setOptions({aspectRatio: aspRat});
          }
        });

      $('.crop-aspect-ratio-unlock:not(.processed)')
        .addClass('processed')
        .click(function () {
          aspectRatioUnlocked = true;

          $(this).hide();
          $('.crop-aspect-ratio-lock').show();
          activeCroppingInstance.setOptions({aspectRatio: false});
        });

      var toggleCropWarning = function () {
        if (imageStyleSafe && imageStyleHasCrop && isCropOverridden()) {
          $('.crop-warning').show();
        }
        else {
          $('.crop-warning').hide();
        }
      };

      $('.enable-interface:not(.processed)')
        .addClass('processed')
        .click(function () {
          $('.enable-interface').hide();
          $('.format-and-crop-container-bottom').show();
          cropEnabled = true;
          resetUI();
          activeCroppingInstance = $('.media-item img:visible').imgAreaSelect($.extend({}, areaSelectOptions, {show: false, enable: cropEnabled}));
        });

      $('.disable-interface:not(.processed)')
        .addClass('processed')
        .click(function () {
          $('.enable-interface').show();
          $('.format-and-crop-container-bottom').hide();
          cropEnabled = false;
          resetUI();
        });

      var isCropOverridden = function () {
        var w = Number($('input[name=width]', context).val());
        var h = Number($('input[name=height]', context).val());

        return (
          safeImageStyleCropSettings.w !== w ||
          safeImageStyleCropSettings.h !== h
        );
      };

      var toggleScaleWarning = Drupal.media_crop.actions.toggleScaleWarning;

      // Store original Drupal.media.formatForm.getOptions() for extending.
      var getOptions = Drupal.media.formatForm.getOptions;

      // Extend Drupal.media.formatForm.getOptions() to incorporate media_crop
      // related settings.
      Drupal.media.formatForm.getOptions = function () {
        var options = getOptions();

        var mediaCropSettings = {
          media_crop_rotate: Number(($('input[name=rotate]', context).val() || '0')),
          media_crop_x: Number(($('input[name=x]', context).val() || '0')),
          media_crop_y: Number(($('input[name=y]', context).val() || '0')),
          media_crop_w: Number(($('input[name=width]', context).val() || '0')),
          media_crop_h: Number(($('input[name=height]', context).val() || '0')),
          media_crop_scale_w: Number(($('input[name=scale_width]', context).val() || '0')),
          media_crop_scale_h: Number(($('input[name=scale_height]', context).val() || '0')),
          media_crop_image_style: getImageStyle(),
          media_crop_instance: '%7BMCIID%7D'
        };

        return $.extend({}, options, mediaCropSettings);
      };

      // Store original Drupal.media.formatForm.getFormattedMedia(),
      // if extending it is needed instead of overriding.
      var getFormattedMedia = Drupal.media.formatForm.getFormattedMedia;
      // Override Drupal.media.formatForm.getFormattedMedia(),
      // it is safe to do, as this js gets loaded only for local images.
      Drupal.media.formatForm.getFormattedMedia = function () {
        var formatType = ($('input[name=format]', context).val() || 'media_crop');
        var options = Drupal.media.formatForm.getOptions();
        var token = ($('input[name=token]', context).val() || ' ');
        var template = ($('input[name=template]', context).val() || '');
        var fid = ($('input[name=fid]', context).val() || '0');

        var r = Math.random() * 10000000000000;
        var id = 'media_crop_' + String(r - (r % 1));

        var replacedData = {
          id: id,
          token: token,
          options: options,
          fid: fid
        };

        parent.window.Drupal.media_crop.replaceImage(replacedData);

        var mediadata = {
          type: formatType,
          options: options,
          html: Drupal.settings.media_crop.imageStyleHtml[options.media_crop_image_style]
        };

        mediadata.html = template.replace('ID_PLACEHOLDER', id);

        return mediadata;
      };

      var getImageStyle = function () {
          return ($('select[name=image_style] option:selected', context).val() || '');
      };

      var resetUI = function () {
        resetDimensions();
        updateRotation(360 - Number($('input[name=rotate]').val()), null);
      };
    }
  };

  Drupal.media_crop.actions = {
    setOrigWidth: function (width) {
      width = Number(width);
      Drupal.media_crop.origWidth = width;
    },
    setOrigHeight: function (height) {
      height = Number(height);
      Drupal.media_crop.origHeight = height;
    },
    setCropWidth: function (width) {
      width = Number(width);
      Drupal.media_crop.cropWidth = width;
      $('input[name=width]').val(width);
    },
    setCropHeight: function (height) {
      height = Number(height);
      Drupal.media_crop.cropHeight = height;
      $('input[name=height]').val(height);
    },
    setScaleWidth: function (width) {
      width = Number(width);
      Drupal.media_crop.scaleWidth = width;
    },
    setScaleHeight: function (height) {
      height = Number(height);
      Drupal.media_crop.scaleHeight = height;
    },
    setScaleWidthUI: function (width) {
      $('input[name=scale_width]').val(width);
    },
    setScaleHeightUI: function (height) {
      $('input[name=scale_height]').val(height);
    },
    resetScale: function () {
      $('input[name=scale_width]').val('');
      $('input[name=scale_height]').val('');
    },
    recalculateScale: function (selection) {
      if (selection.width !== Drupal.media_crop.cropWidth || selection.height !== Drupal.media_crop.cropHeight) {
        Drupal.media_crop.actions.resetScale();
      }
    },
    toggleScaleWarning: function (scaleWidth, scaleHeight) {
      var imageScale = Drupal.media_crop.actions.getImageScale();
      var cropWidth = Drupal.media_crop.cropWidth ? Math.round(Drupal.media_crop.cropWidth / imageScale) : Drupal.media_crop.origWidth;
      var cropHeight = Drupal.media_crop.cropHeight ? Math.round(Drupal.media_crop.cropHeight / imageScale) : Drupal.media_crop.origHeight;
      var widthUpscales = scaleWidth && scaleWidth > cropWidth;
      var heightUpscales = scaleHeight && scaleHeight > cropHeight;
      if (widthUpscales || heightUpscales) {
        $('.scale-warning').show();
      }
      else {
        $('.scale-warning').hide();
      }
    },
    getImageScale: function () {
      return 350 / Math.max(Drupal.media_crop.origWidth, Drupal.media_crop.origHeight);
    },
    enableInterface: function () {
      $('.enable-interface').click();
    },
    init: function (data) {
      var crop = data.crop;
      var isCropRotationScaleEnabled = Boolean(Number(crop.media_crop_w) || Number(crop.media_crop_h) || Number(crop.media_crop_rotate) || Number(crop.media_crop_scale_w) || Number(crop.media_crop_scale_h));

      var setCropRotationScale = function () {
        if (isCropRotationScaleEnabled) {
          Drupal.media_crop.actions.enableInterface();
        }

        if (Number(crop.media_crop_w) && Number(crop.media_crop_h) && Number(crop.media_crop_rotate)) {
          Drupal.media_crop.actions.updateRotation(Number(crop.media_crop_rotate), function () {
            $('input[name=x]').val(crop.media_crop_x);
            $('input[name=y]').val(crop.media_crop_y);
            Drupal.media_crop.actions.setCropWidth(crop.media_crop_w);
            Drupal.media_crop.actions.setCropHeight(crop.media_crop_h);

            var selectionData = {
              x1: Number(crop.media_crop_x),
              x2: Number(crop.media_crop_x) + Number(crop.media_crop_w),
              y1: Number(crop.media_crop_y),
              y2: Number(crop.media_crop_y) + Number(crop.media_crop_h)
            };

            Drupal.media_crop.actions.updateRotation(0, null);
          });
        }
        else if (Number(crop.media_crop_w) && Number(crop.media_crop_h)) {
          $('input[name=x]').val(crop.media_crop_x);
          $('input[name=y]').val(crop.media_crop_y);
          Drupal.media_crop.actions.setCropWidth(crop.media_crop_w);
          Drupal.media_crop.actions.setCropHeight(crop.media_crop_h);

          var selectionData = {
            x1: Number(crop.media_crop_x),
            x2: Number(crop.media_crop_x) + Number(crop.media_crop_w),
            y1: Number(crop.media_crop_y),
            y2: Number(crop.media_crop_y) + Number(crop.media_crop_h)
          };

          Drupal.media_crop.actions.updateRotation(0, null);
        }
        else if (Number(crop.media_crop_rotate)) {
          Drupal.media_crop.actions.updateRotation(Number(crop.media_crop_rotate), null);
        }

        if (Number(crop.media_crop_scale_w) || Number(crop.media_crop_scale_h)) {
          Drupal.media_crop.actions.setScaleWidthUI(crop.media_crop_scale_w);
          Drupal.media_crop.actions.setScaleHeightUI(crop.media_crop_scale_h);
          Drupal.media_crop.actions.toggleScaleWarning(crop.media_crop_scale_w, crop.media_crop_scale_h);
        }
      };

      if (Drupal.settings.media_crop.styles[crop.media_crop_image_style]) {
        $('select[name=image_style]').val(crop.media_crop_image_style);
        $('select[name=image_style]').change();
        $('a', $('select[name=image_style]').parent()).click();

        if (Drupal.settings.media_crop.styles[crop.media_crop_image_style].safe) {
          Drupal.media_crop.actions.updateRotation(360 - Number($('input[name=rotate]').val()), setCropRotationScale());
        }
        else {
          setCropRotationScale();
        }
      }
      else {
        setCropRotationScale();
      }
    }
  };

  Drupal.media_crop.processSpecialSelect = function (context) {
    $('select.media-crop-special-select:not(.processed)', context)
      .addClass('processed')
      .each(function () {
        var select = $(this);
        select.hide();
        var text = $('<span/>')
          .html($('option:selected', select).html())
          .addClass('special-select-text');
        var button = $('<a/>')
          .html(Drupal.t('Change'))
          .attr('href', '#')
          .click(function (event) {
            event.preventDefault();
            text.remove();
            button.remove();
            select.show();
          });
        select
          .after(button)
          .after(text);
      });
  };
})(jQuery);
