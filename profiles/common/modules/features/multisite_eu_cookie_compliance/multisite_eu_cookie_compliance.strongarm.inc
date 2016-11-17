<?php

/**
 * @file
 * multisite_eu_cookie_compliance.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function multisite_eu_cookie_compliance_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_bg';
  $strongarm->value = array(
    'popup_enabled' => 1,
    'popup_clicking_confirmation' => 0,
    'popup_position' => 0,
    'popup_info' => array(
      'value' => '<h2 style="line-height: 20px; ">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px; ">By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_agreed_enabled' => 1,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => '<p>Thank you for accepting cookies.You can now hide this message or find out more about cookies.</p>',
      'format' => 'plain_text',
    ),
    'popup_link' => 'http://ec.europa.eu/cookies/index_en.htm',
    'popup_height' => '60',
    'popup_width' => '100%',
    'popup_delay' => '1',
    'popup_bg_hex' => '0779BF',
    'popup_text_hex' => 'ffffff',
  );
  $export['eu_cookie_compliance_bg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_cs';
  $strongarm->value = array(
    'popup_enabled' => 1,
    'popup_clicking_confirmation' => 0,
    'popup_position' => 0,
    'popup_info' => array(
      'value' => '<h2 style="line-height: 20px; ">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px; ">By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_agreed_enabled' => 0,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => 'Thank you for accepting cookies.You can now hide this message or find out more about cookies.',
      'format' => 'plain_text',
    ),
    'popup_link' => 'http://ec.europa.eu/cookies/index_en.htm',
    'popup_height' => '60',
    'popup_width' => '100%',
    'popup_delay' => '1',
    'popup_bg_hex' => '0779BF',
    'popup_text_hex' => 'ffffff',
  );
  $export['eu_cookie_compliance_cs'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_da';
  $strongarm->value = array(
    'popup_enabled' => 1,
    'popup_clicking_confirmation' => 0,
    'popup_position' => 0,
    'popup_info' => array(
      'value' => '<h2 style="line-height: 20px; ">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px; ">By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_agreed_enabled' => 0,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => 'Thank you for accepting cookies.You can now hide this message or find out more about cookies.',
      'format' => 'plain_text',
    ),
    'popup_link' => 'http://ec.europa.eu/cookies/index_en.htm',
    'popup_height' => '60',
    'popup_width' => '100%',
    'popup_delay' => '1',
    'popup_bg_hex' => '0779BF',
    'popup_text_hex' => 'ffffff',
  );
  $export['eu_cookie_compliance_da'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_de';
  $strongarm->value = array(
    'popup_enabled' => 1,
    'popup_clicking_confirmation' => 0,
    'popup_position' => 0,
    'popup_info' => array(
      'value' => '<h2 style="line-height: 20px; ">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px; ">By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_agreed_enabled' => 0,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => 'Thank you for accepting cookies.You can now hide this message or find out more about cookies.',
      'format' => 'plain_text',
    ),
    'popup_link' => 'http://ec.europa.eu/cookies/index_en.htm',
    'popup_height' => '60',
    'popup_width' => '100%',
    'popup_delay' => '1',
    'popup_bg_hex' => '0779BF',
    'popup_text_hex' => 'ffffff',
  );
  $export['eu_cookie_compliance_de'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_el';
  $strongarm->value = array(
    'popup_enabled' => 1,
    'popup_clicking_confirmation' => 0,
    'popup_position' => 0,
    'popup_info' => array(
      'value' => '<h2 style="line-height: 20px; ">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px; ">By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_agreed_enabled' => 0,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => 'Thank you for accepting cookies.You can now hide this message or find out more about cookies.',
      'format' => 'plain_text',
    ),
    'popup_link' => 'http://ec.europa.eu/cookies/index_en.htm',
    'popup_height' => '60',
    'popup_width' => '100%',
    'popup_delay' => '1',
    'popup_bg_hex' => '0779BF',
    'popup_text_hex' => 'ffffff',
  );
  $export['eu_cookie_compliance_el'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_en';
  $strongarm->value = array(
    'popup_enabled' => 1,
    'popup_clicking_confirmation' => 0,
    'popup_position' => 0,
    'popup_info' => array(
      'value' => '<h2>We use cookies on this site to enhance your user experience</h2><p>By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_agreed_enabled' => 0,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => 'Thank you for accepting cookies.You can now hide this message or find out more about cookies.',
      'format' => 'plain_text',
    ),
    'popup_link' => 'http://ec.europa.eu/cookies/index_en.htm',
    'popup_height' => '60',
    'popup_width' => '100%',
    'popup_delay' => '1',
    'popup_bg_hex' => '0779BF',
    'popup_text_hex' => 'ffffff',
  );
  $export['eu_cookie_compliance_en'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_es';
  $strongarm->value = array(
    'popup_enabled' => 1,
    'popup_clicking_confirmation' => 0,
    'popup_position' => 0,
    'popup_info' => array(
      'value' => '<h2 style="line-height: 20px; ">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px; ">By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_agreed_enabled' => 0,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => 'Thank you for accepting cookies.You can now hide this message or find out more about cookies.',
      'format' => 'plain_text',
    ),
    'popup_link' => 'http://ec.europa.eu/cookies/index_en.htm',
    'popup_height' => '60',
    'popup_width' => '100%',
    'popup_delay' => '1',
    'popup_bg_hex' => '0779BF',
    'popup_text_hex' => 'ffffff',
  );
  $export['eu_cookie_compliance_es'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_et';
  $strongarm->value = array(
    'popup_enabled' => 1,
    'popup_clicking_confirmation' => 0,
    'popup_position' => 0,
    'popup_info' => array(
      'value' => '<h2 style="line-height: 20px; ">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px; ">By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_agreed_enabled' => 0,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => 'Thank you for accepting cookies.You can now hide this message or find out more about cookies.',
      'format' => 'plain_text',
    ),
    'popup_link' => 'http://ec.europa.eu/cookies/index_en.htm',
    'popup_height' => '60',
    'popup_width' => '100%',
    'popup_delay' => '1',
    'popup_bg_hex' => '0779BF',
    'popup_text_hex' => 'ffffff',
  );
  $export['eu_cookie_compliance_et'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_fi';
  $strongarm->value = array(
    'popup_enabled' => 1,
    'popup_clicking_confirmation' => 0,
    'popup_position' => 0,
    'popup_info' => array(
      'value' => '<h2 style="line-height: 20px; ">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px; ">By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_agreed_enabled' => 0,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => 'Thank you for accepting cookies.You can now hide this message or find out more about cookies.',
      'format' => 'plain_text',
    ),
    'popup_link' => 'http://ec.europa.eu/cookies/index_en.htm',
    'popup_height' => '60',
    'popup_width' => '100%',
    'popup_delay' => '1',
    'popup_bg_hex' => '0779BF',
    'popup_text_hex' => 'ffffff',
  );
  $export['eu_cookie_compliance_fi'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_fr';
  $strongarm->value = array(
    'popup_enabled' => 1,
    'popup_clicking_confirmation' => 0,
    'popup_position' => 0,
    'popup_info' => array(
      'value' => '<h2 style="line-height: 20px; ">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px; ">By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_agreed_enabled' => 0,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => '<p>Thank you for accepting cookies.You can now hide this message or find out more about cookies.</p>',
      'format' => 'plain_text',
    ),
    'popup_link' => 'http://www.google.com',
    'popup_height' => '60',
    'popup_width' => '100%',
    'popup_delay' => '1',
    'popup_bg_hex' => '0779BF',
    'popup_text_hex' => 'ffffff',
  );
  $export['eu_cookie_compliance_fr'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_ga';
  $strongarm->value = array(
    'popup_enabled' => 1,
    'popup_clicking_confirmation' => 0,
    'popup_position' => 0,
    'popup_info' => array(
      'value' => '<h2 style="line-height: 20px; ">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px; ">By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_agreed_enabled' => 0,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => 'Thank you for accepting cookies.You can now hide this message or find out more about cookies.',
      'format' => 'plain_text',
    ),
    'popup_link' => 'http://ec.europa.eu/cookies/index_en.htm',
    'popup_height' => '60',
    'popup_width' => '100%',
    'popup_delay' => '1',
    'popup_bg_hex' => '0779BF',
    'popup_text_hex' => 'ffffff',
  );
  $export['eu_cookie_compliance_ga'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_hr';
  $strongarm->value = array(
    'popup_enabled' => 1,
    'popup_clicking_confirmation' => 0,
    'popup_position' => 0,
    'popup_info' => array(
      'value' => '<h2 style="line-height: 20px; ">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px; ">By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_agreed_enabled' => 0,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => '<p>Thank you for accepting cookies.You can now hide this message or find out more about cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_link' => 'http://ec.europa.eu/cookies/index_en.htm',
    'popup_height' => '',
    'popup_width' => '100%',
    'popup_delay' => '1',
    'popup_bg_hex' => '0779BF',
    'popup_text_hex' => 'ffffff',
  );
  $export['eu_cookie_compliance_hr'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_hu';
  $strongarm->value = array(
    'popup_enabled' => 1,
    'popup_clicking_confirmation' => 0,
    'popup_position' => 0,
    'popup_info' => array(
      'value' => '<h2 style="line-height: 20px; ">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px; ">By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_agreed_enabled' => 0,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => 'Thank you for accepting cookies.You can now hide this message or find out more about cookies.',
      'format' => 'plain_text',
    ),
    'popup_link' => 'http://ec.europa.eu/cookies/index_en.htm',
    'popup_height' => '60',
    'popup_width' => '100%',
    'popup_delay' => '1',
    'popup_bg_hex' => '0779BF',
    'popup_text_hex' => 'ffffff',
  );
  $export['eu_cookie_compliance_hu'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_it';
  $strongarm->value = array(
    'popup_enabled' => 1,
    'popup_clicking_confirmation' => 0,
    'popup_position' => 0,
    'popup_info' => array(
      'value' => '<h2 style="line-height: 20px; ">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px; ">By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_agreed_enabled' => 0,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => 'Thank you for accepting cookies.You can now hide this message or find out more about cookies.',
      'format' => 'plain_text',
    ),
    'popup_link' => 'http://ec.europa.eu/cookies/index_en.htm',
    'popup_height' => '',
    'popup_width' => '100%',
    'popup_delay' => '1',
    'popup_bg_hex' => '0779BF',
    'popup_text_hex' => 'ffffff',
  );
  $export['eu_cookie_compliance_it'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_lt';
  $strongarm->value = array(
    'popup_enabled' => 1,
    'popup_clicking_confirmation' => 0,
    'popup_position' => 0,
    'popup_info' => array(
      'value' => '<h2 style="line-height: 20px; ">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px; ">By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_agreed_enabled' => 0,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => '<p>Thank you for accepting cookies.You can now hide this message or find out more about cookies.</p>',
      'format' => 'plain_text',
    ),
    'popup_link' => 'http://ec.europa.eu/cookies/index_en.htm',
    'popup_height' => '60',
    'popup_width' => '100%',
    'popup_delay' => '1',
    'popup_bg_hex' => '0779BF',
    'popup_text_hex' => 'ffffff',
  );
  $export['eu_cookie_compliance_lt'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_lv';
  $strongarm->value = array(
    'popup_enabled' => 1,
    'popup_clicking_confirmation' => 0,
    'popup_position' => 0,
    'popup_info' => array(
      'value' => '<h2 style="line-height: 20px; ">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px; ">By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_agreed_enabled' => 0,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => 'Thank you for accepting cookies.You can now hide this message or find out more about cookies.',
      'format' => 'plain_text',
    ),
    'popup_link' => 'http://ec.europa.eu/cookies/index_en.htm',
    'popup_height' => '60',
    'popup_width' => '100%',
    'popup_delay' => '1',
    'popup_bg_hex' => '0779BF',
    'popup_text_hex' => 'ffffff',
  );
  $export['eu_cookie_compliance_lv'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_mt';
  $strongarm->value = array(
    'popup_enabled' => 1,
    'popup_clicking_confirmation' => 0,
    'popup_position' => 0,
    'popup_info' => array(
      'value' => '<h2 style="line-height: 20px; ">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px; ">By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_agreed_enabled' => 0,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => 'Thank you for accepting cookies.You can now hide this message or find out more about cookies.',
      'format' => 'plain_text',
    ),
    'popup_link' => 'http://ec.europa.eu/cookies/index_en.htm',
    'popup_height' => '60',
    'popup_width' => '100%',
    'popup_delay' => '1',
    'popup_bg_hex' => '0779BF',
    'popup_text_hex' => 'ffffff',
  );
  $export['eu_cookie_compliance_mt'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_nl';
  $strongarm->value = array(
    'popup_enabled' => 1,
    'popup_clicking_confirmation' => 0,
    'popup_position' => 0,
    'popup_info' => array(
      'value' => '<h2 style="line-height: 20px; ">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px; ">By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_agreed_enabled' => 0,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => 'Thank you for accepting cookies.You can now hide this message or find out more about cookies.',
      'format' => 'plain_text',
    ),
    'popup_link' => 'http://ec.europa.eu/cookies/index_en.htm',
    'popup_height' => '60',
    'popup_width' => '100%',
    'popup_delay' => '1',
    'popup_bg_hex' => '0779BF',
    'popup_text_hex' => 'ffffff',
  );
  $export['eu_cookie_compliance_nl'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_pl';
  $strongarm->value = array(
    'popup_enabled' => 1,
    'popup_clicking_confirmation' => 0,
    'popup_position' => 0,
    'popup_info' => array(
      'value' => '<h2 style="line-height: 20px; ">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px; ">By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_agreed_enabled' => 0,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => 'Thank you for accepting cookies.You can now hide this message or find out more about cookies.',
      'format' => 'plain_text',
    ),
    'popup_link' => 'http://ec.europa.eu/cookies/index_en.htm',
    'popup_height' => '60',
    'popup_width' => '100%',
    'popup_delay' => '1',
    'popup_bg_hex' => '0779BF',
    'popup_text_hex' => 'ffffff',
  );
  $export['eu_cookie_compliance_pl'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_pt';
  $strongarm->value = array(
    'popup_enabled' => 1,
    'popup_clicking_confirmation' => 0,
    'popup_position' => 0,
    'popup_info' => array(
      'value' => '<h2 style="line-height: 20px; ">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px; ">By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_agreed_enabled' => 0,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => 'Thank you for accepting cookies.You can now hide this message or find out more about cookies.',
      'format' => 'plain_text',
    ),
    'popup_link' => 'http://ec.europa.eu/cookies/index_en.htm',
    'popup_height' => '60',
    'popup_width' => '100%',
    'popup_delay' => '1',
    'popup_bg_hex' => '0779BF',
    'popup_text_hex' => 'ffffff',
  );
  $export['eu_cookie_compliance_pt'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_ro';
  $strongarm->value = array(
    'popup_enabled' => 1,
    'popup_clicking_confirmation' => 0,
    'popup_position' => 0,
    'popup_info' => array(
      'value' => '<h2 style="line-height: 20px; ">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px; ">By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_agreed_enabled' => 0,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => 'Thank you for accepting cookies.You can now hide this message or find out more about cookies.',
      'format' => 'plain_text',
    ),
    'popup_link' => 'http://ec.europa.eu/cookies/index_en.htm',
    'popup_height' => '60',
    'popup_width' => '100%',
    'popup_delay' => '1',
    'popup_bg_hex' => '0779BF',
    'popup_text_hex' => 'ffffff',
  );
  $export['eu_cookie_compliance_ro'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_sk';
  $strongarm->value = array(
    'popup_enabled' => 1,
    'popup_clicking_confirmation' => 0,
    'popup_position' => 0,
    'popup_info' => array(
      'value' => '<h2 style="line-height: 20px; ">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px; ">By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_agreed_enabled' => 1,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => 'Thank you for accepting cookies.You can now hide this message or find out more about cookies.',
      'format' => 'plain_text',
    ),
    'popup_link' => 'http://ec.europa.eu/cookies/index_en.htm',
    'popup_height' => '60',
    'popup_width' => '100%',
    'popup_delay' => '1',
    'popup_bg_hex' => '0779BF',
    'popup_text_hex' => 'ffffff',
  );
  $export['eu_cookie_compliance_sk'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_sl';
  $strongarm->value = array(
    'popup_enabled' => 1,
    'popup_clicking_confirmation' => 0,
    'popup_position' => 0,
    'popup_info' => array(
      'value' => '<h2 style="line-height: 20px; ">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px; ">By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_agreed_enabled' => 0,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => 'Thank you for accepting cookies.You can now hide this message or find out more about cookies.',
      'format' => 'plain_text',
    ),
    'popup_link' => 'http://ec.europa.eu/cookies/index_en.htm',
    'popup_height' => '60',
    'popup_width' => '100%',
    'popup_delay' => '1',
    'popup_bg_hex' => '0779BF',
    'popup_text_hex' => 'ffffff',
  );
  $export['eu_cookie_compliance_sl'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_sv';
  $strongarm->value = array(
    'popup_enabled' => 1,
    'popup_clicking_confirmation' => 0,
    'popup_position' => 0,
    'popup_info' => array(
      'value' => '<h2 style="line-height: 20px; ">We use cookies on this site to enhance your user experience</h2><p style="font-size: 13px; line-height: 20px; ">By clicking any link on this page you are giving your consent for us to set cookies.</p>',
      'format' => 'full_html',
    ),
    'popup_agreed_enabled' => 0,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => 'Thank you for accepting cookies.You can now hide this message or find out more about cookies.',
      'format' => 'plain_text',
    ),
    'popup_link' => 'http://ec.europa.eu/cookies/index_en.htm',
    'popup_height' => '60',
    'popup_width' => '100%',
    'popup_delay' => '1',
    'popup_bg_hex' => '0779BF',
    'popup_text_hex' => 'ffffff',
  );
  $export['eu_cookie_compliance_sv'] = $strongarm;

  return $export;
}
