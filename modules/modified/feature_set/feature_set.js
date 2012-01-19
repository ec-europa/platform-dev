jQuery(function($){ 
  $(document).ready( function(){ 
    $("#feature-set-admin-form .form-type-checkbox").each(function() {
      $(this).addClass('switch');  
    });
  
    $("#feature-set-admin-form .form-checkbox").each(function() {
      $html_before = '<label class="cb-enable"><span>On</span></label><label class="cb-disable selected"><span>Off</span></label>';
      
      $(this).before($html_before);
    });
      
      
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