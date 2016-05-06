<?php
/**
 * @file
 * Contains template file.
 */
?>

<a href="#" class="token-ckeditor-tips-toggle">
  <?php print t('<b>Tip</b>: How to use tokens in links'); ?>
</a>
<div class="token-ckeditor-tips-container">
  <ol>
    <li>
      <?php print t('Select and copy the desired URL token, e.g. <pre>[node:123:url]</pre>'); ?>
    </li>
    <li>
      <?php print t('Close this browser window.') ?>
    </li>
    <li>
      <?php print t('Select the text you want to link in your text area and click on the "Link" plugin by clicking on.'); ?>
      <?php print theme('image', array('path' => drupal_get_path('module', 'nexteuropa_token_ckeditor') . '/images/link-icon.png')); ?>
    </li>
    <li>
      <?php print t('Select <pre>other</pre> as protocol and paste the URL token in URL field as shown below:'); ?>
      <br>
      <?php print theme('image', array('path' => drupal_get_path('module', 'nexteuropa_token_ckeditor') . '/images/link-settings.png')); ?>
    </li>
  </ol>
</div>
