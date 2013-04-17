/* Load this script using conditional IE comments if you need to support IE 7 and IE 6. */

window.onload = function() {
	function addIcon(el, entity) {
		var html = el.innerHTML;
		el.innerHTML = '<span style="font-family: \'multisite-icons\'">' + entity + '</span>' + html;
	}
	var icons = {
			'multisite-icon-flag' : '&#xe000;',
			'multisite-icon-reorder' : '&#xf0c9;',
			'multisite-icon-home' : '&#xe002;',
			'multisite-icon-cogs' : '&#xe001;',
			'multisite-icon-comments-alt' : '&#xf0e6;',
			'multisite-icon-flow-branch' : '&#xe016;',
			'multisite-icon-vcard' : '&#xe015;',
			'multisite-icon-thumbs-up' : '&#xe013;',
			'multisite-icon-share' : '&#xe012;',
			'multisite-icon-light-bulb' : '&#xe011;',
			'multisite-icon-mail' : '&#xe010;',
			'multisite-icon-directions' : '&#xe00f;',
			'multisite-icon-code' : '&#xe00e;',
			'multisite-icon-publish' : '&#xe00c;',
			'multisite-icon-language' : '&#xe00b;',
			'multisite-icon-pictures' : '&#xe00a;',
			'multisite-icon-archive' : '&#xe009;',
			'multisite-icon-paperplane' : '&#xe008;',
			'multisite-icon-megaphone' : '&#xe007;',
			'multisite-icon-feed' : '&#xe006;',
			'multisite-icon-question' : '&#xe005;',
			'multisite-icon-link' : '&#xe004;',
			'multisite-icon-earth' : '&#xe00d;',
			'multisite-icon-check' : '&#xf046;',
			'multisite-icon-file' : '&#xf016;',
			'multisite-icon-newspaper' : '&#xe017;',
			'multisite-icon-calendar' : '&#xf073;',
			'multisite-icon-book' : '&#xf02d;',
			'multisite-icon-edit' : '&#xf044;',
			'multisite-icon-group' : '&#xf0c0;',
			'multisite-icon-camera' : '&#xe003;',
			'multisite-icon-location' : '&#xe018;',
			'multisite-icon-menu' : '&#xe014;',
			'multisite-icon-pie' : '&#xe019;',
			'multisite-icon-list' : '&#xe01a;',
			'multisite-icon-bookmarks' : '&#xe01b;',
			'multisite-icon-notification' : '&#xe01c;'
		},
		els = document.getElementsByTagName('*'),
		i, attr, html, c, el;
	for (i = 0; ; i += 1) {
		el = els[i];
		if(!el) {
			break;
		}
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