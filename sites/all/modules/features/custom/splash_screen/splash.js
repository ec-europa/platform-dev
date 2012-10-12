(function ($) {
    $(document).ready(function(){
        var ckie = readCookie("splash");
        if(Drupal.settings.splash_screen.isadmin==0)        
        {
            if (ckie == null && are_cookies_enabled()==true  ){ //Check to see if a cookie with name of "query" exists
                window.location.replace(Drupal.settings.splash_screen.base_url + "/" + Drupal.settings.splash_screen.splash);
                createCookie("splash","splash",365);
            }
            else if(are_cookies_enabled()==true && window.location==Drupal.settings.splash_screen.base_url)
                window.location.replace(Drupal.settings.splash_screen.base_url+"/"+readCookie(Drupal.settings.splash_screen.cookie_name));
        }
        
        $('ul.languages li a').click(function() {
            $lg = $(this).find("span").html();

            $.cookie(Drupal.settings.splash_screen.cookie_name, $lg, {
                expires: 365
            });
	  
            return true;
        });
	  	
    });
})(jQuery);

function readCookie(name) {
    var nameEQ = name + "=";
    var ca = document.cookie.split(';');
    for(var i=0;i < ca.length;i++) {
        var c = ca[i];
        while (c.charAt(0)==' ') c = c.substring(1,c.length);
        if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
    }
    return null;
}

function createCookie(name,value,days) {
    if (days) {
        var date = new Date();
        date.setTime(date.getTime()+(days*24*60*60*1000));
        var expires = "; expires="+date.toGMTString();
    }
    else var expires = "";
    document.cookie = name+"="+value+expires+"; path=/";
}

function are_cookies_enabled()
{
    var cookieEnabled = (navigator.cookieEnabled) ? true : false;

    if (typeof navigator.cookieEnabled == "undefined" && !cookieEnabled)
    {
        document.cookie="testcookie";
        cookieEnabled = (document.cookie.indexOf("testcookie") != -1) ? true : false;
    }
    return (cookieEnabled);
}

