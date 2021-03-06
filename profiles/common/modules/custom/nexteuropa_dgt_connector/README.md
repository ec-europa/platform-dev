The NextEuropa DGT connector feature allows the creation of translation managers
that make use of the European Commission DGT connector services
(translations served by DGT).

## Table of Contents
- [Installation](#installation)
  - [Webmaster / Site builder](#webmaster--site-builder)
    - [Site requirements](#site-requirements)
    - [Requesting access](#requesting-access-to-the-dgt-connector)
    - [Configuration of the feature](#activation-of-the-feature)
  - [Server configuration](#server-configuration-devops)
  - [Connector configuration](#dgt-connector-configuration-cem)

- [Testing](#testing)
  - [Testing locally](#testing)
  - [Testing on Playground](#testing-in-house-for-webmasters)

- [Usage](#usage)
  - [How to request a translation](#how-to-request-a-translation)
  - [How to update a translation request](#how-to-update-a-translation-request)

- [Interesting information to go further](#interesting-information-regarding-the-dgt-connector)
  - [The DGT web app](#dgt-web-app--checking-the-translation-was-received)
  - [Logs](#logs)
    - [Files backup](#files-backup)
    - [Watchdog logs](#log-of-activities-from-drupal-and-from-dgt-in-watchdog)
  - [DGT reference number](#dgt-reference-number)
  - [Error debugging](#error-debugging)

[Go to top](#table-of-contents)

# Installation
## Webmaster / Site builder
### Site requirements
To be able to make use of the DGT connector services, the desired target 
languages need to be enabled on the site. Content types that will be translated 
in this way must use multilingual support with **field translation** and need 
to have **moderation** of revisions enabled.

### Requesting access to the DGT-Connector
Before you can start using the DGT-Connector on Playground or Production,
a representative of your DG at the 
[Europa Forum](http://www.cc.cec/home/europa-info/basics/management/committees/forum_europa/members/index_en.htm) 
must make a formal request to the **COMM EUROPA MANAGEMENT (CEM)**.

```
 From: Webmaster
 To: Comm Europa Management
 Subject: DGT-Connector activation
 
 Dear colleagues,
 
 Could you please grant access to the DGT-Connector for the following websites?
 - (URL of your website in playground environment)
 - (URL of your website in production environment)
 
 We want DGT translations to be automatically accepted by our website: YES/NO		
 	Contact person in charge of the translation requests: .............		
 	Contact person at DGT: .............
  Contact "responsible" person (EC official accountable for the requests) ............
 	 
 Thank you,
```

[Go to top](#table-of-contents)

###  Activation of the feature
You cannot enable DGT-Connector feature using feature sets.

- Once approved by **CEM**, CEM will enable the feature on your playground
environment.

- Part of the shared configuration has already been set globally on production
and playground environments by the **DevOps** in the settings.common.php file.

[Go to top](#table-of-contents)

## Server configuration (DevOps)
**DIGIT DevOps** are in charge of the endpoint configuration.

The configuration of the endpoint is done once for all in the
settings.common.php for all the projects.
It is filled with appropriate values depending on the environment.

### On Playground environment:

In order to test against acceptance webservice, the file **settings.common.php**
must contain:

```php
   $conf['poetry_service'] = array(
     'address' => 'http://intragate.test.ec.europa.eu/DGT/poetry_services/components/poetry.cfc?wsdl',
     'method' => 'requestService',
   );
```
### On Production environment:

The file **settings.common.php** must contain:

```php
    $conf['poetry_service'] = array(
      'address' => 'http://intragate.ec.europa.eu/DGT/poetry_services/components/poetry.cfc?wsdl',
      'method' => 'requestService',
    );
```

[Go to top](#table-of-contents)

## DGT-Connector configuration (CEM):
CEM enables the feature 'Nexteuropa DGT connector' through their feature set
access Then it proceeds with the module's configuration.

In order to do this, CEM navigates to:

> Configuration > Regional and Language > Translation management Translator

which points here:

> admin/config/regional/tmgmt_translator/manage/poetry

and edits 'DGT Connector'.

Only UUID 1 can delete the translator, should you need to perform this
operation on playground or production, please send a request to CEM.

### TRANSLATOR SETTINGS
- *Auto accept finished translations*: Check this if the site owner wants to
review a translation before publishing it.

### Translator plugin:
This is shown for information, please do not change it.

### DGT CONNECTOR PLUGIN SETTINGS:
You should see 'Main "poetry_service" variable is properly set.' if all
the steps above were correctly followed. If not, please check the saved settings.

### GENERAL SETTINGS [See DGT reference explanation]
- *Counter*: **NEXT_EUROPA_COUNTER**
- *Requester code*: **WEB** ([more information](#dgt-reference-number))
- *Callback User / Callback Password*: drupal credential - in lowercase, limited
to 15 characters and different to poetry credential. It must identify uniquely
the platform where the translations have to be delivered to. Example:
**projectnameproduction/projectnameproduction**
- *Poetry Username / Poetry Password*: must have been created beforehand in the
Poetry DB. Any valid username/password will work. However, this is supposed to
identify the calling application.
Example **NE-projectname/NE-projectname**.
- *Website identifier*: This helps DGT identifying which site requested the
translation. Example: **PROJECTNAME**

### ORGANIZATION
Organization responsible, Author and requester: consult the values examples
shown below each form field as an example.

### CONTACT USERNAMES
Should be the user names of the persons in charge of the request. This is the
same user name used to connect to the network, ecas or the proxy.
This is important as only these persons can view translation details in the
web app.

### DGT CONTACTS
The email address of your contact person at DGT. They receive
feedback on the translations that are commented. 

### REMOTE LANGUAGES MAPPINGS
Map language codes that are not supported by the
DGT-Connector to the corresponding language code supported.

> Typical example is when the site is configured for using 'Portuguese from
Portugal' (code pt-pt) that should be mapped to 'pt'.

[Go to top](#table-of-contents)

# Testing
## Testing locally (for developers)
If you are working in collaboration with a contractor and he needs to test
the DGT-Connector UI and the workflow locally, this can be done without the
need to access the webservice by using the tmgmt_poetry_mock module.

 Contractors : see [the mock readme](tmgmt_poetry/tmgmt_poetry_mock/README.md) for more
 information on testing with the mock.

## Testing in-house (for webmasters)
When the DGT-Connector is properly enabled and configured in your 
playground environment, CEM will ask you to perform a number of tests monitored
by DGT.

Go to next section ([Usage](#usage)) on how to complete your test.

If your test are successful, please inform CEM team.
Once tests are successful on playground CEM will enable the DGT-Connector in
your production environment.

[Go to top](#table-of-contents)

# Usage
## How to request a translation
- When you are browsing a node that is translatable, an additional tab
**Translate** appears,

- Click that tab and select languages you wish to request a translation for,

- Submit the **Request translation** button,

- By default the **DGT connector (auto created)** translator is selected but you
can click **Change translator** to change it if needed,

- You can change the languages you want to be translated,

- Default values: The values that show in **Contact Usernames** and in
**Organization** are the default values you entered when
[CEM configured your translator](#configure-the-dgt-connector).Those values can
be overridden on a page per page basis. To do this, just click
**Contact Usernames** or **Organization** and changes the values.

- You can select an **Expected delivery time**: Click the field and select a
date from the calendar that pops up. This is an indicative date, DGT might
want to change that date,

- The field **remark** is not mandatory, you can add there any comment you want
to share with DGT.

[Go to top](#table-of-contents)

## How to update a translation request
- After a translation request has been accepted by DGT,
- Click the **Translation** tab and select the languages you wish to request a
translation for,
- Submit the **Update Request translation** button,

> Note: This action will cancel all jobs in progress and jobs that need a
review.

- By default the **DGT connector (auto created)** translator will be selected,
- You can modify the selection of languages you want to be translated,
- You can select an **Expected delivery time**: Click the field and select a
date from the calendar that will pop up. This is an indicative date for DGT.

[Go to top](#table-of-contents)

# Interesting information regarding the DGT connector
## TMGMT DGT CONNECTOR module
The readme file of [NextEuropa DGT Connector](https://github.com/ec-europa/platform-dev/tree/release-2.5/profiles/common/modules/features/nexteuropa_dgt_connector/tmgmt_dgt_connector/README.md)
 module provides useful information on scope and usage of the functionalities.
## DGT Web app: Checking the translation was received
Once a translation has been requested to DGT, the status is updated on the
Drupal site. In addition it is also possible for EC staff to view translation
status and references using the
[Test DGT web app](http://www.test.cc.cec/translation/webpoetry/) or the
[DGT web app](http://www.cc.cec/translation/webpoetry/).

The requester of a translation is also able to read the actual content
of the translations via this application.

[Go to top](#table-of-contents)

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

:warning: We gradually move the _dblog_ to
[kibana](https://webgate.ec.europa.eu/fpfis/logging/) and if dblog is disabled
from your instance, please contact CEM.

[Go to top](#table-of-contents)

## DGT reference number
DGT reference has a format of type *WEB/2018/72000/0/1* and is a suite of
several variables:

  - The **requester code** *(ex: WEB)*,
> Every Website instance using DGT-Connector will have as a requester code
*WEB*.

  - The **year** a new counter was received *(ex: 2018)*

  - The **counter** used when request was sent *(ex: 72000)*

  - The **version** is incremented each time a *partie* version is sent *(ex:0)*

  - The **partie** in our case this is a unique page id *(ex: 1)*

[Go to top](#table-of-contents)

## Error debugging
If your connection to DGT service is broken, please check the following
debugging steps:

#### If you are not an administrator
Contact your site administrator.

#### You are an administrator
Go to URL admin/reports/status and check the status of the 'DGT connector
webservice'
  - **Status is red**

     - If **"The DGT webservice endpoint is not set. Please ask your support
       team to check the configuration."** is shown, the URL of the DGT
       webservice endpoint is not set.  Please contact your support.
       The URL should be set in the settings.common.php file on the server.
        
     - If **"The local connector credentials are not set.  Please contact CEM
       support."** is shown, the credentials of the Drupal endpoint have not
       been set. This information should be filled in by a member of CEM team at
       the time of installation.
       
     - If **"The DGT remote credentials are not set.  Please contact CEM
       support."** is shown, the credentials of the DGT endpoint have not been
       set. This information should be filled in by a member of CEM team at the
       time of install.

  - **Status is green**

      All the required fields have been filled in correctly. However, if
      you still experience issues, contact CEM and ask them to check the values
      that have been configured.

[Go to top](#table-of-contents)
