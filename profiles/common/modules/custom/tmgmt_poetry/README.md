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
  - [Testing locally](#testing)
  - [Testing on Playground](#testing)

- [Usage](#usage)
  - [How to request a translation](#usage)

- [Interesting information to go further]
(#interesting-information-regarding-the-dgt-connector)
  - [The DGT web app] (#dgt-web-app--checking-the-translation-was-received)
  - [Logs](#logs)
    - [Files backup] (#files-backup)
    - [Watchdog logs] (#log-of-activities-from-drupal-and-from-dgt-in-watchdog)
  - [DGT reference number](#dgt-reference-number)

[Go to top](#table-of-content)

# Installation
## Webmaster / Site builder:
### Requesting access to poetry:
:pray: Before you can start using poetry on Playground or Production, you should
make a formal request to the Comm Europa Management team.

```
 [TO BE COMPLETED - WAITING PO FEEDBACK]
  Please send a mail to / fill the document located at http://
  DG COMM will inform DGT and send credentials to FPFIS maintenance team who
  will activate the DGT connector on your site.
  DGCOMM will provide login details to Maintenance team and will give you the
   details of a contact person at DGT.
```

[Go to top](#table-of-content)

### Enabling the feature on your platform instance:
:hand: Poetry feature cannot be enable using feature sets.

- Once green light has been received from DG COMM, the feature needs to be
activated by your FPFIS maintenance team.  Create a support ticket in
[Jira's MULTISITE project]
(https://webgate.ec.europa.eu/CITnet/jira/secure/RapidBoard.jspa) (use the blue
button labelled *Create*) explaining the details and deadlines for your request:
  - The ticket should contain the title 'Poetry activation request',
  - The ticket should include the name of your project,
  - Once maintenance team confirms the feature is ready to be used on
    Playground and/or Production you can configure your connector.
  - It is proved helpful to have the deadline crafted in the jira ticket title.

[Go to top](#table-of-content)

### Configure the DGT connector:
Once the module is enabled and the settings properly set, the webmaster can
proceed with the module's configuration.

Edit the translator labelled "DGT Connector (auto created)".

In order to do this, navigate to:
``` Configuration->Regional and Language->Translation management Translator ```.

or go to:
``` admin/config/regional/tmgmt_translator/manage/poetry_en ```.

 - Translator settings: [x] Auto accept finished translations
   - Check this if you don't want to review a translation before publishing it.

 - Translator plugin:
   - This is shown for information, please do not change it.

 - DGT Connector plugin settings:
   - You should see 'Main "poetry_service" variable is properly set.' if you
   have correctly followed the steps above. Otherwise, get back and check what
   you forgot!
   - Counter: you do not need to fill this. The counter is auto generated.
   - Requester code: must always be *WEB* [See DGT reference explanation]
   (#dgt-reference-number).
   - Organization responsible, Author & requester: check the example provided.
   - Contact usernames: should be the *username* (you connect to the network,
  ecas or the proxy with your username) of the persons in charge of the request.
  This is important as only these persons can view translation details in the
  web app.
   - DGT contacts: The email address of your contact person at DGT. They will
   receive feedback on the translations you want to comment. That information
   should have been provided to you by DGCOMM.

[Go to top](#table-of-content)

## Maintenance staff (FPFIS staff)
:construction: Only maintenance team can enable the DGT translator.
### Enable the feature

The module is included in the platform-dev sources. Run the drush command
```drush en tmgmt_poetry```.

Update the settings.php of the project.
It must be filled with appropriate
values depending on the environment you are setting up.

  - Install on Playground environment:

In order to test against acceptance webservice, *settings.php* should contain
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

  - Install on Production environment:

Make sure the [poetry access was requested by the webmaster]
(#requesting-access-to-poetry) and you have received the credentials.

*Settings.php* should contain (replace variables between [] with custom values):

```php
    $conf['poetry_service'] = array(
      'address' => 'http://intragate.ec.europa.eu/DGT/poetry_services/components/poetry.cfc?wsdl',
      'method' => 'requestService',
      'callback_user' => [CALLBACK_USERNAME],
      'callback_password' => [CALLBACK_PASSWORD],
      'poetry_user' => [POETRY_USERNAME],
      'poetry_password' => [POETRY_PASSWORD],
    );
```

> The values of [CALLBACK_USERNAME] should match NE-projectname where
projectname is the project's code.
> *Example: NE-ERASMUSPLUS*

> [CALLBACK_PASSWORD] is the same as the callback_username.
> These fields are limited to 15 characters.

>[POETRY_USERNAME] and [POETRY_PASSWORD] should have been received from
DGCOMM (see 'Installations step 1').

[Go to top](#table-of-content)

# Testing
:black_joker: There are 2 ways to test the poetry service.

- Locally, without the need to access the webservice  by using the
 tmgmt_poetry_mock module.

 See [the mock readme] (tmgmt_poetry_mock/README.md) for more information.

- On Playground:

 1) Follow the [requesting instance procedure](#requesting-access-to-poetry).

 2) Await confirmation that the [Playground was configured by the maintenance
 team](#enabling-the-feature-on-your-platform-instance).

[Go to top](#table-of-content)

# Usage
## How to request a translation
:warning: TO BE UPDATED AFTER 7719.
- When you are browsing a node that is translatable, an additional tab
'Translate' appears,
- Click that tab and select one language you wish to request a translation for,
- Submit the 'Request translation' button,
- Select the 'DGT connector (auto created)' plugin from the select list,
- Select all the languages you want to be translated,
- Default values:

> The values that show in 'Contact Usernames' and in 'Organization' are the
default values you entered when [you configured your translator]
(#configure-the-dgt-connector). Those values can be overridden on a page per
page basis. To do this, just click 'Contact Usernames' or 'Organization' and
changes the values.

- You can select an 'Expected delivery time': Click the field and select a
date from the calendar that will pop up. This is an indicative date, DGT might
want to change that date,

- The field remark is not mandatory, you can add there any comment you want to
share with DGT.

[Go to top](#table-of-content)

# Interesting information regarding the DGT connector
## DGT Web app: Checking the translation was received

Once a translation has been requested to DGT, the status will be updated on the
Drupal site. In additions it is also possible for EC staff to view translation
status and references using the [DGT web app]
(http://www.cc.cec/translation/webpoetry/).
The requesters of a translation will also be able to read the actual content
of the translations via this application.

[Go to top](#table-of-content)

## Logs

### Files backup

The module handles the backing up of files received from DGT.
Files, including wrapper, received from DGT webservice are saved by reference
in:

> public://tmgmt_files/dgt_responses/WEB/...

Files messages are saved in:

> public://tmgmt_files/JobID[#id]_source_target.html_poetry

### Log of activities from Drupal and from DGT in watchdog

Translations sent and received from the webservices are saved into the watchdog.

:warning: We gradually move the _dblog_ to [kibana]
(https://webgate.ec.europa.eu/fpfis/logging/) and if dblog is disabled from your
 instance, request access to Kibana by creating a request in
 [Jira's MULTISITE project]
(https://webgate.ec.europa.eu/CITnet/jira/secure/RapidBoard.jspa).

[Go to top](#table-of-content)

## DGT reference number

DGT reference has a format of type *WEB/2016/72000/0/1* and is a suite of
several variables:

  - The *requester code*  ``` (ex: WEB) ```,
> Every Website instance using DGT connector will have as a requester code
*WEB*.

  - The *year* a new counter was received  ``` (ex: 2016) ```,

  - The *counter* used when request was sent  ``` (ex: 72000) ```,

  - The *version* (version is incremented each time a 'partie' version is sent)
  ```(ex:0) ```,

  - The *partie* (in our case this is a unique page id) ``` (ex: 1) ```.

[Go to top](#table-of-content)
