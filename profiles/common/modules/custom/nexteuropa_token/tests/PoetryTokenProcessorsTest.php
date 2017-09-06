<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_token\Tests\PoetryTokenProcessorsTest.
 */

namespace Drupal\nexteuropa_token\Tests;

/**
 * Class PoetryTokenProcessorsTest.
 *
 * @group poetry
 *
 * @package Drupal\nexteuropa_token\Tests
 */
class PoetryTokenProcessorsTest extends \PHPUnit_Framework_TestCase {

  /**
   * Test replacement of NextEuropa tokens with ignore token.
   *
   * @param string $text
   *    Input text.
   * @param string $expected
   *    Expected texts.
   *
   * @dataProvider tokenReplacementProvider
   */
  public function testReplaceTokenWithIgnore($text, $expected) {
    $actual = nexteuropa_token_ckeditor_replace_tokens_with_tmgmt_poetry_ignore_tags($text);
    $this->assertEquals($expected, $actual);
  }

  /**
   * Test replacement of ignore tokens with NextEuropa token.
   *
   * @param string $expected
   *    Expected texts.
   * @param string $text
   *    Input text.
   *
   * @dataProvider tokenReplacementProvider
   */
  public function testReplaceIgnoreWithToken($expected, $text) {
    $actual = nexteuropa_token_ckeditor_replace_tmgmt_poetry_ignore_tags_with_tokens($text);
    $this->assertEquals($expected, $actual);
  }

  /**
   * Data provider.
   *
   * @return array
   *   Return PHPUnit data.
   */
  public static function tokenReplacementProvider() {
    return array(
      array(
        '<p>[node:8:link]{Visit the European Commission as Link}</p>',
        '<p><tmgmt_poetry_ignore value="[node:8:link]{Visit the European Commission as Link}"/></p>',
      ),
      array(
        '<p>[node:8:view-mode:full]{Visit the European Commission as Link}</p>',
        '<p><tmgmt_poetry_ignore value="[node:8:view-mode:full]{Visit the European Commission as Link}"/></p>',
      ),
      array(
        '[node:8:link]{Visit the European Commission as Link}',
        '<tmgmt_poetry_ignore value="[node:8:link]{Visit the European Commission as Link}"/>',
      ),
      array(
        '[node:8:view-mode:full]{Visit the European Commission as Link}',
        '<tmgmt_poetry_ignore value="[node:8:view-mode:full]{Visit the European Commission as Link}"/>',
      ),
    );
  }

}
