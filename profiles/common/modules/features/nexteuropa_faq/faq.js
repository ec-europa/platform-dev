/**
 * @file
 * Javascript file for FAQ.
 */

(function ($) {
    $(document).ready(function () {

        // FAQ.
        $(".view-ne-faq .views-field-title").click(function () {
            var parent = $(this).parents('li');
            $(this).next(".views-field-field_ne_body").slideToggle("slow");
            $(this).next(".views-field-field_ne_body").next(".views-field-field-tags").slideToggle("slow");
            $(this).toggleClass("active");
            return false;
        });

        // Init.
        $(".view-ne-faq .views-field-title").css("text-decoration", "underline");
        $(".view-ne-faq .views-field-field_ne_body").css("display", "none");
        $(".view-ne-faq .views-field-field-tags").css("display", "none");

        // Expand.
        $(".view-ne-faq a.action-expand").click(function () {
            $(".view-ne-faq .views-field-field_ne_body").slideDown("slow");
            $(".view-ne-faq .views-field-field-tags").slideDown("slow");
            $(".view-ne-faq .views-field-title").addClass("active");
            return false;
        });

        // Collapse.
        $(".view-ne-faq a.action-collapse").click(function () {
            $(".view-ne-faq .views-field-field_ne_body").slideUp("slow");
            $(".view-ne-faq .views-field-field-tags").slideUp("slow");
            $(".view-ne-faq .views-field-title").removeClass("active");
            return false;
        });

    });
})(jQuery);
