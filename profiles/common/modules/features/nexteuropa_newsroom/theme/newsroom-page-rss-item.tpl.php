<?php

/**
 * @file
 * Default view template to display a item in an RSS feed.
 */
?>
<item>
  <title><?php echo $title; ?></title>
  <link><?php echo $link; ?></link>
  <description><?php echo $teaser; ?></description>
  <guid isPermaLink="true"><?php echo $node_redirect_url; ?></guid>
</item>
