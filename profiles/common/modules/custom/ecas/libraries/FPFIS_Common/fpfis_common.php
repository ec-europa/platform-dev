<?php

if ( is_file(FPFIS_COMMON_LIBRARIES_PATH . '/FPFIS_Common/constants/constants.php') )
	include_once(FPFIS_COMMON_LIBRARIES_PATH . '/FPFIS_Common/constants/constants.php');

if ( is_file(FPFIS_COMMON_LIBRARIES_PATH . '/FPFIS_Common/forwarded-proxy/config-forwarded-proxy.php') )
	include_once(FPFIS_COMMON_LIBRARIES_PATH . '/FPFIS_Common/forwarded-proxy/config-forwarded-proxy.php');

if ( is_file(FPFIS_COMMON_LIBRARIES_PATH . '/FPFIS_Common/generic/generic-functions.php') )
	include_once(FPFIS_COMMON_LIBRARIES_PATH . '/FPFIS_Common/generic/generic-functions.php');

if ( is_file(FPFIS_COMMON_LIBRARIES_PATH . '/FPFIS_Common/generic/generic-actions.php') )
	include_once(FPFIS_COMMON_LIBRARIES_PATH . '/FPFIS_Common/generic/generic-actions.php');

?>