<?php


/// insert new user withdraw/autopay OTP row - default
function addUserOTP($userid, $coin_code, $coin_name){
		try {
		    $result = db_insert('ccdev_otp')->fields(array(
		        'bundle_type' => 'otp_bundle',
		        'uid' => $userid,
		        'coin_name' => $coin_name,
		        'coin_code' => $coin_code,
		        'coin_amount' => 0,
		        'coin_address' => "",
		        'callback_action' => "",
		        'sent' => 0,
		        'created' => date("Y-m-d H:i:s"),
		        'secret' => NULL,
		        'data' => NULL,
		        ))
		        ->execute();
		    } catch (exception $e) {
		        var_dump($e);
		        break;
		        watchdog('ccdev_otp', 'Could not insert OTP Gen into database: !fault', $e->getMessage());
		        return FALSE;
		    }
}

/// add new Balance row - default
function addUserBalance($userid, $coin_code, $coin_name){
	  try {
		  db_insert('ccdev_balance')->fields(array(
		    'bundle_type' => 'balance_bundle',
		    'uid' => $userid,
		    'coin_name' => $coin_name,
		    'coin_code' => $coin_code,
			'coin_pending' => '0',
		    'coin_balance' => '0',
		    'updated' => date("Y-m-d H:i:s"),
		  ))->execute();

	  } catch (exception $e) {
		  watchdog('ccdev_balance', 'Could not insert order into database: !fault', $e->getMessage());
		  return FALSE;
	  }
}

/// get the last userid, from the user's table
function getLastUser(){
	$result = db_select('users')
      ->fields('users', array(
        'uid'))
		->orderBy('uid', 'DESC')
      ->execute()
      ->fetchAssoc();
    if(isset($result)) {
		$userid = $result['uid'];
	}
	return $userid;

}

/// MAKE LINK FOR ADD COIN
function _ccCoin_make_link($args = '') {
// Set a default value if no text in supplied.
  if (!(empty($args))) {
     $link_text = $args['title'];
     $coin_code = $args['coin_code'];
   } else {
     return FALSE;
   }
   return '<div id="'.$coin_code.'-modal-link">' . l($link_text, 'Coin/addcoin/nojs/'.$coin_code, array('attributes' => array('class' => 'ctools-use-modal'))) . '</div>';
 }
/// MAKE LINK FOR EDIT COIN
function _ccCoin_make_edit_link($args = '') {
// Set a default value if no text in supplied.
  if (!(empty($args))) {
     $link_text = $args['title'];
     $coin_code = $args['coin_code'];
   } else {
     return FALSE;
   }
   return '<div id="'.$coin_code.'-modal-link">' . l($link_text, 'Coin/editcoin/nojs/'.$coin_code, array('attributes' => array('class' => 'ctools-use-modal'))) . '</div>';
 }

function getCoinData($coincode){
$coindata = array();
$query = new EntityFieldQuery();
$query->entityCondition('entity_type', 'ccdev_coin')
  ->entityCondition('bundle', 'coin_bundle')
 ->propertyCondition('coin_code', $coincode);
$result = $query->execute();
if (isset($result['ccdev_coin'])) {
  $coin_nids = array_keys($result['ccdev_coin']);
  $coins = entity_load('ccdev_coin', $coin_nids);
	foreach($coins as $coin){
		$coindata['basic_id'] = $coin->basic_id;
		$coindata['type'] = 'ccdev_coin';
		$coindata['entity_bundle'] = 'coin_bundle';
		$coindata['coin_name'] = $coin->coin_name;
		$coindata['coin_code'] = $coin->coin_code;
		$coindata['coin_image'] = $coin->coin_image;
		$coindata['coin_community'] = $coin->coin_community;
		$coindata['coin_rate'] = $coin->coin_rate;
		$coindata['coin_rate_btc'] = $coin->coin_rate_btc;
		$coindata['coin_rate_sell'] = $coin->coin_rate_sell;
		$coindata['coin_rate_buy'] = $coin->coin_rate_buy;
		$coindata['market_sell_depth'] = $coin->market_sell_depth;
		$coindata['market_buy_depth'] = $coin->market_buy_depth;
		$coindata['exchange_id'] = $coin->exchange_id;
		$coindata['exchange_spec'] = $coin->exchange_spec;
		$coindata['coin_fee'] = $coin->coin_fee;
		$coindata['coin_txfee'] = $coin->coin_txfee;
		$coindata['coin_MxConf'] = $coin->coin_MxConf;
  		$coindata['coin_enabled'] = $coin->coin_enabled;
		$coindata['min_amount'] = $coin->min_amount;
		$coindata['max_amount'] = $coin->max_amount;
		$coindata['coin_validate'] = $coin->coin_validate;
		$coindata['coin_description'] = $coin->coin_description;
		$coindata['added'] = $coin->added;
	}
} 
return $coindata;
}

