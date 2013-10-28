<?php
/*
 * sample code for comref database
 */
  
$xml = new DOMDocument('1.0', 'utf-8');
$params = $xml->createElement('data');
$xml->appendChild($params);

$fields = explode(',', $_POST['fields']);

$tns_admin_path = dirname(realpath(__FILE__)) . '/oracle_home';
putenv('TNS_ADMIN=' . $tns_admin_path);
$connection_string = 'XXXX';
$connection_handle = oci_connect('XXXXX', 'XXXXX', $connection_string);
if (!$connection_handle) {
  print "Unable to connect: " . print_r(oci_error(), TRUE);
}

$per_id = $_POST['per_id'];

$statement = oci_parse($connection_handle, 'select * from APP_CRF_P.CRF4PMOCNT_NUPS_V WHERE PER_ID = :perid');
oci_bind_by_name($statement, ":perid", $per_id);
oci_execute($statement);

while ($row = oci_fetch_array($statement, OCI_ASSOC)) {
  foreach ($fields as $item) {
    $param = $xml->createElement($item, $row[strtoupper($item)]);
    $params->appendChild($param);
  }
}
echo $xml->saveXML();
