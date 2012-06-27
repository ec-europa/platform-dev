/**
 *  This javascript file adds a "Select All" button to the form that allows
 *  an administrator to select the ECAS users he wishes to import.
 */

// Checks or unchecks every edit-fs-* checkboxes, i.e. users
function selectAllEcasUsers(checked) {
	checkboxes = document.getElementsByTagName('input');
	for (var i = 0 ; i < checkboxes.length ; ++ i) {
		if (checkboxes[i].type != 'checkbox') continue;
		if (checkboxes[i].id.indexOf('edit-fs-') == -1)  continue;
		checkboxes[i].checked = checked;
	}
	
	updateLink('check_users_link_top',    checked);
	updateLink('check_users_link_bottom', checked);
}

// Changes the text and url of a given link to provide either check or uncheck feature
function updateLink(link_id, checked) {
	link = document.getElementById(link_id);
	if (link == null) return;
	link.innerHTML = checked ? 'Uncheck all users' : 'Check all users';
	link.href = checked ? 'javascript:selectAllEcasUsers(false);' : 'javascript:selectAllEcasUsers(true);';
}
