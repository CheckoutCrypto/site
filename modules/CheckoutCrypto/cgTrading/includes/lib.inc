<?php

function getDefaultKey(){
	global $user;

	try {
     $result = db_select('ccdev_accounts')
        ->fields('ccdev_accounts', array(
          'api_key'))
        ->condition('user_id', '1', '=')
        ->range(0,1)
        ->execute()
        ->fetchAssoc();
	  } catch (exception $e) {
		  watchdog('ccdev_account', 'Could not query database: !fault', $e->getMessage());
	  }
	if(isset($result['api_key'])) {
		return $result['api_key'];	
	}
	

}

function getUserKey($userid){

	try {
     $result = db_select('ccdev_accounts')
        ->fields('ccdev_accounts', array(
          'api_key'))
        ->condition('user_id', $userid, '=')
        ->range(0,1)
        ->execute()
        ->fetchAssoc();
	  } catch (exception $e) {
		  watchdog('ccdev_account', 'Could not query database: !fault', $e->getMessage());
	  }
	if(isset($result['api_key'])) {
		return $result['api_key'];	
	}

}

function getTradeStage($address){
	try {
     $result = db_select('ccdev_trades')
        ->fields('ccdev_trades', array(
          'status'))
        ->condition('address_gen', $address, '=')
        ->range(0,1)
        ->execute()
        ->fetchAssoc();
	  } catch (exception $e) {
		  watchdog('ccdev_trades', 'Could not query database: !fault', $e->getMessage());
	  }
	if(isset($result['status'])) {
		return $result['status'];
	}	
}

function getAllTrades($min, $max, $header){

	global $user;

	$AllTrades = array();
	$trade = array();
	try {
	$result = db_select('ccdev_trades')
		  ->fields('ccdev_trades', array('coin_to', 'amount_to', 'coin_from', 'amount_from', 'address_gen', 'address_out', 'txid', 'timestamp'))
        ->condition('status', '2', '=')
		// ->orderBy('timestamp', 'DESC')
		 ->extend('TableSort')
		  ->orderByHeader($header)
		    ->range($min,$max) //max 10 results
		    ->execute();
	  } catch (exception $e) {
		  watchdog('ccdev_trades', 'Could not query database: !fault', $e->getMessage());
	  }
	while ($rows = $result->fetchAssoc()) {
	  if(is_array($rows) AND count($rows) > 0) { //check that object is array and populated
		  if(isset($rows['coin_to']) AND isset($rows['coin_from'])) {
			$trade['coin_to'] = $rows['coin_to'];
			$trade['amount_to'] = $rows['amount_to'];
			$trade['coin_from'] = $rows['coin_from'];
			$trade['amount_from'] = $rows['amount_from'];
			$trade['address_gen'] = $rows['address_gen'];
			$trade['address_out'] = $rows['address_out'];
			$trade['txid'] = $rows['txid'];
			$trade['timestamp'] = $rows['timestamp'];
			array_push($AllTrades, $trade); 
			}
		}
	}
	return $AllTrades;

}

function getSpecificTrade($address){

	global $user;

	$trade = array();
	try {
	$result = db_select('ccdev_trades')
		  ->fields('ccdev_trades', array('coin_to', 'amount_to', 'coin_from', 'amount_from', 'address_gen', 'address_out', 'txid', 'timestamp'))
       ->condition('address_gen', $address, '=')
        ->condition('status', '2', '=')
		    ->range(0,1) //max 10 results
		    ->execute();
	  } catch (exception $e) {
		  watchdog('ccdev_trades', 'Could not query database: !fault', $e->getMessage());
	  }
	while ($rows = $result->fetchAssoc()) {
	  if(is_array($rows) AND count($rows) > 0) { //check that object is array and populated
		  if(isset($rows['coin_to']) AND isset($rows['coin_from'])) {
			$trade['coin_to'] = $rows['coin_to'];
			$trade['amount_to'] = $rows['amount_to'];
			$trade['coin_from'] = $rows['coin_from'];
			$trade['amount_from'] = $rows['amount_from'];
			$trade['address_gen'] = $rows['address_gen'];
			$trade['address_out'] = $rows['address_out'];
			$trade['txid'] = $rows['txid'];
			$trade['timestamp'] = $rows['timestamp'];
			return $trade;
			}
		}
	}

}

