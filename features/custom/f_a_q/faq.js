(function ($) {
  $(document).ready(function(){
  
		//FAQ
		$(".view-faq .views-field-title").click(function(){
			$(this).next(".views-field-body").slideToggle("slow");
			$(this).next(".views-field-field-tags").slideToggle("slow");
			$(this).toggleClass("active");
			return false;
		});	
		
		//init
		$(".view-faq .views-field-title").toggleClass("active");
		$(".view-faq .views-field-title").css("text-decoration","underline");
		$(".view-faq .views-field-body").css("display","none");
		$(".view-faq .views-field-field-tags").css("display","none");
		
		//expand
		$(".faq_expand").click(function(){
			$(".view-faq .views-field-body").slideDown("slow");
			$(".view-faq .views-field-field-tags").slideDown("slow");
			$(".view-faq .views-field-title").addClass("active");
			return false;
		});	
		
		//collapse
		$(".faq_collapse").click(function(){
			$(".view-faq .views-field-body").slideUp("slow");
			$(".view-faq .views-field-field-tags").slideUp("slow");
			$(".view-faq .views-field-title").removeClass("active");
			return false;
		});	
		
		
	});
})(jQuery);