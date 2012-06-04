//use jQuery 1.4.4
jQuery(function($){

	$(document).ready(function() {  //Once the page elements are fully loaded
    /* Gallery lightbox */
    $('.fancybox').fancybox({
      padding: 0,
      closeBtn : false,
      arrows : false,
      autoSize: true,
      fitToView: true,
      openEffect: 'elastic',
      closeEffect: 'elastic',
      helpers		: {
        title	: { type : 'outside' },
        buttons	: {},
        /*thumbs	: {
          width	: 50,
          height	: 50,
          position: 'top',
        }*/
      }
    });    
    /* /Gallery lightbox */
});

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
	});

})(jq171); 