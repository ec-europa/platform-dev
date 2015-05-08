(function ($) {
	Drupal.behaviors.embeddedImage = {
		attach: function(context, settings) {
			$("a[href^='http://www.flickr.com']").attr({
				target : "_blank"
			})
		}
	}
	
})(jQuery);