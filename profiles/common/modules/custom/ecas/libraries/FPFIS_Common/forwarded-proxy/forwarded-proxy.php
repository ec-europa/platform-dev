<?php

/***************************************************************************
 *                            forwarded-proxy.php
 *                            -------------------
 *   begin                : 2008-01-30
 *   author            :    Alexandre BOSSERELLE (BOSSEAL)
 *   email                : DIGIT-FPFIS-SUPPORT@ec.europa.eu
 *   Revisions
 *     - 2009-09-22: BOSSEAL - Update script to manage new proxy (bluecoat)
 *     - 2009-10-08: BOSSEAL - Set $_SERVER['SCRIPT_URI'] only if defined in server (mod_rewrite activated)
 *                             Code optimization and globalization
 *     - 2009-11-25: BOSSEAL - Rules for PHP constants when mapped behind webgate
 *     - 2009-12-17: KLEINGY - Referer rewriten, new rules when mapped behind webgate
 *     - 2009-12-18: BOSSEAL - Europa hostnames allowed for proxy bypass
 *     - 2010-03-24: BOSSEAL - Support intracomm.cec.eu-admin.net and *.cc.cec
 *     - 2010-07-27: BOSSEAL - Tests on referer (use value if defined only)
 *     - 2011-08-01: BOSSEAL - Management of server port
 *     - 2011-12-20: BOSSEAL - Access though Testa
 ***************************************************************************/

/*
When applications are installed behind a reverse proxy, they may use the unproxied FQDN of the server rather than the proxied FQDN from which it should be access
Some PHP variables are forced with the proxied FQDN

WARNING: this proxy hack is included by the file config-forwarded-proxy.php - Please use config-forwarded-proxy.php conf file when required
*/

/* Management of Testa (inter-institutions access to cc.cec through intracomm.ec.testa.eu) */
if (!empty($_SERVER["HTTP_X_FORWARDED_POPULATION"]))
{
	if ( stristr($_SERVER["HTTP_X_FORWARDED_POPULATION"], 'testa') !== false )
		$_SERVER["HTTP_X_FORWARDED_HOST"] = 'intracomm.ec.testa.eu';
}

if ( !empty($_SERVER["HTTP_FORWARDED"]) || !empty($_SERVER["HTTP_X_FORWARDED_HOST"]) )
{
	$fpfis_server_hostname_wi_proxy = 'www.cc.cec'; //proxied FQDN

	if ( !empty($_SERVER["HTTP_FORWARDED"]) )
	{
		if ( stristr($_SERVER["HTTP_FORWARDED"], 'cc.cec') !== false )
			$fpfis_server_hostname_wi_proxy = 'www.cc.cec';
		if ( stristr($_SERVER["HTTP_FORWARDED"], '.cc.cec') !== false )
			$fpfis_server_hostname_wi_proxy = $_SERVER["HTTP_FORWARDED"];
		if ( stristr($_SERVER["HTTP_FORWARDED"], 'cc.cec.') !== false )
			$fpfis_server_hostname_wi_proxy = $_SERVER["HTTP_FORWARDED"];
		if ( stristr($_SERVER["HTTP_FORWARDED"], 'europa.eu') !== false )
			$fpfis_server_hostname_wi_proxy = $_SERVER["HTTP_FORWARDED"];
		if ( stristr($_SERVER["HTTP_FORWARDED"], 'intracomm.cec.eu-admin.net') !== false )
			$fpfis_server_hostname_wi_proxy = $_SERVER["HTTP_FORWARDED"];
		if ( stristr($_SERVER["HTTP_FORWARDED"], 'intracomm.ec.testa.eu') !== false )
			$fpfis_server_hostname_wi_proxy = $_SERVER["HTTP_FORWARDED"];
	}

	if ( !empty($_SERVER["HTTP_X_FORWARDED_HOST"]) )
	{
		if ( stristr($_SERVER["HTTP_X_FORWARDED_HOST"], 'cc.cec') !== false )
			$fpfis_server_hostname_wi_proxy = 'www.cc.cec';
		if ( stristr($_SERVER["HTTP_X_FORWARDED_HOST"], '.cc.cec') !== false )
			$fpfis_server_hostname_wi_proxy = $_SERVER["HTTP_X_FORWARDED_HOST"];
		if ( stristr($_SERVER["HTTP_X_FORWARDED_HOST"], 'cc.cec.') !== false )
			$fpfis_server_hostname_wi_proxy = $_SERVER["HTTP_X_FORWARDED_HOST"];
		if ( stristr($_SERVER["HTTP_X_FORWARDED_HOST"], 'europa.eu') !== false )
			$fpfis_server_hostname_wi_proxy = $_SERVER["HTTP_X_FORWARDED_HOST"];
		if ( stristr($_SERVER["HTTP_X_FORWARDED_HOST"], 'intracomm.cec.eu-admin.net') !== false )
			$fpfis_server_hostname_wi_proxy = $_SERVER["HTTP_X_FORWARDED_HOST"];
		if ( stristr($_SERVER["HTTP_X_FORWARDED_HOST"], 'intracomm.ec.testa.eu') !== false )
			$fpfis_server_hostname_wi_proxy = $_SERVER["HTTP_X_FORWARDED_HOST"];
	}

	$fpfis_server_hostname_wo_proxy = $_SERVER['HTTP_HOST']; //real FQDN
	$_SERVER['HTTP_HOST'] = $fpfis_server_hostname_wi_proxy;
	$_SERVER['SERVER_NAME'] = $fpfis_server_hostname_wi_proxy;
	if ( !empty($_SERVER['SCRIPT_URI']) )
		$_SERVER['SCRIPT_URI'] = str_replace($fpfis_server_hostname_wo_proxy,$fpfis_server_hostname_wi_proxy,$_SERVER['SCRIPT_URI']);
	if ( !empty($_SERVER['HTTP_REFERER']) )
		$_SERVER['HTTP_REFERER'] = str_replace($fpfis_server_hostname_wo_proxy,$fpfis_server_hostname_wi_proxy,$_SERVER['HTTP_REFERER']);
	if ( defined('FPFIS_SERVER_PORT') && FPFIS_SERVER_PORT != '' )
		$_SERVER['SERVER_PORT'] = FPFIS_SERVER_PORT;
	if ( stristr($fpfis_server_hostname_wi_proxy, 'webgate') !== false ) {
		$_SERVER['HTTPS'] = 'on';
		if ( !empty($_SERVER['HTTP_REFERER']) )
			$_SERVER['HTTP_REFERER'] = str_replace('http://','https://',$_SERVER['HTTP_REFERER']);
		$_SERVER['SERVER_PORT'] = 443;
	}
}

?>