<?php
require_once('lib/site.class.php');
require_once('lib/drupalmastersite.class.php');
require_once('lib/solrinstance.class.php');
class DrupalSubSite extends Site {
	public function __construct($array) {
		parent::__construct($array);
		foreach (array('url_pattern', 'master', 'state', 'install_policy', 'install_variant', 'solr_id', 'notes') as $member) {
			$intern_member = $member . '_';
			$this->$intern_member = $array[$member];
		}
		// contacts are simple comma-separated email addresses
		foreach (array('owner_contact', 'technical_contact') as $member) {
			$intern_member = $member . '_';
			$this->$intern_member = explode(',', $array[$member]);
		}
		$this->data_ = array();
		if (strlen($array['data'])) {
			$this->data_ = unserialize($array['data']);
		}
		$this->last_update_ = strtotime($array['last_update']);
		$this->declaration_date_ = strtotime($array['declaration_date']);
	}
	
	public static function fetchAllSubSites() {
		global $db_conn;
		$results = array();
		$query = 'SELECT s.*, w.* FROM drupal_subsites s JOIN workflow_states w ON s.id = w.subsite_id;';
		$res = mysqli_query($db_conn, $query);
		if (!$res) return $results;
		while ($row = mysqli_fetch_assoc($res)) {
			$results[] = new DrupalSubSite($row);
		}
		return $results;
	}

	public static function fetchSubSiteById($id) {
		global $db_conn;
		$query = 'SELECT s.*, w.* FROM drupal_subsites s JOIN workflow_states w ON s.id = w.subsite_id AND s.id = %d;';
		$query = sprintf($query, mysqli_real_escape_string($db_conn, $id));
		$res = mysqli_query($db_conn, $query);
		if (!$res || !mysqli_num_rows($res)) return null;
		$row = mysqli_fetch_assoc($res);
		$master_object = new DrupalSubSite($row);
		return $master_object;
	}

	public static function fetchSubSiteByMaster($id) {
		global $db_conn;
		$results = array();
		$query = 'SELECT s.*, w.* FROM drupal_subsites s JOIN workflow_states w ON s.id = w.subsite_id AND s.master = %d;';
		$query = sprintf($query, mysqli_real_escape_string($db_conn, $id));
		$res = mysqli_query($db_conn, $query);
		if (!$res) return $results;
		while ($row = mysqli_fetch_assoc($res)) {
			$results[] = new DrupalSubSite($row);
		}
		return $results;
	}
	
	public static function fetchIncompleteSubSites() {
		global $db_conn;
		$results = array();
		$query = 'SELECT s.*, w.* FROM drupal_subsites s JOIN workflow_states w ON s.id = w.subsite_id AND w.state <> "%s" JOIN environments e ON s.environment = e.id AND (e.system_user IS NULL OR e.system_user = "%s");';
		$query = sprintf($query, mysqli_real_escape_string($db_conn, constant('STATE_DONE')), mysqli_real_escape_string($db_conn, get_username()));
		$res = mysqli_query($db_conn, $query);
		if (!$res) return $results;
		while ($row = mysqli_fetch_assoc($res)) {
			$results[] = new DrupalSubSite($row);
		}
		return $results;
	}
	
	public function completeUrlPattern() {
		$pattern = $this->urlPattern();
		$complete_pattern = sprintf($pattern, $this->name());
		return($complete_pattern);
	}
	
	public function urlPattern() {
		if (!strlen(trim($this->url_pattern_))) {
			return $this->master()->defaultUrlPattern();
		}
		return trim($this->url_pattern_);
	}

	public function urls() {
		$urls = $this->customUrls();
		if (!count($urls)) {
			$urls = $this->masterInheritedUrls();
		}
		return $urls;
	}

