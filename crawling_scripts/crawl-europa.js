// Note: you might need to adjust some system limits like max number of open
// files (ulimit -n 15000).
var args = require('system').args;
var fs = require('fs');
var spawn = require('child_process').spawn;

// argument parsing
var is_child = false;
var must_resume = false;
var conf_file = false;
var child_urls = [];
var current_script = args[0];
for (i = 1; i < args.length; ++ i) {
	arg = args[i];
	if (arg == '--resume') must_resume = true;
	if (arg == '--child') is_child = true;
	if (!conf_file && fs.exists(arg)) {
		say("About to load " + arg + " as configuration file");
		require(arg);
		conf_file = arg;
	}
	if ((/^https?:\/\//).test(arg)) {
		child_urls.push(arg);
	}
};

// initial list of URLs to crawl -- defaults to ec_base_url
if (typeof ec_start_urls == 'undefined') {
	ec_start_urls = [ec_base_url];
}

// set default parameters if they were not already set by the configuration file
// maximum time spent trying to load a page and its resources, in milliseconds
if (typeof ec_page_timeout == 'undefined') ec_page_timeout = 50000;

// pause time between pages, in milliseconds
if (typeof ec_page_sleep == 'undefined') ec_page_sleep = 800;

// number of URL child processes should treat
if (typeof urls_per_child == 'undefined') urls_per_child = 10;

// User Agent
ec_user_agent_header = 'Mozilla/5.0 (Unknown; Linux x86_64) AppleWebKit/534.34 (KHTML, like Gecko) PhantomJS/1.9.0 Safari/534.34';
if (typeof ec_site_name != 'undefined' && ec_site_name.length) {
	ec_user_agent_header += ' [FPFIS cache filler for ' + ec_site_name + ']';
}
else {
	ec_user_agent_header += ' [FPFIS cache filler for unnamed site]';
}

// whether to display the URL list from time to time
if (typeof ec_display_url_list == 'undefined') ec_display_url_list = true;

// the url list will be displayed every 15 requests
if (typeof ec_display_url_list_every == 'undefined') ec_display_url_list_every = 15;

// whether to save the URL list (useful to recover from PhantomJS/Qt/WebKit crashes)
if (typeof ec_save_url_list == 'undefined') ec_save_url_list = true;

// filepath the URL list shall be saved to
if (typeof ec_save_url_filepath == 'undefined') {
	ec_save_url_filepath = conf_file.replace(/\.conf\.js$/, '.urls.json');
	say("will use " + ec_save_url_filepath + " as url filepath");
}

// sometimes, fetching a few extra resources is better than missing content or
// generating JavaScript errors.
if (typeof skip_external_resources == 'undefined') {
	skip_external_resources = true;
}
if (typeof ec_external_resources_whitelist == 'undefined') {
	ec_external_resources_whitelist = {};
}

// Avoid crawling very long URLs, they are probably a waste of time
if (typeof max_url_length == 'undefined') max_url_length = 300;

// skip_urls_regexp allows to define extra URLs pattern which should not be crawled
if (typeof skip_urls_regexps == 'undefined') skip_urls_regexps = [];





if (!is_child) {
	/* These 3 variables are used to keep track of the crawling. */

	// This array contains simple objects having two properties: url and visited
	var urls = [];
	// In order to quickly determine the state of a given URL, this object maps URLs
	// to their index in the "urls" array
	var urls_index = {};
	// This simple integer is used to crawl through the "urls" array.
	var index = 0;

	if (must_resume) {
		try {
			say('Trying to resume from ' + ec_save_url_filepath);

			var resume_file_content = fs.read(ec_save_url_filepath);
			if (!resume_file_content) throw 'Unable to read ' + ec_save_url_filepath;

			// parse read content (we expect JSON)
			resume_file_content = JSON.parse(resume_file_content);

			if (urls in resume_file_content) throw 'no "urls" property found';
			if (urls_index in resume_file_content) throw 'no "urls_index" property found';
			if (index in resume_file_content) throw 'no "index" property found';

			var urls_length = resume_file_content['urls'].length;
			var urls_index_lenth = Object.keys(resume_file_content['urls_index']).length;
			if (urls_length !== urls_index_lenth) {
				throw 'Index length does not match URLs list (' + urls_length + ' vs ' + urls_index_lenth + ')';
			}

			urls = resume_file_content['urls'];
			urls_index = resume_file_content['urls_index'];
			index = resume_file_content['index'];

			say('  Resume from ' + ec_save_url_filepath + ' succeeded');
		} catch (err) {
			say('  Failed to resume from ' + ec_save_url_filepath + ': ' + err);
		}
	}
	else {
		ec_start_urls.forEach(
			function(start_url) {
				addUrl(start_url);
			}
		);
	}
	nextStep();
}
else {
	/* This variable will hold the WebPage object used to crawl the given site */
	say('Received ' + child_urls.length + ' URLs to process');
	var child_page;
	var child_index = 0;
	nextChildStep();
}

function indexForUrl(url) {
	return urls_index[url];
}
function urlIsKnown(url) {
	return urls_index[url] !== undefined;
}
function urlWasAlreadyVisited(url) {
	// unknown URLs are not considered visited
	if (!urlIsKnown(url)) return 0;
	var url_index = indexForUrl(url);
	return urls[url_index]['visited'];
}
function setUrlAsVisited(url) {
	if (!urlIsKnown(url)) return 0;
	var url_index = indexForUrl(url);
	urls[url_index]['visited'] = 1;
}
function addUrl(url) {
	if (urlIsKnown(url)) return 0;
	var url_index = indexForUrl(url);
	urls_index[url] = urls.length;
	urls.push({
		'url': url,
		'visited': 0
	});
	return 1;
}

function abbrev(str, limit) {
	if (limit === undefined) limit = 75;
	if (limit <= 3) return '...';
	if (str.length <= limit) return str;
	return str.substr(0, limit - 3) + '...';
}

function initPage() {
	child_page = require('webpage').create();
	child_page.onResourceRequested = function(requestData, request) {
		if (skip_external_resources) {
			// if the requested resource URL does not belong to the crawled
			// website (i.e. it is an external resource)...
			if (requestData['url'].indexOf(ec_base_url) !== 0) {
				// and if the said URL was not explicitly whitelisted...
				if (ec_external_resources_whitelist[requestData['url']] === undefined) {
					// then skip it.
					say('    Skipping external resource ' + abbrev(requestData['url']));
					request.abort();
					return;
				}
			}
		}
		// otherwise, announce that it will be fetched
		say('    Fetching ' + requestData['url']);
	}

	// disable cookies management
	phantom.clearCookies();
	phantom.cookiesEnabled = false;

	// force the user-agent header for all outgoing requests
	var custom_headers = {
		'User-Agent': ec_user_agent_header,
	};
	// optionally force the Cookie header for all outgoing requests
	if (typeof ec_cookie_header != 'undefined') {
		custom_headers['Cookie'] = ec_cookie_header;
	}
	child_page.customHeaders = custom_headers;
}

function extractLinksFromPage() {
	var links_array = [];
	links = document.getElementsByTagName('a');
	for (var i = 0; i < links.length; ++ i) {
		links_array.push(links.item(i).href);
	}
	return links_array;
}

function filterLinks(links, parent_page_url) {
	// While some pages may behave differently depending on anchor,
	// we explicitly choose to discard anchors in URLs to reduce
	// duplicates.
	links = links.map(
		function (link) {
			return link.replace(/#.*$/, '');
		}
	);

	var empty_links = 0;
	var javascript_links = 0;
	var external_links = 0;
	var local_anchor_links = 0;
	var too_long_links = 0;
	var search_links = 0;
	var printpdf_links = 0;
	var calendar_links = 0;
	var multiple_facets_links = 0;
	var login_destination_links = 0;
	var user_skipped_links = 0;
	var duplicate_links = 0;
	links = links.filter(
		function(link, index, self) {
			if ((/^ *$/).test(link)) {
				++ empty_links;
				return 0;
			}
			if ((/javascript:/).test(link)) {
				++ javascript_links;
				return 0;
			}
			if (link.indexOf(ec_base_url) !== 0) {
				++ external_links;
				return 0;
			}
			var relative_url = link.substr(parent_page_url.length);
			if ((/^\/*#/).test(relative_url)) {
				++ local_anchor_links;
				return 0;
			}
			if (max_url_length > 0 && link.length > max_url_length) {
				++ too_long_links;
				return 0;
			}
			if ((/search\/site\/?\?f/).test(link)) {
				++ search_links;
				return 0;
			}
			if ((/\/printpdf\//).test(link)) {
				++ printpdf_links;
				return 0;
			}
			if ((/\/calendar-node-field-date\//).test(link)) {
				++ calendar_links;
				return 0;
			}
			if ((/ecas(logout)?(\/|\?|$)/).test(link)) {
				return 0;
			}
			if ((/=([is]m_field_|bundle|ds_).+=([is]m_field_|bundle|ds_)/).test(link)) {
				++ multiple_facets_links;
				return 0;
			}
			if ((/user\/(login|register)\?destination=/).test(link)) {
				++ login_destination_links;
				return 0;
			}
			for (var i = 0; i < skip_urls_regexps.length; ++ i) {
				if ((skip_urls_regexps[i]).test(link)) {
					++ user_skipped_links;
					return 0;
				}
			}
			if (self.indexOf(link) !== index) {
				++ duplicate_links;
				return 0;
			}
			return 1;
		}
	);
	say('    ' + empty_links + ' empty links');
	say('    ' + javascript_links + ' javascript links');
	say('    ' + external_links + ' external links');
	say('    ' + local_anchor_links + ' anchor links');
	say('    ' + too_long_links + ' too long links');
	say('    ' + search_links + ' search links');
	say('    ' + printpdf_links + ' printpdf links');
	say('    ' + calendar_links + ' calendar links');
	say('    ' + multiple_facets_links + ' multiple facets links');
	say('    ' + login_destination_links + ' login+destination links');
	say('    ' + user_skipped_links + ' links skipped according to user configuration');
	say('    ' + duplicate_links + ' duplicate links');
	say('    ' + links.length + ' remaining links');

	return links;
}

function say(string) {
	if (is_child) {
		console.log('=' + string);
	}
	else {
		console.log(string);
	}
}

function nextStep() {
	if (index >= urls.length) {
		say('Finished!');
		phantom.exit();
	}

	var index_end = index;
	var process_args = [current_script, '--child', conf_file];
	for (i = index; i < index + urls_per_child && i < urls.length; ++ i) {
		process_args.push(urls[i]['url']);
		++ index_end;
	}
	say('Now treating indexes ' + index + ' to ' + (index_end - 1));

	say('  Launching child process...');
	var child_ended = false;
	var child_exited = false;
	var child = spawn('phantomjs', process_args);
	say('    Spawned pid ' + child.pid);
	child.stdout.on('data', function(data) {
		// ensure we analyze the child process stdout line by line
		lines = data.match(/[^\r\n]+/g);
		lines.forEach(
			function(line) {
				// lines starting with + are meant to be parsed in order to
				// follow the progress of the child process
				if ((/^\+DISCOVEREDLINK (.*)$/).test(line)) {
					// the child process discovered a link
					addUrl(line.replace(/^\+DISCOVEREDLINK /, ''));
				}
				else if ((/^\+VISITEDURL (.*)$/).test(line)) {
					// the child process crawled a URL
					var visited_url = line.replace(/^\+VISITEDURL /, '');
					setUrlAsVisited(visited_url);
				}
				else if ((/^\+END$/.test(line))) {
					// the child process has finished its work and will exit
					child_ended = true;
				}
				say('      ' + line.replace(/(\r\n|\n|\r)/gm, ''));
			}
		);
	});
	child.on('exit', function(code) {
		// prevent this function from being called twice for a same process
		if (child_exited) return;
		child_exited = true;
		
		if (child_ended) {
			say('    Child process exited as expected after its work.');
			index = index_end;
		}
		else {
			say('    Child process exited before finishing its work!');
			// determine the lowest index (among the current batch) which was not visited as expected
			for (i = index; i < index + urls_per_child && i < urls.length; ++ i) {
				if (!urls[i]['visited']) {
					say('      Adjusting index to ' + i);
					index = i;
					break;
				}
			}
		}

		say('  There is now a total of ' + urls.length + ' URLs');
		// display links if required by configuration
		if (ec_display_url_list) {
			if (index % ec_display_url_list_every === 0) {
				urls.forEach(function(l) { say('    ' + l['url']); } );
			}
		}

		// save links if required by configuration
		if (ec_save_url_list) {
			var file_content = JSON.stringify({'urls': urls, 'urls_index': urls_index, 'index': index});
			fs.write(ec_save_url_filepath, file_content, 'w');
		}

		setTimeout(nextStep, ec_page_sleep);
	});
}

function nextChildStep() {
	if (child_index >= child_urls.length) {
		console.log('+END');
		phantom.exit();
	}
	var child_current_url = child_urls[child_index];
	say('Now treating received URL #' + (child_index + 1));

	say('  About to load ' + child_current_url);
	initPage();
	child_page.open(child_current_url, function (status) {
		console.log('+VISITEDURL ' + child_current_url);
		if (status !== 'success') {
			console.log('-  Failed to load page ' + child_current_url);
		}
		else {
			say('  Loaded page ' + child_current_url);
			// fetch all links on the page
			var child_page_links = child_page.evaluate(extractLinksFromPage);
			say('  Discovered ' + child_page_links.length + ' links.');
			child_page_links = filterLinks(child_page_links, child_current_url);
			say('  Kept ' + child_page_links.length + ' links.');
			child_page_links.forEach(
				function(item) { console.log('+DISCOVEREDLINK ' + item); }
			);
		}
		++ child_index;
		setTimeout(nextChildStep, ec_page_sleep);
	});

	setTimeout(
		function(page_to_stop) {
			if (child_index != page_to_stop) return;
			console.log('-    Timeout! Stopping page...');
			child_page.stop();
		},
		ec_page_timeout,
		child_index
	);
}
