<?php

/*
* Fill and create server default API keys (maintenance)
*/
function ccInsertMaintainers($users) {
  //generate maintenance api key
  module_load_include('inc','ccAccount','includes/cc-php/generate_credentials');
	$count = 0;
  $ccCred = new ccCredentials();
  foreach($users as $usr) {
	
    $apikey = $ccCred->generateAPI();
    $result = db_select('ccdev_accounts')
      ->fields('ccdev_accounts', array(
        'walletname'))
      ->condition('walletname', $usr, '=')
      ->range(0,1)
      ->execute()
      ->fetchAssoc();

    if(isset($result['walletname'])) {
      db_update('ccdev_accounts')
        ->fields(array(
          'api_key' => $apikey,
        ))
        ->condition('walletname', $result['walletname'], '=')
        ->execute();
    } else {
        try {
          db_insert('ccdev_accounts')->fields(array(
            'bundle_type' => 'ccAccount_maintenance',
            'user_id' => 0,
            'walletname' => $usr,
            'api_key' => $apikey,
            'isMaintenance' => 1,
            'isFrozen' => 0,
            'total_balance' => 0,
            'total_transactions' => 0,
            'default_coin' => 'BTC',
            'delay_seconds' => 0,
            'created' => date("Y-m-d H:i:s"),
          ))->execute();
        } catch (exception $e) {
			var_dump($e);
			break;
        }
    }
	$count++;
  }

	break;
}


/*
* Generate a Client API key, begin billing
*/
function ccGenApiKey($userid, $update, $coin = FALSE){
    module_load_include('inc', 'ccAccount', 'includes/cc-php/generate_credentials');
  $ccCred = new ccCredentials();
  $api_key = $ccCred->generateAPI();
	if($update == true){
      db_update('ccdev_accounts')
        ->fields(array(
          'api_key' => $api_key,
        ))
        ->condition('user_id', $userid, '=')
        ->execute();
    } else {
  		$walletname = $ccCred->generateWalletName();
		/// create account
        try {
          db_insert('ccdev_accounts')->fields(array(
            'bundle_type' => 'ccdev_account_bundle',
            'user_id' => $userid,
            'walletname' => $walletname,
            'api_key' => $api_key,
            'isMaintenance' => 0,
            'isFrozen' => 0,
            'total_balance' => 0,
            'total_transactions' => 0,
            'default_coin' => $coin,
            'delay_seconds' => 0,
            'created' => date("Y-m-d H:i:s"),
          ))->execute();
        } catch (exception $e) {
 //         var_dump($e);
        }
		writeBillingSummary();
	}
}

/*
 * Update user default coin
*/
function updateAccountCoin($userid, $coin){
 	try {
          db_update('ccdev_accounts')
           ->fields(array(
				'default_coin' => $coin,
           ))
		->condition('user_id', $userid, '=')
		->execute();
      } catch (exception $e) {
            watchdog('ccdev_accounts', 'Could not update account in database: !fault', $e->getMessage());
            return FALSE;
      }
}

/*
* Create Billing_Summary
*/
function writeBillingSummary(){
global $user;
        try {
          db_insert('ccdev_billing_summary')->fields(array(
            'bundle_type' => 'ccdev_billing_summary_bundle',
            'user_id' => $user->uid,
            'grp_id' => 1,
            'paid_amt' => 0,
       		'billing_trans' => 0,
       		'total_trans' => 0,
       		'total_email_trans' => 0,
            'last_paid_date' => date("Y-m-d H:i:s"),
            'total_paid_amt' => 0,
            'billing_cycle' => date("Y-m-d H:i:s"),
          ))->execute();
        } catch (exception $e) {
         /// var_dump($e);
        }
}

/*
* Get Settings for a single Billing Group
*/
function getAllAccountInfo(){
		global $user;
		$account = array();
	  $result = db_select('ccdev_accounts')
      ->fields('ccdev_accounts', array(
        'walletname', 'api_key', 'total_balance', 'total_transactions', 'default_coin', 'verified', 'created'))
      ->condition('user_id', $user->uid, '=')
      ->range(0,1)
      ->execute()
      ->fetchAssoc();
    if(isset($result['walletname'])) {	
		$account['walletname'] = $result['walletname'];
		$account['api_key'] = $result['api_key'];
		$account['total_balance'] = $result['total_balance'];
		$account['total_trans'] = $result['total_transactions'];
		$account['default_coin'] = $result['default_coin'];
		$account['verified'] = $result['verified'];
		$account['created'] = $result['created'];
	}
	return $account;

}

/*
* Get Settings for a single Billing Group
*/
function getBillingSummary($userid){
		$billing = array();
	  $result = db_select('ccdev_billing_summary')
      ->fields('ccdev_billing_summary', array(
        'grp_id','paid_amt', 'billing_trans', 'total_trans', 'total_email_trans', 'last_paid_date', 'total_paid_amt', 'billing_cycle'))
      ->condition('user_id', $userid, '=')
      ->range(0,1)
      ->execute()
      ->fetchAssoc();
    if(isset($result['grp_id'])) {
		$billing['grp_id'] = $result['grp_id'];
		$billing['paid_amt'] = $result['paid_amt'];
		$billing['billing_trans'] = $result['billing_trans'];
		$billing['total_trans'] = $result['total_trans'];
		$billing['total_email_trans'] = $result['total_email_trans'];
		$billing['last_paid_date']  = $result['last_paid_date'];
		$billing['total_paid_amt'] = $result['total_paid_amt'];
		$billing['billing_cycle'] = $result['billing_cycle'];		
	}
	return $billing;

}

/*
* UPDATE Billing_Summary
*/
function addEmailTrans($userid){
 	try {
          db_update('ccdev_billing_summary')
		->expression('total_email_trans', 'total_email_trans + 1')
		->condition('user_id', $userid, '=')
		->execute();
      } catch (exception $e) {
            watchdog('ccdev_billing_summary', 'Could not insert order into database: !fault', $e->getMessage());
            return FALSE;
      }
}

/*
* Check if API key exists
*/
function checkIfKeyExists(){
global $user;
  $result = db_select('ccdev_accounts')
      ->fields('ccdev_accounts', array(
        'api_key'))
      ->condition('user_id', $user->uid, '=')
      ->range(0,1)
      ->execute()
      ->fetchAssoc();

    if(isset($result['api_key'])) {
		return true;
	}
	return false;
}


/*
* Check if API key exists
*/
function getServerKey(){
	global $user;
  $result = db_select('ccdev_accounts')
      ->fields('ccdev_accounts', array(
        'api_key'))
      ->condition('user_id', '0', '=')
      ->condition('isMaintenance', '1', '=')
      ->range(0,1)
      ->execute()
      ->fetchAssoc();

    if(isset($result['api_key'])) {
		return $result['api_key'];
	}
	return false;
}


/*
* Get Settings for a single Billing Group
*/
function getGroupInfo($grpid){

	  $result = db_select('ccdev_groups')
      ->fields('ccdev_groups', array(
        'grp_name','grp_description', 'grp_type', 'grp_payment_length', 'grp_max_transactions', 'grp_max_emails'))
      ->condition('basic_id', $grpid, '=')
      ->range(0,1)
      ->execute()
      ->fetchAssoc();

	return $result;

}
