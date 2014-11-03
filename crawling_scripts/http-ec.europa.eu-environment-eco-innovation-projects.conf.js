ec_site_name = 'Eco Innovation Projects';
ec_protocol = 'http';
ec_domain = 'ec.europa.eu';
ec_base_path = '/environment/eco-innovation/projects';
ec_base_url = ec_protocol + '://' + ec_domain + ec_base_path;

ec_save_url_filepath  = './state/' + ec_protocol + "-" + ec_domain + "-";
ec_save_url_filepath += ec_base_path.replace(/^\//, "").replace(/\//g, "-") + ".urls.json";

// Cookie header (which is systematically forced)
ec_cookie_header = 'language=en; has_js=1';

// sometimes, fetching a few extra resources is better than missing content or
// generating JavaScript errors.
ec_external_resources_whitelist = {
	// any value other than undefined is fine
	'http://ec.europa.eu/wel/socialbookmark/share.js': 1,
	'http://b.tile.openstreetmap.org/2/1/0.png': 1,
	'http://c.tile.openstreetmap.org/2/2/0.png': 1,
	'http://a.tile.openstreetmap.org/2/2/1.png': 1,
	'http://c.tile.openstreetmap.org/2/1/1.png': 1,
};

 skip_urls_regexps = [ /projects\/gist/ ];
max_url_length = 130
