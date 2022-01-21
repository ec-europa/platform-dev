<?php
	
include ("build/vendor/autoload.php");
use EC\Behat\PoetryExtension\Context\Services\PoetryMock;
use EC\Poetry\Poetry;

print_r("Start test". PHP_EOL);

$parameters= array(
	"service" => 
		array (
			"host" => "behat",
			"port" => "28999",
			"endpoint" => "/service",
			"wsdl" => "/wsdl",
			"username" => "username",
			"password" => "password",
		),
	"application" => 
		array (
			"base_url" => "http://web:8080/build",
			"endpoint" => "/poetry/notification",
		),
	);

$poetry= new Poetry(array());
$PoetryMock = new PoetryMock($poetry, $parameters);

$saved_parameter = $PoetryMock->getParameters();
print_r("------ PoetryMock setUp ------". PHP_EOL);
$PoetryMock->setUp();
print_r(PHP_EOL);
print_r(PHP_EOL);
sleep(1);
print_r(PHP_EOL);
print_r(PHP_EOL);
print_r("------ PoetryMock tearDown ------". PHP_EOL);
$PoetryMock->setParameters($saved_parameter);
$PoetryMock->tearDown();