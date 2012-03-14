<div class="fivestar-widget-ideas">
  <div class="<?php print $class ?> clear-block">
    <div class ="idea-edit-vote-wrapper">
      <?php print drupal_render_children($form); ?>
    </div>
    <div class="fivestar-tally-box">
      <div class="fivestar-average">
        <span class="vote-average">Average vote:</span> <?php print number_format($avg, 1); ?> <span class="vote-total">of 5</span>
      </div>
      <div class="fivestar-count">
        <?php print format_plural($cast, '1 vote', '@count votes') ?>
      </div>
    </div>
  </div>
</div>