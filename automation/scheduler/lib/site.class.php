<?php
require_once('lib/databaseaccount.class.php');
class Site {
	public function __construct($array) {
		foreach (array('id', 'name', 'database_name', 'database_account') as $member) {
			$intern_member = $member . '_';
			$this->$intern_member = $array[$member];
		}
	}
	
	public function id() {
		return $this->id_;
	}
	
	public function name() {
		return $this->name_;
	}
	
	public function databaseName() {
		return $this->database_name_;
	}
	
	public function databaseUsername() {
		$this->getDatabaseAccount();
		return $this->database_account_->username();
	}
	
	public function databasePassword() {
		$this->getDatabaseAccount();
		return $this->database_account_->password();
	}
	
	public function databaseInstance() {
		$this->getDatabaseAccount();
		return $this->database_account_->instance();
	}
	
	public function connectionString($include_password = TRUE) {
		if ($include_password) {
			return sprintf(
				'%s://%s:%s@%s:%d/%s',
				$this->databaseInstance()->type(),
				$this->databaseUsername(),
				$this->databasePassword(),
				$this->databaseInstance()->hostname(),
				$this->databaseInstance()->port(),
				$this->databaseName()
			);
		} else {
			return sprintf(
				'%s://%s@%s:%d/%s',
				$this->databaseInstance()->type(),
				$this->databaseUsername(),
				$this->databaseInstance()->hostname(),
				$this->databaseInstance()->port(),
				$this->databaseName()
			);
		}
	}
	
	protected function getDatabaseAccount() {
		if (is_numeric($this->database_account_)) {
			$account = DatabaseAccount::fetchAccountById($this->database_account_);
			if (is_object($account)) $this->database_account_ = $account;
		}
	}
	
	protected $id_;
	protected $name_;
	protected $database_name_;
	protected $database_account_;
};
