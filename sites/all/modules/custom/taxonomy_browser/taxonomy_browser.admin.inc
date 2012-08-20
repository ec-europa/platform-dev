<?php
function form_taxonomy_browser_settings($form, &$form_state) {
  $vocabularies = taxonomy_get_vocabularies();
  foreach($vocabularies as $vid => $vocabulary) {
    $items_vocabulary[$vid] = $vocabulary->name;	
  }
	
  $form['taxonomy_browser_vocabulary'] = array(
    '#type' => 'select',
    '#title' => t('vocabulary'),
    '#options' => $items_vocabulary,
    '#default_value' => variable_get('taxonomy_browser_vocabulary'),
  ); 
  
 
  $items_view = array();
  $result_views = db_select('views_view', 'v')
    ->fields('v', array('vid', 'name', 'human_name'))
    ->execute();
  while($record = $result_views->fetchAssoc()) {
    $items_view[$record['name']] = $record['human_name'];
  }
  

  
  $form['taxonomy_browser_description'] = array(
    '#type' => 'item',
    '#title' => t('For each view, choose the display to alter.'),
  );
  foreach($items_view as $view_name => $view) {
    $diplays = _taxonomy_browser_get_display($view_name);
    
    $form[$view_name] = array(
      '#type' => 'fieldset', 
      '#title' => t($view), 
      '#collapsible' => TRUE, 
      '#collapsed' => TRUE,
    );
    
    $form[$view_name]['taxonomy_browser_'.$view_name] = array(
      '#type' => 'checkboxes',
      '#options' => $diplays,
      '#default_value' => variable_get('taxonomy_browser_'.$view_name, array()),
    ); 	  

  }
  
  return system_settings_form($form);
}


function _taxonomy_browser_get_display($key = '') {	
  $query = db_select('views_display', 'vd');
  $query->join('views_view', 'vv', 'vv.vid = vd.vid');
  $query->fields('vd', array('id', 'display_title', 'display_plugin'));
  $query->fields('vv', array('name'));
  $query->condition('vv.name', $key);
  $result = $query->execute();
    
  $items_view_display = array();
  while($record = $result->fetchAssoc()) {
    $items_view_display[$record['id']] = $record['display_title'];
  }
	
  return $items_view_display;
}

function taxonomy_browser_dependent_dropdown_callback($form, $form_state) {
  return $form['taxonomy_browser_view_display'];
}
