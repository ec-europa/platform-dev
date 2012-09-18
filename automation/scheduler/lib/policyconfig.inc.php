<?php

/**
	Simple singleton class providing get/set static/non-static methods. It is
	intended to be derived by installation policies which need to access their
	configuration somehow.
*/
abstract class PolicyConfig {
	
	public static function getInstance() {
		$current_class = get_called_class();
		if ($current_class === FALSE) return null;
		if (isset(self::$instances[$current_class])) {
			return self::$instances[$current_class];
		} else {
			try {
				$new_instance = new $current_class();
				self::registerInstance($new_instance);
				return $new_instance;
			} catch (Exception $e) {
				return FALSE;
			}
		}
	}

	private static function registerInstance($instance_object) {
		$given_class = get_class($instance_object);
		if ($given_class === FALSE) return;
		if (!isset(self::$instances[$given_class])) {
			self::$instances[$given_class] = $instance_object;
		}
	}

	public static function set($setting, $value) {
		$instance = self::getInstance();
		if ($instance) return $instance->setSetting($setting, $value);
		return null;
	}
	
	public static function get($setting, $fallback_value = null) {
		$instance = self::getInstance();
		if ($instance) return $instance->getSetting($setting, $fallback_value);
		return null;
	}

	public function setSetting($setting, $value) {
		$previous_value = $this->get($setting);
		$this->settings[$setting] = $value;
		return $previous_value;
	}

	public function getSetting($setting, $fallback_value = null) {
		if (isset($this->settings[$setting])) {
			return($this->settings[$setting]);
		}
		return $fallback_value;
	}

	protected $settings;
	private static $instances;
};

