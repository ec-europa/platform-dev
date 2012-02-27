jQuery(function($){

    
    
	$(document).ready(function() {  //Once the page elements are fully loaded
   
    /* News slider */
      //init
    $('.view-news > .view-content').addClass('news_content tab-content');
    $('#slider .news_list li:first-child').addClass('active');
    $('#slider .news_content div.news').first().show();
    
    /*setInterval(function() {
      var current_id = '';
      var next_id = '';
      
      $('#slider .news_list li a').each(function() {
        if ($(this).is('.active')) {
          $(this).removeClass('active');
          current_id = $(this).attr('href').replace('#', '');
          
          next_id = $(this).next('a').attr('href').replace('#', '');
          $('#'+next_id).addClass('active');
        }
      });
      
      var news_id = clicked.attr('href').replace('#', '');
      $('#'+previous_id).hide();
      $('#'+news_id).fadeIn(500);   
    },2000); */
    
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
    /* /News slider */
  
	/* Dropdown*/	
	$('[data-toggle="dropdown"]').click(function () {
			  $(this).parent().toggleClass('open');
	});	
	/*/Dropdown*/
  
	});

}); 