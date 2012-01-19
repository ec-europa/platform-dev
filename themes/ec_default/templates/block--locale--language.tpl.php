<!-- LANGUAGE DROP-DOWN SECTION -->
<?php
global $language;
$languages = language_list('enabled');
$li = "";

$li = '<li class="selected" lang="'.$language->language.'" title="'.$language->native.'"><span class="off-screen">Current language:</span> '.$language->language.'</li>';

foreach($languages[1] as $lang) {

  //get path of translated content
  $translations = translation_path_get_translations($_GET['q']);

  if ($lang->prefix) {
    if ($translations) {
      $path = $lang->prefix.'/'.$translations[$lang->prefix];
    } else { // no translations for this content
      $path = ($_GET['q'] == 'node' ? $lang->prefix.'/' : $lang->prefix.'/'.$_GET['q']);
    }
  } else { //default language, no prefix
    if ($translations) {
      $path = $translations[$lang->language];
    } else { // no translations for this content
      $path = ($_GET['q'] == 'node' ? '' : $_GET['q']);
    }
  }
  //$path = ($translations ? '/'.$translations[$lang->prefix] : '');
  
  //add enabled languages
  $li .= '<li><a href="'.base_path().$path.'" hreflang="'.$lang->language.'" lang="'.$lang->language.'" title="'.$lang->native.'">'.$lang->language.'</a></li>';
}
?>
	<ul class="reset-list language-selector" id="language-selector">
  <?php print $li; ?>
  </ul>
<!-- LANGUAGE DROP-DOWN SECTION -->