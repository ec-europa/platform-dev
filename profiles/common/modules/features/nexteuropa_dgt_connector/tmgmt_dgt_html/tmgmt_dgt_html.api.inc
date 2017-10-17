<?php

/**
 * @file
 * This file contains examples of hooks that can be implemented.
 */

/**
 * Define filter formats that are supposed to process HTML code.
 *
 * The content of text fields using one of these filter formats will not
 * be escaped when embedded in the translation HTML document.
 *
 * @return array
 *   A list of filter format names.
 */
function hook_tmgmt_dgt_html_filter_formats_containing_html() {
  return array(
    'basic_html',
    'full_html',
  );
}
