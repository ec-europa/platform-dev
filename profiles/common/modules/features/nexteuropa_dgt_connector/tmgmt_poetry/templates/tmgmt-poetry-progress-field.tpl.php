<?php

/**
 * @file
 * Template file for the TMGMT POETRY progress field.
 *
 * Available custom variables:
 * - $stats: An array with statistics data.
 * - $title: String which can be used as a tooltip.
 */
?>
<span title="<?php print $title ?>">
  <ul class="tmgmt-poetry progress-field-list">
    <?php foreach ($stats as $key => $stat): ?>
      <li>
        <label>[<?php print drupal_strtoupper($key[1]) ?>]</label>
        <span>[<?php print $stat; ?>]</span>
      </li>
    <?php endforeach; ?>
  </ul>
</span>
