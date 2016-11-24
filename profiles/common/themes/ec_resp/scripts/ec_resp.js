/**
 * @file
 * Javascripts for ec_resp theme.
 */

(function ($) {
  // Drupal.behaviours
  // https://drupal.org/node/304258
  // http://blog.amazeelabs.com/en/drupal-behaviors-quick-how
  Drupal.behaviors.ec_resp = {
    attach: function (context, settings) {

      // Gallery carrousel.
      $('.carousel').carousel({
        interval: 5000
      });

      // Tooltips.
      $('[data-toggle="tooltip"]').tooltip();

      // Back on top link.
      $(window).scroll(function () {
        if ($(this).scrollTop() > 200) {
          $('.btn-back-top').fadeIn(200);
        }
        else {
          $('.btn-back-top').fadeOut(200);
        }
      });

      $('.btn-back-top').on("click", function (e) {
        e.preventDefault();
        $('html,body').animate({scrollTop: 0}, 300);
        $(this).blur();
        return false;
      });

      // Gallery add media form.
      $('.node-gallerymedia #add_picture').click(function (e) {
        e.preventDefault();
        $('#add-media-form').slideToggle('slow');
        return false;
      });

      // Menu dropdown.
      $('.dropdown-toggle').dropdown();
    }
  }

  // News slider implementation.
  Drupal.behaviors.ec_resp_news_slider = {
    attach: function (context) {
      // News slider.
      $('#slider').once('news-slider', function () {
        // Init.
        $('.view-news > .view-content').addClass('news_content tab-content');
        $('#slider .news_list li:first-child').addClass('active');
        $('#slider .news_content div.news').first().show();

        // Browse top news.
        var topNews = new Array();
        var totalHeight = 0;
        $('#slider .news_list li a').each(function () {
          topNews.push($(this));
          totalHeight = totalHeight + $(this).height() + 21;
        });

        var NbNews = topNews.length;
        var i = 1;
        var interval = setInterval(function () {
          if (i >= NbNews) {
            i = 0;
          }

          changeNews(topNews[i]);
          i++;
        },5000);

        $('#slider').mouseover(function () {
          clearInterval(interval);
        }).mouseout(function () {
          interval = setInterval(function () {
            if (i >= NbNews) {
              i = 0;
            }

            changeNews(topNews[i]);
            i++;
          },5000);
        });

        $('#slider .news_list li a').click(function (e) {
          e.preventDefault();
          changeNews($(this));
          return false;
        });

        function changeNews(clicked) {
          var previous_id = '';

          $('#slider .news_list li a').each(function () {
            var previous_parent = $(this).parent('li');
            if (previous_parent.is('.active')) {
              previous_parent.removeClass('active');
              previous_id = $(this).attr('href').replace('#', '');
            }
          });

          clicked.parent('li').addClass('active');

          var news_id = clicked.attr('href').replace('#', '');
          $('#' + previous_id).hide();
          $('#' + news_id).fadeIn(500);
        }
      });
    }
  }

  // Fancybox implementation.
  Drupal.behaviors.ec_resp_fancybox = {
    attach: function (context) {

      function stopPlayer() {
        var id = $('.fancybox-opened').find(".lightbox").children().attr('id');

        var isVideo = false;
        if (navigator.appName != 'Microsoft Internet Explorer' && id != null && id.indexOf("player") >= 0) {
          isVideo = true;
          var player = document.getElementById(id);
          player.sendEvent('STOP');
        }
      }

      $('.fancybox').fancybox({
        padding:      0,
        closeBtn:     false,
        arrows:       false,
        autoSize:     true,
        fitToView:    true,
        openEffect:   'elastic',
        closeEffect:  'elastic',
        helpers: {
          title:     { type : 'outside' },
          buttons:   {}
        },
        beforeClose: function () {
          stopPlayer();
        },
        beforeLoad: function () {
          stopPlayer();
        }
      });
    }
  }

  // Responsive menu implementation.
  Drupal.behaviors.ec_resp_responsive_menu = {
    attach: function (context) {
      $('#menu-button').on("click", function () {
        $(this).toggleClass('menu-open');
        $('#menu-button > div').toggleClass("arrow-down");
        $('#menu-button > div').toggleClass("arrow-up");
      });
    }
  }

  // Responsive sidebar implementation.
  Drupal.behaviors.ec_resp_responsive_sidebar = {
    attach: function (context) {
      $('#responsive-sidebar').once('responsive-sidebar', function () {

        // Hide the sidebar on load.
        $('#responsive-sidebar').addClass('reduced').removeClass('expanded');

        $('.sidebar-button').on("click", function () {
          $('.sidebar-button').toggleClass('sidebar-open');

          if ($('#layout-body').is('.reduced')) {
            hide_sidebar();
          }
          else {
            // Scroll to top when showing the sidebar.
            window.scrollTo(0,0);
            show_sidebar();
          }
        });

        $(window).resize(function () {
          if ($('#layout-body').is('.reduced')) {
            hide_sidebar();
          }
        });

        function hide_sidebar() {
          // Close responsive sidebars.
          $('#responsive-sidebar').addClass('reduced').removeClass('expanded');
          $('#layout-body').addClass('expanded').removeClass('reduced').delay(400).promise().done(function () {
            // Move left sidebar.
            $('#responsive-sidebar-left > div').detach().appendTo($('#sidebar-left'));

            // Move right sidebar.
            $('#responsive-sidebar-right > div').detach().appendTo($('#sidebar-right'));

            // Move header right.
            $('#responsive-header-right > div').detach().appendTo($('#banner-image-right'));
          });
        }

        function show_sidebar() {
          // Move left sidebar.
          $('#sidebar-left > div').detach().appendTo($('#responsive-sidebar-left'));

          // Move right sidebar.
          $('#sidebar-right > div').detach().appendTo($('#responsive-sidebar-right'));

          // Move header right.
          $('#banner-image-right > div').detach().appendTo($('#responsive-header-right'));

          // Open responsive sidebars.
          $('#responsive-sidebar').addClass('expanded').removeClass('reduced');
          $('#layout-body').addClass('reduced').removeClass('expanded');
        }
      });
    }
  }

})(jQuery);
