<?php

/**
 * @file
 * Preprocess functions for Newsroom blocks.
 */

/**
 * Returns HTML for a Newsroom Agenda type block.
 */
function theme_newsroom_agenda($variables) {
  $agenda = array();
  $days_to_list = variable_get('newsroom_summary_home_block_num_agenda', 3);

  $i = 0;
  $today = date('Y-m-d', time());
  foreach ($variables as $date => $events) {
    // Show only items from a specific date.
    // @TODO: make this flexible.
    if ($date < $today) {
      continue;
    }

    // Show only the number of days needed.
    if ($i == $days_to_list) {
      break;
    }

    $agenda[$date]['#prefix'] = '<div class="date-row">';
    $agenda[$date]['#suffix'] = '</div>';
    $agenda[$date]['date']['#prefix'] = '<div class="date-date">';
    $agenda[$date]['date']['#markup'] = theme('newsroom_agenda_date', array('date' => strtotime($date)));
    $agenda[$date]['date']['#suffix'] = '</div>';
    $agenda[$date]['events']['#prefix'] = '<div class="date-events">';
    $agenda[$date]['events']['#suffix'] = '</div>';

    if (is_array($events)) {
      // Order items by their lenght.
      usort($events, function ($a, $b) {
        return $a['attributes']['length'] >= $b['attributes']['length'];
      });

      foreach ($events as $delta => $event) {
        $agenda[$date]['events'][$delta] = $event;
      }
    }
    $i++;
  }
  return drupal_render($agenda);
}

/**
 * Returns HTML for a Newsroom Agenda type block date card.
 */
function theme_newsroom_agenda_date($variables) {
  $date = array();
  $date['day']['#markup'] = '<span class="day">' . date('d', $variables['date']) . '</span>';
  $date['month']['#markup'] = '<span class="month">' . date('M', $variables['date']) . '</span>';
  $date['year']['#markup'] = '<span class="year">' . date('Y', $variables['date']) . '</span>';
  return drupal_render($date);
}
