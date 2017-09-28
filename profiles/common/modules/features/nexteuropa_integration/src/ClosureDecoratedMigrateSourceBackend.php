<?php
/**
 * @file
 * Contains \Drupal\nexteuropa_integration\ClosureDecoratedMigrateSourceBackend.
 */

namespace Drupal\nexteuropa_integration;

use Drupal\integration_consumer\Migrate\MigrateSourceBackend;
use \Closure;

/**
 * Decorates the documents from another MigrateSourceBackend with a closure.
 */
class ClosureDecoratedMigrateSourceBackend extends MigrateSourceBackend {

  /**
   * The actual MigrateSourceBackend to decorate.
   *
   * @var Drupal\integration_consumer\Migrate\MigrateSourceBackend
   */
  protected $wrappedSource;

  /**
   * Closure to replace each document from the MigrateSourceBackend.
   *
   * @var \Closure
   */
  protected $closure;

  /**
   * ClosureDecoratedMigrateSourceBackend constructor.
   *
   * @param Drupal\integration_consumer\Migrate\MigrateSourceBackend $wrapped_source
   *   The actual MigrateSourceBackend to decorate.
   * @param \Closure $closure
   *   The closure which will be used to decorate the documents.
   */
  public function __construct(MigrateSourceBackend $wrapped_source, Closure $closure) {
    $this->wrappedSource = $wrapped_source;

    $this->closure = $closure;
  }

  /**
   * {@inheritdoc}
   */
  public function __toString() {
    return (string) $this->wrappedSource;
  }

  /**
   * {@inheritdoc}
   */
  public function fields() {
    return $this->wrappedSource->fields();
  }

  /**
   * {@inheritdoc}
   */
  public function computeCount() {
    return $this->wrappedSource->computeCount();
  }

  /**
   * {@inheritdoc}
   */
  public function performRewind() {
    return $this->wrappedSource->performRewind();
  }

  /**
   * {@inheritdoc}
   */
  public function getNextRow() {
    $row = $this->wrappedSource->getNextRow();

    if (!$row) {
      return $row;
    }

    $callback = $this->closure;

    return $callback($row);
  }

}