function getTradeCoinImages($coinTo, $coinFrom){

	global $user;

	$trade = array();
	try {
	$result = db_select('ccdev_coin')
		  ->fields('ccdev_coin', array('coin_image', 'coin_code'))
       ->condition('coin_code', $coinTo, '=')
		    ->range(0,1) //max 10 results
		    ->execute();
	  } catch (exception $e) {
		  watchdog('ccdev_trades', 'Could not query database: !fault', $e->getMessage());
	  }
	while ($rows = $result->fetchAssoc()) {
	  if(is_array($rows) AND count($rows) > 0) { //check that object is array and populated
		  if(isset($rows['coin_image'])) {
			$trade['coin_to'] = $rows['coin_image'];
			}
		}
	}

	try {
	$result = db_select('ccdev_coin')
		  ->fields('ccdev_coin', array('coin_image', 'coin_code'))
       ->condition('coin_code', $coinFrom, '=')
		    ->range(0,1) //max 10 results
		    ->execute();
	  } catch (exception $e) {
		  watchdog('ccdev_trades', 'Could not query database: !fault', $e->getMessage());
	  }
	while ($rows = $result->fetchAssoc()) {
	  if(is_array($rows) AND count($rows) > 0) { //check that object is array and populated
		  if(isset($rows['coin_image'])) {
			$trade['coin_from'] = $rows['coin_image'];
			}
		}
	}

	if(isset($trade['coin_to']) && isset($trade['coin_from'])){
		return $trade;
	}

}


function getHotBalance($coin){
	$hotUser = 1; ///// REMINDER THIS SHOULDN"T BE STATIC
	$trade = array();
	try {
	$result = db_select('ccdev_balance')
		  ->fields('ccdev_balance', array('coin_balance', 'coin_code'))
       ->condition('coin_code', $coin, '=')
		    ->range(0,1) //max 10 results
		    ->execute();
	  } catch (exception $e) {
		  watchdog('ccdev_trades', 'Could not query database: !fault', $e->getMessage());
	  }
	while ($rows = $result->fetchAssoc()) {
	  if(is_array($rows) AND count($rows) > 0) { //check that object is array and populated
		  if(isset($rows['coin_balance'])) {
			$hotWal['coin_balance'] = $rows['balance_total'];
			return $hotWal['coin_balance'];
			}
		}
	}

}
/// Validate Address with Coin Field
function validateCoinAddress($coin, $address){
	module_load_include('inc', 'cgTrading', 'includes/validateaddress');

	$validCode = getCoinValidateCode($coin);
	$v = new validateAddress($validCode);
	$result = $v->checkAddress($address, $validCode);
	return $result;
}

/// Validate Address Field
function validateTradeAddress($trade_address, $coin_to){
	$addressRec = false;
			  	if (!empty($trade_address) ){
					$address = $trade_address;
					if(preg_match("/^[A-Z0-9]+$/i", $address) && $errors == 0) {
						$validAddress = validateCoinAddress($coin_to, $address);
						if($validAddress == true){
							$addressRec = $address;
						}
					}
				}else{
					$adressRec = NULL;
				}
	return $addressRec;
}

//// Validate Trade Amount field
function validateTradeAmount($amt){
	$amount = false;
	if (!empty($amt)){
			if(preg_match("/^[0-9]{0,}\.[0-9]{1,8}|[0-9]{1,}+$/", $amt)) {
				$amount = $amt;
			} 
	}else{
		$amount = NULL;
	}

	return $amount;
}

//// Validate Trade Coin 
function validateTradeCoin($allcoins, $coin_from){
	$coin = false;
				if(!empty($coin_from)){
					foreach($allcoins as $cn){
						if($cn['coin_code'] == $coin_from){
								$coin = $coin_from;
						}
					}
				}else{
					$coin = NULL;
				}
	return $coin;
}
