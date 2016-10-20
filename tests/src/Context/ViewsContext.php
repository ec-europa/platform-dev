<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\ViewsContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Gherkin\Node\PyStringNode;
use Drupal\DrupalExtension\Context\RawDrupalContext;
use function \bovigo\assert\assert;
use function \bovigo\assert\predicate\isNotNull;

/**
 * Class ViewsContext.
 *
 * @package Drupal\nexteuropa\Context
 */
class ViewsContext extends RawDrupalContext {

  /**
   * Views created during test execution.
   *
   * @var \view[]
   */
  protected $views = [];

  /**
   * Import given view.
   *
   * @Given I import the following view:
   */
  public function importView(PyStringNode $view_export) {
    /** @var \view $view */
    $view = NULL;

    // This is actually how Views imports exported views.
    // @see views_ui_import_validate()
    eval($view_export->getRaw());

    assert($view, isNotNull());
    $view->vid = 'new';
    $view->save();
    $this->views[] = $view;
  }

  /**
   * Remove views imported during test execution.
   *
   * @AfterScenario
   */
  public function removeViews() {
    foreach ($this->views as $view) {
      views_delete_view($view);
    }
  }

}
