<?php print render($page['content']); ?>
  <div class="layout-footer">
    <div class="layout-footer-wrapper navbar-inner">
      <?php if ($page['footer']): ?>
        <?php print render($page['footer']); ?>
      <?php endif; ?>
      <?php print t('Last update:') . ' ' . date('d/m/Y'); ?> | <a href="#top-page">Top</a>
    </div>
  </div><!-- /.layout-footer -->
</div><!-- /#layout -->
