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
    'field_top_news' => array(
      'und' => array(
        0 => array(
          'value' => '0',
        ),
      ),
    ),
  );

  $content['top1'] = (object) array(
    'exported_path' => 'news/top-news-one',
    'title' => 'Top News One',
    'status' => '1',
    'promote' => '0',
    'sticky' => '0',
    'type' => 'news',
    'language' => 'en',
    'created' => '1330963548',
    'comment' => '2',
    'translate' => '0',
    'machine_name' => 'top1',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<p>Lorem Elsass ipsum risus, gal r&eacute;chime so knack Coop&eacute; de Truchtersheim purus gravida Hans leo sit Christkindelsm&auml;rik habitant ch&#39;ai rucksack mamsell eleifend rossbolla sed salu blottkopf, leo id schneck Wurschtsalad jetz gehts los id, leverwurscht elit hopla turpis turpis, quam. gewurztraminer auctor, n&uuml;dle schnaps Richard Schirmeck hoplageiss geht&#39;s amet Sp&auml;tzle morbi m&eacute;t&eacute;or libero, tellus kuglopf consectetur schpeck lotto-owe sagittis DNA, Oberschaeffolsheim dui amet placerat baeckeoffe Gal. semper kougelhopf munster ante hopla messti de Bischheim nullam Miss Dahlias tchao bissame condimentum varius kartoffelsalad dolor pellentesque suspendisse sit eget vielmols, libero, porta Yo d&ucirc;. wie mollis non hopla Pfourtz ! Oberschaeffolsheim ge&iuml;z lacus dignissim Kabinetpapier Racing. Salu bissame Gal ! bredele wurscht Mauris s&#39;guelt libero. ac vulputate Salut bisamme elementum in, rhoncus Chulia Roberstau sed Verdammi et flammekueche commodo bissame picon bi&egrave;re Pellentesque tellus adipiscing merci vielmols Morbi ftomi! ornare yeuh. Strasbourg amet, Carola tristique Chulien senectus ornare hop barapli quam, chambon knepfle ullamcorper Huguette non hopla sit Heineken und ac m&auml;nele aliquam .</p>
  ',
          'summary' => '',
          'format' => 'filtered_html',
          'safe_value' => '<p>Lorem Elsass ipsum risus, gal réchime so knack Coopé de Truchtersheim purus gravida Hans leo sit Christkindelsmärik habitant ch\'ai rucksack mamsell eleifend rossbolla sed salu blottkopf, leo id schneck Wurschtsalad jetz gehts los id, leverwurscht elit hopla turpis turpis, quam. gewurztraminer auctor, nüdle schnaps Richard Schirmeck hoplageiss geht\'s amet Spätzle morbi météor libero, tellus kuglopf consectetur schpeck lotto-owe sagittis DNA, Oberschaeffolsheim dui amet placerat baeckeoffe Gal. semper kougelhopf munster ante hopla messti de Bischheim nullam Miss Dahlias tchao bissame condimentum varius kartoffelsalad dolor pellentesque suspendisse sit eget vielmols, libero, porta Yo dû. wie mollis non hopla Pfourtz ! Oberschaeffolsheim geïz lacus dignissim Kabinetpapier Racing. Salu bissame Gal ! bredele wurscht Mauris s\'guelt libero. ac vulputate Salut bisamme elementum in, rhoncus Chulia Roberstau sed Verdammi et flammekueche commodo bissame picon bière Pellentesque tellus adipiscing merci vielmols Morbi ftomi! ornare yeuh. Strasbourg amet, Carola tristique Chulien senectus ornare hop barapli quam, chambon knepfle ullamcorper Huguette non hopla sit Heineken und ac mänele aliquam .</p>
  ',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_top_news' => array(
      'und' => array(
        0 => array(
          'value' => '1',
        ),
      ),
    ),
  );

  $content['top2'] = (object) array(
    'exported_path' => 'news/second-top-news',
    'title' => 'A Second Top News',
    'status' => '1',
    'promote' => '0',
    'sticky' => '0',
    'type' => 'news',
    'language' => 'en',
    'created' => '1330963605',
    'comment' => '2',
    'translate' => '0',
    'machine_name' => 'top2',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<p>Lorem Elsass ipsum salu Mauris schneck mamsell adipiscing Gal. sed Salu bissame condimentum Pfourtz ! rucksack tristique non Hans gal quam, non eget commodo geht&#39;s schnaps Coop&eacute; de Truchtersheim nullam ornare Christkindelsm&auml;rik m&auml;nele bissame s&#39;guelt knepfle Huguette ac amet, porta baeckeoffe libero, turpis, DNA, ullamcorper Carola und Chulien placerat purus munster vulputate suspendisse Salut bisamme hopla wie leverwurscht chambon hopla bredele id schpeck Richard Schirmeck sit consectetur blottkopf, picon bi&egrave;re Oberschaeffolsheim sagittis ge&iuml;z messti de Bischheim Strasbourg n&uuml;dle dolor Sp&auml;tzle flammekueche et sit ch&#39;ai sit jetz gehts los risus, Oberschaeffolsheim in, kougelhopf yeuh. pellentesque amet gewurztraminer leo r&eacute;chime hop hopla turpis tellus lotto-owe Miss Dahlias rossbolla mollis kuglopf m&eacute;t&eacute;or tchao bissame ac ante Wurschtsalad sed hopla ftomi! morbi hoplageiss Verdammi varius senectus kartoffelsalad merci vielmols tellus Gal ! knack id, quam. vielmols, Chulia Roberstau habitant amet elit ornare Racing. libero. so aliquam wurscht eleifend Kabinetpapier dignissim Pellentesque libero, auctor, rhoncus Yo d&ucirc;. dui elementum Heineken gravida lacus leo Morbi semper barapli .</p>
  ',
          'summary' => '',
          'format' => 'filtered_html',
          'safe_value' => '<p>Lorem Elsass ipsum salu Mauris schneck mamsell adipiscing Gal. sed Salu bissame condimentum Pfourtz ! rucksack tristique non Hans gal quam, non eget commodo geht\'s schnaps Coopé de Truchtersheim nullam ornare Christkindelsmärik mänele bissame s\'guelt knepfle Huguette ac amet, porta baeckeoffe libero, turpis, DNA, ullamcorper Carola und Chulien placerat purus munster vulputate suspendisse Salut bisamme hopla wie leverwurscht chambon hopla bredele id schpeck Richard Schirmeck sit consectetur blottkopf, picon bière Oberschaeffolsheim sagittis geïz messti de Bischheim Strasbourg nüdle dolor Spätzle flammekueche et sit ch\'ai sit jetz gehts los risus, Oberschaeffolsheim in, kougelhopf yeuh. pellentesque amet gewurztraminer leo réchime hop hopla turpis tellus lotto-owe Miss Dahlias rossbolla mollis kuglopf météor tchao bissame ac ante Wurschtsalad sed hopla ftomi! morbi hoplageiss Verdammi varius senectus kartoffelsalad merci vielmols tellus Gal ! knack id, quam. vielmols, Chulia Roberstau habitant amet elit ornare Racing. libero. so aliquam wurscht eleifend Kabinetpapier dignissim Pellentesque libero, auctor, rhoncus Yo dû. dui elementum Heineken gravida lacus leo Morbi semper barapli .</p>
  ',
          'safe_summary' => '',
        ),
      ),
    ),
    'field_top_news' => array(
      'und' => array(
        0 => array(
          'value' => '1',
        ),
      ),
    ),
  );

return $content;
}
