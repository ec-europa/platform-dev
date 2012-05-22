(function ($) {
  $(document).ready(function(){
  
    $('ul.languages li a').click(function() {
	  $lg = $(this).find("span").html();

	  $.cookie("ecweb_cookie_language", $lg, { expires: 365 });
	  
      return true;
    });
	  	
  });
})(jQuery);
