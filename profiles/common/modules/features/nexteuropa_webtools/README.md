NextEuropa Webtools provides a bean for integrating with the Webtools service.

Feature user documentation: https://webgate.ec.europa.eu/fpfis/wikis/display/MULTISITE/Webtools+feature

Webtools service documentation: https://webgate.ec.europa.eu/fpfis/wikis/display/webtools/Webtools+documentation+-+Homepage

Table of content:
=================
- [Installation](#installation)
  - [How to: activate the feature](#how-to-activate-the-feature)

- [Configuration](#configuration)
  - [Configure the Smartloader](#configure-the-smartloader)
  - [Set up permissions](#set-up-permissions)

- [Usage](#usage)
  - [How to: create a block](#how-to-create-a-block)
  - [How to: use the webtools block(s)](#how-to-use-the-webtools-blocks)

- [Testing](#testing)

- [Useful information](#useful-information)
  - [Webtools documentation](#webtools-documentation)

[Go to top](#table-of-content)

# Installation

## How to: activate the feature

To activate the feature, an administrator user needs to:
- Go on the feature set page "admin/structure/feature-set"
- Enable the "Webtools" feature

[Go to top](#table-of-content)

# Configuration

## Configure the Smartloader

The only thing that needs to be configured is the url where the Smartloader is defined.
This can be done as an administrative user on "/admin/config/services/webtools".
Most sites can use the europa.eu smartloader (//europa.eu/webtools/load.js),
but this can be configured to use an other one if needed.

Or set the variable "nexteuropa_webtools_smartloader_prurl"

[Go to top](#table-of-content)

## Set up permissions

To allow users to change the "custom" parameter in the JSON Object field,
the permission "Upload webtools custom js" needs to be granted.
- As an administrator user, go to Permissions form "/admin/people/permissions".
- Filter the form with the keyword "Webtools" or select "NextEuropa webtools" in the module list on the left-hand side.
- Grant the permission "Upload webtools custom js" to the required roles.
- Save the form by clicking "Save permission" below.

By default, only users with the "Administrator" role are allowed to change
the "custom" parameter and to view the fields File and External link in the
Webtools block.

[Go to top](#table-of-content)

# Usage

## How to: create a block

As an authorized user, go on the Webtools block form "block/add/webtools"

Steps:
- Indicate a label and optionally a title
- Enter the JSON parameters
    - Example: {"service" : "map"}
    - Parameters should be defined using the [Webtools documentation](#webtools-documentation).
    - warning: It is no longer allowed to use the "custom" parameter in the JSON
    Object field. This parameter is now controlled by the fields in the Custom
    js group.Any changes to this parameter will be ignored and removed when
    saving the block.
- Provide settings for the Custom js group:
    - Included indicates if the "custom" parameter should be added to the JSON Object.
    This can be disabled in case the "custom" parameter needs to be replaced by
    static data when the fields File and External link are not visible for the
    user (See permissions below).
    - File is a file upload field, allowing users to upload the JavaScript file
    to this block.
    - External link allows user to use an external JavaScript file.
- Click on 'Save'
- You are automatically redirected to the result

[Go to top](#table-of-content)

## How to: use the webtools block(s)

The created blocks are listed at "admin/content/blocks".
These blocks can be uses as any other block in Drupal.
You can add them to the page with the block system "admin/structure/blocks" -
or via context "admin/structure/context" or via any other system to place blocks
in Drupal.

Note that the blocks created are named Beans, as the Webtools feature is based
on beans module.

[Go to top](#table-of-content)

## How to: insert a existing webtools block into a content

As an authorized user, edit the content and go to the CKEditor:

Steps:
- Click "Insert internal content"
- Go in the tab "Insert internal blocks"
- Select a block and click the link "Default" in the column "Insert as"

[Go to top](#table-of-content)

# Testing

The Behat test exist in the file "/tests/features/webtools.feature".

[Go to top](#table-of-content)

# Useful information

## Webtools documentation

These links are also mentioned in the sections above.
- [Documentation](https://webgate.ec.europa.eu/fpfis/wikis/display/webtools/Webtools+documentation+-+Homepage)
- [Widgets](https://webgate.ec.europa.eu/fpfis/wikis/pages/viewpage.action?spaceKey=MULTISITE&title=Webtools+feature#)
    - [Charts](https://webgate.ec.europa.eu/fpfis/wikis/x/F7AjBg)
    - [Maps](https://webgate.ec.europa.eu/fpfis/wikis/x/BIlDBg)
    - [Social Bookmarking and Networking](https://webgate.ec.europa.eu/fpfis/wikis/x/_I5DBg) (Share buttons)
    - [Social Media Kit](https://webgate.ec.europa.eu/fpfis/wikis/x/gaUjBg) (Twitter feeds)

[Go to top](#table-of-content)
