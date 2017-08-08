The Nexteuropa DGT connector feature allows the creation of translation managers
that make use of the European Commission DGT connector services
(translations served by DGT).

Table of content:
=================
- [Installation](#a-installation)
  - [Webmaster / Site builder](#webmaster--site-builder)
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

- [Interesting information to go further]
(#interesting-information-regarding-the-dgt-connector)
  - [The DGT web app] (#dgt-web-app--checking-the-translation-was-received)
  - [Logs](#logs)
    - [Files backup] (#files-backup)
    - [Watchdog logs] (#log-of-activities-from-drupal-and-from-dgt-in-watchdog)
  - [DGT reference number](#dgt-reference-number)
  - [Error debugging](#error-debugging)

[Go to top](#table-of-content)

# Installation
## Webmaster / Site builder:
### Requesting access to the DGT-Connector:
:pray: Before you can start using the DGT-Connector on Playground or Production,
a representative of your DG at the 
[Europa Forum](http://www.cc.cec/home/europa-info/basics/management/committees/forum_europa/members/index_en.htm) 
must make a formal request to the COMM EUROPA MANAGEMENT (CEM).

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
 	 
 Thank you,
```

[Go to top](#table-of-content)

###  Activation of the feature:
:hand: You cannot enable DGT-Connector feature using feature sets.

- Once approved by CEM, CEM will enable the feature on your playground 
environment.
- Part of the shared configuration has already been set globally on production 
and playground environments by the DevOps in the settings.common.php file.

[Go to top](#table-of-content)

## Server configuration (DevOps)
:construction: DIGIT DevOps are in charge of the endpoint configuration.

The configuration of the endpoint is done once for all in the 
settings.common.php for all the projects.
It is filled with appropriate values depending on the environment. 

  - On Playground environment:

In order to test against acceptance webservice, *settings.common.php* must 
contain:

```php
   $conf['poetry_service'] = array(
     'address' => 'http://intragate.test.ec.europa.eu/DGT/poetry_services/components/poetry.cfc?wsdl',
     'method' => 'requestService',
   );
```
  - On Production environment:

*settings.common.php* must contain:

```php
    $conf['poetry_service'] = array(
      'address' => 'http://intragate.ec.europa.eu/DGT/poetry_services/components/poetry.cfc?wsdl',
      'method' => 'requestService',
    );
```

[Go to top](#table-of-content)

## DGT-Connector configuration (CEM):
CEM enable the feature "Nexteuropa DGT connector" through their feature set 
access Then it proceeds with with the module's configuration.

In order to do this, CEM navigates to:

    Configuration > Regional and Language > Translation management Translator

and edits "DGT Connector", or go to:

    admin/config/regional/tmgmt_translator/manage/poetry 

 - Translator settings: [x] Auto accept finished translations
   - Check this if the site owner wants to review a translation before 
   publishing it.

 - Translator plugin:
   - This is shown for information, please do not change it.

 - DGT Connector plugin settings:
   - You should see 'Main "poetry_service" variable is properly set.' if all
   the steps above were correctly followed. Otherwise, get back and check what
   you forgot!
   - Counter: The counter always is *NEXT_EUROPA_COUNTER* 
     [See DGT reference explanation]  
   - Website identifier: This helps DGT identifying which site requested the 
     translation.
   - Requester code: always is *WEB* [See DGT reference explanation]
   (#dgt-reference-number).
   - Callback User: it must match NE-projectname where projectname is the 
   project's code.
   *Example: NE-ERASMUSPLUS*
   - Callback Password: is the same as the callback_username.
   These fields are limited to 15 characters.
   - Poetry Username and Poetry Password: Those credential are provided by DGT.
   On playground, you should use 'Poetry' & 'PoetryPWD'.
   - Organization responsible, Author & requester: consult the values examples
   shown below each form field as an example.
   - Contact usernames: should be the *user names* (you connect to the network,
  ecas or the proxy with your user name) of the persons in charge of the request.
  This is important as only these persons can view translation details in the
  web app.
   - DGT contacts: The email address of your contact person at DGT. They receive
   feedback on the translations that are commented. 
   - Remote languages mappings: Map language codes that are not supported by the
   DGT-Connector to the corresponding language code supported.
   Typical example is when the site is configured for using 'Portuguese from 
   Portugal' (code pt-pt) that should be mapped to 'pt'.

[Go to top](#table-of-content)


# Testing

## Testing locally (for developers)

If you are working in collaboration with a contractor and he needs to test 
locally the DGT-Connector UI and the workflow, this can be done without the 
need to access the webservice by using the tmgmt_poetry_mock module.

 Contractors : see [the mock readme] (tmgmt_poetry_mock/README.md) for more 
 information on testing with the mock.

## Testing in-house (for webmasters)
When the DGT-Connector is properly enabled and configured in your 
playground environment, CEM will ask you to perform few tests monitored by DGT.

Go to next section ([Usage](#usage)) on how to complete your test.

When your test are successful, please inform CEM team.
Once tests are successful on playground CEM will enable the DGT-Connector in 
your production environment.

[Go to top](#table-of-content)

# Usage
## How to request a translation
- When you are browsing a node that is translatable, an additional tab
'Translate' appears,
- Click that tab and select languages you wish to request a translation for,
- Submit the 'Request translation' button,
- By default the 'DGT connector (auto created)' translator is selected but you 
can click 'Change translator' to change it if needed,
- You can change the languages you want to be translated,
- Default values:

> The values that show in 'Contact Usernames' and in 'Organization' are the
default values you entered when [CEM configured your translator]
(#configure-the-dgt-connector). Those values can be overridden on a page per
page basis. To do this, just click 'Contact Usernames' or 'Organization' and
changes the values.

- You can select an 'Expected delivery time': Click the field and select a
date from the calendar that pops up. This is an indicative date, DGT might
want to change that date,

- The field remark is not mandatory, you can add there any comment you want to
share with DGT.

[Go to top](#table-of-content)

## How to update a translation request
- After a translation request has been accepted by DGT,
- Click the "Translation" tab and select the languages you wish to request a translation for,
- Submit the 'Update Request translation' button,

> Note: This action will cancel all jobs in progress and jobs that need a review.

- By default the 'DGT connector (auto created)' translator will be selected,
- You can modify the selection of languages you want to be translated,
- You can select an 'Expected delivery time': Click the field and select a date from the calendar that will pop up. This is an indicative date, DGT

[Go to top](#table-of-content)

# Interesting information regarding the DGT connector

## DGT Web app: Checking the translation was received

Once a translation has been requested to DGT, the status is updated on the
Drupal site. In addition it is also possible for EC staff to view translation
status and references using the [Test DGT web app] 
(http://www.test.cc.cec/translation/webpoetry/) or the [DGT web app]
(http://www.cc.cec/translation/webpoetry/).
The requester of a translation is also able to read the actual content
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
> Every Website instance using DGT-Connector will have as a requester code
*WEB*.

  - The *year* a new counter was received  ``` (ex: 2016) ```,

  - The *counter* used when request was sent  ``` (ex: 72000) ```,

  - The *version* (version is incremented each time a 'partie' version is sent)
  ```(ex:0) ```,

  - The *partie* (in our case this is a unique page id) ``` (ex: 1) ```.

## Error debugging
If your connection to DGT service is broken, please check the following 
debugging steps:
   - If you are not administrator, contact your site administrator.
   - If you are administrator: go to URL admin/reports/status and check the 
   status of the "DGT connector webservice"
     - Status is red :
       - If "The DGT webservice endpoint is not set. Please ask your support 
       team to check the configuration." is shown, the URL of the DGT webservice
        endpoint is not set.  Please contact your support. 
        The URL should be set in the settings.common.php file on the server.
        
       - If "The local connector credentials are not set.  Please contact CEM 
       support." is shown, the credentials of the Drupal endpoint have not been 
       set. This information should be filled in by a member of CEM team at the 
       time of install.
       
       - If "The DGT remote credentials are not set.  Please contact CEM 
       support." is shown, the credentials of the DGT endpoint have not been 
       set. This information should be filled in by a member of CEM team at the 
       time of install.
       
     - Status is green: All the required fields have been filled. However, if 
      you still experience issues, contact CEM and ask them to check the values
      that have been configured.
              
[Go to top](#table-of-content)

