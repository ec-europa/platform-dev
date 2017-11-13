/**
 * @file
 * Create a dropdown.
 */

(function ($) {
  Drupal.behaviors.taxonomy_browser = {
    attach: function (context, settings) {
                $('.tb-browser-tree > ul.taxonomy-tree').find('ul.taxonomy-tree').hide();
                var $currentActive = $('.tb-browser-tree').find('a.active');

                $currentActive.parents('ul.taxonomy-tree').show().parent('.taxonomy-tree-item').removeClass('jstree-closed').addClass('jstree-open');
                $currentActive.siblings('ul.taxonomy-tree').show().parent('.taxonomy-tree-item').removeClass('jstree-closed').addClass('jstree-open');
                $('.taxonomy-tree-opener').click(function (e) {
                  e.preventDefault();

                  if ($(this).parent().hasClass('jstree-open')) {
                    $(this).parent().removeClass('jstree-open');
                    $(this).parent().addClass('jstree-closed');
                  }
                  else {
                         $(this).parent().addClass('jstree-open');
                         $(this).parent().removeClass('jstree-closed');
                  }

                  $(this).siblings('ul.taxonomy-tree').stop(true, true).slideToggle(200);
                });
    }
  }
})(jq171);
