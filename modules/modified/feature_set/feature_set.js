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
        var html_before = '<label class="cb-enable selected"><span>On</span></label><label class="cb-disable"><span>Off</span></label>';
        var row = $(this).parents('tr');
        row.addClass('gradient');
      } else {
        var html_before = '<label class="cb-enable"><span>On</span></label><label class="cb-disable selected"><span>Off</span></label>';
      }     
      
      $(this).before(html_before);
      $(this).css('opacity',0);
    });
      

    
    //Manage click on switcher  
    $(".cb-enable").click(function(){
      var parent = $(this).parents('.switch');
      $('.cb-disable',parent).removeClass('selected');
      $(this).addClass('selected');
      $('.form-checkbox',parent).attr('checked', true);
    });
    $(".cb-disable").click(function(){
      var parent = $(this).parents('.switch');
      $('.cb-enable',parent).removeClass('selected');
      $(this).addClass('selected');
      $('.form-checkbox',parent).attr('checked', false);
    });
  });
});