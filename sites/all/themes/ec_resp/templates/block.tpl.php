<?php

/**
 * @file
 * Default theme implementation to display a block.
 *
 * Available variables:
 * - $block->subject: Block title.
 * - $content: Block content.
 * - $block->module: Module that generated the block.
 * - $block->delta: An ID for the block, unique within each module.
 * - $block->region: The block region embedding the current block.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - block: The current template type, i.e., "theming hook".
 *   - block-[module]: The module generating the block. For example, the user
 *     module is responsible for handling the default user navigation block. In
 *     that case the class would be 'block-user'.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Helper variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $block_zebra: Outputs 'odd' and 'even' dependent on each block region.
 * - $zebra: Same output as $block_zebra but independent of any block region.
 * - $block_id: Counter dependent on each block region.
 * - $id: Same output as $block_id but independent of any block region.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 * - $block_html_id: A valid HTML ID and guaranteed unique.
 *
 * @see template_preprocess()
 * @see template_preprocess_block()
 * @see template_process()
 *
 * @ingroup themeable
 */
?>

<?php
  // list of all block than don't need a panel
  $block_no_panel = array(
    'search' => 'form',
    'print' => 'print-links',
    'workbench' => 'block',
    'social_bookmark' => 'social-bookmark',
    'views' => 'view_ec_content_slider-block',
    'om_maximenu' => array('om-maximenu-1','om-maximenu-2'),
    'menu' => 'menu-service-tools',
    'cce_basic_config' => 'footer_ipg',
  );

  // list of all blocks that don't need their title to be displayed
  $block_no_title = array(
    'fat_footer' => 'fat-footer',
    'om_maximenu' => array('om-maximenu-1','om-maximenu-2'),
    'menu' => 'menu-service-tools',
    'cce_basic_config' => 'footer_ipg',
  );

  $block_no_body_class = array(
    
  );
  
  $panel = true;
  foreach ($block_no_panel as $key => $value) {
    if ($block->module == $key) {
      if (is_array($value)) {
        foreach ($value as $delta) {
          if ($block->delta == $delta) {
            $panel = false;
            break;
          }
        }
      }
      else {
        if ($block->delta == $value) {
          $panel = false;
          break;
        }
      }
    }
  }

  $title = true;
  foreach ($block_no_title as $key => $value) {
    if ($block->module == $key) {
      if (is_array($value)) {
        foreach ($value as $delta) {
          if ($block->delta == $delta) {
            $title = false;
            break;
          }
        }
      }
      else {
        if ($block->delta == $value) {
          $title = false;
          break;
        }
      }
    }
  }   

  $body_class = true;
  foreach ($block_no_body_class as $key => $value) {
    if ($block->module == $key && $block->delta == $value) {
      $body_class = false;
    }
  }      
?>

<div id="<?php print $block_html_id; ?>" class="<?php print $classes; ?> <?php if ($panel) print 'panel panel-default clearfix'; ?>">
  
<?php print render($title_prefix); ?>
<?php if ($title && $block->subject): ?>
  <div class="<?php if ($panel) print 'panel-heading'; ?>">
    <?php print $block->subject ?>
  </div>
<?php endif;?>
<?php print render($title_suffix); ?>

  <div class="<?php if ($panel && $body_class) print 'panel-body'; ?> content"<?php print $content_attributes; ?>>
  <?php 
    print $content;
   ?>
  </div>

</div>