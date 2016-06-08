Summary
=======

The TMGMT Poetry module allows the creation of translation managers
that make use of the European Commission Poetry translation services
(served by DGT).


Installation
============

- Install as usual, see http://drupal.org/node/70151 for further information.
- The settings.php of your project must contain the following variables filled
  with appropriate values:

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

Manual test of Poetry translator
================================

To manually test the Poetry translator plugin without accessing the actual
DGT service enable the follow the steps below:

1. Enable the ```tmgmt_poetry_test``` module.
2. Set the address property to the newly available test endpoint:
```php
    $conf['poetry_service'] = array(
      'address' => 'http://your.local.base.url/profiles/multisite_drupal_standard/modules/custom/tmgmt_poetry/tests/tmgmt_poetry_test.wsdl',
      'method' => 'requestService',
      'callback_user' => 'Poetry',
      'callback_password' => 'PoetryPWD',
      'poetry_user' => 'Poetry',
      'poetry_password' => 'PoetryPWD',
    );
```
   Notice that this refers to a Multisite standard profile, change relevant
   portion if necessary.
3. Request a new translation using the "TMGMT Poetry: Test translator" translator.


Simulate Poetry callback
========================

The following steps let you test a response as it was coming from the Poetry service itself, assuming you have the
`tmgmt_poetry_test` module enabled:

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
