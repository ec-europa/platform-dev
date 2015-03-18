/**
 * @file d4eu.js
 * D4EU main js file.
 */
var D4EU = {};

function $dc(v) {
  return document.createElement(v);
}

/**
 * Initializes navigation for mobile devices.
 */
D4EU.initNavForMobile = function (isLast) {
  if (D4EU.initNavForMobileIsInit)
    return true;
  if (isLast)
    D4EU.initNavForMobileIsInit = true;

  var mNav = jQuery("#main-navigation")[0];
  if (mNav) {
    var h = jQuery(".panel-heading", mNav)[0];
    if (h) {
      h.onclick = function () {
        jQuery(this.parentNode).toggleClass("showMenu");
      }
    } else {
      if (console && console.error) {
        console.error("header for main menu link for mobile is missing from '.panel-heading' in '#main-navigation'");
      }
    }
    return true;
  } else {
    return D4EU.initNavForMobileIsInit;
  }
};

/**
 * Initializes navigation to follow scroll when user scrolls up.
 */
D4EU.setNavFollowingScroll = function (isLast) {
  if (D4EU.setNavFollowingScrollIsInit)
    return true;

  if (isLast)
    D4EU.setNavFollowingScrollIsInit = true;

  var mNav = jQuery("#main-navigation")[0];
  var body = jQuery("body")[0];
  if (body && mNav) {
    D4EU.showMenuFromFolScroll = function () {
      jQuery("#layout #main-navigation .block-menu-block").addClass("showMenu");
      window.scrollTo(0, 0);
    };
    var fNav = D4EU.navFollowingScroll = document.createElement("nav");
    fNav.innerHTML = mNav.innerHTML.replace('panel-heading">', 'panel-heading" onclick="D4EU.showMenuFromFolScroll();">');
    s = fNav.style;
    s.position = "fixed";
    s.top = "-50px";
    s.left = "0px";
    s.width = "100%";
    s.height = "inherit";
    s.zIndex = "1035";
    s.boxShadow = "0px 3px 3px rgba(0,0,0,0.1)";
    s.backgroundColor = "#E7F1F7";
    s.WebkitTransition = s.MozTransition = s.transition = "top 0.5s";
    fNav.id = mNav.id;
    fNav.className = mNav.className + " scrollFollowNav";
    body.appendChild(fNav);

    var loseHover = D4EU.navFollowingLoseHover = document.createElement("div");
    loseHover.innerHTML = "&#160;";
    s = loseHover.style;
    s.position = "fixed";
    s.top = "0px";
    s.left = "0px";
    s.width = "100%";
    s.height = "100vh";
    s.zIndex = "1036";
    s.display = "none";
    body.appendChild(loseHover);

    D4EU.navFollowingScrollPreviousState = {scrl: 0, type: false};

    jQuery(window).scroll(function () {
      var nav = jQuery("#layout #main-navigation")[0];
      var adminMenu = jQuery("#admin-menu")[0];
      if (!adminMenu)adminMenu = jQuery("#toolbar")[0];
      if (adminMenu)adminMenu = adminMenu.offsetHeight;
      else adminMenu = 0;
      var topNavPos = nav.offsetTop + nav.offsetHeight - adminMenu;

      var scrTop = jQuery(window).scrollTop();
      var curState = {
        scrl: scrTop,
        type: scrTop > topNavPos && scrTop <= D4EU.navFollowingScrollPreviousState.scrl
      };
      if (curState.type != D4EU.navFollowingScrollPreviousState.type) {
        D4EU.navFollowingScroll.style.top = D4EU.navFollowingScrollPreviousState.type ? "-50px" : (adminMenu - 1) + "px";
        D4EU.navFollowingLoseHover.style.display = "block";
        setTimeout(function () {
          D4EU.navFollowingLoseHover.style.display = "none";
        }, 50);
      }
      D4EU.navFollowingScrollPreviousState = curState;
    });

    return true;
  }

}

/**
 * Initializes pager to fit with responsive rendering.
 */
D4EU.initPager = function (isLast) {
  if (D4EU.initPagerIsInit)
    return true;

  var pgItems = jQuery(".pager");
  for (var i = 0; i < pgItems.length; i++) {
    pgItems[i].parentNode.className += " pagerContainer";
    var pg = jQuery("li", pgItems[i]);
    var lstPg = [];
    var cur = -1;
    for (var j = 0; j < pg.length; j++) {
      if (pg[j].className.indexOf("pager-current") > -1) {
        cur = 1;
        for (var k = lstPg.length - 1; k >= 0; k--) {
          lstPg[k].className += " js_pager-item-dist" + (lstPg.length - k);
        }
        pgItems[i].className += " js_pagerCurrentPos" + (lstPg.length + 1);
      }
      if (pg[j].className.indexOf("pager-item") > -1) {
        if (cur < 0)lstPg.push(pg[j]);
        else pg[j].className += " js_pager-item-dist" + (cur++);
      }
    }
  }
  ;

  if (isLast || pgItems.length > 0) {
    D4EU.initPagerIsInit = true;
    return true;
  }
};

/**
 * Runs the initialization.
 */
function initASAP() {
  var isInit = true;
  isInit = isInit && (D4EU.initNavForMobileIsInit = D4EU.initNavForMobile());
  isInit = isInit && (D4EU.setNavFollowingScrollIsInit = D4EU.setNavFollowingScroll());
  isInit = isInit && (D4EU.initPagerIsInit = D4EU.initPager());

  if (!isInit) {
    setTimeout(initASAP, 50);
  }
};

initASAP();

/**
 * Runs the final initialization.
 * */
(function ($) {
  Drupal.behaviors.digitalAgenda = {
    attach: function (context, settings) {
      D4EU.initNavForMobile(true);
      D4EU.setNavFollowingScroll(true);
      D4EU.initPager(true);
    }
  };


})(jQuery);
