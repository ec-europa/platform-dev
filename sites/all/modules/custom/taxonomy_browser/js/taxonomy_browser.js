/**
 * @file
 * create a dropdown
 *  
 */

(function($){
	Drupal.behaviors.taxonomy_browser = {
		attach: function(context, settings) {
			$('.tb-browser-tree').once('tb-browser-tree', function(){
				$('.tb-browser-tree > ul.taxonomy-tree').find('ul.taxonomy-tree').hide();
				var $currentActive = $(this).find('a.active');

				$currentActive.parents('ul.taxonomy-tree').show().siblings('.taxonomy-tree-opener').removeClass('glyphicon-plus').addClass('glyphicon-minus');;
				$('.taxonomy-tree-opener').click(function(e){
					e.preventDefault();

					if ($(this).hasClass('glyphicon-minus')) {
						$(this).removeClass('glyphicon-minus');
						$(this).addClass('glyphicon-plus');
					} else {
						$(this).addClass('glyphicon-minus');
						$(this).removeClass('glyphicon-plus');
					}

					$(this).siblings('ul.taxonomy-tree').stop(true, true).slideToggle(200);
				});
			});
		}
	}
})(jQuery);
