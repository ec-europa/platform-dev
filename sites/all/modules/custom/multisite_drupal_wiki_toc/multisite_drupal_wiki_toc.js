(function ($) {
  $(document).ready(function() {
    $('.node-wiki > .content .field-name-body').prepend('<ul id="toc"/>');
    $("#toc").tableOfContents(
      $(".node-type-wiki .node-wiki>.content"),
      {
        startLevel: 2,    // H2 and up
        depth:      5,    // H2 through H6,
        topLinks:   false, // Add "Top" Links to Each Header
      }
    ); 

    if ($("#toc li").length > 0) {
      $("#toc").addClass('well well-sm');
    }
  });
}(jQuery));