function getAllCoinData(){
$allCoins = array();
$coindata = array();
$query = new EntityFieldQuery();
$query->entityCondition('entity_type', 'ccdev_coin')
  ->entityCondition('bundle', 'coin_bundle');
$result = $query->execute();
if (isset($result['ccdev_coin'])) {
  $coin_nids = array_keys($result['ccdev_coin']);
  $coins = entity_load('ccdev_coin', $coin_nids);
	foreach($coins as $coin){
		$coindata['basic_id'] = $coin->basic_id;
		$coindata['type'] = 'ccdev_coin';
		$coindata['entity_bundle'] = 'coin_bundle';
		$coindata['coin_name'] = $coin->coin_name;
		$coindata['coin_code'] = $coin->coin_code;
		$coindata['coin_image'] = $coin->coin_image;
		$coindata['coin_community'] = $coin->coin_community;
		$coindata['coin_rate'] = $coin->coin_rate;
		$coindata['coin_rate_btc'] = $coin->coin_rate_btc;
		$coindata['coin_rate_sell'] = $coin->coin_rate_sell;
		$coindata['coin_rate_buy'] = $coin->coin_rate_buy;
		$coindata['market_sell_depth'] = $coin->market_sell_depth;
		$coindata['market_buy_depth'] = $coin->market_buy_depth;
		$coindata['exchange_id'] = $coin->exchange_id;
		$coindata['exchange_spec'] = $coin->exchange_spec;
		$coindata['coin_rate_btc'] = $coin->coin_rate_btc;
		$coindata['coin_fee'] = $coin->coin_fee;
		$coindata['coin_txfee'] = $coin->coin_txfee;
		$coindata['coin_MxConf'] = $coin->coin_MxConf;
  		$coindata['coin_enabled'] = $coin->coin_enabled;
		$coindata['min_amount'] = $coin->min_amount;
		$coindata['max_amount'] = $coin->max_amount;
		$coindata['coin_validate'] = $coin->coin_validate;
		$coindata['coin_description'] = $coin->coin_description;
		$coindata['added'] = $coin->added;
		array_push($allCoins, $coindata);
	}
} 
return $allCoins;
}

/*
*  get the TX fee for any coin
*/
function getCoinTxFee($coincode){
    $result = db_select('ccdev_coin')
      ->fields('ccdev_coin', array(
        'coin_txfee'))
      ->condition('coin_code', $coincode, '=')
      ->execute()
      ->fetchAssoc();
    if(isset($result)) {
		return $result['coin_txfee'];
	}
}

/*
*  Convert $ to coin rate of any coin
*/
function getCoinRate($coincode, $amount){
$result = db_select('ccdev_coin')
      ->fields('ccdev_coin', array(
        'coin_rate'))
      ->condition('coin_code', $coincode, '=')
      ->execute()
      ->fetchAssoc();
    if(isset($result)) {
		$total = ($amount) / $result['coin_rate'];
	}
	return $total;
}

function getAccountData($coincode){
global $user;
$query = new EntityFieldQuery();
$query->entityCondition('entity_type', 'ccdev_balance')
->entityCondition('bundle', 'balance_bundle')
->propertyCondition('coin_code', $coincode)
->propertyCondition('uid', $user->uid);
$result = $query->execute();
if (isset($result['ccdev_balance'])) {
    $coinExists = true;
    return $coinExists;
} 

return FALSE;
}



