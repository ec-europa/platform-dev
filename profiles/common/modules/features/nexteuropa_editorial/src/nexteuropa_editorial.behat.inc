<?php

/**
 * @file
 * Contains \NextEuropaEditorialSubContext.
 */

use Drupal\DrupalDriverManager;
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalExtension\Context\RawDrupalContext;

/**
 * Behat step definitions for the NextEuropa Editorial module.
 */
class NextEuropaEditorialSubContext extends RawDrupalContext implements DrupalSubContextInterface {

  /**
   * The Drupal driver manager.
   *
   * @var \Drupal\DrupalDriverManager;
   */
  protected $drupal;

  /**
   * Constructs a NextEuropaEditorialSubContext object.
   *
   * @param Drupal\DrupalDriverManager $drupal
   *   The Drupal driver manager.
   */
  public function __construct(DrupalDriverManager $drupal) {
    $this->drupal = $drupal;
  }

  /**
   * Subscribes the user to the given group and grants the given OG role.
   *
   * @param string $role
   *   The OG role to grant to the user.
   * @param string $group
   *   The group to subscribe the user to.
   *
   * @throws \InvalidArgumentException
   *   Thrown when the group doesn't exist, when multiple groups have the given
   *   group name, or when the given role doesn't exist in the given group.
   * @throws \Exception
   *   Thrown when an anonymous user is attempted to be subscribed to a group.
   *
   * @Given I have the :role role in the :group group
   */
  public function assignUserToGroupRole($role, $group) {
    // Discover the groups with the given name.
    $groups = $this->getGroupsByName($group);

    // Check that we only have one group to rule them all.
    $count = array_sum(array_map('count', $groups));
    if ($count == 0) {
      throw new \InvalidArgumentException("No such group '$group'.");
    }
    if ($count > 1) {
      throw new \InvalidArgumentException("Multiple groups with the name '$group' exist.");
    }

    // We only have one group. Retrieve it from the $groups array.
    $entity_type = key($groups);
    $group = reset($groups[$entity_type]);

    // Get the available roles for this group.
    list($entity_id, , $bundle) = entity_extract_ids($entity_type, $group);
    $roles = og_roles($entity_type, $bundle, $entity_id);

    // Check that the given role exists in the group.
    $rid = array_search($role, $roles);
    if ($rid === FALSE) {
      throw new \InvalidArgumentException("The '$group' group does not have a '$role' role.");
    }

    // Get the currently logged in user from DrupalContext.
    /** @var \Drupal\DrupalExtension\Context\DrupalContext $context */
    $context = $this->getContext('\Drupal\DrupalExtension\Context\DrupalContext');
    if (empty($context->user)) {
      throw new \Exception('Cannot assign anonymous user to a group.');
    }

    // Subscribe the user to the group.
    og_group($entity_type, $entity_id, array('entity' => $context->user));

    // Grant the OG role to the user.
    og_role_grant($entity_type, $entity_id, $context->user->uid, $rid);
  }

  /**
   * Returns a list of OG groups with the given name across all entities.
   *
   * @param string $name
   *   The name of the groups to return.
   *
   * @return array
   *   An associative array, keyed by entity type, each value an indexed array
   *   of groups with the given name.
   */
  public function getGroupsByName($name) {
    $groups = array();

    foreach (og_get_all_group_bundle() as $entity_type => $bundles) {
      $entity_info = entity_get_info($entity_type);
      $query = new EntityFieldQuery();
      $result = $query
        ->entityCondition('entity_type', $entity_type)
        ->entityCondition('bundle', array_keys($bundles), 'IN')
        ->fieldCondition(OG_GROUP_FIELD, 'value', 1, '=')
        ->propertyCondition($entity_info['entity keys']['label'], $name)
        // Make sure we can retrieve the data even if we are an anonymous user.
        ->addTag('DANGEROUS_ACCESS_CHECK_OPT_OUT')
        ->execute();

      if (!empty($result[$entity_type])) {
        $groups[$entity_type] = entity_load($entity_type, array_keys($result[$entity_type]));
      }
    }

    return $groups;
  }

  /**
   * Returns the Behat context that corresponds with the given class name.
   *
   * This is different from InitializedContextEnvironment::getContext() in that
   * it also returns subclasses of the given class name. This allows us to
   * retrieve for example DrupalContext even if it is overridden in a project.
   *
   * @param string $class
   *   A fully namespaced class name.
   *
   * @return \Behat\Behat\Context\Context|false
   *   The requested context, or FALSE if the context is not registered.
   */
  protected function getContext($class) {
    /** @var \Behat\Behat\Context\Environment\InitializedContextEnvironment $environment */
    $environment = $this->drupal->getEnvironment();
    foreach ($environment->getContexts() as $context) {
      if ($context instanceof $class) {
        return $context;
      }
    }

    return FALSE;
  }

}
