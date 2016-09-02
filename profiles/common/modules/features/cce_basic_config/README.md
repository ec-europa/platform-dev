The "cce_basic_config" feature supplies basic configuration that allows
the running Next Europa platform.

# :warning:  Attention points while regenerating the feature

When the feature is regenerated, ensure that at the end,the ".info" file contains:
*
```php
# The image_captcha_fonts variable is set in cce_basic_config_strongarm_alter().
# Please do not remove this entry when re-exporting the variables.
features[variable][] = image_captcha_fonts
```
*
```php
# The print_pdf_pdf_tool variable is set in cce_basic_config_strongarm_alter().
# Please do not remove this entry when re-exporting the variables.
features[variable][] = print_pdf_pdf_tool
```

# Installation

The module is activated when the platform is installed

