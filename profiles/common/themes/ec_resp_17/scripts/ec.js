/**
 * @file
 * Duplicate of europa script
 */
(function($){  
	Drupal.behaviors.ec_resp_test = {
    attach: function(context, settings) {
			var translations = { // All translations used in webservice
				"en":{"wsD":"Ok","wsE":"Webservice is busy, try later","wsL":"Please wait","wsR":"No languages found"},
				"bg":{"wsE":"Уеб приложението не отговаря, опитайте по-късно.","wsL":"Моля изчакайте","wsR":"Не са намерени преводи на други езици"},
				"cs":{"wsE":"Webová služba je vytížená, zkuste to znovu později","wsL":"Prosím čekejte","wsR":"Nebyly nalezeny žádné jiné jazykové verze"},
				"da":{"wsE":"Webtjenesten er optaget, prøv igen senere","wsL":"Vent venligst","wsR":"Ingen sprog fundet"},
				"de":{"wsE":"Webservice besetzt, später nochmals versuchen ","wsL":"Bitte warten","wsR":"Keine Sprache gefunden"},
				"el":{"wsE":"Η δικτυακή πρόσβαση δεν είναι εφικτή, δοκιμάστε αργότερα","wsL":"Περιμένετε","wsR":"Δεν βρέθηκε καμία γλώσσα"},
				"es":{"wsE":"Servicio web ocupado, inténtelo más tarde","wsL":"Espere","wsR":"No se ha encontrado ningún idioma"},
				"et":{"wsE":"Veebiteenus on hõivatud, proovige hiljem uuesti","wsL":"Palun oodake","wsR":"Muid keeli ei leitud"},
				"fi":{"wsE":"Verkkopalvelu ei ole tällä hetkellä käytettävissä, yritä myöhemmin uudelleen","wsL":"Odota","wsR":"Muita kieliä ei löytynyt"},
				"fr":{"wsE":"Ce service web est occupé. Veuillez réessayer plus tard.","wsL":"Veuillez patienter","wsR":"Aucune autre langue trouvée"},
				"ga":{"wsE":"Tá an suíomh gréasáin gnóthach, bain triail as níos déanaí ","wsL":"Fan, le do thoil","wsR":"Ní bhfuarthas aon teanga "},
				"hu":{"wsE":"A webszolgáltatás foglalt, kérjük, próbálja később!","wsL":"Kérjük várjon","wsR":"Nincs találat"},
				"it":{"wsE":"Servizio web occupato, prova più tardi","wsL":"Attendere prego","wsR":"Nessuna lingua trovata"},
				"lt":{"wsE":"Tinklo tarnyba užimta, bandykite vėliau","wsL":"Prašome palaukti","wsR":"Kalbų nerasta"},
				"lv":{"wsE":"Šis tīmekļa pakalpojums ir noslogots, mēģiniet vēlāk.","wsL":"Lūdzu, uzgaidiet","wsR":"Nav atrasta neviena cita valoda"},
				"mt":{"wsE":"Is-servizz tal-web huwa okkupat, erġa pprova aktar tard","wsL":"Jekk jogħġbok stenna","wsR":"Ma nstabet l-ebda lingwa"},
				"nl":{"wsE":"De webservice is overbelast, probeer het later opnieuw.","wsL":"Even geduld","wsR":"Geen talen gevonden"},
				"pl":{"wsE":"Serwis nie odpowiada, spróbuj później","wsL":"Proszę czekać","wsR":"Nie znaleziono innych języków"},
				"pt":{"wsE":"Serviço Web ocupado. Tente mais tarde.","wsL":"Aguarde","wsR":"Nenhuma língua encontrada"},
				"ro":{"wsE":"Serviciul web este ocupat, vă rugăm reveniţi.","wsL":"Vă rugăm aşteptaţi","wsR":"Nu au fost găsite alte limbi"},
				"sk":{"wsE":"Webová služba je preťažená, vyskúšajte neskôr","wsL":"Čakajte, prosím","wsR":"Preklady do iných jazykov nenájdené"},
				"sl":{"wsE":"Spletna storitev trenutno ni na voljo. Poskusite znova kasneje.","wsL":"Počakajte trenutek.","wsR":"Drugi jeziki niso na voljo"},
				"sv":{"wsE":"Webbtjänsten är upptagen, försök igen senare","wsL":"Var god vänta","wsR":"Hittar inga andra språk"}
			},// global variable
				doc			 	= document,
				docType			= doc.documentElement||doc.body,
				isIE			= /*@cc_on!@*/false,
				isIE6			= isIE&&(!window.XMLHttpRequest),
			corporate={ // scripts used in the banner
				img				:[Drupal.settings.basePath + Drupal.settings.pathToTheme +"/images/arrows-down.gif",Drupal.settings.basePath + Drupal.settings.pathToTheme +"/images/arrows-up.gif"],
				run				:function(){var b=doc.getElementsByTagName('body');if(b.length==1){var c=b[0].className;b[0].className=(c)?"js "+c:"js";}corporate.getDocLang();corporate.langSelector();corporate.minMaxCSS();tools.init();},
				ready			:function(func){if(corporate.domIsReady){func();return;}if(!corporate.loadEvents){corporate.loadEvents=[];}var doc=document;function isReady(){corporate.domIsReady=true;clearInterval(corporate.loadTimer);while(corporate.exec=corporate.loadEvents.shift()){corporate.exec();}if(corporate.ieReady){corporate.ieReady.onreadystatechange='';}}if(!corporate.loadEvents[0]){if(doc.addEventListener){doc.addEventListener("DOMContentLoaded",isReady,false);}else if(isIE){/*document.write("<script id='__ie_onload' defer src='javascript:void(0)'><\/script>");var script=document.getElementById("__ie_onload");script.onreadystatechange=function(){if(this.readyState=="complete"){isReady();}};*/}else if(/WebKit|KHTML|iCab/i.test(navigator.userAgent)){corporate.loadTimer=setInterval(function(){if(/loaded|complete/.test(doc.readyState)){isReady();}},10);}corporate.oldOnload=window.onload;window.onload=function(){isReady();if(corporate.oldOnload){corporate.oldOnload();}};}corporate.loadEvents.push(func);},
				addEvent		:function(o,e,f){if(o.addEventListener){o.addEventListener(e,f,false);}else if(o.attachEvent){if(e=="load"&&window.isLoad){f();return;}if(!o[e]){o[e]=[];}var l=o[e].length;function r(){for(var i=0;i<l+1;i++){o[e][i]();}if(e=="load"){window.isLoad=true;}}o[e][l]=f;o["on"+e]=r;}},
				getDocLang		:function(){var h=doc.getElementsByTagName('html');if(h.length==1){var l=h[0].lang;if(l){doc.lang=l;return;}}var v=corporate.getMetaValue("content-language");if(v){doc.lang=v;return;}var l=window.location+"",u=l.replace( /(.*)(_|-|::|=)([a-zA-Z]{2})(\.|&|#)(.*)/ig,"$3");if(u.length==2&&u){doc.lang=u.toLowerCase();return;}if(!doc.lang){doc.lang="en";}},
				getMetaValue	:function(h){var p=document.getElementsByTagName("meta"),a,o="",l,q,v,n;for(var i=0,j=p.length;i<j;i++){if(p[i].nodeType==1){a=p[i].attributes;l="";q="";for(var k=0,f=a.length;k<f;k++){v=a[k].value;n=a[k].name;if(v!=""&&(n=="name"||n=="http-equiv")){l=v;}else{if(n=="content"){q=v;}}}if(l.toLowerCase()==h.toLowerCase()){o=q;break;}}}return o.toLowerCase();},
				minMaxCSS		:function(){var l=doc.getElementById("layout"),w,ma=null,mi=null;if(l&&isIE6){function r(){w=docType.clientWidth;l.style.width=(w<(mi+2)?mi+"px":(w>(ma+2)&&ma!="auto")?ma+"px":"auto");}if(mi===null||ma===null){mi=parseInt(l.currentStyle.minWidth||l.currentStyle["min-width"],10)||"auto";ma=parseInt(l.currentStyle.maxWidth||l.currentStyle["max-width"],10)||"auto";if(mi=="auto"||ma=="auto"){return;}setTimeout(function(){r();},0);corporate.addEvent(window,"resize",r);}}},
				langSelector	:function(){var	ls=doc.getElementById("language-selector");if(!ls){return;};var li=ls.getElementsByTagName("li"),lk=ls.getElementsByTagName("a"),clk,cli,cur,men="",slc,span,fno=true,a,b,c,d,e,f,img,lng=li.length,lk;ls.className="reset-list language-selector-close";function toggle(){if(ls.isOpen){closeMe();}else{show();this.blur();}}function over(){cur.onblur=null;cur.onfocus=null;timer();}function timer(){clearTimeout(ls.timer);}function show(){timer();ls.className="reset-list language-selector-open";ls.isOpen=true;if(isIE){var ow=ls.offsetWidth;ls.style.width=(ow-2)+"px";setTimeout(function(){ls.removeAttribute("style");},0);}setTimeout(function(){img.src=corporate.img[1];},0);if(lng==1){ls.className="reset-list language-selector-open language-selector-alone";}}function hide(){set(cur);if(ls.isOpen){ls.timer=setTimeout(closeMe,250);}}function closeMe(){timer();ls.className="reset-list language-selector-close";ls.isOpen=false;img.src=corporate.img[0];if(lng==1){ls.className="reset-list language-selector-close";}}function set(elm){elm.onfocus=show;elm.onblur=hide;}function bindEvent(){for(var i=0,l=lk.length;i<l;i++){clk=lk[i];if(i==0){cur=clk;clk.onclick=toggle;}set(clk);}}function builMenu(){var x=0,io="",ifa;for(var i=0,l=li.length;i<l;i++){clk=lk[x];cli=li[i];a=cli.className;b=cli.lang;c=cli.title;if(clk){d=clk.href;e=clk.lang;f=clk.title;}if(a.indexOf("selected")!= -1){span=cli.getElementsByTagName("span")[0].innerHTML;slc="<li class='selected'><a href='javascript:void(0)' lang='"+b+"'><span class='off-screen'>"+span+" </span>"+c+" ("+b+")"+"<img src='"+corporate.img[0]+"' alt='' border='0'></a></li>";}else{if(a.indexOf("non-official")!= -1 && fno==true){io=" class='lang-separate'";fno=false;}else{io=""}men +="<li"+io+"><a href='"+d+"' hreflang='"+e+"' lang='"+e+"'>"+f+" ("+e+")"+"</a></li>";x++;}}ls.innerHTML=slc+""+men;img=ls.getElementsByTagName("img")[0];lk=ls.getElementsByTagName("a");bindEvent();}builMenu();ls.onmouseout=hide;ls.onmouseover=over;}
			},
			tools={ // Some widget tools for the accessibility
				fontSet			:[1,2,3,4],
				init			:function(){var t=doc.getElementById("additional-tools");if(t){this.getFontSize();}},
				setCook			:function(cookName,cookValue,cookDay){var s,e="";if(cookDay){s=new Date();s.setTime(s.getTime()+(cookDay*24*60*60*1000));e=";expires="+s.toGMTString();}doc.cookie=cookName+"="+cookValue+e+";path=/";},
				getCook			:function(cookName,cookDefaultValue){var c,o,n,i,t;o=doc.cookie.split(';');n=cookName+"=";for(i=0,t=o.length;i<t;i++){c=o[i];while(c.charAt(0)==' '){c=c.substring(1,c.length);}if(c.indexOf(n)===0){return c.substring(n.length,c.length);}}return cookDefaultValue||null;},
				getFontSize		:function(){cfz=this.getCook("fontSize");if(!cfz || cfz > 4 || cfz < 0 || isNaN(cfz)){cfz=1;}else{this.applyFontSize(cfz);}},
				applyFontSize	:function(cfz){var n=this.fontSet[cfz];if(n){var b=doc.body,c=b.className.replace(/ font-size-(1|2|3|4|5)/ig,"");b.className=c+" font-size-"+(Math.round(cfz));this.setCook("fontSize",cfz);}},
				increaseFontSize:function(){var l=this.fontSet.length;cfz++;if( cfz > l-1 ){cfz = l-1;}this.applyFontSize(cfz);},
				decreaseFontSize:function(){cfz--;if( cfz <= 0 ){cfz = 1;}this.applyFontSize(cfz);},
				printPage		:function(){print();}
			},
			translate={ // Allow scripts to use a dictionnary in javascript
				label			:function(l){var c="",t=translations[doc.lang],d=translations["en"];if(t){c=(t[l])?t[l]:false;}if(c==""||!c){c=(d[l])?d[l]:"";}return c;},
				add				:function(json){var t=translations,n=json;for(var i in t){if(n[i]){for(var l in n[i]){t[i][l]=n[i][l];}}}for(var i in n){if(!t[i]){t[i]={};for(var l in n[i]){t[i][l]=n[i][l];}}}return t;}
			},
			webservice={ // Retrieve any translations of any documents and showing inside a popup.
				img				:["../images/languages/ws.gif","../images/languages/loading.gif"],
				xhr				:function(){var x=false,w=window;if(w.XMLHttpRequest){x=new XMLHttpRequest();}else if(w.ActiveXObject){x=new ActiveXObject("Microsoft.XMLHTTP");}return x;},
				getViewport		:function(){var v=window,w=v.innerWidth,h=v.innerHeight;return {w:(!w)?docType.clientWidth:w,h:(!h)?docType.clientHeight:h};},
				getPosition		:function(domElm){var x=0,y=0,d=domElm;if(d){try{if(d.offsetParent){do{x +=d.offsetLeft;y +=d.offsetTop;}while(d=d.offsetParent);}}catch(e){};}return [x,y];},
				wrap			:function(srcEl,newEl){if(!srcEl){return;};newEl.appendChild(srcEl.cloneNode(true));if(srcEl.parentNode){srcEl.parentNode.replaceChild(newEl,srcEl);}},
				prevLink		:function(srcElm,tag){var e=srcElm,o=e;for(;e;e=e["previousSibling"]){if( e.nodeType === 1 && e!=o ){break;}}return e;},
				load			:function(c){var u=c["url"],e=c["error"],s=c["success"];if(u!=""&&u!=undefined&&u!=null){var r=webservice.xhr();if(!r){return;}u=u.replace(/&amp;/ig,"&");r.onreadystatechange=function(){if(r.readyState==4){if(r.status!=200&&r.status!=304){if(typeof e=="function"){e(c);}}else{if(typeof s=="function"){s(r.responseText,r.responseXML,c);}else{return {txt:r.responseText,xml:r.responseXML};}}}};r.open("GET",u,true);r.send(null);}},
				popup			:function(srcElm,coverage)
				{
					var e=srcElm,span=e.parentNode,wsUrl=(span)?span.u:null;

				// CREATE THE REF CONTAINER ON THE FLY

					if(span.tagName!="SPAN"){span=document.createElement("span");span.className="ws-popup";webservice.wrap(e,span);if(coverage){wsUrl=span.u=coverage;}else{var p=webservice.prevLink(span,"A");wsUrl=span.u="/cgi-bin/coverage/coverage?url="+encodeURIComponent(decodeURIComponent(p.href));}}

				// DOM CACHE

					var	iso		= span,
						child	= span.getElementsByTagName("span"),
						popup	= child[1],
						img		= span.getElementsByTagName("img")[0],
						imgSrc	= (img)?img.src:webservice.img[0],
						lnk		= e.href,
						cls		= span.className.split(" ")[0],
						v		= webservice.getViewport(),
						p		= webservice.getPosition(span),
						st		= docType.scrollTop||document.body.scrollTop,
						sl		= docType.scrollLeft||document.body.scrollLeft,
						pSpan	= webservice.prevPopup;
						e.href 	= "javascript:void(0)";

						if(!span.oTitle){span.oTitle=e.title;}

				// Close the previous available "POPUP"
					if(pSpan){clearTimeout(pSpan.timer);pSpan.getElementsByTagName("a")[0].title=pSpan.oTitle;var pImg=pSpan.getElementsByTagName("img")[0];if(pImg){pImg.src=imgSrc;pImg.alt=pSpan.oTitle;}setTimeout(function(){pSpan.isOpen=false;},50);pSpan.className=cls;}
				// WS: CLOSE
					if(span.isOpen && wsUrl){if(popup){popup.innerHTML="";}close();}
				// WS: CALL
					else if(wsUrl){wsUrl=wsUrl.replace(/&amp;/ig,"&");webservice.prevPopup=span;pop("wsL",cls+" ws-loading");if(popup){popup.innerHTML="";}else{popup=doc.createElement("span");popup.className="ws-links";span.appendChild(popup)}webservice.prevPopup.timer=setTimeout(function(){webservice.load({url:wsUrl,success:success,error:error});},250);}
				// MODAL WINDOW CLOSE
					else if(span.isOpen){if(popup){popup.style.display="none";}close();}
				// MODAL WINDOW SHOW
					else{if(popup){popup.style.display="block";popup.style.left="-5px";}show();}

				// FUNCTIONS

					function out(){popup.timer=setTimeout(function(){close();},250);}
					function over(){clearTimeout(popup.timer);}
					function restore(elm,cls){if(cls){elm.className=cls;}elm.getElementsByTagName("a")[0].title=elm.oTitle;}
					function bindEvent(){var lnks=popup.getElementsByTagName("a");for(var i=0,l=lnks.length;i<l;i++){lnks[i].onblur=out;lnks[i].onfocus=over;}}
					function getOverflowParent(elm){if(elm.style){if(elm.style.overflow!=""){iso=elm;iso.doit=true;}else{iso=elm.parentNode;getOverflowParent(iso);}}}
					function error(xml){if(xml[0]){pop("wsE",cls + " ws-error",xml[0].firstChild.nodeValue);}else{pop("wsE",cls + " ws-error");}}
					function getList(xml){var h,s,t,v='',p,b,r,a,i,j,e,z,n,l='';z=xml.getElementsByTagName("message");d=xml.getElementsByTagName("document");p=d.length;n=z.length;c=false;k=doc.lang;for(i=0;i<p;i++){b=d[i];r=b.getAttribute("lang");a=b.getAttribute("label");t=b.getAttribute("type");e=b.getAttribute("href").split("#")[0]+window.location.hash;s=a.split("(")[0];l +='<a class="lang" href="'+e+'" hreflang="'+r+'" lang="'+r+'" title="'+a+'"><span class="off-screen">'+s+' (</span>'+r+'<span class="off-screen">)</span></a> ';}return {lst:l,nbr:n,cnt:p,error:z};}
					function success(txt,xml,cfg){var ws=getList(xml);if(ws.lst!==''){pop("wsD",cls,ws.lst);}else if(ws.nbr==0&&ws.cnt==0){pop("wsR",cls+" ws-retry");}else if(ws.nbr>0||ws.lst==""){error(ws.error);}}
					function pop(label,cls,content){var cnt=content,lbl=translate.label(label);cnt=(cnt)?cnt:lbl;span.className=cls;e.title=lbl;if(label!="wsL"){popup.innerHTML="<span class='ws-popup-layout'>"+cnt+"</span>";if(img){img.src=imgSrc;img.alt=lbl;}show();}else{if(img){img.src=webservice.img[1];img.alt=lbl;}}}
					function close(elm){span.getElementsByTagName("a")[0].title=span.oTitle;img=span.getElementsByTagName("img")[0];if(img){img.src=imgSrc;img.alt=span.oTitle;}span.isOpen=false;span.className=cls;var c=span.getElementsByTagName("span");if(c){if(c[1]){c[1].style.left="-9999px";}}if(popup){popup.style.display="none";}e.onblur=function(){};}
					function show(){span.isOpen=true;span.className=cls+" ws-popup-show";var a=span.getElementsByTagName("a");if(a[0]){a[0].focus();}if(popup){popup.style.display="";}
						// POSITION THE POPUP
						var c=span.getElementsByTagName("span"),m=c[1],j=c[2],w,h,vl,vt,o;
						m.style.width="170px";
						m.style.zIndex="9999";
						m.style.top="-5px";
						m.style.left="-5px";
						w=j.offsetWidth;
						h=j.offsetHeight;
						if((p[0]+w)>(v.w+sl)){vl=((p[0]+w)-(v.w+sl));vl=(!isIE)?(vl+20):(vl+5);m.style.left="-"+vl+"px";}
						if((p[1]+h+16)>(v.h+st)){vt=((p[1]+h)-(v.h+st));vt=(!isIE)?(vt+20):(vt+5);m.style.top="-"+vt+"px";}

						// IN OVERFLOW ELEMENT ?
						getOverflowParent(span);if(iso.doit){o=webservice.getPosition(iso);v.w=iso.offsetWidth;v.h=iso.offsetHeight;st=iso.scrollTop;sl=iso.scrollLeft;if(w>v.w){w=Math.round((v.w)-70);j.style.width=w+"px";h=j.offsetHeight;}if((p[0]+w)>o[0]+v.w+sl){m.style.left="-"+(((p[0]+w)-(o[0]+v.w+sl))+30)+"px";}if((p[1]+h+16)>(o[1]+v.h+st)){m.style.top="-"+((p[1]+h+5)-(o[1]+v.h+st)+10)+"px";}}

						// EVENTS
						bindEvent();span.onmouseover=over;span.onmouseout=out;
						if(w){m.style.width=w+"px";}
						setTimeout(function(){e.href=lnk;e.onblur=function(){restore(span);out();};},5);
					}
			}};
			corporate.ready(corporate.run);
		}
	}
})(jQuery);