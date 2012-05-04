jQuery(function($){

	$(document).ready(function() {  //Once the page elements are fully loaded
   
   // make close button for modals works
    $('.modal .close').click(function(e) {
      e.preventDefault();
      $(this).closest('.modal').modal('hide');
    });
  
	});

});  