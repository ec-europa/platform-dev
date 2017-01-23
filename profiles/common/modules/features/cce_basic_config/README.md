The "cce_basic_config" feature supplies basic configuration that allows
running Next Europa platform.

# :warning:  Attention points when recreating the feature

When the feature is regenerated, ensure that at the end, the ".info" file contains:

```php
# The image_captcha_fonts variable is set in cce_basic_config_strongarm_alter().
# Please do not remove this entry when recreating the feature.
features[variable][] = image_captcha_fonts
```

And 

```php
# The print_pdf_pdf_tool variable is set in cce_basic_config_strongarm_alter().
# Please do not remove this entry when recreating the feature.
features[variable][] = print_pdf_pdf_tool
```

# Installation

The module is activated when the platform is installed

