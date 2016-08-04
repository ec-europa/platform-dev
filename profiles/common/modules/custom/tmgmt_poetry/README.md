# Summary

The TMGMT Poetry module allows the creation of translation managers
that make use of the European Commission DGT connector services
(translations served by DGT).

Table of content:
=================
- Installation
  - Requesting access
  - Enabling the feature as a webmaster
  - Enabling the feature as a FPFIS staff
  - Configuration of the connector

- Testing
  - Testing locally
  - Testing on playground

- Use on production
  - Configuration
  - DGT Web app

- Logs

# A. Installation

## 1. Requesting access to poetry:
:pray: Before you can start using poetry, you should make a formal request to the Comm
Europa Management team.

Please send a mail to / fill the document located at http://
DG COMM will inform DGT and send credentials to FPFIS maintenance team who will
activate the DGT connector on your site.

## 2. Enabling the feature on your platform instance
:hand: Poetry is not a feature you can enable using feature sets.
Once green light has been received from DG COMM, the feature needs to be
activated by your FPFIS maintenance team.  Create a support ticket in [Jira's
MULTISITE project] (https://webgate.ec.europa.eu/CITnet/jira/) explaining the
details and deadlines for your request.

## 3. Enabling the feature as a FPFIS maintenance staff
:construction_worker: Only maintenance team can enable the DGT translator.
* Make sure the poetry access has be requested and credentials have been
received. (See point 1 above).
* The module is included in the platform-dev sources. Run the drush command
```drush en tmgmt_poetry```
* Update the settings.php of the project. It must be filled with appropriate
values depending on the environement you are using it in.

For more details on variables setting see below section 3 *Implementation on
production*.

## 4. Configure the DGT connector
Once the module is enabled and the settings properly set, the webmaster can
proceed with the module's configuration.

In order to do this, navigate to:
``` Configuration->Regional and Language->Translation management Translator ```

or go to :
``` admin/config/regional/tmgmt_translator ```

Edit the translator labeled "DGT Connector (auto created)".


# Testing

## 1. Testing locally

You can test the feature locally, throught the UI or in an automated way, by
using the tmgmt_poetry_mock module.
See [the mock readme] (tmgmt_poetry_mock/README.md) for more information.
You do not need to set variables in settings.php

## 2. Testing on playground environment

In order to test against acceptance webservice, settings.php should contain
(exactly as is):

```php
    $conf['poetry_service'] = array(
      'address' => 'http://intragate.test.ec.europa.eu/DGT/poetry_services/components/poetry.cfc?wsdl',
      'method' => 'requestService',
      'callback_user' => 'Callback',
      'callback_password' => 'CallbackPWD',
      'poetry_user' => 'Poetry',
      'poetry_password' => 'PoetryPWD',
    );
```

# Use on production

In order to send translations to production webservice, settings.php should
contain (replace variables between [] with custom value):

```php
    $conf['poetry_service'] = array(
      'address' => ''http://intragate.ec.europa.eu/DGT/poetry_services/components/poetry.cfc?wsdl',
      'method' => 'requestService',
      'callback_user' => [CALLBACK_USERNAME],
      'callback_password' => [CALLBACK_PASSWORD],
      'poetry_user' => [POETRY_USERNAME],
      'poetry_password' => [POETRY_PASSWORD],
    );
```

> The values of [CALLBACK_USERNAME] should match NE-projectname where
projectname is the project's code.

> [CALLBACK_PASSWORD] is the same as the callback_username.
> These fields are limited to 15 characters.


>[POETRY_USERNAME] and [POETRY_PASSWORD] should have been received from
DGCOMM (see 'Installations step 1')

## Configuration

Once the variables are set in settings.php, [you can configure DGT connector]
(admin/config/regional/tmgmt_translator/manage/tmgmt_poetry_test_translator_en).
 ### Translator settings
 - [x] Auto accept finished translations
   - Check this if you don't want to review a translation before publishing it.
 ### Translator plugin
 - This cannot be modified and is just for information.

 #### DGT Connector plugin settings
  - You should see 'Main "poetry_service" variable is properly set.' if you have
  correctly followed the steps above. Otherwise get back and check what you
  forgot !
  - Counter:
  - Requester code:

## DGT Web app : Checking the translation was received

Once a translation has been requested to DGT, it is possible for EC staff to
view translation status and references using the [DGT web app]
(http://www.cc.cec/translation/webpoetry/)
The requesters of a translation will also be able to read the actual content
of the translations via this application.

Logs
====

Files, including wrapper, received from DGT webservice are saved by reference in
public://tmgmt_files/dgt_responses/WEB/...
Files messages are saved in
public://tmgmt_files/JobID[#id]_source_target.html_poetry

Technical details you may want to know
======================================
Every Website instance using DGT connector will have as a requester code 'WEB'.
DGT references are a suite of several variables:

The 'requester code'  (WEB)

The 'year' a new counter was received (ex: 2016)

The 'counter' used when request was sent (ex: 72000)

The 'partie' (in our case this is a unique page id) (ex: 1)

The 'version' (version is incremented each time a 'partie' version is sent)
(ex:0)
