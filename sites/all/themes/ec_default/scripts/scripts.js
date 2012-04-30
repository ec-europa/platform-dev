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
    $('.carousel').carousel({
      interval: 5000
    });
    /* /Gallery carrousel */
    
    /* Gallery lightbox */
    $('.modal .close').click(function(e) {
      e.preventDefault();
      $(this).closest('.modal').modal('hide');
    });
    
    /*$("#single_1").fancybox({
          helpers: {
              title : {
                  type : 'float'
              }
          }
      });*/
  
    /* /Gallery lightbox */
    
    /* Menu dropdown */
    $('.dropdown-toggle').dropdown();
    /* /Menu dropdown */
	});

}); 