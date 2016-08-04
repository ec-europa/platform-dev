# Summary

The TMGMT Poetry module allows the creation of translation managers
that make use of the European Commission DGT connector services
(translations served by DGT).

Table of content:
=================
* A. Installation
 ** Requesting access
 ** Enabling the feature as a webmaster
 ** Enabling the feature as a FPFIS staff
 ** Configuration of the connector

* B. Testing

* C. DGT Web app

* D. Logs

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
MULTISITE project] (https://webgate.ec.europa.eu/CITnet/jira/)explaining the
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
---------

## 1. Testing locally
---------------------
You can test the feature locally, throught the UI or in an automated way, by
using the tmgmt_poetry_mock module.
See [the mock readme] (/tmgmt_poetry_mock/README.md) for more information.

## 2. Testing on playground environment
---------------------------------------
In order to test against acceptance webservice, settings.php should contain:

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
--------------------
## Configuration
In order to send translations to production webservice, settings.php should
contain:

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

