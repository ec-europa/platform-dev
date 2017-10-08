<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\DrupalContext.
 */

namespace Drupal\nexteuropa\Context;

use Drupal\DrupalExtension\Context\RawDrupalContext;

/**
 * Provides step definitions for interacting with ECAS.
 */
class EcasContext extends RawDrupalContext {

  /**
   * Creates and authenticates an ECAS user with the given role(s).
   *
   * @Given I am logged in as an ECAS user with the :role role(s)
   */
  public function assertAuthenticatedEcasByRole($role) {
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
      $this->login();
    }
  }

  /**
   * ECAS user with a given role is already logged in.
   *
   * @param string $role
   *   A single role, or multiple comma-separated roles in a single string.
   *
   * @return bool
   *   Returns TRUE if the current logged in user comes from
   *   Ecas and has this role (or roles).
   */
  public function ecasLoggedInWithRole($role) {
    return $this->loggedIn() && $this->user && $this->user->ecas && isset($this->user->role) && $this->user->role == $role;
  }


  /**
   * Create an ECAS user.
   *
   * @return object
   *   The created user.
   */
  public function ecasUserCreate($user) {
    $this->dispatchHooks('BeforeUserCreateScope', $user);
    $this->parseEntityFields('user', $user);
    $this->getDriver()->userCreate($user);
    $this->dispatchHooks('AfterUserCreateScope', $user);

    // Add the user to the authmap table.
    db_insert('authmap')
      ->fields(array(
        'authname' => $user->name,
        'uid' => $user->uid,
        'module' => 'ecas',
      ))
      ->execute();
    $user->ecas = 1;
    $this->users[$user->name] = $this->user = $user;
    return $user;
  }

  /**
   * Remove any created ECAS users.
   *
   * @AfterScenario @Ecas
   */
  public function cleanEcasUsers() {
    // Remove any users that were created.
    if (!empty($this->users)) {
      foreach ($this->users as $user) {
        $this->getDriver()->userDelete($user);
        db_delete('authmap')
          ->condition('uid', $user->uid)
          ->execute();
      }
      $this->getDriver()->processBatch();
      $this->users = array();
    }
  }

}
