(function ($) {

$(document).ready(function() {
  $('.node-type-wiki .node-wiki>.content').prepend('<fieldset><ul id="toc"/></fieldset>');
    $("#toc").tableOfContents(
      $(".node-type-wiki .node-wiki>.content"),      // Scoped to div#wrapper
      {
        startLevel: 2,    // H2 and up
        depth:      5,    // H2 through H6,
        topLinks:   true, // Add "Top" Links to Each Header
      }
    ); 

  });
}(jQuery));
