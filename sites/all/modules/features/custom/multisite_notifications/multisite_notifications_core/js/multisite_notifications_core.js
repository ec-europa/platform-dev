(function ($) {

  Drupal.behaviors.multisite_notifications_core = {
    attach: function(context, settings) {


    }
  };

})(jQuery);


//use jQuery 1.4.4
//MOVE HERE ALL THE CODE THAT NEEDS TO BE EXECUTED AS LAST
jQuery(function($){

  $(document).ready(function() {  //Once the page elements are fully loaded
    var Input = $('#multisite-notifications-core-form input[name=mail]');
    var default_value = Input.val();

    $(Input).focus(function() {
        if($(this).val() == default_value)
        {
             $(this).val("");
        }
    }).blur(function(){
        if($(this).val().length == 0) /*Small update*/
        {
            $(this).val(default_value);
        }
    });
  });



});