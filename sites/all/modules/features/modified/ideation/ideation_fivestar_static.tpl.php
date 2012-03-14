<?php
  //drupal_set_message(print_r('<pre>'. print_r(get_defined_vars(), TRUE) .'</pre>'));
  $output = '';
  $output .= '<div class="fivestar-widget-static fivestar-widget-static-'. $tag .' fivestar-widget-static-'. $stars .' clear-block">';
  if (empty($stars)) {
    $stars = 5;
  }
  $numeric_rating = $rating/(100/$stars);
  for ($n=1; $n <= $stars; $n++) {
    $star_value = ceil((100/$stars) * $n);
    $prev_star_value = ceil((100/$stars) * ($n-1));
    $zebra = ($n % 2 == 0) ? 'even' : 'odd';
    $first = $n == 1 ? ' star-first' : '';
    $last = $n == $stars ? ' star-last' : '';
    $output .= '<div class="star star-'. $n .' star-'. $zebra . $first . $last .'">';
    if ($rating < $star_value && $rating > $prev_star_value) {
      $percent = (($rating - $prev_star_value) / ($star_value - $prev_star_value)) * 100;
      $output .= '<span class="on" style="width: '. $percent .'%">';
    }
    elseif ($rating >= $star_value) {
      $output .= '<span class="on">';
    }
    else {
      $output .= '<span class="off">';
    }
    if ($n == 1)$output .= $numeric_rating;
    $output .= '</span></div>';
  }
  $output .= '</div>';
?>

<div class="ideation-fivestar-static-wrapper">
  <div class="fivestar-widget-ideas">
    <div class="<?php print $class ?> clear-block">
      <div class ="idea-edit-vote-wrapper">
        <?php print $output ?>
      </div>
      <div class="fivestar-tally-box">
        <div class="fivestar-average">
          <span class="vote-average">Average vote:</span> <?php print number_format($avg, 1); ?> <span class="vote-total">of 5</span>
        </div>
        <div class="fivestar-count">
          <?php print format_plural($cast, '1 vote', '@count votes') ?>
        </div>
      </div>
    </div>
  </div>
</div>