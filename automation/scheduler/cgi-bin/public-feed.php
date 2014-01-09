<?php
$script_filepath = __FILE__;
$script_dirpath = dirname($script_filepath);
chdir($script_dirpath . '/..');

// require PicoFeed stuff
require('lib/vendor/PicoFeed/Writers/Rss20.php');
use PicoFeed\Writers\Rss20;

// require Scheduler stuff
require('lib/helpers.inc.php');
require('conf/supermaster.inc.php');
if (file_exists('conf/supermaster.local.inc.php')) {
	require('conf/supermaster.local.inc.php');
}
require('lib/drupalsubsite.class.php');

// connect to the database
connect_to_supermaster_database();

// initialize a RSS 2.0 write object
$writer = new Rss20();
$writer->site_url = $_SERVER['PHP_SELF']; // to be improved?
$writer->feed_url = $_SERVER['PHP_SELF'];
$writer->title = 'All existing subsites';

// fetch required subsites
if (isset($_GET['master']) && preg_match('/^[0-9]+$/', $_GET['master'])) {
	$master_id = $_GET['master'];
	$master_site = DrupalMasterSite::fetchMasterSiteById($master_id);
	if (!is_null($master_site)) {
		$writer->title = sprintf('All existing subsites for master "%s"', $master_site->name());
	}
	$subsites = DrupalSubSite::fetchSubSiteByMaster($master_id);
	$display_master = FALSE;
}
else {
	$subsites = DrupalSubSite::fetchAllSubSites();
	$display_master = TRUE;
}

// compile data into a formatted description
foreach ($subsites as $subsite) {
	$urls = $subsite->urls();

	/* Title */
	if ($display_master) {
		$title = sprintf('%s (%s)', $subsite->name(), $subsite->master()->name());
	}
	else {
		$title = $subsite->name();
	}

	/* Content */
	$content  = '';

	// URLs
	$content .= "<p>All known URLs:</p>\n";
	$content .= "<ul>\n";
	foreach ($urls as $url) {
		$content .= "<li>$url</li>\n";
	}
	$content .= "</ul>\n";

	// Owner contacts
	$content .= "<p>Owner contacts:</p>\n";
	$content .= "<ul>\n";
	foreach ($subsite->ownerContacts() as $owner_contact) {
		$content .= "<li>$owner_contact</li>\n";
	}
	$content .= "</ul>\n";
	
	// Technical contacts
	$content .= "<p>Technical contacts:</p>\n";
	$content .= "<ul>\n";
	foreach ($subsite->technicalContacts() as $tech_contact) {
		$content .= "<li>$tech_contact</li>\n";
	}
	$content .= "</ul>\n";

	$notes = $subsite->notes();
	if (strlen($notes)) {
		$content .= "<p>Notes: " . $notes . "</p>\n";
	}

	// Hand data to PicoFeed
	$writer->items[] = array(
		'title' => $title,
		'updated' => $subsite->lastUpdateTimeStamp(),
		'url' => $urls[count($urls) - 1],
		'content' => $content,
	);
}

echo $writer->execute();
