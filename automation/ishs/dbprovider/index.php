<?php

$topmessage = 'This page is intended for the ISHS team to provide database passwords to the FPFIS team.';
$bottommessage = 'Contact: FPFIS team digit-fpfis-support@ec.europa.eu';
$form_action = htmlentities($_SERVER['REQUEST_URI']);

include(dirname(__FILENAME__) . '/conf.inc.php');

// connect to the database
$link = mysqli_connect($supermaster_server, $supermaster_user, $supermaster_password, $supermaster_database, $supermaster_port);
if (!$link) {
	$errormessage = 'Unable to connect to the database.';
} else {
	// handles posted data, if any
	if (preg_match('/^\d+$/', @$_POST['account_id'])) {
		if (!strlen(trim($_POST['account_password']))) {
			$errormessage = 'You must enter a password.';
		} else {
			// set account password (sap)
			$sap_query = mysqli_prepare($link, 'SELECT set_account_password(?, ?);');
			$sap_query->bind_param('is', $_POST['account_id'], $_POST['account_password']);
			$sap_query->execute();
			$sap_query->bind_result($result);
			$sap_query->fetch();
			if ($result == 1) {
				$infomessage = 'Password was successfully provided.';
			} else {
				$errormessage = 'Password could not be provided. Maybe it was already provided?';
			}
			$sap_query->close();
		}
	}
	
	// fetches password-less accounts (pla)
	$plas = array();
	$pla_query = mysqli_prepare($link, 'SELECT id, hostname, port, user FROM password_less_accounts');
	$pla_query->execute();
	$pla_query->bind_result($pla_id, $pla_hostname, $pla_port, $pla_user);
	while ($pla_query->fetch()) {
		$plas[] = array(
			'id' => $pla_id,
			'url' => sprintf('mysql://%s@%s:%d/', $pla_user, $pla_hostname, $pla_port)
		);
	}
	$pla_query->close();
	if (empty($plas)) {
		$infomessage .= ' There is no account waiting for a password.';
	}
}
?><html>
	<head>
		<title>FPFIS DB providers</title>
		<style type="text/css">
			.error-message { color: red; text-align: center; }
			.info-message { color: green; text-align: center; }
			.top-message, .bottom-message { margin-left: auto; margin-right: auto; text-align: center; }
			.form-area { width: 800px; }
			.account_url { float: left; width: 350px; }
			.account_password { float: left; }
			.account_submit { float: left; }
			.account_end { clear: both; }
		</style>
	</head>
	<body>
		<div id="top-message" class="top-message"><?php echo @$topmessage; ?></div>
			<div id="info-message" class="info-message"><?php echo @$infomessage; ?></div>
			<div id="error-message" class="error-message"><?php echo @$errormessage; ?></div>
		</div>
		<div id="form-area" class="form-area">
<?php foreach ($plas as $pla): ?>
			<form id="password-form-<?php echo $pla['id']; ?>" method="post" action="<?php echo @$form_action; ?>">
				<input name="account_id"       type="hidden" value="<?php echo $pla['id']; ?>" />
				<div class="account_url">
					<?php echo htmlentities($pla['url']); ?>:
				</div>
				<div class="account_password">
					<input class="password_field"  name="account_password" type="text"    value="" />
				</div>
				<div class="account_submit">
					<input class="password_submit" name="account_submit"   type="submit"  value="Provide password" />
				</div>
				<div class="account_end"></div>
			</form>
<?php endforeach ?>
		</div>
		<div id="bottom-message" class="bottom-message"><?php echo @$bottommessage; ?></div>
	</body>
</html>
