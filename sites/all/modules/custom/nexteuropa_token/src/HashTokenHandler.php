<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_token\HashTokenHandler
 */

namespace Drupal\nexteuropa_token;

/**
 * Class HashTokenHandler
 * @package Drupal\nexteuropa_token
 *
 * Implements hash token generation as described on:
 * https://webgate.ec.europa.eu/CITnet/confluence/display/NEXTEUROPA/Hash+id+generation#comment-403571860
 */
class HashTokenHandler extends TokenAbstractHandler {

  const DEFAULT_PREFIX = 'prefix';
  const TOKEN_NAME = 'url-hash';

  /**
   * Character sets used in encoding routine.
   *
   * @see: https://webgate.ec.europa.eu/CITnet/confluence/display/NEXTEUROPA/Hash+id+generation#comment-403571860
   */
  protected $sliceChars   = "5zqcn9l7mg0rskjb621pwtv3xd84fh";
  protected $typeChars    = "d3gxr6zws4fb2qp8mk9n1vtcj7l5h0";
  protected $firstChars   = "6svjw1z7dmt9kqgcr405b3nxp82hlf";
  protected $secondChars  = "fnwjpx30tlr276419qgbc85zmdvksh";
  protected $thirdChars   = "f6tjlvq5r3n1phdswzbc7xg02k9m48";
  protected $fourthChars  = "9pvmj1cs5bt763w2frx04qngkdz8hl";
  protected $allChars     = array();

  /**
   * {@inheritdoc}
   */
  function __construct() {
    $this->allChars = array(
      $this->firstChars,
      $this->secondChars,
      $this->thirdChars,
      $this->fourthChars,
    );
  }

  /**
   * {@inheritdoc}
   */
  public function hookToken() {
    return array();
  }

  /**
   * {@inheritdoc}
   */
  public function hookTokens($type, $tokens, array $data = array(), array $options = array()) {
    $replacements = array();

    if ($this->isValidTokenType($type)) {
      foreach ($tokens as $name => $original) {
        if ($name == self::TOKEN_NAME) {
          $id = $this->getEntityKeysId($type);
          $replacements[$original] = $this->generate($this->getHashPrefix(), $type, $data[$type]->{$id});
        }
      }
    }
    return $replacements;
  }

  /**
   * {@inheritdoc}
   */
  public function hookTokenInfoAlter(&$data) {
    foreach ($this->getEntityTokenTypes() as $token_type => $entity_info) {
      $data['tokens'][$token_type][self::TOKEN_NAME] = array(
        'name' => t("!entity Hash", array('!entity' => $entity_info['label'])),
        'description' => t("Unique hash derived from a site specific prefix, the entity tye and the entity ID."),
      );
    }
  }

  /**
   * Generate URL hash given the following three arguments.
   *
   * @param $prefix
   *    Unique prefix identifier.
   * @param $entity_type
   *    Entity type machine name.
   * @param $entity_id
   *    Entity ID in the current site.
   * @return string
   *    Encoded URL hash.
   *
   * @see: https://webgate.ec.europa.eu/CITnet/confluence/display/NEXTEUROPA/Hash+id+generation#comment-403571860
   */
  public function generate($prefix, $entity_type, $entity_id) {
    return $this->encodePrefix($prefix) . $this->encodeEntityType($entity_type) . $this->encodeEntityId($entity_id);
  }

  /**
   * Get system wide hash prefix.
   *
   * @return string
   */
  protected function getHashPrefix() {
    return variable_get('nexteuropa_token_hash_prefix', self::DEFAULT_PREFIX);
  }

  /**
   * Return encoded prefix portion.
   *
   * @param $prefix
   * @return string
   */
  function encodePrefix($prefix){
    $numeric = '';
    foreach (str_split($prefix) as $char) {
      $numeric .= ord($char);
    }
    return $this->encodeNumericValue($numeric, array($this->sliceChars, $this->firstChars));
  }

  /**
   * Return encoded entity type portion.
   *
   * @param $entity_type
   * @return string
   *
   * @see: https://webgate.ec.europa.eu/CITnet/confluence/display/NEXTEUROPA/Hash+id+generation#comment-403571860
   */
  function encodeEntityType($entity_type){
    $numeric = '';
    foreach (str_split($entity_type) as $char) {
      $numeric .= ord($char);
    }
    return $this->encodeNumericValue($numeric, $this->typeChars);
  }

  /**
   * Return encoded entity ID portion.
   *
   * @param $entity_id
   * @return string
   */
  function encodeEntityId($entity_id) {
    return $this->encodeNumericValue($entity_id, $this->allChars);
  }

  /**
   * Encode numeric value following specifications available at:
   * @see: https://webgate.ec.europa.eu/CITnet/confluence/display/NEXTEUROPA/Hash+id+generation#comment-403571860
   *
   * @param $numeric
   * @return string
   */
  function encodeNumericValue($numeric, $charset) {
    $hash = '';
    $charset = is_array($charset) ? $charset : array($charset);
    $crumbs = $numeric;
    for ($i = 0; $i < count($charset); $i++) {
      $position = $crumbs % strlen($charset[$i]);
      $hash .= $charset[$i]{$position};
      $crumbs = round($crumbs / strlen($charset[$i]));
    }
    return $hash;
  }
}
