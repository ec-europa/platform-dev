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
    //list basic fields
    $basic = array('field_firstname', 'field_lastname', 'user_picture', 'summary');
    $output = '';

    $profile_user = user_load(arg(1));
  ?>
  
  <fieldset>
  <legend>Identity</legend>
    <div class="span2">
  <?php 
    print render($user_profile['user_picture']);
  ?>
    </div>
    <div class="span7">
    <?php
      $identity = '';
      if (isset($user_profile['field_firstname'][0]['#markup'])) {
        $identity .= $user_profile['field_firstname'][0]['#markup'];
      }
      if (isset($user_profile['field_lastname'][0]['#markup'])) {
        if ($identity != '') {
          $identity .= ' ';
        }
        $identity .= $user_profile['field_lastname'][0]['#markup'];
      }      
      $output .= '<h3>' . $identity . '</h3>';
      
      $output .= '<p><strong>' . t('Member since') . '</strong>: ' . date('d/m/Y',$profile_user->created) . '</p>';
    
      $output .= l(t('Contact this user'), 'user/'.$elements['#account']->uid.'/contact', array('attributes' => array('type' => 'message')));
      
      print $output;
    ?>
    
    </div>
  </fieldset>
  
  <?php 
    $display_additionnal = FALSE;
    foreach ($user_profile as $key => $value) {
      if (!in_array($key,$basic)) {
        $display_additionnal = TRUE;
        break;
      }
    }
  ?>    
  
  <?php if ($display_additionnal) { ?>
  <fieldset>
  <legend>Additional information</legend>
  <?php 
    foreach ($user_profile as $key => $value) {
      if (!in_array($key,$basic)) {
        $field = '<div class="field">';
        $field .= '<div class="span2 field-label">'.$value['#title'].'</div>';
        if ($variables['no_left']) {
          $field .= '<div class="span9 no_label">'.render($value).'</div>';
        } else {
          $field .= '<div class="span7 no_label">'.render($value).'</div>';
        }
        $field .= '</div>';
        
        print $field;
      }
    }
  ?>  
  </fieldset>  
  <?php } ?>
  
</div>