<?php
require_once('lib/databaseinstance.class.php');

class DatabaseAccount {
	public static function fetchAccountById($id) {
		global $db_conn;
		$query = 'SELECT dba.* from database_accounts dba WHERE id = %d;';
		$query = sprintf($query, mysqli_real_escape_string($db_conn, $id));
		$res = mysqli_query($db_conn, $query);
		if (!$res || !mysqli_num_rows($res)) return null;
		$row = mysqli_fetch_assoc($res);
		$db_object = DatabaseAccount::initFromArray($row);
		return $db_object;
	}
	
	private static function initFromArray($array) {
		$dbaccount = new DatabaseAccount();
		foreach (array('id', 'user', 'password', 'database_instance') as $member) {
			$intern_member = $member . '_';
			$dbaccount->$intern_member = $array[$member];
		}
		return $dbaccount;
	}
	
	public function id() {
		return $this->id_;
	}
	
	public function username() {
		return $this->user_;
	}
	
	public function password() {
		return $this->password_;
	}
	
	public function instance() {
		if (is_numeric($this->database_instance_)) {
			$dbinstance = DatabaseInstance::fetchInstanceById($this->database_instance_);
			if (is_object($dbinstance)) $this->database_instance_ = $dbinstance;
		}
		return $this->database_instance_;
	}
	
	private $id_;
	private $user_;
	private $password_;
	private $database_instance_;
}
