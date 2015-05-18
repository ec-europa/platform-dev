<?php
// $Id: simplenews-multi-block.tpl.php,v 1.6 2009/01/02 12:01:17 sutharsan Exp $

/**
 * @file
 * Default theme implementation to display the simplenews block.
 *
 * Copy this file in your theme directory to create a custom themed block.
 *
 * Available variables:
 * - $subscribed: the current user is subscribed to the $tid newsletter
 * - $user: the current user is authenticated
 * - $message: announcement message (Default: 'Stay informed on our latest news!')
 * - $form: newsletter subscription form
 *
 * @see template_preprocess_simplenews_multi_block()
 */
?>

	<?php 
	//check user permissions
	$add_newsletter = (user_access('administer nodes') ? 1 : 0);
	$add_category = (user_access('administer taxonomy') ? 1 : 0);

	$attributes_first = array('type' => 'add', 'action_bar' => 'first', 'btn_group' => 'first');
	$attributes_last = array('type' => 'add_alt', 'action_bar' => 'last', 'btn_group' => 'last');
	$attributes_single = array('type' => 'add', 'action_bar' => 'single', 'btn_group' => 'single');

	if ($add_newsletter && $add_category) {
		print l(t('Create a Newsletter issue'), 'node/add/simplenews', array('attributes' => $attributes_first));
		print l(t('Create a Newsletter'), 'admin/config/services/simplenews', array('attributes' => $attributes_last));
	} 
	else if ($add_newsletter) {
		print l(t('Create a Newsletter issue'), 'node/add/simplenews', array('attributes' => $attributes_single));
	}
	else if ($add_category) {
		print l(t('Create a Newsletter'), 'admin/config/services/simplenews', array('attributes' => $attributes_single));
	}
	?>

  <?php if ($message): ?>
    <p><?php print $message; ?></p>
  <?php endif; ?>

  <?php print render($form); ?>
