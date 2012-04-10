<?php

/***************************************************************************
 *                            generic-actions.php
 *                            -------------------
 *   author            :    DIGIT FPFIS SUPPORT
 *   email                : DIGIT-FPFIS-SUPPORT@ec.europa.eu
 *   Revisions
 *     - See sources repository
 *
 ***************************************************************************/

/*
Generic actions used by several applications for common or specific purposes
*/

// Overwrite REMOTE_ADDR with CLIENT-IP rather than proxy value
if ((defined('FPFIS_OVERWRITE_REMOTE_ADDR') && FPFIS_OVERWRITE_REMOTE_ADDR))
{
	if (function_exists('overwriteRemoteAddr'))
	{
		overwriteRemoteAddr();
	}
}

// Overwrite user_agent used by PHP with certain functions (fopen, file_get_contents, etc.)
if ((defined('FPFIS_OVERWRITE_USER_AGENT') && FPFIS_OVERWRITE_USER_AGENT))
{
	@ini_set('user_agent',FPFIS_OVERWRITE_USER_AGENT);
}

?>