<?php
/**
 * @file
 * Splash screen.
 */
?>

<div id="splash-block">
<?php print render($page['content']); ?>
</div>

<?php global $base_url; ?>
<script type="text/javascript">
  var templatePath = "<?php print $base_url . '/' . path_to_theme(); ?>";
</script>
