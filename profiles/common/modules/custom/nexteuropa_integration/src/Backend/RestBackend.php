<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_integration\Backend\RestBackend.
 */

namespace Drupal\nexteuropa_integration\Backend;

use Drupal\integration\Backend\AbstractBackend;
use Drupal\integration\Document\Document;
use Drupal\integration\Document\DocumentInterface;

/**
 * Class RestBackend.
 *
 * Simple REST backend using standard drupal_http_request(), without overrides.
 *
 * @method BackendConfiguration getConfiguration()
 *
 * @package Drupal\integration\Backend
 */
class RestBackend extends AbstractBackend {

  /**
   * {@inheritdoc}
   */
  public function find($resource_schema, $args = []) {
    $this->validateResourceSchema($resource_schema);

    $options['method'] = 'GET';
    $response = $this->httpRequest($this->getChangeFeedUri($resource_schema), $options);

    $return = [];
    if (!$this->hasErrors($response)) {
      $data = $this->getData($response);
      foreach ($data->results as $item) {
        if (!isset($item->deleted)) {
          $return[] = $item->id;
        }
      }
    }
    return $return;
  }

  /**
   * {@inheritdoc}
   */
  public function create($resource_schema, DocumentInterface $document) {
    $this->validateResourceSchema($resource_schema);

    // If document already exists then update it.
    if ($id = $this->getBackendContentId($document)) {
      $document->setMetadata('_id', $id);
      $this->update($resource_schema, $document);
    }
    else {
      $document->deleteMetadata('_id');
      $options['method'] = 'POST';
      $options['data'] = $this->getFormatterHandler()->encode($document);
      $options['headers'] = ['Content-Type' => $this->getFormatterHandler()->getContentType()];
      $response = $this->httpRequest($this->getResourceUri($resource_schema), $options);

      if (!$this->hasErrors($response)) {
        return new Document($this->getData($response));
      }
    }
  }

  /**
   * {@inheritdoc}
   */
  public function read($resource_schema, $id) {
    $this->validateResourceSchema($resource_schema);

    $options['method'] = 'GET';
    $response = $this->httpRequest($this->getResourceUri($resource_schema) . '/' . $id, $options);

    if (!$this->hasErrors($response)) {
      return new Document($this->getData($response));
    }
  }

  /**
   * {@inheritdoc}
   */
  public function update($resource_schema, DocumentInterface $document) {
    $this->validateResourceSchema($resource_schema);

    $options['method'] = 'PUT';
    $options['data'] = $this->getFormatterHandler()->encode($document);
    $options['headers'] = ['Content-Type' => $this->getFormatterHandler()->getContentType()];
    $response = $this->httpRequest($this->getResourceUri($resource_schema) . '/' . $this->getBackendContentId($document), $options);

    if (!$this->hasErrors($response)) {
      return new Document($this->getData($response));
    }
  }

  /**
   * {@inheritdoc}
   */
  public function delete($resource_schema, $id) {
    $this->validateResourceSchema($resource_schema);

    $options['method'] = 'DELETE';
    $response = $this->httpRequest($this->getResourceUri($resource_schema) . '/' . $id, $options);

    if (!$this->hasErrors($response)) {
      return TRUE;
    }
  }

  /**
   * {@inheritdoc}
   */
  public function getBackendContentId(DocumentInterface $document) {
    $options['method'] = 'GET';
    $producer = $document->getMetadata('producer');
    $producer_content_id = $document->getMetadata('producer_content_id');
    if ($producer && $producer_content_id) {
      $parts[] = $this->getConfiguration()->getPluginSetting('backend.base_url');
      $parts[] = $this->getConfiguration()->getPluginSetting('backend.backend_id');
      $parts[] = $producer;
      $parts[] = $producer_content_id;
      $url = implode('/', $parts);
      $response = $this->httpRequest($url, $options);

      if (!$this->hasErrors($response)) {
        $data = $this->getData($response);
        return $data->rows[0]->id;
      }
    }
    return NULL;
  }

  /**
   * Forwards HTTP requests to drupal_http_request().
   *
   * @param string $url
   *    A string containing a fully qualified URI.
   * @param array $options
   *    Array of options.
   *
   * @return object
   *    Response object, as returned by drupal_http_request().
   */
  protected function httpRequest($url, array $options = []) {
    global $conf;
    $authentication = $this->getAuthenticationHandler();
    $authentication->setContext(['url' => $url, 'options' => $options]);
    $authentication->authenticate();
    $context = $authentication->getContext();

    // Make sure we use standard drupal_http_request(), without overrides.
    $conf['drupal_http_request_function'] = FALSE;
    return $this->doRequest($context['url'], $context['options']);
  }

  /**
   * Wrapper about Drupal core drupal_http_request() to ease unit-testing.
   *
   * @param string $url
   *    A string containing a fully qualified URI.
   * @param array $options
   *    Array of options.
   *
   * @return object
   *    Response object, as returned by drupal_http_request().
   *
   * @see drupal_http_request()
   */
  protected function doRequest($url, $options) {
    return drupal_http_request($url, $options);
  }

  /**
   * Get full, single resource URI.
   *
   * @param string $resource_schema
   *    Machine name of a resource schema configuration object.
   *
   * @return string
   *    Single resource URI.
   */
  protected function getResourceUri($resource_schema) {
    $base_url = $this->getConfiguration()->getPluginSetting('backend.base_url');
    $endpoint = $this->getConfiguration()->getResourceEndpoint($resource_schema);
    return "$base_url/$endpoint";
  }

  /**
   * Get resource change feed URI.
   *
   * @param string $resource_schema
   *    Machine name of a resource schema configuration object.
   *
   * @return string
   *    Resource change feed URI.
   */
  protected function getChangeFeedUri($resource_schema) {
    $base_url = $this->getConfiguration()->getPluginSetting('backend.base_url');
    $endpoint = $this->getConfiguration()->getResourceChangeFeed($resource_schema);
    return "$base_url/$endpoint";
  }

  /**
   * Check whereas response has got errors or not.
   *
   * @param object $response
   *    Response object.
   *
   * @return bool
   *    TRUE if errors, FALSE otherwise.
   */
  protected function hasErrors($response) {
    return $response->code > 299;
  }

  /**
   * Get response data.
   *
   * @param object $response
   *    Response object.
   *
   * @return mixed|null
   *    Response data if response was successful, NULL otherwise.
   */
  protected function getData($response) {
    if (!$this->hasErrors($response)) {
      return json_decode($response->data);
    }
    else {
      return NULL;
    }
  }

}
