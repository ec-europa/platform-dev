<?php
class SolrInstance {
	private static $cache = array();
	
	public static function fetchInstanceById($id) {
		global $db_conn;
		if (isset($cache[$id])) return $cache[$id];
		
		$query = 'SELECT si.* FROM solr_instances si WHERE id = %d;';
		$query = sprintf($query, mysqli_real_escape_string($db_conn, $id));
		$res = mysqli_query($db_conn, $query);
		if (!$res || !mysqli_num_rows($res)) return null;
		$row = mysqli_fetch_assoc($res);
		$db_object = SolrInstance::initFromArray($row);
		$cache[$id] = $db_object;
		return $db_object;
	}
	
	private static function initFromArray($array) {
		$dbinstance = new SolrInstance();
		foreach (array('id', 'name', 'url') as $member) {
			$intern_member = $member . '_';
			$dbinstance->$intern_member = $array[$member];
		}
		return $dbinstance;
	}
	
	public function id() {
		return $this->id_;
	}
	
	public function name() {
		return $this->name_;
	}
	
	public function url() {
		return $this->url_;
	}
	
	private $id_;
	private $name_;
	private $url_;
}
