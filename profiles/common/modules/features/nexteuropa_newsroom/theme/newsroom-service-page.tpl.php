<?php
/**
 * @file
 * Service list page.
 */
global $user;
?>
<div class="newsroom-service-page">
  <?php if (user_is_logged_in()): ?>
    <h3><?php echo t('You e-mail'); ?></h3>
    <div class="newsroom-service-email-description">
      <?php echo $user->mail; ?>
    </div>
  <?php else: ?>
    <h3><span><?php echo t('Step 1'); ?></span> - <?php echo t('You e-mail'); ?></h3>
    <div>
      <input type="text" class="newsroom-service-email" id="newsroom-service-email" />
    </div>
    <div class="newsroom-service-email-description">
      <span><?php echo 'or'; ?></span> <?php echo l(t('login'), 'user/login'); ?> <?php echo t('to manage your subscriptions.'); ?>
    </div>
  <?php endif; ?>

  <?php if (user_is_logged_in()): ?>
    <h3><?php echo t('Subscribe to newsletters'); ?></h3>
  <?php else: ?>
    <h3><span><?php echo t('Step 2'); ?></span> - <?php echo t('Subscribe to newsletters'); ?></h3>
  <?php endif; ?>

  <?php echo $central_items; ?>
  <?php echo $basic_items; ?>    

  <?php if (!empty($privacy_text)): ?>
    <h3><?php echo t('Privacy Statement'); ?></h3>
    <?php echo $privacy_text; ?>
  <?php endif; ?>
</div>

<script type="text/javascript">
  (function ($) {
    $('#newsroom-service-email').change(function() {
      var regex = /^([a-zA-Z0-9_.+-])+\@(([a-zA-Z0-9-])+\.)+([a-zA-Z0-9]{2,4})+$/;
      var email = $(this).val();
      if (regex.test($(this).val())) {
        $('.service-item-container input[name="email"]').each(function(){
          $(this).val(email);
        });
        $('.service-item-container input[type="submit"]').each(function(){
          $(this).prop('disabled', false);
        });
      } else {
        alert('<?php echo t('Wrong e-mail address'); ?>');
      }
    });
  })(jQuery);
</script>

