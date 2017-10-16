<p>For security matters, this form has been removed.</p>

<p>If you still want to configure the allowed tags, you need to do it via code.</p>

<p>A new hook_alter has been added to NextEuropa in order to allow you to do it:

<code>hook_multisite_drupal_toolbox_filter_options_alter(&$filter_options)</code>
</p>

<p>Please, have a look at the file: <code>multisite_drupal_toolbox.api.php</code> in
the module multisite_drupal_toolbox to have a code example on how it works.</p>
