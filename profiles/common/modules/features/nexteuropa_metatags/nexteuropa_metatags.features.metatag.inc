<?php

/**
 * @file
 * nexteuropa_metatags.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function nexteuropa_metatags_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: global.
  $config['global'] = array(
    'instance' => 'global',
    'config' => array(
      'title' => array(
        'value' => '[current-page:title] | [site:name]',
      ),
      'description' => array(
        'value' => '[site:name] - [site:slogan]',
      ),
      'abstract' => array(
        'value' => '',
      ),
      'keywords' => array(
        'value' => 'European Comission, European Union, EU',
      ),
      'viewport' => array(
        'value' => 'width=device-width, initial-scale=1.0',
      ),
      'robots' => array(
        'value' => array(
          'index' => 'index',
          'follow' => 'follow',
          'noindex' => 0,
          'nofollow' => 0,
          'noarchive' => 0,
          'nosnippet' => 0,
          'noodp' => 0,
          'noydir' => 0,
          'noimageindex' => 0,
          'notranslate' => 0,
        ),
      ),
      'news_keywords' => array(
        'value' => '',
      ),
      'standout' => array(
        'value' => '',
      ),
      'rating' => array(
        'value' => '',
      ),
      'referrer' => array(
        'value' => '',
      ),
      'generator' => array(
        'value' => 'Drupal 7 (http://drupal.org)',
      ),
      'rights' => array(
        'value' => '',
      ),
      'image_src' => array(
        'value' => '',
      ),
      'canonical' => array(
        'value' => '[current-page:url:absolute]',
      ),
      'shortlink' => array(
        'value' => '[current-page:url:unaliased]',
      ),
      'publisher' => array(
        'value' => '',
      ),
      'author' => array(
        'value' => '',
      ),
      'original-source' => array(
        'value' => '',
      ),
      'prev' => array(
        'value' => '',
      ),
      'next' => array(
        'value' => '',
      ),
      'revisit-after' => array(
        'value' => 15,
        'period' => 'day',
      ),
      'content-language' => array(
        'value' => '[language:language-ui:language]',
      ),
      'geo.position' => array(
        'value' => '',
      ),
      'geo.placename' => array(
        'value' => '',
      ),
      'geo.region' => array(
        'value' => '',
      ),
      'icbm' => array(
        'value' => '',
      ),
      'refresh' => array(
        'value' => '',
      ),
      'dcterms.title' => array(
        'value' => '[current-page:title]',
      ),
      'dcterms.creator' => array(
        'value' => '',
      ),
      'dcterms.subject' => array(
        'value' => '',
      ),
      'dcterms.description' => array(
        'value' => '',
      ),
      'dcterms.publisher' => array(
        'value' => '',
      ),
      'dcterms.contributor' => array(
        'value' => '',
      ),
      'dcterms.date' => array(
        'value' => '',
      ),
      'dcterms.type' => array(
        'value' => 'Text',
      ),
      'dcterms.format' => array(
        'value' => 'text/html',
      ),
      'dcterms.identifier' => array(
        'value' => '[current-page:url:absolute]',
      ),
      'dcterms.source' => array(
        'value' => '',
      ),
      'dcterms.language' => array(
        'value' => '',
      ),
      'dcterms.relation' => array(
        'value' => '',
      ),
      'dcterms.coverage' => array(
        'value' => '',
      ),
      'dcterms.rights' => array(
        'value' => '',
      ),
      'fb:admins' => array(
        'value' => '',
      ),
      'fb:app_id' => array(
        'value' => '',
      ),
      'og:site_name' => array(
        'value' => '[site:name] - European Commission',
      ),
      'og:type' => array(
        'value' => 'website',
      ),
      'og:url' => array(
        'value' => '[current-page:url:absolute]',
      ),
      'og:title' => array(
        'value' => '[current-page:title]',
      ),
      'og:determiner' => array(
        'value' => '',
      ),
      'og:description' => array(
        'value' => '[site:name] - [site:slogan]',
      ),
      'og:updated_time' => array(
        'value' => '',
      ),
      'og:see_also' => array(
        'value' => '',
      ),
      'og:image' => array(
        'value' => '',
      ),
      'og:image:url' => array(
        'value' => '',
      ),
      'og:image:secure_url' => array(
        'value' => '',
      ),
      'og:image:type' => array(
        'value' => '',
      ),
      'og:image:width' => array(
        'value' => '',
      ),
      'og:image:height' => array(
        'value' => '',
      ),
      'og:latitude' => array(
        'value' => '',
      ),
      'og:longitude' => array(
        'value' => '',
      ),
      'og:street_address' => array(
        'value' => '',
      ),
      'og:locality' => array(
        'value' => '',
      ),
      'og:region' => array(
        'value' => '',
      ),
      'og:postal_code' => array(
        'value' => '',
      ),
      'og:country_name' => array(
        'value' => '',
      ),
      'og:email' => array(
        'value' => '',
      ),
      'og:phone_number' => array(
        'value' => '',
      ),
      'og:fax_number' => array(
        'value' => '',
      ),
      'og:locale' => array(
        'value' => '',
      ),
      'og:locale:alternate' => array(
        'value' => '',
      ),
      'article:author' => array(
        'value' => '',
      ),
      'article:publisher' => array(
        'value' => '',
      ),
      'article:section' => array(
        'value' => '',
      ),
      'article:tag' => array(
        'value' => '',
      ),
      'article:published_time' => array(
        'value' => '',
      ),
      'article:modified_time' => array(
        'value' => '',
      ),
      'article:expiration_time' => array(
        'value' => '',
      ),
      'profile:first_name' => array(
        'value' => '',
      ),
      'profile:last_name' => array(
        'value' => '',
      ),
      'profile:username' => array(
        'value' => '',
      ),
      'profile:gender' => array(
        'value' => '',
      ),
      'og:audio' => array(
        'value' => '',
      ),
      'og:audio:secure_url' => array(
        'value' => '',
      ),
      'og:audio:type' => array(
        'value' => '',
      ),
      'book:author' => array(
        'value' => '',
      ),
      'book:isbn' => array(
        'value' => '',
      ),
      'book:release_date' => array(
        'value' => '',
      ),
      'book:tag' => array(
        'value' => '',
      ),
      'og:video' => array(
        'value' => '',
      ),
      'og:video:secure_url' => array(
        'value' => '',
      ),
      'og:video:width' => array(
        'value' => '',
      ),
      'og:video:height' => array(
        'value' => '',
      ),
      'og:video:type' => array(
        'value' => '',
      ),
      'video:actor' => array(
        'value' => '',
      ),
      'video:actor:role' => array(
        'value' => '',
      ),
      'video:director' => array(
        'value' => '',
      ),
      'video:writer' => array(
        'value' => '',
      ),
      'video:duration' => array(
        'value' => '',
      ),
      'video:release_date' => array(
        'value' => '',
      ),
      'video:tag' => array(
        'value' => '',
      ),
      'video:series' => array(
        'value' => '',
      ),
      'creator' => array(
        'value' => 'COMM/DG/UNIT',
      ),
      'reference' => array(
        'value' => '[site:name]',
      ),
      'X-UA-Compatible' => array(
        'value' => 'IE=edge',
      ),
      'date' => array(
        'value' => '[current-date:short]',
      ),
      'classification' => array(
        'value' => '[variable:classification]',
      ),
      'ESS_GF' => array(
        'value' => '',
      ),
      'ESS_RF' => array(
        'value' => '',
      ),
    ),
  );

  // Exported Metatag config instance: node.
  $config['node'] = array(
    'instance' => 'node',
    'config' => array(
      'title' => array(
        'value' => '[node:title] | [site:name]',
      ),
      'description' => array(
        'value' => '[node:title]',
      ),
      'keywords' => array(
        'value' => '[node:field-tags]',
      ),
      'dcterms.title' => array(
        'value' => '[node:title]',
      ),
      'dcterms.creator' => array(
        'value' => '[node:author]',
      ),
      'dcterms.description' => array(
        'value' => '[node:summary]',
      ),
      'dcterms.date' => array(
        'value' => '[node:created:custom:Y-m-d\\TH:iP]',
      ),
      'dcterms.language' => array(
        'value' => '[node:language]',
      ),
      'og:type' => array(
        'value' => '[node:content-type]',
      ),
      'og:title' => array(
        'value' => '[node:title] - [site:name] - European Commission',
      ),
      'og:description' => array(
        'value' => '[node:title]',
      ),
      'og:updated_time' => array(
        'value' => '[node:changed:custom:c]',
      ),
      'article:published_time' => array(
        'value' => '[node:created:custom:c]',
      ),
      'article:modified_time' => array(
        'value' => '[node:changed:custom:c]',
      ),
    ),
  );

  return $config;
}
