jQuery(function($){

	$(document).ready(function() {  //Once the page elements are fully loaded
   
    //Display language selector arrow
    $('#language-selector li a img').each(function() {
      $(this).attr('src','http://ec.europa.eu' + $(this).attr('src'));
    });
  
	});

});  