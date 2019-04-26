<?php

namespace Drupal\nexteuropa\Context;

use Behat\Mink\Element\Element;

/**
 * Util trait proposing.
 *
 * @package Drupal\nexteuropa\Context
 */
trait ContextUtil {

  /**
   * Determine if the a user is already logged in.
   *
   * Override the existing loggedIn method from DrupalExtension,
   * to skip login form test in user/login page
   * (because ecas revokes permissions for this page).
   */
  public function loggedIn() {
    $session = $this->getSession();
    $session->visit($this->locatePath('/'));

    // Check if the 'logged-in' class is present on the page.
    $element = $session->getPage();
    return $element->find('css', 'body.logged-in');
  }

  /**
   * Returns whether or not Pathauto is enabled for the given entity.
   *
   * @param string $entity_type
   *   The entity type.
   * @param mixed $entity
   *   The entity.
   * @param string $langcode
   *   The language code for the entity.
   *
   * @return bool
   *   TRUE if Pathauto is enabled, FALSE if not.
   *
   * @see pathauto_field_attach_form()
   * @see \NextEuropaMultilingualSubContext::createMultilingualContent()
   * @see \Drupal\nexteuropa\Context\DrupalContext::theFollowingContents()
   */
  public function isPathautoEnabled($entity_type, $entity, $langcode) {
    list($id, , $bundle) = entity_extract_ids($entity_type, $entity);
    if (!isset($entity->path['pathauto'])) {
      if (!empty($id)) {
        module_load_include('inc', 'pathauto');
        $uri = entity_uri($entity_type, $entity);
        $path = drupal_get_path_alias($uri['path'], $langcode);
        $pathauto_alias = pathauto_create_alias($entity_type, 'return', $uri['path'], array($entity_type => $entity), $bundle, $langcode);
        return $path != $uri['path'] && $path == $pathauto_alias;
      }
      else {
        return TRUE;
      }
    }
    return $entity->path['pathauto'];
  }

  /**
   * Retrieve a table row containing specified text from a given element.
   *
   * @param \Behat\Mink\Element\Element $element
   *   The DOM element where to search in.
   * @param string $search
   *   The text to search for in the table row.
   *
   * @return \Behat\Mink\Element\NodeElement
   *   The row containing the searched text.
   *
   * @throws \Exception
   */
  public function getTableRow(Element $element, $search) {
    $rows = $element->findAll('css', 'tr');
    if (empty($rows)) {
      throw new \Exception(sprintf('No rows found on the page %s', $this->getSession()->getCurrentUrl()));
    }

    foreach ($rows as $row) {
      if (strpos($row->getText(), $search) !== FALSE) {
        return $row;
      }
    }
    throw new \Exception(sprintf('Failed to find a row containing "%s" on the page %s', $search, $this->getSession()->getCurrentUrl()));
  }

}
