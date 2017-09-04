<?php

/**
 * @file
 * Contains the template file of the blockquote component.
 *
 * Available variables:
 * - $markup: string or a render array.
 */
?>

<blockquote class="blockquote"<?php print $attributes; ?>>
  <p><?php print render($markup);?></p>
</blockquote>
