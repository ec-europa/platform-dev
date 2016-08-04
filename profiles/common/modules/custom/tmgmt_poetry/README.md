# Summary

The TMGMT Poetry module allows the creation of translation managers
that make use of the European Commission DGT connector services
(translations served by DGT).

Table of content:
=================
- [Installation](#a-installation)
  - [Webmaster / Site builder](#webmaster--site-builder-)
    - [Requesting access](#requesting-access-to-poetry)
    - [Enabling the feature](#enabling-the-feature-on-your-platform-instance)
    - [Configuration of the connector](#configure-the-dgt-connector)
  - [Maintenance staff (FPFIS staff)](#maintenance-staff-fpfis-staff)
    - [Enabling the feature](#enable-the-feature)

- [Testing](#testing)
  - Testing locally
  - Testing on playground

- [Interesting information to go further] (#test)


- Logs

- Extra technical information

# Installation

## Webmaster / Site builder :
### Requesting access to poetry:
:pray: Before you can start using poetry on playground or production, you should
make a formal request to the Comm Europa Management team.

 [TO BE COMPLETED - WAITING PO FEEDBACK]
  Please send a mail to / fill the document located at http://
  DG COMM will inform DGT and send credentials to FPFIS maintenance team who
  will activate the DGT connector on your site.

### Enabling the feature on your platform instance:
:hand: Poetry is not a feature you can enable using feature sets.

- Once green light has been received from DG COMM, the feature needs to be
activated by your FPFIS maintenance team.  Create a support ticket in [Jira's
MULTISITE project] (https://webgate.ec.europa.eu/CITnet/jira/) explaining the
details and deadlines for your request:
  - The ticket should contain the title 'Poetry activation request'
  - The ticket should include the name of your project.
  - Once maintenance team confirms the feature is ready to be used on
    playground and/or production you can configure your connector.

### Configure the DGT connector:
Once the module is enabled and the settings properly set, the webmaster can
proceed with the module's configuration.

Edit the translator labeled "DGT Connector (auto created)".

In order to do this, navigate to:
``` Configuration->Regional and Language->Translation management Translator ```

or go to :
``` admin/config/regional/tmgmt_translator/manage/tmgmt_poetry_test_translator_en ```

 - Translator settings : [x] Auto accept finished translations
   - Check this if you don't want to review a translation before publishing it.

 - Translator plugin:
   - This cannot be modified and is just for information.

 - DGT Connector plugin settings:
   - You should see 'Main "poetry_service" variable is properly set.' if you have
  correctly followed the steps above. Otherwise get back and check what you
  forgot !
   - Counter: you do not need to fill this. The counter is auto generated.
   - Requester code: must always be *WEB*
   - Organization responsable, Author & requester: check the example provided.
   - Contact usernames: should be the *username* (you connect to the network,
  ecas or the proxy with your username) of the persons in charge of the request.
  This is important as only these persons can view translation details in the
  web app.
   - DGT contacts : persons who will be notified when a translation is received
   or a translation status is sent. Here you need to introduce email addresses.


## Maintenance staff (FPFIS staff)
:construction: Only maintenance team can enable the DGT translator.
### Enable the feature

The module is included in the platform-dev sources. Run the drush command
```drush en tmgmt_poetry```

Update the settings.php of the project.
It must be filled with appropriate
values depending on the environement you are setting up.
- Install on playground environment

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


  - Install on on production

Make sure the poetry access has be requested and credentials have been
received. (See point 1 above).

Settings.php should contain (replace variables between [] with custom values):

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

# Testing
:black_joker: There are 2 ways to test the poetry service.

- Locally, without the need to access the webservice  by using the
 tmgmt_poetry_mock module.

 See [the mock readme] (tmgmt_poetry_mock/README.md) for more information.

- On playground : please follow first the [requesting instance procedure]
(#requesting-access-to-poetry)

# Interesting information regarding the DGT connector
## DGT Web app : Checking the translation was received

Once a translation has been requested to DGT, it is possible for EC staff to
view translation status and references using the [DGT web app]
(http://www.cc.cec/translation/webpoetry/)
The requesters of a translation will also be able to read the actual content
of the translations via this application.

## Logs

- Backup of files received from DGT

Files, including wrapper, received from DGT webservice are saved by reference in
```public://tmgmt_files/dgt_responses/WEB/...```
Files messages are saved in
```public://tmgmt_files/JobID[#id]_source_target.html_poetry```

- Log of activities from Drupal and from DGT in watchdog.
Transations sent and received from the webervices are saved into the watchdog.

:warning: We gradually move the dblog to [kibana]
(https://webgate.ec.europa.eu/fpfis/logging/).

If dblog is disabled from your instance, request access to Kibana by creating a
request in [Jira's MULTISITE project]
(https://webgate.ec.europa.eu/CITnet/jira/)

- DGT reference number

DGT references has a format of type *WEB/2016/72000/0/1* and is a suite of
several variables:

  - The *requester code*  (WEB)

Every Website instance using DGT connector will have as a requester code *WEB*.

  - The *year* a new counter was received (ex: 2016)

  - The *counter* used when request was sent (ex: 72000)

  - The *partie* (in our case this is a unique page id) (ex: 1)

  - The *version* (version is incremented each time a 'partie' version is sent)
(ex:0)
