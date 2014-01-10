<?php
require_once('lib/site.class.php');
require_once('lib/cluster.class.php');
require_once('lib/solrinstance.class.php');
class DrupalMasterSite extends Site {
	private static $cache = array();
	
	public static function flushCache() {
		self::$cache = array();
	}
	
	public function __construct($array) {
		parent::__construct($array);
		$known_fields = array(
			'cluster_id', 
			'sites_local_path',
			'files_local_path',
			'rewritemap_local_path',
			'default_subsite_url_pattern',
			'default_subsite_hostname_pattern',
			'default_subsite_uri_pattern',
			'default_subsite_http',
			'default_subsite_https',
			'default_subsite_install_policy',
			'default_subsite_install_variant',
			'default_subsite_solr_id',
		);
		foreach ($known_fields as $member) {
			$intern_member = $member . '_';
			$this->$intern_member = $array[$member];
		}
	}
	
	
	public static function fetchMasterSiteById($id) {
		if (isset(self::$cache[$id])) return self::$cache[$id];
		
		global $db_conn;
		$query = 'SELECT m.* FROM drupal_master_sites m WHERE id = %d;';
		$query = sprintf($query, mysqli_real_escape_string($db_conn, $id));
		$res = mysqli_query($db_conn, $query);
		if (!$res || !mysqli_num_rows($res)) return null;
		$row = mysqli_fetch_assoc($res);
		$master_object = new DrupalMasterSite($row);
		self::$cache[$id] = $master_object;
		return $master_object;
	}
	
	public function path($item = 'sites') {
		$property_name = $item . '_local_path_';
		if (!isset($this->$property_name)) return null;
		return $this->$property_name;
	}

	public function defaultRewriteMapTarget() {
		$target = 'production';
		$matches = array();
		if (preg_match('/([^\/]+)\/sites\/*$/', $this->path('sites'), $matches)) {
			$target = $matches[1];
		}
		return $target;
	}
	
	public function defaultUrlPattern() {
		return $this->default_subsite_url_pattern_;
	}

	public function defaultUrlHostname() {
		return $this->default_subsite_hostname_pattern_;
	}

	public function defaultUrlURI() {
		return $this->default_subsite_uri_pattern_;
	}

	public function defaultUrlHTTP() {
		return (bool)$this->default_subsite_http_;
	}

	public function defaultUrlHTTPS() {
		return (bool)$this->default_subsite_https_;
	}

	public function defaultUrlProtocol() {
		return $this->defaultUrlHTTPS() ? 'https' : 'http';
	}

	public function defaultInstallPolicy() {
		return $this->default_subsite_install_policy_;
	}
	
	public function defaultInstallVariant() {
		return $this->default_subsite_install_variant_;
	}
	
	public function cluster() {
		if (is_numeric($this->cluster_id_)) {
			$cluster = Cluster::fetchClusterById($this->cluster_id_);
			if (is_object($cluster)) $this->cluster_id_ = $cluster;
		}
		return $this->cluster_id_;
	}
	
	public function defaultSolrInstance() {
		if (is_numeric($this->default_subsite_solr_id_)) {
			$solr_instance = SolrInstance::fetchInstanceById($this->default_subsite_solr_id_);
			if (is_object($solr_instance)) $this->default_subsite_solr_id_ = $solr_instance;
		}
		return $this->default_subsite_solr_id_;
	}
	
	protected $id_;
	protected $cluster_id_;
	protected $name_;
	protected $sites_local_path_;
	protected $files_local_path_;
	protected $rewritemap_local_path_;
	protected $default_subsite_url_pattern_;
	protected $default_subsite_hostname_pattern_;
	protected $default_subsite_uri_pattern_;
	protected $default_subsite_http_;
	protected $default_subsite_https_;
	protected $default_subsite_install_policy_;
	protected $default_subsite_install_variant_;
	protected $default_subsite_solr_id_;
}
