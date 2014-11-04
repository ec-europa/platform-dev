ec_site_name = 'Commissioners';
ec_protocol = 'https';
ec_domain = 'ec.europa.eu';
ec_base_path = '/commission/';
ec_base_url = ec_protocol + '://' + ec_domain + ec_base_path;

// For a change, we do not want the crawling to start from the base URL; we
// want it to start from its localized variants: /en, /es, etc.
ec_start_urls = [];
var languages = ['en', 'bg', 'cs', 'da', 'de', 'el', 'fr', 'ga', 'hr', 'hu', 'it', 'lt', 'lv', 'mt', 'nl', 'pl', 'pt', 'ro', 'fi', 'sk', 'sl', 'sv'];
languages.forEach(
	function(lang) {
		ec_start_urls.push(ec_base_url + lang);
	}
);

ec_save_url_filepath  = './state/' + ec_protocol + "-" + ec_domain + "-";
ec_save_url_filepath += ec_base_path.replace(/^\//, "").replace(/\//g, "-") + ".urls.json";

// Cookie header (which is systematically forced)
ec_cookie_header = 'language=en; has_js=1';

// sometimes, fetching a few extra resources is better than missing content or
// generating JavaScript errors.
ec_external_resources_whitelist = {
	// any value other than undefined is fine
	'http://ec.europa.eu/wel/socialbookmark/share.js': 1,
};

skip_urls_regexps = [ /\/download_/ ];
