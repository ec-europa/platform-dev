/**
 * @file
 * Javascript functionality for the Multisite Drupal Wiki ToC module.
 */

(function ($) {
  $(document).ready(function() {
    $('.node-wiki > .content .field-name-body').prepend('<ul id="toc"/>');
    $("#toc").tableOfContents(
      $(".node-type-wiki .node-wiki>.content"),
      {
        // H2 and up.
        startLevel: 2,
        // H2 through H6.
        depth:      5,
        // Add "top" links to each header.
        topLinks:   false,
      }
    );

    if ($("#toc li").length > 0) {
      $("#toc").addClass('well well-sm');
    }
  });
}(jQuery));
