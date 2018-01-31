/**
 * @file
 * Javascript file for FAQ.
 */

(function ($) {
  $(document).ready(function () {

    // FAQ.
    $(".view-faq .views-field-title").click(function () {
      var parent = $(this).parents('li');
      $(this).next(".views-field-body").slideToggle("slow");
      $(this).next(".views-field-body").next(".views-field-field-tags").slideToggle("slow");
      $(this).toggleClass("active");
      return false;
    });

        // Init.
        $(".view-faq .views-field-title").css("text-decoration","underline");
        $(".view-faq .views-field-body").css("display","none");
        $(".view-faq .views-field-field-tags").css("display","none");

        // Expand.
        $(".view-faq a.action-expand").click(function () {
          $(".view-faq .views-field-body").slideDown("slow");
          $(".view-faq .views-field-field-tags").slideDown("slow");
          $(".view-faq .views-field-title").addClass("active");
          return false;
        });

        // Collapse.
        $(".view-faq a.action-collapse").click(function () {
          $(".view-faq .views-field-body").slideUp("slow");
          $(".view-faq .views-field-field-tags").slideUp("slow");
          $(".view-faq .views-field-title").removeClass("active");
          return false;
        });

  });
})(jQuery);
