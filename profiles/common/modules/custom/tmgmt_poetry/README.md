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
