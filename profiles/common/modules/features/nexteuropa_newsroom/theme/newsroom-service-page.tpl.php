<?php
/**
 * @file
 * Service list page.
 */
global $user;
?>
<div class="newsroom-service-page">
  <?php if (user_is_logged_in()): ?>
    <h2><?php echo t('Your e-mail'); ?></h2>
    <div class="newsroom-service-email-description">
      <?php echo $user->mail; ?>
    </div>
  <?php else: ?>
    <h2><span><?php echo t('Step 1'); ?></span> - <?php echo t('Your e-mail'); ?></h2>
    <div>
      <input type="text" class="newsroom-service-email" id="newsroom-service-email" />
    </div>
    <div class="newsroom-service-email-description">
      <span><?php echo 'or'; ?></span> <?php echo l(t('login'), 'user/login'); ?> <?php echo t('to manage your subscriptions.'); ?>
    </div>
  <?php endif; ?>

  <?php if (user_is_logged_in()): ?>
    <h2><?php echo t('Subscribe to newsletters'); ?></h2>
  <?php else: ?>
    <h2><span><?php echo t('Step 2'); ?></span> - <?php echo t('Subscribe to newsletters'); ?></h2>
  <?php endif; ?>

  <?php echo $central_items; ?>
  <?php echo $basic_items; ?>    

  <?php if (!empty($privacy_text)): ?>
    <h2><?php echo t('Privacy Statement'); ?></h2>
    <?php echo $privacy_text; ?>
  <?php endif; ?>
</div>
<script type="text/javascript">
  (function ($) {
    $('.serviceItemContainer input[type="submit"]').each(function(){
      $(this).prop('disabled', <?php echo !user_is_logged_in(); ?>);
    });
    $('#newsroom-service-email').change(function() {
      var regex = /^([a-zA-Z0-9_.+-])+\@(([a-zA-Z0-9-])+\.)+([a-zA-Z0-9]{2,4})+$/;
      var email = $(this).val();
      if (regex.test($(this).val())) {
        $('.serviceItemContainer input[name="email"]').each(function(){
          $(this).val(email);
        });
        $('.serviceItemContainer input[type="submit"]').each(function(){
          $(this).prop('disabled', false);
        });
      } else {
        alert('<?php echo t('Wrong e-mail address'); ?>');
      }
    });
  })(jQuery);
</script>