function getAllCoinCodes(){
$allCoins = array();
$coindata = array();
$query = new EntityFieldQuery();
$query->entityCondition('entity_type', 'ccdev_coin')
  ->entityCondition('bundle', 'coin_bundle');
$result = $query->execute();
if (isset($result['ccdev_coin'])) {
  $coin_nids = array_keys($result['ccdev_coin']);
  $coins = entity_load('ccdev_coin', $coin_nids);
	foreach($coins as $coin){
		$coindata['coin_name'] = $coin->coin_name;
		$coindata['coin_code'] = $coin->coin_code;
		$coindata['coin_image'] = $coin->coin_image;
		array_push($allCoins, $coindata);
	}
} 
return $allCoins;
}


function ConvertAmount($amount, $amount_type, $coin_to, $coin_from){
	$conversion = array();
	$cnTO = getSpecificCoinRate($coin_to);
	$cnFROM = getSpecificCoinRate($coin_from);
	if($amount_type == "usd"){
		$cnBTC = getSpecificCoinRate('BTC');
		// convert USD to coin - deposit
		$amountDep = ($amount / $cnBTC['coin_rate']) / $cnFROM['coin_rate_btc'];
		/// convert amountRec $coin_to - received
		$amountRec = ($amount / $cnBTC['coin_rate']) / $cnTO['coin_rate_btc'];  // without fee

	}else if($amount_type == "coin"){
		/// accept the amount as the natural amount - deposit
		$amountDep = $amount;
		/// convert amountRec $coin_to - received
		$amountRec = $amount * $cnFROM['coin_rate_btc'];  // without fee

	}else if($amount_type == "btc"){
		/// convert btc to desired coin - deposit
		$amountDep = $amount / $cnFROM['coin_rate_btc'];
		/// convert amountRec $coin_to - received
		$amountRec = $amount;
	}

	$conversion['amount'] = $amountDep;
	$conversion['amountRec'] = $amountRec;

	return $conversion;
}


function getSpecificCoinImg($coin){
	global $user;

	try {
	$result = db_select('ccdev_coin')
		  ->fields('ccdev_coin', array('coin_image'))
        ->condition('coin_code', $coin, '=')
		    ->range(0,1) //max 10 results
		    ->execute();
	  } catch (exception $e) {
		  watchdog('ccdev_coin', 'Could not query database: !fault', $e->getMessage());
	  }
	while ($rows = $result->fetchAssoc()) {
	  if(is_array($rows) AND count($rows) > 0) { //check that object is array and populated
		  if(isset($rows['coin_image'])) {
				$coinimg = $rows['coin_image'];
				return $coinimg;
			}
		}
	}
}

function getIndividualCoinImg($coins, $coincode){

	foreach($coins as $cn){
		if($cn['coin_code'] == $coincode){
			return $cn['coin_image'];
		}
	}

}

function getSpecificCoinRate($coin){
	$coinrate = array();
	try {
     $result = db_select('ccdev_coin')
        ->fields('ccdev_coin', array(
          'coin_rate', 'coin_rate_btc'))
        ->condition('coin_code', $coin, '=')
        ->range(0,1)
        ->execute()
        ->fetchAssoc();
	  } catch (exception $e) {
		  watchdog('ccdev_coin', 'Could not query database: !fault', $e->getMessage());
	  }
	if(isset($result['coin_rate'])) {
		$coinrate['coin_rate'] = $result['coin_rate'];	
		$coinrate['coin_rate_btc'] = $result['coin_rate_btc'];	
	}	
		return $coinrate;
}



function getCoinValidateCode($coin){
	try {
     $result = db_select('ccdev_coin')
        ->fields('ccdev_coin', array(
          'coin_validate'))
        ->condition('coin_code', $coin, '=')
        ->range(0,1)
        ->execute()
        ->fetchAssoc();
	  } catch (exception $e) {
		  watchdog('ccdev_account', 'Could not query database: !fault', $e->getMessage());
	  }
	if(isset($result['coin_validate'])) {
		return $result['coin_validate'];	
	}
}
