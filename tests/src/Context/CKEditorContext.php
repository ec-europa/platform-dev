<?php
/**
 * @file
 * Contains \Drupal\nexteuropa\Context\CKEditorContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\MinkExtension\Context\RawMinkContext;

/**
 * Extension for performing CKEditor related actions.
 */
class CKEditorContext extends RawMinkContext {

  /**
   * Fills in a specific value in a rich text editor (CKEditor).
   *
   * @Given I fill in the rich text editor :arg1 with :arg2
   */
  public function iFillInTheRichTextEditorWith($arg1, $arg2) {
    /** @var \Behat\Mink\Element\NodeElement $field */
    $field = $this->getSession()->getPage()->findField($arg1);

    if (NULL === $field) {
      throw new \Exception(sprintf('Unable to find field "%s"', $arg1));
    }

    $id = $field->getAttribute('id');

    $args = [
      'ckeditor_instance_id' => $id,
      'value' => $arg2,
    ];

    $args_as_js_object = json_encode($args);

    $this->getSession()->executeScript(
      "args = {$args_as_js_object};" .
      "CKEDITOR.instances[args.ckeditor_instance_id].setData(args.value);"
    );
  }

}
