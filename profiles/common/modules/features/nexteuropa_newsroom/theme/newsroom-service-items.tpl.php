<?php
/**
 * @file
 * Service items template.
 */
?>
<?php if (count($items) > 0) : ?>
  <div class="<?php echo $css_class; ?>-items-container service-item-container">
    <h4><?php echo $title; ?></h4>
    <?php foreach ($items as $item) : ?>
      <div class="newsletter-item">
        <h5><?php echo $item->taxonomy_term_data_name; ?></h5>
        <?php $service_id = NULL; ?> 
        <?php if (isset($item->field_field_newsroom_service_id[0])): ?>
        <?php $service_id = $item->field_field_newsroom_service_id[0]['raw']['value']; ?>
        <div class="sample"><?php echo l(t('sample'), 'http://ec.europa.eu/information_society/newsroom/cf/dae/newsletter-specific-archive.cfm?serviceId=' . $item->field_field_newsroom_service_id[0]['raw']['value'], array('external' => TRUE)); ?></div>
        <?php endif; ?>
        <?php if (isset($item->field_field_newsroom_service_image[0])): ?>
        <?php $item->field_field_newsroom_service_image[0]['rendered']['#image_style'] = 'newsroom_style'; ?>
        <div class="image"><?php echo drupal_render($item->field_field_newsroom_service_image[0]['rendered']); ?></div>
        <?php endif; ?>
        <div class="description"><?php echo $item->taxonomy_term_data_description; ?></div>
        <?php $form = drupal_get_form('nexteuropa_newsroom_newsletter_form', $service_id); ?>
        <div class="form"><?php echo drupal_render($form); ?></div>
      </div>
    <?php endforeach; ?>
  </div>
<?php endif; ?>