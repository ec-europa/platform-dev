
-- SUMMARY --

The TMGMT Poetry module allows the creation of translation managers that make use of the European Commission Poetry translation services (served by DGT).


-- INSTALLATION --

* Install as usual, see http://drupal.org/node/70151 for further information.

* The settings.php of your project must contain the following variables filled with appropiate values:
  $conf['poetry_service'] = array(
  'address' => 'http://intragate.test.ec.europa.eu/DGT/poetry_services/components/poetry.cfc?wsdl',
  'method' => 'requestService',
  'user' => 'multisite',
  'password' => 'MultiSitePWD',
  'callback_user' => 'Poetry',
  'callback_password' => 'PoetryPWD',
);
