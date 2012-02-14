=========================================
Usage
=========================================

Implement hook_feature_set_api() and return a version number currently this is
unused but you should just use the following. 


  function hook_feature_set_api() {
    return array('version' => '1.0');
  }
  
Once you do that the corresponding module should also define feature sets via
an info file. See the following example.

  feature_sets[taco][title] = 'Tacos are good'
  feature_sets[taco][description] = 'I like tacos'
  feature_sets[taco][icon] = 'feature-set-icons/taco.png'
  feature_sets[taco][enable][] = views
  feature_sets[taco][enable][] = views_ui
  feature_sets[taco][enable][] = wysiwyg
  feature_sets[taco][disable][] = views_ui
  feature_sets[taco][disable][] = wysiwyg
  feature_sets[taco][uninstall][] = views_ui

  feature_sets[burrito][title] = 'Burritos are good'
  feature_sets[burrito][description] = 'Sometimes I prefer burritos'
  feature_sets[burrito][icon] = 'feature-set-icons/burrito.png'
  feature_sets[burrito][enable][] = aggregator
  feature_sets[burrito][disable][] = aggregator

This defines two feature sets 'taco' and 'burrito'

You can also implement feature sets in your install profile. The active install
profile will be checked for available feature sets and included if they are 
available note that the install profile does not need to implement hook_feature_set_api()

Once you have defined feature sets you can enable or disable them at admin/structure/feature-set

=========================================
Known Issues/Requirements
=========================================

The list of disable modules for a feature set must be a subset of the enable modules.

You will get erratic behavior if a module shows up in the disable list of more
than one feature set. In the future feature sets will be flagged as incompatible 
if they have any modules in their disable list that are also in other feature sets.
