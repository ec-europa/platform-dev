<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_token\Tests\PoetryHrefProcessorsTest.
 */

namespace Drupal\nexteuropa_token\Tests;

/**
 * Class PoetryHrefProcessorsTest.
 *
 * @group poetry
 *
 * @package Drupal\nexteuropa_token\Tests
 */
class PoetryHrefProcessorsTest extends \PHPUnit_Framework_TestCase {

  /**
   * Test replacement of href attributes with ignore tokens.
   *
   * @param string $text
   *    Input text.
   * @param string $expected
   *    Expected texts.
   *
   * @dataProvider hrefReplacementProvider
   */
  public function testReplaceHrefWithIgnore($text, $expected) {
    $actual = nexteuropa_token_ckeditor_replace_href_with_tmgmt_poetry_ignore_href_token($text);
    $this->assertEquals($expected, $actual);
  }

  /**
   * Test replacement ignore tokens with href attributes.
   *
   * @param string $expected
   *    Expected texts.
   * @param string $text
   *    Input text.
   *
   * @dataProvider hrefReplacementProvider
   */
  public function testReplaceIgnoreWithHref($expected, $text) {
    $actual = nexteuropa_token_ckeditor_replace_tmgmt_poetry_ignore_href_token_with_tokens($text);
    $this->assertEquals($expected, $actual);
  }

  /**
   * Data provider.
   *
   * @return array
   *    Return PHPUnit data.
   */
  public static function hrefReplacementProvider() {
    return array(
      array(
        'Vestibulum <a href="[node:123:url]">The link</a> aliquet.',
        'Vestibulum <a tmgmt_poetry_ignore_href="[node:123:url]">The link</a> aliquet.',
      ),
      array(
        'Vestibulum <a href="[node:123:url]" style="display: none;" target="_blank">The link</a> aliquet.',
        'Vestibulum <a tmgmt_poetry_ignore_href="[node:123:url]" style="display: none;" target="_blank">The link</a> aliquet.',
      ),
      array(
        '<a href="[node:123:url]" style="display: none;" target="_blank">The link</a>',
        '<a tmgmt_poetry_ignore_href="[node:123:url]" style="display: none;" target="_blank">The link</a>',
      ),
      array(
        '<a href="[node:123:url]"target="_blank"></a>',
        '<a tmgmt_poetry_ignore_href="[node:123:url]"target="_blank"></a>',
      ),
      array(
        'Lorem ipsum [node:123:url] aliquet.',
        'Lorem ipsum [node:123:url] aliquet.',
      ),
      array(
        '<a href="[node:123:url]"target="_blank">',
        '<a tmgmt_poetry_ignore_href="[node:123:url]"target="_blank">',
      ),
    );
  }

}
