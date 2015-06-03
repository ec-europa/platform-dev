/**
 * @file
 * Javascripts for ec_resp theme
 * - Drupal.settings.pathToTheme: it is the equivalent to the path_to_theme() PHP function, it is set in the theme_preprocess_page()
 */

//use jQuery 1.7.1
(function($){  
  // Drupal.behaviours 
  // https://drupal.org/node/304258 
  // http://blog.amazeelabs.com/en/drupal-behaviors-quick-how
	Drupal.behaviors.ec_resp = {
    attach: function(context, settings) {
  		
      // Gallery carrousel
      $('.carousel').carousel({
        interval: 5000
      });
      // /Gallery carrousel

      // Tooltips
      $('[data-toggle="tooltip"]').tooltip();
      // /Tooltips

      // Back on top link
      $(window).scroll(function() {
        if ($(this).scrollTop() > 200) {
          $('.btn-back-top').fadeIn(200);
        }
        else {
          $('.btn-back-top').fadeOut(200);
        }
      });

      $('.btn-back-top').on("click", function(e) {
        e.preventDefault();
        $('html,body').animate({scrollTop: 0}, 300);
        $(this).blur();
        return false;
      });
      // /Back on top link

      // Gallery add media form
      $('.node-gallerymedia #add_picture').click(function(e) {
        e.preventDefault();
        $('#add-media-form').slideToggle('slow');
        return false;
      });
      // /Gallery add media form
      

      // Menu dropdown
      $('.dropdown-toggle').dropdown();
      // /Menu dropdown

      // Font size buttons
      $('.text_size_big').on("click", function() {
        $('link[data-name="switcher"]').attr('href',Drupal.settings.basePath + Drupal.settings.pathToTheme + '/css/text_size_big.css');
      });
      $('.text_size_small').on("click", function() {
        $('link[data-name="switcher"]').attr('href',Drupal.settings.basePath + Drupal.settings.pathToTheme + '/css/text_size_small.css');
      });
      // /Font size buttons
    }
	}

  // News slider implementation
  Drupal.behaviors.ec_resp_news_slider = {
    attach: function(context) {
      // News slider
      $('#slider').once('news-slider', function(){
        //init
        $('.view-news > .view-content').addClass('news_content tab-content');
        $('#slider .news_list li:first-child').addClass('active');
        $('#slider .news_content div.news').first().show();
        
        //browse top news
        var topNews = new Array();
        var totalHeight = 0;
        $('#slider .news_list li a').each(function() {
          topNews.push($(this));
          totalHeight = totalHeight + $(this).height() + 21;
        });
        /*if (totalHeight < 180) totalHeight = 180;
        $('#slider.news .content > .view-news > .news_content div.news').height(totalHeight+1);*/
        
          var NbNews = topNews.length;
          var i = 1;
          var interval = setInterval(function() {
            if (i >= NbNews) {
              i = 0;
            }

            changeNews(topNews[i]);
            i++;
          },5000);
          
          $('#slider').mouseover(function() {
            clearInterval(interval);
          }).mouseout(function() {
            interval = setInterval(function() {
              if (i >= NbNews) {
                i = 0;
              }

              changeNews(topNews[i]);
              i++;
            },5000);
          });
        
        $('#slider .news_list li a').click(function(e) {
          e.preventDefault();
          changeNews($(this));
          return false;
        });
        
        function changeNews(clicked) {
          var previous_id = '';
          
          $('#slider .news_list li a').each(function() {
            var previous_parent = $(this).parent('li');
            if (previous_parent.is('.active')) {
              previous_parent.removeClass('active');
              previous_id = $(this).attr('href').replace('#', '');
            }
          });
          
          clicked.parent('li').addClass('active');
          
          var news_id = clicked.attr('href').replace('#', '');
          $('#'+previous_id).hide();
          $('#'+news_id).fadeIn(500);
        }    
      });
    }
  }

  // Feature set
  Drupal.behaviors.ec_resp_feature_set = {
    attach: function(context) {

      // Activate first tab by default.
      $('.feature-set__categories a:first').tab('show');

      // Manage click on a row.
      $('.feature-set__header').click(function() {
        $(this)
          .not('.feature-set__header--locked')
          .toggleClass('feature-set__header--pending')
          .find('.form-checkbox')
          .each(function() {
            $this = $(this);
            console.log($this.closest('.feature-set__header').hasClass('feature-set__header--disabled'));
            if ($this.is(':checked')) {
              $this
                .prop('checked', false)
                .siblings('span')
                .toggleClass('glyphicon-time')
                .toggleClass(function() {
                  if ($this.closest('.feature-set__header').hasClass('feature-set__header--disabled')) {
                    return 'glyphicon-remove-sign';
                  }
                  else {
                    return 'glyphicon-ok-sign';
                  }
                });
            }
            else {
              $this
                .prop('checked', true)
                .siblings('span')
                .toggleClass('glyphicon-time')
                .toggleClass(function() {
                  if ($this.closest('.feature-set__header').hasClass('feature-set__header--disabled')) {
                    return 'glyphicon-remove-sign';
                  }
                  else {
                    return 'glyphicon-ok-sign';
                  }
                });
            }
          })
      });

      // Add icon and hide checkbox.
      $(".feature-set__feature .form-checkbox").each(function() {
        $this = $(this);
        // Check if the feature has been enabled.
        if ($this.is(':checked')) {
          var html_before = '<span class="glyphicon glyphicon-ok-sign"></span>';
          $this
            .closest('.feature-set__header')
            .addClass('feature-set__header--enabled');
        }
        else {
          var html_before = '<span class="glyphicon glyphicon-remove-sign"></span>';
          $this
            .closest('.feature-set__header')
            .addClass('feature-set__header--disabled');
        }
        $this
          .before(html_before)
          .css('opacity',1);
      });

      // Add class to row corresponding to button state.
      $(".feature-set__switch")
        .filter('.form-disabled')
        .find('span')
        .addClass('glyphicon-ban-circle')
        .closest('.feature-set__header')
        .addClass('feature-set__header--locked');
    }
  }// /Feature set

  // Fancybox implementation
  Drupal.behaviors.ec_resp_fancybox = {
    attach: function(context) {

      function stopPlayer() {
        var id= $('.fancybox-opened').find(".lightbox").children().attr('id');

        var isVideo = false;
        if (navigator.appName != 'Microsoft Internet Explorer' && id != null && id.indexOf("player") >= 0) {
          isVideo = true;
          var player= document.getElementById(id);
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
        beforeClose: function() {
          stopPlayer();
        },
        beforeLoad: function() {
          stopPlayer();
        }
      });
      /* /Gallery lightbox */
    }
  }

  // Responsive menu implementation
  Drupal.behaviors.ec_resp_responsive_menu = {
    attach: function(context) { 
      $('#menu-button').on("click", function() {
        $(this).toggleClass('menu-open');
        $('#menu-button > div').toggleClass("arrow-down");
        $('#menu-button > div').toggleClass("arrow-up");
      });
    }
  }

  // Responsive sidebar implementation
  Drupal.behaviors.ec_resp_responsive_sidebar = {
    attach: function(context) { 
      $('#responsive-sidebar').once('responsive-sidebar', function(){

        // Hide the sidebar on load 
        $('#responsive-sidebar').addClass('reduced').removeClass('expanded');

        $('.sidebar-button').on("click", function() {
          $('.sidebar-button').toggleClass('sidebar-open');

          if ($('#layout-body').is('.reduced')) {
            hide_sidebar();
          }
          else {
            // Scroll to top when showing the sidebar
            window.scrollTo(0,0);
            show_sidebar();
          }
        });

        $(window).resize( function() {
          if ($('#layout-body').is('.reduced')) {
            hide_sidebar();
          }
        });

        function hide_sidebar() {
          // close responsive sidebars
          $('#responsive-sidebar').addClass('reduced').removeClass('expanded');
          $('#layout-body').addClass('expanded').removeClass('reduced').delay(400).promise().done(function(){
            // move left sidebar
            $('#responsive-sidebar-left > div').detach().appendTo($('#sidebar-left'));

            // move right sidebar
            $('#responsive-sidebar-right > div').detach().appendTo($('#sidebar-right'));

            // move header right
            $('#responsive-header-right > div').detach().appendTo($('#banner-image-right'));
          });
        }

        function show_sidebar() {
          // move left sidebar
          $('#sidebar-left > div').detach().appendTo($('#responsive-sidebar-left'));

          // move right sidebar
          $('#sidebar-right > div').detach().appendTo($('#responsive-sidebar-right'));

          // move header right
          $('#banner-image-right > div').detach().appendTo($('#responsive-header-right'));

          // open responsive sidebars
          $('#responsive-sidebar').addClass('expanded').removeClass('reduced');
          $('#layout-body').addClass('reduced').removeClass('expanded');
        }
      });
    }
  }

})(jQuery); 