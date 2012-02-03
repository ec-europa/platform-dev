jQuery(function($){ 
  $(document).ready( function(){ 
    //Add class to switcher column
    $("#feature-set-admin-form .form-type-checkbox").each(function() {
      $(this).addClass('switch');  
    });
  
    //Add switcher before checkbox and hide checkbox
    $("#feature-set-admin-form .form-checkbox").each(function() {
      //Check if the feature has been enabled
      if ($(this).is(':checked')) {
        var html_before = '<label class="cb-enable selected"><span><i class="icon-ok icon-white"></i></span></label><label class="cb-disable"><span><i class="icon-remove icon-white"></i></span></label>';
        /*var row = $(this).parents('tr');
        row.addClass('gradient');*/
      } else {
        var html_before = '<label class="cb-enable"><span><i class="icon-ok icon-white"></i></span></label><label class="cb-disable selected"><span><i class="icon-remove icon-white"></i></span></label>';
      }     
      
      $(this).before(html_before);
      $(this).css('opacity',0);
    });

    //Manage click on switcher 
    $('.switch').click(function() {
    
      //check if button is disabled
      if (!$(this).is('.form-disabled')) {    
      
        //add pending status
        $(this).toggleClass('pending');
        
        //change button
        $(this).children('label').each(function() {
          $(this).toggleClass('selected');
        });
        
        //check or uncheck checkbox
        checkbox = $(this).children('.form-checkbox');
        if (checkbox.attr('checked')) {
          checkbox.attr('checked', false);
        } else {
          checkbox.attr('checked', true);
        }        
      }
    });
  });
});