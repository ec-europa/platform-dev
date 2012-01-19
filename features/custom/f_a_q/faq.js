(function ($) {
  $(document).ready(function(){
		//FAQ
		$(".view-faq dt").click(function(){
			$(this).next("dd").slideToggle("slow");
			$(this).toggleClass("active");
			return false;
		});	
		
		$(".view-faq dt").toggleClass("active");
		$(".view-faq dt").css("text-decoration","underline");
		$(".view-faq dd").css("display","none");
	});
})(jQuery);