# Summary
---------

The TMGMT Poetry module allows the creation of translation managers
that make use of the European Commission Poetry translation services
(served by DGT).

Table of content:
=================
*Installation
*Testing
*DGT Web app

# Installation
--------------

## 1. Requesting access to poetry:
Before you can start using poetry, you should make a formal request to DGCOMM.
Please send a mail to / fill the document located at http://
DG COMM will inform DGT and send credentials to FPFIS maintenance team who will
activate poetry on your site.

## 2. Enabling on your platform instance
:hand: Poetry is not a feature you can enable using feature sets. It needs to be
activated by your FPFIS maintenance team.

## 3. Enabling as a FPFIS maintenance staff.
* Make sure the poetry access has be requested and credentials have been
received. (See point 1 above).
* The module is included in the platform-dev sources. Run the drush command
```drush en tmgmt_poetry```
* Update the settings.php of the project. It must be filled with appropriate
values depending on the environement you are using it in.
For more details on variables setting see below section 3 'Implementation on
production'.

# Testing
---------

## 1. Testing locally
=====================
You can test the feature locally, throught the UI or in an automated way, by
using the tmgmt_poetry_mock module.
See [the mock readme] (/tmgmt_poetry_mock/README.md) for more information.

## 2. Testing on playground environment
=======================================
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

# Using on production
=====================
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

> The values of
>[CALLBACK_USERNAME]
>[CALLBACK_PASSWORD]
>[POETRY_USERNAME]
>[POETRY_PASSWORD]
> should have been received from DGCOMM (see 'Installations step 1')


Check  my translation request was indeed received
=================================================

Once a translation has been requested to DGT, it is possible for EC staff to
view translation status and references using the web app located at:
http://www.cc.cec/translation/webpoetry/
The requesters of a translation will also be able to read the actual content
of the translations via this application.

Simulate Poetry callback
========================

The following steps let you test a response as it was coming from the Poetry
service itself, assuming you have the `tmgmt_poetry_test` module enabled:

```
$poetry_service = variable_get('poetry_service');
$job = tmgmt_job_load(13);
$msg = _tmgmt_poetry_test_make_xml_msg($job, 'fr', 'HTML');
FPFISPoetryIntegrationRequest($poetry_service['callback_user'], $poetry_service['callback_password'], $msg);
```

The following callback lets you simulate you received a response from poetry for job item N
http://your.local.base.url/tmgmt_poetry_test/receivetranslation/N
The response will contain a copy of the original content

The following callback lets you import a a Rejection message from poetry for job item N
http://your.local.base.url/tmgmt_poetry_test/refusetranslation/N
The XML message should be saved in folder tmgmt_poetry/tests/test.xml
The job item N must match the job with the reference set in the XML.

Testing Poetry responses
========================

TMGMT Poetry module logs all responses in the Watchdog by tagging them with type "Poetry: Response".
To re-send received responses use the fully logged message as POST request content.

The example below assumes you have stored the full XML message in '/path/to/response-file.xml'.

```php
$poetry_service = variable_get('poetry_service');
$content = file_get_contents('/path/to/response-file.xml');
$content = htmlentities($content);

$data = <<<DATA
<soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
  <soapenv:Body>
    <ns1:FPFISPoetryIntegrationRequest soapenv:encodingStyle="http://schemas.xmlsoap.org/soap/encoding/" xmlns:ns1="urn:FPFISPoetryIntegration">
      <user xsi:type="xsd:string">{$poetry_service['callback_user']}</user>
      <password xsi:type="xsd:string">{$poetry_service['callback_password']}</password>
      <msg xsi:type="xsd:string">{$content}</msg>
    </ns1:FPFISPoetryIntegrationRequest>
  </soapenv:Body>
</soapenv:Envelope>
DATA;

$options = [
  'method' => 'POST',
  'headers' => [
    'Content-Type' => 'application/soap+xml; charset=UTF-8',
  ],
  'data' => $data,
];

$response = drupal_http_request('http://your.local.base.url/tmgmt_poetry/service_callback', $options);
```

