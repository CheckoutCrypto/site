<?php

/*
*  Create a link to the Balance form modal
*/
function _ccBalance_make_link($args = '') {
    $fee = (float)0.01;
    $txfee = (float)0.01;
    drupal_add_js(drupal_get_path('module','ccBalance').'/js/ccBalance.js');
    drupal_add_js(array('ccBalance' => array('fee' => $fee,'txfee' => $txfee)), array('type' => 'setting'));

  if (!(empty($args))) {
     $link_text = $args['title'];
     $coin_code = $args['coin_code'];
   } else {
     return FALSE;
   }
   return '<div id="'.$coin_code.'-modal-link">' . l($link_text, 'Balance/withdraw/nojs/'.$coin_code, array('attributes' => array('class' => 'ctools-use-modal'))) . '</div>';
}

/*
*  Create a link to the autopay form modal
*/
function _ccBalance_make_link_autopay($args = '') {
    $fee = (float)0.01;
    $txfee = (float)0.01;
    drupal_add_js(drupal_get_path('module','ccBalance').'/js/ccBalance.js');
    drupal_add_js(array('ccBalance' => array('fee' => $fee,'txfee' => $txfee)), array('type' => 'setting'));
  if (!(empty($args))) {
     $link_text = $args['title'];
     $coin_code = $args['coin_code'];
   } else {
     return FALSE;
   }
   return '<div id="'.$coin_code.'-modal-link">' . l($link_text, 'Balance/autopay/nojs/'.$coin_code, array('attributes' => array('class' => 'ctools-use-modal'))) . '</div>';
}

/*
*  Create a link to the deposit form modal
*/
function _ccBalance_make_link_deposit($args = '') {
    $fee = (float)0.01;
    $txfee = (float)0.01;
    drupal_add_js(drupal_get_path('module','ccBalance').'/js/ccBalance.js');
    drupal_add_js(array('ccBalance' => array('fee' => $fee,'txfee' => $txfee)), array('type' => 'setting'));
  if (!(empty($args))) {
     $link_text = $args['title'];
     $coin_code = $args['coin_code'];
   } else {
     return FALSE;
   }
   return '<div id="'.$coin_code.'-modal-link">' . l($link_text, 'Balance/deposit/nojs/'.$coin_code, array('attributes' => array('class' => 'ctools-use-modal'))) . '</div>';
}

/*
*  Create a link to the deposit form modal
*/
function _ccBalance_make_link_autotrade($args = '') {
    $fee = (float)0.01;
    $txfee = (float)0.01;
    drupal_add_js(drupal_get_path('module','ccBalance').'/js/ccBalance.js');
    drupal_add_js(array('ccBalance' => array('fee' => $fee,'txfee' => $txfee)), array('type' => 'setting'));
  if (!(empty($args))) {
     $link_text = $args['title'];
     $coin_code = $args['coin_code'];
   } else {
     return FALSE;
   }
   return '<div id="'.$coin_code.'-modal-link">' . l($link_text, 'Balance/autotrade/nojs/'.$coin_code, array('attributes' => array('class' => 'ctools-use-modal'))) . '</div>';
}

/*
*  Grab Client's API KEY  - reminder* no key no withdraw!
*/
function getUserApiKey(){
	global $user;
  try {
      $validType = array();
      $result = db_select('ccdev_accounts')
        ->fields('ccdev_accounts', array(
          'api_key',
		 'walletname'))
        ->condition('user_id', $user->uid, '=')
        ->condition('isMaintenance', '0', '=')
        ->condition('isFrozen', '0', '=')
        ->range(0,1)
        ->execute()
      ->fetchAssoc();
  } catch (exception $e) {
      watchdog('ccdev_accounts', 'Could not query database: !fault', $e->getMessage());
  }
  if(isset($result)) {
	$validType['api_key'] = $result['api_key'];
	$validType['walletname'] = $result['walletname'];
    return $validType;
  }
}

/*
*  Grab Client's API KEY  - reminder* no key no withdraw!
*/
function getSpecificKey($userid){
  try {
      $validType = array();
      $result = db_select('ccdev_accounts')
        ->fields('ccdev_accounts', array(
          'api_key',
		 'walletname'))
        ->condition('user_id', $userid, '=')
        ->condition('isMaintenance', '0', '=')
        ->condition('isFrozen', '0', '=')
        ->range(0,1)
        ->execute()
      ->fetchAssoc();
  } catch (exception $e) {
      watchdog('ccdev_accounts', 'Could not query database: !fault', $e->getMessage());
  }
  if(isset($result)) {
	$validType['api_key'] = $result['api_key'];
	$validType['walletname'] = $result['walletname'];
    return $validType;
  }
}


