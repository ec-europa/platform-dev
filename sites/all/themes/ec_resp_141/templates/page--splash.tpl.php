<?php
/**
 * @file
 * Splash screen.
 */
?>

<?php print render($page['content']); ?>

<?php global $base_url; ?>
<script type="text/javascript">
  var templatePath = "<?php print $base_url . '/' . path_to_theme(); ?>";
</script>
