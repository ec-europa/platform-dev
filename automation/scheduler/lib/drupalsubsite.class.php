<?php
require_once('lib/site.class.php');
require_once('lib/drupalmastersite.class.php');
class DrupalSubSite extends Site {
	public function __construct($array) {
		parent::__construct($array);
		foreach (array('url_pattern', 'master', 'state', 'install_policy') as $member) {
			$intern_member = $member . '_';
			$this->$intern_member = $array[$member];
		}
		$this->data_ = array();
		if (strlen($array['data'])) {
			$this->data_ = unserialize($array['data']);
		}
		$this->last_update_ = strtotime($array['last_update']);
	}
	
	public static function fetchIncompleteSubSites() {
		global $db_conn;
		$results = array();
		$query = 'SELECT s.*, w.* FROM drupal_subsites s JOIN workflow_states w ON s.id = w.subsite_id AND w.state <> "%s";';
		$query = sprintf($query, mysqli_real_escape_string($db_conn, constant('STATE_DONE')));
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
	
	public function installPolicy() {
		if (!strlen(trim($this->install_policy_))) {
			return $this->master()->defaultInstallPolicy();
		}
		return trim($this->install_policy_);
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
	
	protected $url_pattern_;
	protected $install_policy_;
	protected $master_;
	protected $state_;
	protected $last_update_;
	protected $data_;
};
