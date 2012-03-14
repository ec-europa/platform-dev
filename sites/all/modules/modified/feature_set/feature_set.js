jQuery(function($){ 
  $(document).ready( function(){ 
    //Add class to switcher column
    $("#feature-set-admin-form .form-type-checkbox").each(function() {
      $(this).addClass('switch');  
    });
    
    //Add class to row if button is disabled
    $("#feature-set-admin-form tr").each(function() {
      if ($(this).find('.switch').is('.form-disabled')) {
        $(this).addClass('form-disabled');
      }
    });  
  
    //Add switcher before checkbox and hide checkbox
    $("#feature-set-admin-form .form-checkbox").each(function() {
      $this = $(this);
      //Check if the feature has been enabled
      if ($this.is(':checked')) {
        var html_before = '<label class="cb-enable selected"><span><i class="icon-ok icon-white"></i></span></label><label class="cb-disable"><span><i class="icon-remove icon-white"></i></span></label>';
      } else {
        var html_before = '<label class="cb-enable"><span><i class="icon-ok icon-white"></i></span></label><label class="cb-disable selected"><span><i class="icon-remove icon-white"></i></span></label>';
      }     
      
      $this
        .before(html_before)
        .css('opacity',0);
    });

    //Manage click on a row
    $('#feature-set-admin-form tr').on('click', function() {
      //get switcher
      var $this = $(this),
          switcher = $this.find('.switch');          
      
      //check if button is disabled
      if (!($this.is('.form-disabled'))) {    
      
        //add pending status
        switcher.toggleClass('pending');
        
        //change button
        switcher.children('label').each(function() {
          $(this).toggleClass('selected');
        });
        
        //check or uncheck checkbox
        checkbox = switcher.children('.form-checkbox');
        if (checkbox.attr('checked')) {
          checkbox.attr('checked', false);
        } else {
          checkbox.attr('checked', true);
        }        
      }
    });
  });
});