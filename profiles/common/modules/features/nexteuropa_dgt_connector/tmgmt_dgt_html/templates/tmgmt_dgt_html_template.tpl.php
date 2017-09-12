<?php

/**
 * @file
 * Template of the DGT supported HTML format.
 */
?><?php
// NEPT-862: Add XML declaration above the HTML structure to force the
// UTF-8 encoding.
$xml = <<<XML
<?xml version="1.0" encoding="UTF-8"?>\n
XML;
print $xml;
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <meta name="JobID" content="<?php echo filter_xss($tjid); ?>" />
    <meta name="languageSource" content="<?php echo filter_xss($source_language); ?>" />
    <meta name="languageTarget" content="<?php echo filter_xss($target_language); ?>" />
    <title>Job ID <?php echo filter_xss($tjid); ?></title>
  </head>
  <body>
    <?php foreach ($items as $item_key => $item): ?>
      <div class="asset" id="item-<?php echo filter_xss($item_key); ?>">
        <?php foreach ($item as $field_key => $field): ?>
          <?php
            $key = drupal_substr($field_key, 1);
            $key = base64_decode(str_pad(strtr($key, '-_', '+/'), drupal_strlen($key) % 4, '=', STR_PAD_RIGHT));
          ?>
        <!--
          label="<?php echo filter_xss($field['#label']); ?>"
          context="[<?php echo filter_xss($key); ?>]"
        -->
        <div class="atom" id="<?php echo filter_xss($field_key); ?>"><?php echo $field['#text']; ?></div>
        <?php endforeach; ?>
      </div>
    <?php endforeach; ?>
  </body>
</html>
