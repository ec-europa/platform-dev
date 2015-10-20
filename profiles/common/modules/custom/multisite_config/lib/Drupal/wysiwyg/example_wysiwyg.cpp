// Enable CKEditor Lite buttons for "Full HTML" WYSIWYG profile.
$ckeditor_lite_buttons = array(
  'lite_AcceptAll',
  'lite_RejectAll',
  'lite_AcceptOne',
  'lite_RejectOne',
  'lite_ToggleShow',
  'lite_ToggleTracking',
);
multisite_config_service('wysiwyg')->addButtonsToProfile('full_html', 'lite', $ckeditor_lite_buttons);

// Disable Source button for "Full HTML" WYSIWYG profile.
$ckeditor_lite_buttons = array(
  'Source',
);
multisite_config_service('wysiwyg')->removeButtonsFromProfile('full_html', 'lite', $ckeditor_lite_buttons);
