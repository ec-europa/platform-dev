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

# Default permissions sets
This feature provides the default permissions sets. The list below presents the permissions split by the roles.
The permissions are setup and bound with the user roles during the platform installation process.
Site owners can configure permissions for a give role and adapt them to the current need.

## administrator
    'administer features',
    'administer modules',
    'administer software updates',
    'manage features',
    'manage feature nexteuropa_dgt_connector'

## contributor
    'access media browser',
    'access own broken links report',
    'create article content',
    'create files',
    'delete own article content',
    'delete own image files',
    'edit own article content',
    'edit own image files',
    'moderate content from draft to needs_review',
    'moderate content from needs_review to draft',
    're convert video',
    'revert revisions',
    'show format selection for comment',
    'show format selection for file',
    'show format selection for taxonomy_term',
    'show format selection for user',
    'show format tips',
    'show more format tips link',
    'use workbench_moderation my drafts tab',
    'use workbench_moderation needs review tab',
    'view all unpublished content',
    'view own files',
    'view own private files',
    'use media wysiwyg',
    'use text format full_html'

## editor
    'access broken links report',
    'access media browser',
    'access own broken links report',
    'create article content',
    'create files',
    'delete any article content',
    'delete own article content',
    'delete own image files',
    'delete revisions',
    'edit any article content',
    'edit own article content',
    'edit own image files',
    'moderate content from draft to needs_review',
    'moderate content from needs_review to draft',
    'moderate content from needs_review to published',
    'revert revisions',
    'show format selection for comment',
    'show format selection for file',
    'show format selection for taxonomy_term',
    'show format selection for user',
    'show format tips',
    'show more format tips link',
    'use media wysiwyg',
    'use text format full_html',
    'use workbench_moderation my drafts tab',
    'use workbench_moderation needs review tab',
    'view all unpublished content',
    'view own files',
    'view own private files'

## authenticated user
    'access comments',
    'access PDF version',
    'access print',
    'access send by email',
    'access user profiles',
    'access workbench',
    'post comments',
    'search content',
    'show format selection for node',
    'use advanced search',
    'use text format basic_html',
    'use text format filtered_html',
    'view files',
    'view moderation history',
    'view moderation messages',
    'view own unpublished content',
    'view revisions'

## anonymous users
    'access comments',
    'access PDF version',
    'access print',
    'post comments',
    'search content',
    'use advanced search',
    'use text format basic_html',
    'use text format filtered_html'
