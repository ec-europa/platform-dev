/* Use this script if you need to support IE 7 and IE 6. */

window.onload = function() {
	function addIcon(el, entity) {
		var html = el.innerHTML;
		el.innerHTML = '<span style="font-family: \'multisite-icons\'">' + entity + '</span>' + html;
	}
	var icons = {
			'multisite-icon-vcard' : '&#xe015;',
			'multisite-icon-checkbox' : '&#xe014;',
			'multisite-icon-thumbs-up' : '&#xe013;',
			'multisite-icon-share' : '&#xe012;',
			'multisite-icon-light-bulb' : '&#xe011;',
			'multisite-icon-mail' : '&#xe010;',
			'multisite-icon-directions' : '&#xe00f;',
			'multisite-icon-code' : '&#xe00e;',
			'multisite-icon-list' : '&#xe00d;',
			'multisite-icon-publish' : '&#xe00c;',
			'multisite-icon-language' : '&#xe00b;',
			'multisite-icon-pictures' : '&#xe00a;',
			'multisite-icon-archive' : '&#xe009;',
			'multisite-icon-paperplane' : '&#xe008;',
			'multisite-icon-megaphone' : '&#xe007;',
			'multisite-icon-feed' : '&#xe006;',
			'multisite-icon-question' : '&#xe005;',
			'multisite-icon-link' : '&#xe001;',
			'multisite-icon-earth' : '&#xe004;',
			'multisite-icon-copy' : '&#xe002;',
			'multisite-icon-book' : '&#xe003;',
			'multisite-icon-calendar' : '&#xe000;'
		},
		els = document.getElementsByTagName('*'),
		i, attr, html, c, el;
	for (i = 0; i < els.length; i += 1) {
		el = els[i];
		attr = el.getAttribute('data-icon');
		if (attr) {
			addIcon(el, attr);
		}
		c = el.className;
		c = c.match(/multisite-icon-[^\s'"]+/);
		if (c && icons[c[0]]) {
			addIcon(el, icons[c[0]]);
		}
	}
};