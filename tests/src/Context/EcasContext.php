<?php

namespace Drupal\nexteuropa\Context;

use Drupal\DrupalExtension\Context\RawDrupalContext;

/**
 * Provides step definitions for interacting with ECAS.
 */
class EcasContext extends RawDrupalContext {
  use \Drupal\nexteuropa\Context\ContextUtil;

  /**
   * Creates and authenticates an ECAS user with the given role(s).
   *
   * @see \Drupal\DrupalExtension\Context\DrupalContext::assertAuthenticatedByRole()
   *
   * @Given I am logged in as an ECAS user with the :role role(s)
   */
  public function ecasAssertAuthenticatedByRole($role) {
    // Check if a user with this role is already logged in.
    if (!$this->ecasLoggedInWithRole($role)) {
      // Create user (and project).
      $user = (object) array(
        'name' => $this->getRandom()->name(8),
        'pass' => $this->getRandom()->name(16),
        'role' => $role,
      );
      $user->mail = "{$user->name}@example.com";

      $this->ecasUserCreate($user);

      $roles = explode(',', $role);
      $roles = array_map('trim', $roles);
      foreach ($roles as $role) {
        if (!in_array(strtolower($role), array('authenticated', 'authenticated user'))) {
          // Only add roles other than 'authenticated user'.
          $this->getDriver()->userAddRole($user, $role);
        }
      }

      // Login.
      $this->login($user);
    }
  }

  /**
   * ECAS user with a given role is already logged in.
   *
   * @param string $role
   *   A single role, or multiple comma-separated roles in a single string.
   *
   * @see RawDrupalContext::loggedInWithRole()
   *
   * @return bool
   *   Returns TRUE if the current logged in user comes from
   *   Ecas and has this role (or roles).
   */
  public function ecasLoggedInWithRole($role) {
    $user = $this->getUserManager()->getCurrentUser();
    return $this->loggedIn() && $user && $user->ecas && isset($user->role) && $user->role == $role;
  }

  /**
   * Create an ECAS user.
   *
   * @see RawDrupalContext::userCreate()
   *
   * @return object
   *   The created user.
   */
  public function ecasUserCreate($user) {
    $this->dispatchHooks('BeforeUserCreateScope', $user);
    $this->parseEntityFields('user', $user);
    $this->getDriver()->userCreate($user);
    $this->dispatchHooks('AfterUserCreateScope', $user);
    $this->getUserManager()->addUser($user);

    // Add the user to the authmap table.
    db_insert('authmap')
      ->fields(array(
        'authname' => $user->name,
        'uid' => $user->uid,
        'module' => 'ecas',
      ))
      ->execute();
    $user->ecas = 1;

    return $user;
  }

  /**
   * Remove any created ECAS users.
   *
   * @see RawDrupalContext::cleanUsers()
   *
   * @AfterScenario @Ecas
   */
  public function ecasCleanUsers() {
    // Remove any users that were created.
    if ($this->getUserManager()->hasUsers()) {
      foreach ($this->getUserManager()->getUsers() as $user) {
        $this->getDriver()->userDelete($user);
        db_delete('authmap')
          ->condition('uid', $user->uid)
          ->execute();
      }
      $this->getDriver()->processBatch();
      $this->getUserManager()->clearUsers();
      if ($this->loggedIn()) {
        $this->logout();
      }
    }
  }

}
