<?php

/**
 * @file
 * Default theme implementation to present all user profile data.
 *
 * This template is used when viewing a registered member's profile page,
 * e.g., example.com/user/123. 123 being the users ID.
 *
 * Use render($user_profile) to print all profile items, or print a subset
 * such as render($user_profile['user_picture']). Always call
 * render($user_profile) at the end in order to print all remaining items. If
 * the item is a category, it will contain all its profile items. By default,
 * $user_profile['summary'] is provided, which contains data on the user's
 * history. Other data can be included by modules. $user_profile['user_picture']
 * is available for showing the account picture.
 *
 * Available variables:
 *   - $user_profile: An array of profile items. Use render() to print them.
 *   - Field variables: for each field instance attached to the user a
 *     corresponding variable is defined; e.g., $account->field_example has a
 *     variable $field_example defined. When needing to access a field's raw
 *     values, developers/themers are strongly encouraged to use these
 *     variables. Otherwise they will have to explicitly specify the desired
 *     field language, e.g. $account->field_example['en'], thus overriding any
 *     language negotiation rule that was previously applied.
 *
 * @see user-profile-category.tpl.php
 *   Where the html is handled for the group.
 * @see user-profile-item.tpl.php
 *   Where the html is handled for each item in the group.
 * @see template_preprocess_user_profile()
 */
?>
<div class="profile"<?php print $attributes; ?>>
  <?php
    // List basic fields.
    $basic = array(
      'field_firstname',
      'field_lastname',
      'user_picture',
      'summary',
    );
  ?>

  <div class="well well-sm">
    <div class="row">
      <div class="col-lg-2 col-md-3 col-sm-3 col-xs-4">
        <?php print render($user_profile['user_picture']); ?>
      </div>
      <div class="col-lg-10 col-md-9 col-sm-9 col-xs-8">
        <blockquote>
          <h3>
            <?php print $user_info['name']; ?>
          </h3>
          <small>
            <?php print $user_info['date']; ?>
          </small>
      </div>
    </div>
    <?php
      if (isset($contact_form)):
        print $contact_form;
      endif;
    ?>
  </div>

  <?php
    foreach ($user_profile as $key => $value):
      if (!in_array($key, $basic)):
        print render($value);
      endif;
    endforeach;
  ?>
</div>
