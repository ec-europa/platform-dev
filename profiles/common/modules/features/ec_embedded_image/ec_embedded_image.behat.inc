<?php

use \Drupal\DrupalExtension\Context\DrupalSubContextBase;
use \Behat\Behat\Tester\Exception\PendingException;
use \Behat\Behat\Hook\Scope\BeforeScenarioScope;
use \Drupal\nexteuropa\Context\VariablesContext;

class ECEmbeddedImageSubContext extends DrupalSubContextBase {

  /**
   * @var VariablesContext
   */
  protected $variablesContext;

  /**
   * @var array
   */
  protected $initialVariables = array();

  /**
   * @BeforeScenario
   */
  public function gatherContexts(BeforeScenarioScope $scope) {
    $environment = $scope->getEnvironment();

    $this->variablesContext = $environment->getContext(VariablesContext::class);
  }

  /**
   * @Given a valid Flickr API key & secret have been configured
   */
  public function aValidFlickrApiKeySecretHaveBeenConfigured()
  {
    $flickr = $this->variablesContext->getVariable('flickr');

    $this->initialVariables += array(
      'media_flickr__api_key' => variable_get('media_flickr__api_key'),
      'media_flickr__api_secret' => variable_get('media_flickr__api_secret'),
    );

    variable_set('media_flickr__api_key', $flickr['key']);
    variable_set('media_flickr__api_secret', $flickr['secret']);
  }

  /**
   * @Given there is a media gallery content type with a field to embed images from flickr
   */
  public function thereIsAMediaGalleryContentTypeWithAFieldToEmbedImagesFromFlickr()
  {
    throw new PendingException();
  }

  /**
   * @AfterScenario
   */
  public function revertVariables() {
    foreach ($this->initialVariables as $variable => $value) {
      variable_set($variable, $value);
    }
  }
}
