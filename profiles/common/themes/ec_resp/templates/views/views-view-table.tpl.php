<?php
/**
 * @file
 * Template to display a view as a table.
 *
 * Available variables:
 * - $attributes: array of HTML attributes populated by modules, intended to
 *   be added to the main container tag of this template.
 * - $title : The title of this group of rows. May be empty.
 * - $header: An array of header labels keyed by field id.
 * - $header_classes: An array of header classes keyed by field id.
 * - $fields: An array of CSS IDs to use for each field id.
 * - $classes: A class or classes to apply to the table, based on settings.
 * - $row_classes: An array of classes to apply to each row, indexed by row
 *   number. This matches the index in $rows.
 * - $rows: An array of row items. Each row is an array of content.
 *   $rows are keyed by row number, fields within rows are keyed by field ID.
 * - $field_classes: An array of classes to apply to each field, indexed by
 *   field id, then row number. This matches the index in $rows.
 *
 * @ingroup views_templates
 */
?>
<div class="table-responsive">
  <table class="table table-striped table-hover <?php if ($classes) : print $classes; endif; ?>" <?php print $attributes; ?>>
    <?php if (!empty($title)) : ?>
      <caption><?php print $title; ?></caption>
    <?php endif; ?>
    <thead>
      <tr>
        <?php foreach ($header as $field => $label): ?>
          <th <?php if ($header_classes[$field]) : print 'class="' . $header_classes[$field] . '" '; endif; ?>>
            <?php print $label; ?>
          </th>
        <?php endforeach; ?>
      </tr>
    </thead>
    <tbody>
      <?php foreach ($rows as $count => $row): ?>
        <tr class="<?php print implode(' ', $row_classes[$count]); ?>">
          <?php foreach ($row as $field => $content): ?>
            <td <?php if ($field_classes[$field][$count]) : print 'class="' . $field_classes[$field][$count] . '" '; endif; ?><?php print drupal_attributes($field_attributes[$field][$count]); ?>>
              <?php print $content; ?>
            </td>
          <?php endforeach; ?>
        </tr>
      <?php endforeach; ?>
    </tbody>
  </table>
</div>
