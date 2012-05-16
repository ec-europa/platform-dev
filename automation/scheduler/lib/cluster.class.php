<?php
class Cluster {
	public static function fetchClusterById($id) {
		global $db_conn;
		$query = 'SELECT c.* from clusters c WHERE id = %d;';
		$query = sprintf($query, mysqli_real_escape_string($db_conn, $id));
		$res = mysqli_query($db_conn, $query);
		if (!$res || !mysqli_num_rows($res)) return null;
		$row = mysqli_fetch_assoc($res);
		$cluster_object = new Cluster($row);
		return $cluster_object;
	}
	
	public function __construct($array) {
		$this->id_ = $array['id'];
		$this->name_ = $array['name'];
		$this->database_instance_ = $array['mysql_instance'];
		$this->sync_command_ = $array['sync_command'];
	}
	
	public function name() {
		return($this->name);
	}
	
	public function databaseInstance() {
		if (is_numeric($this->database_instance_)) {
			$dbinstance = DatabaseInstance::fetchInstanceById($this->database_instance_);
			if (is_object($dbinstance)) $this->database_instance_ = $dbinstance;
		}
		return $this->database_instance_;
	}
	
	public function webServers() {
		global $db_conn;
		$query = 'SELECT ws.hostname AS hostname, ws.port AS port FROM clusters_servers cs JOIN web_servers ws ON cs.web_server_id = ws.id WHERE cs.cluster_id = %d;';
		$query = sprintf($query, mysqli_real_escape_string($db_conn, $this->id_));
		$res = mysqli_query($db_conn, $query);
		if (!$res || !mysqli_num_rows($res)) return null;
		for ($rows = array() ; $row = mysqli_fetch_assoc($res) ; $rows[] = $row);
		return $rows;
	}
	
	public function syncCommand($path = '')  {
		$delimiter = 'sources';
		// if the provided path is absolute, only consider the part after the
		// delimiter
		$regexp = '#^/.*' . $delimiter . '/*(.*)$#';
		if (preg_match($regexp, $path, $matches)) {
			$subset = $matches[1];
		} else {
			$subset = $path;
		}
		return str_replace('@path', $subset, $this->sync_command_);
	}
	
	private $id_;
	private $name_;
	private $database_instance_;
	private $sync_command_;
};
