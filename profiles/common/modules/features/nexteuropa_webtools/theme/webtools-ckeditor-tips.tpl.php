<?php
/**
 * @file
 * Contains template file.
 */
?>

<a href="#" class="webtools-ckeditor-tips-toggle">
  <?php print t('<b>Tip</b>: How to use tokens in webtools'); ?>
</a>
<div class="webtools-ckeditor-tips-container">
  <ol>
    <li>
      <?php print t('Select and copy the desired URL token, e.g. <pre>[node:123:mode-view:default]</pre>'); ?>
    </li>
    <li>
      <?php print t('Close this browser window.') ?>
    </li>
    <li>
      <?php print t('Select the text you want to link in your text area and click on the "Link" plugin by clicking on.'); ?>
    </li>
    <li>
      <?php print t('Select <pre>other</pre> as protocol and paste the URL token in URL field as shown below:'); ?>
    </li>
  </ol>
</div>
