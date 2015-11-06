
-- SUMMARY --

The TMGMT MT@EC module allows the creation of translation managers that make use of the European Comission Automated Translation services (MT@EC).

-- REQUIREMENTS --

The MT@EC services make use of a FTP server as a means to exchange data to be translated. In order for this module to work a FTP server must be available.

-- INSTALLATION --

* Install as usual, see http://drupal.org/node/70151 for further information.

* The settings.php of your project must contain the following variables filled with appropiate values:
  $conf['ftp_server'] = array(
    'address' => '127.0.0.1', //IP address or url to the FTP erver 
    'port' => '21', //Port of the FTP server
    'user' => 'user', //Username to access the FTP server
    'password' => 'pass', //Password associated to the username
  );

  $conf['mtec_service'] = array (
  'address' => 'https://mtatecservice.ec.testa.eu/MtatecOsbConnector/InboundConnectorPublicSimpleProxyService?WSDL',
  'applicationName' = 'multisite20150219',
  );
