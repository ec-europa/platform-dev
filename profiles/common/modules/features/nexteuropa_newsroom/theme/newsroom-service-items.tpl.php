<?php
/**
 * @file
 * Service items template.
 */
?>
<?php if (count($items) > 0) : ?>
  <div class="<?php echo $css_class; ?>-items-container serviceItemContainer">
    <h3><?php echo $title; ?></h3>
    <div class="subscrNewsletterList">
    <?php foreach ($items as $item) : ?>
      <div class="subscrNewsletterItem clearfix">
        <h4><?php echo $item->taxonomy_term_data_name; ?></h4>
        <?php $item->field_field_newsroom_service_image[0]['rendered']['#image_style'] = 'newsroom_style'; ?>
        <?php
          $service_id = isset($item->field_field_newsroom_service_id[0]) ? $service_id = $item->field_field_newsroom_service_id[0]['raw']['value'] : NULL;
          $nr_image = isset($item->field_field_newsroom_service_image[0]);
        ?>
        <?php if($nr_image || $service_id): ?>
            <div class="image">
                <?php if ($nr_image): ?>
                    <?php echo drupal_render($item->field_field_newsroom_service_image[0]['rendered']); ?>
                <?php endif; ?>
                <?php if ($service_id): ?>
                    <?php ; ?>
                    <div class="sample"><?php echo l(t('sample'), 'http://ec.europa.eu/information_society/newsroom/cf/dae/newsletter-specific-archive.cfm?serviceId=' . $service_id, array('external' => TRUE)); ?></div>
                <?php endif; ?>
            </div>
        <?php endif; ?>
        <div class="description"><?php echo $item->taxonomy_term_data_description; ?></div>
        <?php if ($service_id): ?>
        <?php $form = drupal_get_form('nexteuropa_newsroom_newsletter_form', $service_id); ?>
        <div class="form"><?php echo drupal_render($form); ?></div>
        <?php endif; ?>
      </div>
    <?php endforeach; ?>
    </div>
  </div>
<?php endif; ?>
