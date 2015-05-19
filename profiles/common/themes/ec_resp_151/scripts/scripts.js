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
   
    /* News slider */
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
    /* /News slider */
		
    /* Gallery carrousel */
    $('.carousel').carousel({
      interval: 5000
    });
    /* /Gallery carrousel */

    /* Gallery add media form */
    $('.node-gallerymedia #add_picture').click(function(e) {
      e.preventDefault();
      $('#add-media-form').slideToggle('slow');
      return false;
    });
    /* /Gallery add media form */
    
    /* Menu dropdown */
    $('.dropdown-toggle').dropdown();
    /* /Menu dropdown */

    /* Responsive menu */
    $('#responsive-sidebar > div').hide();
    $('#sidebar-button').on("click", function() {
      $('#responsive-sidebar > div').slideToggle(300);
      if ($('#layout-body').is('.reduced')) {
        $('#layout-body').animate({
          left:'0'
        }, 300).removeClass('reduced');
      }
      else {
        $('#layout-body').animate({
          left:'85%'
        }, 300).addClass('reduced');        
      }
    });

    $('#menu-button').on("click", function() {
      $('#menu-button > div').toggleClass("arrow-down");
      $('#menu-button > div').toggleClass("arrow-up");
    });
    /* /Responsive menu */ 

    /* Font size buttons */
    $('.text_size_big').on("click", function() {
      $('link[data-name="switcher"]').attr('href',templatePath + '/css/text_size_big.css');
    });
    $('.text_size_small').on("click", function() {
      $('link[data-name="switcher"]').attr('href',templatePath + '/css/text_size_small.css');
    });
    /* /Font size buttons */
	});

})(jq171); 