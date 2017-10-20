<?php
/**
 * @file
 * Definition of views_handler_area_communities_glossary.
 */

/**
 * Views area handler to display glossary for the list of communities.
 */
class views_handler_area_communities_glossary extends views_handler_area {

  /**
   * Return the glossary.
   */
  public function render($empty = FALSE) {
    global $user;

    // Add alphabetical index.
    $alphabet = array('a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
      'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    );

    $output = '';

    $i = 0;
    $len = count($alphabet);
    foreach ($alphabet as $letter) {
      if (arg(1) == 'my') {
        $url = arg(0) . "/my/" . $user->uid . "/" . $letter;
      }
      else {
        $url = arg(0) . "/" . $letter;
      }

      if ($i == 0) {
        // First.
        $options = array(
          'attributes' => array(
            'type' => 'small',
            'action_bar' => 'first',
            'btn_group' => 'first',
            'class' => array('hidden-phone'),
          ),
        );
        $output .= l($letter, $url, $options);
      }
      elseif ($i == $len - 1) {
        // Last.
        $options = array(
          'attributes' => array(
            'type' => 'small',
            'btn_group' => 'last',
            'class' => array('hidden-phone'),
          ),
        );
        $output .= l($letter, $url, $options);
      }
      else {
        $options = array(
          'attributes' => array(
            'type' => 'small',
            'class' => array('hidden-phone'),
          ),
        );
        $output .= l($letter, $url, $options);
      }
      $i++;
    }

    return $output;
  }

}
