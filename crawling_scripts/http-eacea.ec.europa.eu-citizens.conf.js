ec_site_name = 'EACEA site';
ec_protocol = 'http';
ec_domain = 'eacea.ec.europa.eu';
ec_base_path = '/europe-for-citizens';
ec_base_url = ec_protocol + '://' + ec_domain + ec_base_path;

ec_save_url_filepath  = './state/' + ec_protocol + "-" + ec_domain + "-";
ec_save_url_filepath += ec_base_path.replace(/^\//, "").replace(/\//g, "-") + ".urls.json";

// Cookie header (which is systematically forced)
ec_cookie_header = 'language=en; has_js=1';

// do not skip external resources for eacea because of its particular set of mappings
skip_external_resources = false;
