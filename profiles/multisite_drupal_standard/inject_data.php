<?php

inject_data();

function inject_data() {
  // populate users fields of dummy users
  $account = user_load_by_name("admin");
  $account1 = user_load_by_name("administrator");
  $account2 = user_load_by_name("contributor");

  $account->field_firstname['und'][0]['value'] = 'John';
  $account->field_lastname['und'][0]['value'] = 'Doe';
  user_save($account);
	
  $account1->field_firstname['und'][0]['value'] = 'John';
  $account1->field_lastname['und'][0]['value'] = 'Smith';
  user_save($account1);	
	
  $account2->field_firstname['und'][0]['value'] = 'John';
  $account2->field_lastname['und'][0]['value'] = 'Name';
  user_save($account2);	

}

