<?php
/**
 * @file
 * theme implementation to display feature set.
 *
 * Available variables:
 * - $feature_set_category: list of features, grouped by category
 * - $feature_set_row: raw list of features, ungrouped
 * - $feature_set_input: rendered form input (submit and hidden fields)
 */

?>

<?php foreach ($feature_set_category['category'] as $category => $features) { ?>
  <table>
    <thead>
      <tr>
        <th colspan="2">
          <?php print $category; ?>
        </th>
      </tr>
    </thead>

    <tbody>
    <?php foreach ($features as $key => $item) { ?>
      <tr>
        <td>
          <?php 
            if (!empty($item['#featuresetinfo']['featureset']))
              print '<strong>' . $item['#featuresetinfo']['featureset'] . '</strong>';
            if (!empty($item['#featuresetinfo']['description']))
              print '<br /><small>' . $item['#featuresetinfo']['description'] . '</small>';
          ?>
        </td>
        <td>
          <?php print render($item); ?>
        </td>
      </tr>
    <?php } ?>
    </tbody>
  </table>
<?php } ?>

<?php 
  print $feature_set_input;
?>