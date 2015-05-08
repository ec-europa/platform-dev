<?php
/*
 * sample code for comref database
 */

$settings_file = dirname(__FILE__) . '/settings_oracle.php';

if (file_exists($settings_file)) {
  require_once($settings_file);
  
  if(isset($_POST['access_token']) && $_POST['access_token'] == $access_token) {
    $xml = new DOMDocument('1.0', 'utf-8');
    $params = $xml->createElement('data');
    $xml->appendChild($params);

    $tns_admin_path = dirname(realpath(__FILE__)) . '/oracle_home';
    putenv('TNS_ADMIN=' . $tns_admin_path);
    $connection_handle = oci_connect($username, $passwd, $connection_string);
    if (!$connection_handle) {
      print "Unable to connect: " . print_r(oci_error(), TRUE);
    }

    $statement = oci_parse($connection_handle, 'select * from (select * from APP_CRF_P.CRF4PMOCNT_NUPS_V WHERE PER_ID = :perid ORDER BY DT_ATTRIB_LIEN DESC) where rownum = 1');
    oci_bind_by_name($statement, ":perid", $_POST['per_id']);
    oci_execute($statement);

    $fields = explode(',', $_POST['fields']); // fields to get from the Oracle view
    while ($row = oci_fetch_array($statement, OCI_ASSOC)) {
      foreach ($fields as $item) {
        $param = $xml->createElement($item, $row[strtoupper($item)]);
        $params->appendChild($param);
      }
    }
    echo $xml->saveXML();
  }
  else {
    print "acces denied to service";
  }  
}
else {
  print "settings not found";   
}
