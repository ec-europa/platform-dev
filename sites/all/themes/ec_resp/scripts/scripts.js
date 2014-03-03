/**
 * @file
 * Javascripts for ec_resp theme
 */

//use jQuery 1.4.4
jQuery(function($){

	$(document).ready(function() {  //Once the page elements are fully loaded

    if (!($.browser.msie)) {
      window.addEventListener('resize', manageWindowSize, false);
    }

    manageWindowSize();

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
  });

  function stopPlayer() {
    var id= $('.fancybox-opened').find(".lightbox").children().attr('id');

    var isVideo = false;
    if ($.browser.msie !=true && id != null && id.indexOf("player") >= 0) {
      isVideo = true;
      var player= document.getElementById(id);
      player.sendEvent('STOP');
    } 
  }

  function manageWindowSize(e) {
    if ("matchMedia" in window) {
      if (window.matchMedia("(max-width: 979px)").matches) {
      // Mobile version
        $('#main-menu-mobile').prependTo('#main-menu');
      } else if (window.matchMedia("(min-width: 980px)").matches) {
      // Desktop version
        $('#main-menu-desktop').prependTo('#main-menu');
      }
    }
  }

});

//use jQuery 1.7.1
(function($){
    
	$(document).ready(function() {  //Once the page elements are fully loaded
   
    // News slider
    if ($('#slider').length != 0) {
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
    }
    // /News slider
		

    // Gallery carrousel
    $('.carousel').carousel({
      interval: 5000
    });
    // /Gallery carrousel


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


    // Responsive menu
    $('#responsive-sidebar').hide();
    $('#sidebar-button').on("click", function() {
      if ($('#layout-body').is('.reduced')) {
        hide_sidebar();
      }
      else {
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
      $('#responsive-sidebar').slideToggle('2000', "linear").hide();
      $('#layout-body').animate({
        left:'0'
      }, 300, function() {
          // move left sidebar
          $('#responsive-sidebar-left > div').detach().appendTo($('#sidebar-left'));

          // move right sidebar
          $('#responsive-sidebar-right > div').detach().appendTo($('#sidebar-right'));
      }).removeClass('reduced');
    }
    function show_sidebar() {
      // move left sidebar
      $('#sidebar-left > div').detach().appendTo($('#responsive-sidebar-left'));

      // move right sidebar
      $('#sidebar-right > div').detach().appendTo($('#responsive-sidebar-right'));

      // open responsive sidebars
      $('#responsive-sidebar').slideToggle('2000', "linear").show();
      $('#layout-body').animate({
        left:'85%'
      }, 300).addClass('reduced');
    }

    $('#sidebar-left').addClass('visible-lg visible-md');
    $('#sidebar-right').addClass('visible-lg visible-md');

    $('#menu-button').on("click", function() {
      $('#menu-button > div').toggleClass("arrow-down");
      $('#menu-button > div').toggleClass("arrow-up");
    });
    // /Responsive menu


    // Font size buttons
    $('.text_size_big').on("click", function() {
      $('link[data-name="switcher"]').attr('href',templatePath + '/css/text_size_big.css');
    });
    $('.text_size_small').on("click", function() {
      $('link[data-name="switcher"]').attr('href',templatePath + '/css/text_size_small.css');
    });
    // /Font size buttons


    // Feature set
    //Toggle visibility of feature set tables
    $("#feature-set-admin-form .feature-set-category").click(function(){
      $(this).next(".feature-set-content").slideToggle("slow");
      $(this).toggleClass("active");
    });
        
    //Add class to switcher column
    $("#feature-set-admin-form .form-type-checkbox").addClass('switch');
    
    //Add class to row if button is disabled
    $("#feature-set-admin-form tr .switch")
      .filter('.form-disabled')
      .closest('tr')
      .addClass('form-disabled');
  
    $("#feature-set-admin-form .form-checkbox").each(function() {
      $this = $(this);
      //Check if the feature has been enabled
      if ($this.is(':checked')) {
        var html_before = '<label class="cb-enable selected"><span><i class="glyphicon glyphicon-ok icon-ok icon-white"></i></span></label><label class="cb-disable"><span><i class="glyphicon glyphicon-remove icon-remove icon-white"></i></span></label>';
      }
      else {
        var html_before = '<label class="cb-enable"><span><i class="glyphicon glyphicon-ok icon-ok icon-white"></i></span></label><label class="cb-disable selected"><span><i class="glyphicon glyphicon-remove icon-remove icon-white"></i></span></label>';
      }  
      
      $this
        .before(html_before)
        .css('opacity',0);
    });

    //Manage click on a row
    $('#feature-set-admin-form tr').click(function() {
      $(this)
        .not('.form-disabled')
        .find('.switch')
        .toggleClass('pending')
        .children('label')
        .toggleClass('selected')
        .end()
        .children('.form-checkbox')
        .each(function() {
          $this = $(this);
          if ($this.is(':checked')) {
            $this.attr('checked', false);
          }
          else {
            $this.attr('checked', true);
          }               
        }); 
    });
    // /Feature set
	});

})(jq171); 