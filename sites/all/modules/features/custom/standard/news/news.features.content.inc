<?php
/**
 * @file
 * news.features.content.inc
 */

/**
 * Implements hook_content_defaults().
 */
function news_content_defaults() {
  $content = array();

  $content['news1'] = (object) array(
    'exported_path' => 'content/my-news-1',
    'title' => 'my news 1',
    'status' => '1',
    'promote' => '0',
    'sticky' => '1',
    'type' => 'news',
    'language' => 'en',
    'created' => '1328886129',
    'comment' => '2',
    'translate' => '0',
    'machine_name' => 'news1',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<p>Lorem Elsass ipsum elementum bredele lacus Racing. auctor, Richard Schirmeck Wurschtsalad Salu bissame tchao bissame amet hopla schneck Heineken Oberschaeffolsheim bissame m&auml;nele dignissim schpeck varius Morbi quam, blottkopf, n&uuml;dle tellus pellentesque Carola turpis wurscht baeckeoffe Pellentesque ullamcorper rossbolla Huguette Mauris ch&#39;ai senectus ftomi! hop rucksack lotto-owe leverwurscht jetz gehts los dolor elit suspendisse vulputate hopla gal habitant leo munster non tristique purus ac risus, placerat consectetur yeuh. kougelhopf vielmols, so wie turpis, barapli Miss Dahlias et merci vielmols libero, adipiscing in, und commodo id sagittis m&eacute;t&eacute;or salu Pfourtz ! leo flammekueche Chulien Yo d&ucirc;. geht&#39;s rhoncus hopla messti de Bischheim morbi Verdammi ante dui schnaps chambon Strasbourg semper hoplageiss mamsell s&#39;guelt Gal ! ornare ac sit libero. Kabinetpapier Gal. sed condimentum Salut bisamme gewurztraminer Coop&eacute; de Truchtersheim tellus sit hopla r&eacute;chime ge&iuml;z Sp&auml;tzle non picon bi&egrave;re amet DNA, Christkindelsm&auml;rik kuglopf Oberschaeffolsheim amet, Chulia Roberstau gravida quam. mollis knack kartoffelsalad sed ornare porta eget libero, eleifend knepfle aliquam Hans sit id, nullam .</p>
  ',
          'summary' => '',
          'format' => 'filtered_html',
          'safe_value' => '<p>Lorem Elsass ipsum elementum bredele lacus Racing. auctor, Richard Schirmeck Wurschtsalad Salu bissame tchao bissame amet hopla schneck Heineken Oberschaeffolsheim bissame mänele dignissim schpeck varius Morbi quam, blottkopf, nüdle tellus pellentesque Carola turpis wurscht baeckeoffe Pellentesque ullamcorper rossbolla Huguette Mauris ch\'ai senectus ftomi! hop rucksack lotto-owe leverwurscht jetz gehts los dolor elit suspendisse vulputate hopla gal habitant leo munster non tristique purus ac risus, placerat consectetur yeuh. kougelhopf vielmols, so wie turpis, barapli Miss Dahlias et merci vielmols libero, adipiscing in, und commodo id sagittis météor salu Pfourtz ! leo flammekueche Chulien Yo dû. geht\'s rhoncus hopla messti de Bischheim morbi Verdammi ante dui schnaps chambon Strasbourg semper hoplageiss mamsell s\'guelt Gal ! ornare ac sit libero. Kabinetpapier Gal. sed condimentum Salut bisamme gewurztraminer Coopé de Truchtersheim tellus sit hopla réchime geïz Spätzle non picon bière amet DNA, Christkindelsmärik kuglopf Oberschaeffolsheim amet, Chulia Roberstau gravida quam. mollis knack kartoffelsalad sed ornare porta eget libero, eleifend knepfle aliquam Hans sit id, nullam .</p>
  ',
          'safe_summary' => '',
        ),
      ),
    ),
  );

return $content;
}
