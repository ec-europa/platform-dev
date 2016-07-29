<?php
/**
 * @file
 * Template for the message display in the node form instead of pathauto field.
 */
?>
<?php foreach ($messages as $key => $message): ?>
  <p class="nexteuropa-multilingual-forced-pathauto message-<?php print $key; ?> ">
    <?php print $message; ?>
  </p>
<?php endforeach; ?>