	public function customUrls() {
		global $db_conn;
		$urls = array();

		// We expect each subsite to have 1 to n records in the drupal_subsites_urls table
		$query = 'SELECT hostname, uri, http, https FROM drupal_subsites_urls WHERE subsiteid = %d';
		$query = sprintf($query, mysqli_real_escape_string($db_conn, $this->id()));
		$res = mysqli_query($db_conn, $query);
		if ($res) {
			while ($row = mysqli_fetch_assoc($res)) {
				// NULL columns mean "inherit value from the master site"
				if (is_null($row['hostname'])) {
					$row['hostname'] = sprintf($this->master()->defaultUrlHostname(), $this->name());
				}
				if (is_null($row['uri'])) {
					$row['uri'] = sprintf($this->master()->defaultUrlURI(), $this->name());
				}
				else {
					// some organizations tend to store the URI of the "user" page for various reasons -- remove it
					$row['uri'] = preg_replace('/user\/*$/', '', $row['uri']);
				}
				if ($row['https']) {
					$urls[] = sprintf('https://%s%s', $row['hostname'], $row['uri']);
				}
				if ($row['http']) {
					$urls[] = sprintf('http://%s%s', $row['hostname'], $row['uri']);
				}
			}
		}
		return $urls;
	}

	public function masterInheritedUrls() {
		$urls = array();

		$hostname = sprintf($this->master()->defaultUrlHostname(), $this->name());
		$uri      = sprintf($this->master()->defaultUrlURI(),      $this->name());
		if ($this->master()->defaultUrlHTTPS()) {
			$urls[] = sprintf('https://%s%s', $hostname, $uri);
		}
		if ($this->master()->defaultUrlHTTP()) {
			$urls[] = sprintf('http://%s%s', $hostname, $uri);
		}

		return $urls;
	}
	
	public function installPolicy() {
		if (!strlen(trim($this->install_policy_))) {
			return $this->master()->defaultInstallPolicy();
		}
		return trim($this->install_policy_);
	}
	
	public function installVariant() {
		if (!strlen(trim($this->install_policy_))) {
			return $this->master()->defaultInstallVariant();
		}
		return trim($this->install_variant_);
	}

	public function solrInstance() {
		if (!is_object($this->solr_id_)) {
			if (is_numeric($this->solr_id_)) {
				$solr_instance = SolrInstance::fetchInstanceById($this->solr_id_);
			} else {
				$solr_instance = $this->master()->defaultSolrInstance();
			}
			if (is_object($solr_instance)) $this->solr_id_ = $solr_instance;
		}
		return $this->solr_id_;
	}
	
	public function notes() {
		return $this->notes_;
	}
	
	public function ownerContacts() {
		return $this->owner_contact_;
	}
	
	public function technicalContacts() {
		return $this->technical_contact_;
	}
	
	public function master() {
		if (is_numeric($this->master_)) {
			$master = DrupalMasterSite::fetchMasterSiteById($this->master_);
			if (is_object($master)) $this->master_ = $master;
		}
		return($this->master_);
	}
	
	public function state() {
		return $this->state_;
	}
	
	public function setState($new_state) {
		$this->state_ = $new_state;
	}
	
	public function lastUpdateTimeStamp() {
		return $this->last_update_;
	}
	
	public function declarationTimeStamp() {
		return $this->declaration_date_;
	}
	
	public function data() {
		return $this->data_;
	}
	
	public function setData($data) {
		$this->data_ = $data;
	}
	
	public function saveState() {
		global $db_conn;
		if (!is_numeric($this->id())) return FALSE;
		if (!strlen(trim($this->state()))) return FALSE;
		
		$query = 'REPLACE INTO workflow_states (subsite_id, state, last_update, data) VALUES (%d, \'%s\', CURRENT_TIMESTAMP(), \'%s\')';
		$query = sprintf($query, $this->id(), mysqli_real_escape_string($db_conn, $this->state()), mysqli_real_escape_string($db_conn, serialize($this->data_)));
		return (bool)mysqli_query($db_conn, $query);
	}
	
	/// TODO we should have an "environment" attribute (along with the related methods)
	protected $url_pattern_;
	protected $install_policy_;
	protected $install_variant_;
	protected $solr_id_;
	protected $notes_;
	protected $owner_contact_;
	protected $technical_contact_;
	protected $master_;
	protected $state_;
	protected $last_update_;
	protected $data_;
};
