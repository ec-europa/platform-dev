/**
 * @file
 * Javascripts for feature set.
 */

(function ($) {

  Drupal.behaviors.ec_resp_feature_set = {
    attach: function (context) {

      // Activate sticky menu.
      $('.feature-set__categories').affix({
        offset: {
          top: $('.feature-set__categories').offset().top
        }
      });
      $('.feature-set__category').width($('#feature-set__scrollspy').width());
      $(window).resize(function () {
        $('.feature-set__category').width($('#feature-set__scrollspy').width());
      });

      // Activate scrollspy.
      $('body').scrollspy({
        target: '#feature-set__scrollspy',
      });

      // Manage click on a row.
      $('.feature-set__header').click(function () {
        $(this)
          .closest('.feature-set__feature')
          .not('.feature-set__feature--locked')
          .toggleClass('feature-set__feature--pending')
          .find('.form-checkbox')
          .each(function () {
            $this = $(this);
            if ($this.is(':checked')) {
              $this
                .prop('checked', false)
                .siblings('span')
                .toggleClass('glyphicon-time')
                .toggleClass(function () {
                  if ($this.closest('.feature-set__feature').hasClass('feature-set__feature--disabled')) {
                    return 'glyphicon-remove';
                  }
                  else {
                    return 'glyphicon-ok';
                  }
                });
            }
            else {
              $this
                .prop('checked', true)
                .siblings('span')
                .toggleClass('glyphicon-time')
                .toggleClass(function () {
                  if ($this.closest('.feature-set__feature').hasClass('feature-set__feature--disabled')) {
                    return 'glyphicon-remove';
                  }
                  else {
                    return 'glyphicon-ok';
                  }
                });
            }
          })
      });

      // Add icon and hide checkbox.
      $(".feature-set__feature .form-checkbox").each(function () {
        $this = $(this);
        // Check if the feature has been enabled.
        if ($this.is(':checked')) {
          var html_before = '<span class="glyphicon glyphicon-ok"></span>';
          $this
            .closest('.feature-set__feature')
            .addClass('feature-set__feature--enabled');
        }
        else {
          var html_before = '<span class="glyphicon glyphicon-remove"></span>';
          $this
            .closest('.feature-set__feature')
            .addClass('feature-set__feature--disabled');
        }
        $this
          .before(html_before)
          .css('opacity',0);
      });

      // Add class to row corresponding to button state.
      $(".feature-set__switch")
        .filter('.form-disabled')
        .find('span')
        .addClass('glyphicon-ban-circle')
        .closest('.feature-set__feature')
        .addClass('feature-set__feature--locked');
    }
  }

})(jQuery);
