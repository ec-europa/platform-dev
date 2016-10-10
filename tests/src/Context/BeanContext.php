<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\BeanContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;

/**
 * Context for configuring the Bean.
 */
class BeanContext implements Context {

  /**
   * A random string.
   *
   * @var string
   */
  protected $randomString;

  /**
   * BeanContext constructor.
   */
  public function __construct() {
    $this->randomString = uniqid();
  }

  /**
   * Create a block type.
   *
   * @param string $type
   *   Type of the block.
   *
   * @When /^I create the new block type "([^"]*)"$/
   */
  public function iCreateTheNewBlockType($type) {
    $plugin_info = _bean_admin_default_plugin();
    $plugin_info['name'] = '';

    $bean_type = new \BeanCustom($plugin_info);
    $bean_type->type = $this->getRandomMachineName($type);
    $bean_type->setLabel($type);
    $bean_type->setDescription('Behat');
    $bean_type->save(TRUE);
  }

  /**
   * Set all permissions to admin role.
   *
   * @Given I update the administrator role permissions
   */
  public function iGiveAllPermToAdminRole() {
    if ($rid = variable_get('user_admin_role', 0)) {
      $perms = array();

      foreach (module_implements('permission') as $module) {
        foreach(module_invoke($module, 'permission') as $key => $perm) {
          $perms[$key] = $module;
        }
      }

      if ($perms) {
        foreach ($perms as $perm => $module) {
          $query = db_merge('role_permission');
          $query->key(array(
            'rid' => $rid,
            'permission' => $perm,
          ));
          $query->fields(array(
            'rid' => $rid,
            'permission' => $perm,
            'module' => $module,
          ));
          $query->execute();
        }
      }
    }
  }

  /**
   * Return a random type name.
   *
   * @param string $type
   *   The block type.
   *
   * @return string
   *   The random block type.
   */
  public function getRandomMachineName($type) {
    $type = str_pad($this->getMachineName($type), 32, '_');
    $type = substr($type, 0, 23) . '_' . substr($this->randomString, 0, 8);

    return $type;
  }

  /**
   * Create a machine name.
   *
   * @param string $name
   *    Name.
   *
   * @return string
   *    Machine name.
   */
  private function getMachineName($name) {
    $a = explode(",", " ,&,à,á,â,ã,ä,å,æ,ç,è,é,ê,ë,ì,í,î,ï,ñ,ò,ó,ô,õ,ö,ø,ù,ú,û,ü,ý,ÿ,ā,ă,ą,ć,ĉ,ċ,č,ď,đ,ē,ĕ,ė,ę,ě,ĝ,ğ,ġ,ģ,ĥ,ħ,ĩ,ī,ĭ,į,ı,ĳ,ĵ,ķ,ĺ,ļ,ľ,ŀ,ł,ń,ņ,ň,ŉ,ō,ŏ,ő,œ,ŕ,ŗ,ř,ś,ŝ,ş,š,ţ,ť,ŧ,ũ,ū,ŭ,ů,ű,ų,ŵ,ŷ,ź,ż,ž,ƒ,ơ,ư,ǎ,ǐ,ǒ,ǔ,ǖ,ǘ,ǚ,ǜ,ǻ,ǽ,ǿ,ά,έ,ό,Ώ,ώ,ί,ϊ,ΐ,ύ,ϋ,ΰ,ή");
    $b = explode(",", "_,_,a,a,a,a,a,a,ae,c,e,e,e,e,i,i,i,i,n,o,o,o,o,o,o,u,u,u,u,y,y,a,a,a,c,c,c,c,d,d,e,e,e,e,e,g,g,g,g,h,h,i,i,i,i,i,ij,j,k,l,l,l,l,l,l,n,n,n,n,o,o,o,oe,r,r,r,s,s,s,s,t,t,t,u,u,u,u,u,u,w,y,z,z,z,s,f,o,u,a,i,o,u,u,u,u,u,a,ae,o,α,ε,ο,Ω,ω,ι,ι,ι,υ,υ,υ,η");
    $machine_name = str_replace($a, $b, strtolower($name));
    return $machine_name;
  }

}
