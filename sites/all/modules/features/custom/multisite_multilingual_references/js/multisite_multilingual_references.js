(function ($) {
    Drupal.behaviors.multilingual_entity_references = {
        attach: function(context, settings) {
            var max_items_row = 4;
            var locate_class = "link-multilingual";
            var process_class = "link-multilingual-popup";
            $("span."+locate_class).addClass(process_class).mouseleave(function(){$(this).hide();})
            .children().filter("span").each(function(){
                // calculate width of the first "max_items_row" children
                var w=1; // 1px borders
                $(this).children().filter("a:lt("+max_items_row+")").each(function(){w+=$(this).outerWidth("true")});
                $(this).width(w);
            }).parent().hide();
            $("img."+locate_class).css("cursor","pointer").click(function(){
                // IE8 does not understand well toggle(), so the following line does not work
                // $(this).next("span."+process_class).toggle();
                var s = $(this).next("span."+process_class);
                ("none"==s.css("display")) ? s.show() : s.hide();
            });
        }
    };
})(jQuery);
