<?php
class DatabaseInstance {
	private static $cache = array();
	
	public static function flushCache() {
		self::$cache = array();
	}
	
	public static function fetchInstanceById($id) {
		global $db_conn;
		if (isset(self::$cache[$id])) return self::$cache[$id];
		
		$query = 'SELECT dbi.* FROM database_instances dbi WHERE id = %d;';
		$query = sprintf($query, mysqli_real_escape_string($db_conn, $id));
		$res = mysqli_query($db_conn, $query);
		if (!$res || !mysqli_num_rows($res)) return null;
		$row = mysqli_fetch_assoc($res);
		$db_object = DatabaseInstance::initFromArray($row);
		self::$cache[$id] = $db_object;
		return $db_object;
	}
	
	private static function initFromArray($array) {
		$dbinstance = new DatabaseInstance();
		foreach (array('id', 'hostname', 'port', 'type') as $member) {
			$intern_member = $member . '_';
			$dbinstance->$intern_member = $array[$member];
		}
		return $dbinstance;
	}
	
	public function id() {
		return $this->id_;
	}
	
	public function hostname() {
		return $this->hostname_;
	}
	
	public function port() {
		return $this->port_;
	}
	
	public function type() {
		return $this->type_;
	}
	
	private $id_;
	private $hostname_;
	private $port_;
	private $type_;
}
