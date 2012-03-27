jQuery(function($){
    
	$(document).ready(function() {  //Once the page elements are fully loaded
   
    /* News slider */
    if ($('#slider').length != 0) {
        //init
      $('.view-news > .view-content').addClass('news_content tab-content');
      $('#slider .news_list li:first-child').addClass('active');
      $('#slider .news_content div.news').first().show();
      
      //browse top news
      var topNews = new Array();
      $('#slider .news_list li a').each(function() {
        topNews.push($(this));
      });
      
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
    if ($('ul.carrousel').length != 0) {
      $('ul.carrousel').roundabout({
        btnNext: $('#next'),
        btnPrev: $('#previous'),
        /*btnToggleAutoplay: $('#play'),*/
        minOpacity: 0.05,
        autoplay: true,
        autoplayDuration: 5000,
        autoplayPauseOnHover: true,
        responsive: true,
        minScale: 0.1
      });
    }
    /* /Gallery carrousel */
	});

}); 