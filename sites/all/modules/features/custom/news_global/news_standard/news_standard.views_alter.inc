<?php

/**
* Implementation of hook_views_default_views_alter().
*/
function news_standard_views_default_views_alter(&$views) {
  // Alter only the 'view_name_of_interest' view.
  if (array_key_exists('news', $views)) {
	$view=$views['news'];
	 

  }
}