/*
*  Grab Server's Maintenance API KEY  - reminder* no key no withdraw!
*/
function getServerApiKey($walletname){
	$accountdata = array();
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'ccdev_accounts')
	  ->entityCondition('bundle', 'ccAccount_maintenance')
	 ->propertyCondition('user_id', '0')
	 ->propertyCondition('walletname', $walletname)
	 ->propertyCondition('isMaintenance', '1')
	 ->propertyCondition('isFrozen', '0');
	$result = $query->execute();
	if (isset($result['ccdev_accounts'])) {
	  $account_nids = array_keys($result['ccdev_accounts']);
	  $accounts = entity_load('ccdev_accounts', $account_nids);
		foreach($accounts as $account){
			$accountdata['basic_id'] = $account->basic_id;
			$accountdata['bundle_type'] ='ccAccount_maintenance';
			$accountdata['walletname'] = $account->walletname;
			$accountdata['api_key'] = $account->api_key;
		}
	} 
	return $accountdata;
}

/*
*  Get Client's Balance for a specific coin
*/
function getBalance($userid, $coincode){
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'ccdev_balance')
	  ->entityCondition('bundle', 'balance_bundle')
	 ->propertyCondition('coin_code', $coincode)
	->propertyCondition('uid', $userid)
	  ->addMetaData('account', user_load($userid)); // Run the query as user 1.
	$result = $query->execute();
	if (isset($result['ccdev_balance'])) {
	  $wallet_nids = array_keys($result['ccdev_balance']);
	  $wallets = entity_load('ccdev_balance', $wallet_nids);
	  foreach($wallets as $wallet){
			$balance = $wallet->coin_balance;
			return $balance;
		}
	}
}

/*
*  Set Client's autopay settings
*/
function calcTotal($amt, $coincode, $userid){
	module_load_include('inc','ccCoin','includes/cc-php/lib');
	module_load_include('inc','ccGroup','includes/cc-php/lib');
	$usergrpid = getUserGroup($userid);
	$coindata = getCoinData($coincode);
	$groupdata = getGroupData($usergrpid['grp_id']);
	/// calc fee
	$feeTotal = ($amt * ($groupdata['grp_cost']/100)) + ($coindata['coin_txfee'] * 2);
	/// add tx fee
	$GrandTotal = $amt + $feeTotal; 
	return $GrandTotal;
}


/*
*  Set Client's autopay settings
*/
function autopay_insert($coin, $amount, $address){
	global $user;

 	try {
          db_update('ccdev_balance')->fields(array(
            'coin_autopay' => $amount,
            'coin_autoaddress' => $address,
          ))
		->condition('coin_code', $coin, '=')
		->condition('uid', $user->uid, '=')
		->execute();
      } catch (exception $e) {
            watchdog('ccdev_balance', 'Could not insert order into database: !fault', $e->getMessage());
            return FALSE;
      }
}

/*
*  Validate client's twofactor code
*/
function ccValidateTwoFact($pin, $key){
	  module_load_include('inc','ccBalance','includes/GAuth/GoogleAuthenticator');
	 $ga = new PHPGangsta_GoogleAuthenticator();	
	$checkResult = $ga->verifyCode($key, $pin, 2);  
	if ($checkResult) {
	   	return true;
	} else {
		return false;
	}
}

/*
* Validate transaction number is less than package maximum
*/
function checkMaxTrans(){
	global $user;
	 try {
      $result = db_select('ccdev_billing_summary')
        ->fields('ccdev_billing_summary', array(
          'total_trans',
			'grp_id'))
        ->condition('user_id', $user->uid, '=')
        ->range(0,1)
        ->execute()
      ->fetchAssoc();
  } catch (exception $e) {
      watchdog('ccdev_billing_summary', 'Could not query database: !fault', $e->getMessage());
  }
  if(isset($result)) {
		$totaltrans = $result['total_trans'];
		$grpid = $result['grp_id'];
	}
	 try {
      $result = db_select('ccdev_groups')
        ->fields('ccdev_groups', array(
          'grp_max_transactions'))
        ->condition('basic_id', $grpid, '=')
        ->range(0,1)
        ->execute()
      ->fetchAssoc();
  } catch (exception $e) {
      watchdog('ccdev_groups', 'Could not query database: !fault', $e->getMessage());
  }
  if(isset($result)) {
		$maxgrouptrans = $result['grp_max_transactions'];
	}

	if($totaltrans > $maxgrouptrans){
		return false;
	}else{
		return true;
	}

}



