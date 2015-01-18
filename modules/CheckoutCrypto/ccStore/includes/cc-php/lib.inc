<?php

/**
 * Author: Grant Hutchinson - CheckoutCrypto - dreamcode@checkoutcrypto.com
 * Copyright 2014 Apache 2.0 Licensed
 **/


/*
*  Control the order payment progress/cache based on the status
*/
function cc_order_status($order) {
   module_load_include('inc', 'ccStore', 'includes/cc-php/api');
	$result = getCachedOrder($order->order_id);

    if($result != FALSE) {
        $time = time();
        $order_time = strtotime($result['timestamp']);

        if($order_time < ($time - 5)) {
            $queue_id = $result['cc_queue_id_tmp'];
            $pay_status = $result['cc_pay_status'];
            switch ($pay_status) {
            case 'registered':
                    $response = ccApiOrderStatus($queue_id, $result['cc_coinname_short']);
					
                    if(isset($response['address']) AND ($response['address'] != $result['cc_address']))  {

                        $request['balance'] = $result['cc_coin_amount'];
                        $request['address'] = $response['address'];
                        $status = 'pending_payment';
                        $address = $response['address'];
          				updateCachedOrderAddress($status, $response['address'],  $order->order_id);
						module_load_include('inc', 'ccStore', 'includes/cc-php/service');
						$commands[] = fillPaymentWrapper($result['cc_coinname_full'],$result['cc_coinname_short'], $result['cc_coin_amount']);
  						ajax_render($commands);
                      $result['cc_queue_id'] = $queue_id;
                      $result['cc_pay_status'] = $status;
                      $result['cc_address'] = $response['address'];
                    }
                    break;
                case 'partial_payment_received':
                case 'pending_payment':
                  $response = ccApiOrderStatus($queue_id, $result['cc_coinname_short']);
                  if (isset($response['balance']) AND $response['balance'] != FALSE) {
                      $balance = floatval($response['balance']);
                      if(($balance > floatval('0.00000000'))) {
                          if($balance >= floatval($result['cc_coin_amount'])) {
                              $status = 'payment_received';
                          } else {
                              $status = 'partial_payment_received';
                          }
                      } else {
                          $status = 'pending_payment';
                      }
                      if($status == 'payment_received') {
                          try {
                              $data = 'Currency: '.$result['cc_coinname_full'];
                              $payment_details = uc_payment_enter($result['order_id'], 'checkoutcrypto', $order->order_total, 0, $data, NULL);
                              uc_cart_complete_sale($order);
                              $status = 'payment_entered';
                        } catch (exception $e) {
                              //    watchdog('cc_order_status', 'Could not complete sale. !fault', $e->getMessage());
                              }
                      }
						updateCachedPayment($status, $queue_id, $balance, $order->order_id);

                      $result['cc_queue_id'] = $queue_id;
                      $result['cc_pay_status'] = $status;
                      $result['cc_pay_amount'] = $balance;
                  
                 } else {
                        $request['address'] = $result['cc_address'];
                        $request['coin_amount'] = $result['cc_coin_amount'];
                        $request['coin_name'] = $result['cc_coinname_short'];
						try {
        
                            $response = ccApiAddressBalance($request);
                            $queue_id = $response['queue_id'];
                            db_update('uc_payment_cc')
                              ->fields(array(
                                'cc_queue_id_tmp' => $queue_id,
                               ))
                              ->condition('order_id', $order->order_id, '=')
                              ->execute();
                        } catch (exception $e) {
                            watchdog('cc_order_status', 'Could not update queue_id in database: fault', $e->getMessage());
                        }
                  }
                  break;

                default:
                  break;
            }
        }
        return $result;
    } else {
        return FALSE;
    }
}

/***********************
*  QUERIES
**********************/
/*
*  Get our queued recipt for the the client order
*/
function getCachedOrder($orderid){
   try {
    $result = db_select('uc_payment_cc')
      ->fields('uc_payment_cc', array(
        'order_id',
        'cc_coinname_short',
        'cc_coinname_full',
        'cc_coin_amount',
        'cc_address',
        'cc_pay_status',
        'cc_queue_id',
        'cc_queue_id_tmp',
        'cc_pay_amount',
        'timestamp'))
      ->condition('order_id', $orderid, '=')
      ->execute()
      ->fetchAssoc();
      } catch (exception $e) {
       $result = FALSE;
      }
	return $result;
}

function checkOrderExists($orderid){
      try {
      $hasOrder = db_select('uc_payment_cc')
        ->fields('uc_payment_cc', array(
          'order_id'))
        ->condition('order_id', $orderid, '=')
        ->execute()
        ->fetchAssoc();
      } catch (exception $e) {
        //  watchdog('uc_payment_method_cc', 'Could not select order info from database: !fault', $e->getMessage());
      }
		return $hasOrder;
}


function createCachedOrder($orderid, $rate, $coin_name, $coin_name_full, $coin_amount, $queue_id, $status){
	try {
      db_insert('uc_payment_cc')->fields(array(
                'order_id' => $orderid,
                'exchange_rate' => $rate,
                'cc_coinname_short' => $coin_name,
                'cc_coinname_full' => $coin_name_full,
                'cc_coin_amount' => $coin_amount,
                'cc_queue_id' => $queue_id,
                'cc_queue_id_tmp' => $queue_id,
                'cc_pay_status' => $status,
              ))->execute();
	 } catch (exception $e) {
	 	  watchdog('createCachedOrder', 'Could not insert order into database: !fault', $e->getMessage());
	 	return FALSE;
	}
}

function updateCachedOrder($address, $coin, $amt, $orderid){
	try {
		$request['address'] = $address;
		$request['coin_amount'] = $amt;
		$request['coin_name'] = $coin;
		$response = ccApiAddressBalance($request);
		$queue_id = $response['queue_id'];
		db_update('uc_payment_cc')
		->fields(array(
		  'cc_queue_id_tmp' => $queue_id,
		))
	  ->condition('order_id', $orderid, '=')
	  ->execute();
	} catch (exception $e) {
	 watchdog('updateCachedOrder', 'Could not update queue_id in database: fault', $e->getMessage());
	}
}

function updateCachedOrderAddress($status, $address, $orderid){
	try {
		db_update('uc_payment_cc')
			->fields(array(
			'cc_pay_status' => $status,
			'cc_address' => $address,
			))
	  	 ->condition('order_id', $orderid, '=')
	  	->execute();
	} catch (exception $e) {
	   watchdog('updateCachedOrderAddress', 'Could not update order in database: !fault', $e->getMessage());
	 }
}


function updateCachedPayment($status, $queue_id, $balance, $orderid){
	try {
 		db_update('uc_payment_cc')
            ->fields(array(
             'cc_pay_status' => $status,
             'cc_queue_id_tmp' => $queue_id,
            'cc_pay_amount' => $balance,
              ))
             ->condition('order_id', $orderid, '=')
             ->execute();
	} catch (exception $e) {
	   watchdog('updateCachedPayment', 'Could not update order in database: !fault', $e->getMessage());
	 }
}

function addCoin($coin_name, $coin_code, $coin_rate){
          try {
              $result = db_merge('cc_coins')
				->key(array('coin_code' => $coin_code))
				->insertFields(array(
                'coin_code' => $coin_code,
				'coin_name' => $coin_name,
				'coin_image' => '/checkoutcrypto/'.strtolower($coin_name).'.png',
      			'coin_confirm' => '1',
                'rate' => $coin_rate,
				'timestamp' => '',
              ))
			->updateFields(array(
                'coin_code' => $coin_code,
				'coin_name' => $coin_name,
                'coin_confirm' => '1',
				'rate' => $coin_rate,
				'timestamp' => '',
				))

			 ->execute();
          } catch (exception $e) {

                watchdog('cc_coins', 'Could not insert coin into database: !fault', $e->getMessage());
                return FALSE;
        }
	return true;
}


/*
*   Generate QR with a bitcoin address, default size = 150
*/
function generateQR($address, $size){
    $url_qr_base = 'https://chart.googleapis.com/chart?cht=qr';
    $url_qr_args = '&chs='.$size;
    $url_qr_args .= '&choe=UTF8';
    $url_qr_args .= '&chld=L';
    $url_qr_args .= '&chl='.$address;
    $url_qr = $url_qr_base.$url_qr_args;
    $url_qr_output = '<img src="'.$url_qr.'">';
	return $url_qr_output;
}

/***********************
*  RATES!
**********************/

/*
*  Request rate for the preferred coin, 
*  if it doesn't exist in the database, 
*   go retrieve it from Checkoutcrypto API
*/
function ccStore_exchange_rate($order) {

  $enabled_coins = array();
  $coins = getAvailableCoins();
  foreach($coins as $coin) {
    $enabled_coins[] = strtoupper($coin['coin_code']);
  }

  try {
     $result = db_select('ccdev_coins')
        ->fields('cc_coins', array(
          'coin_code',
          'rate'))
        ->condition('coin_code', $order->cc_coinname_short, '=')
        ->condition('timestamp', (time()-900), '>=') //cache no more than 15 min
        ->range(0,1)
        ->execute()
        ->fetchAssoc();
  } catch (exception $e) {
      watchdog('ccStore_exchange_rate', 'Could not query database: !fault', $e->getMessage());
  }
  if(isset($result['rate'])) {
    return $result['rate'];
  } else {
      if(isset($order->cc_coinname_short)) {
          $request['coin_name'] = $order->cc_coinname_short;
      } else {
          watchdog('ccStore_exchange_rate', 'Unable to determine coin', WATCHDOG_ERROR);
          return FALSE; //coin could not be determined
      }
      $response = ccApiExchangeRate($request);
      $rate = $response['rate'];
  }

  if (!$rate || !is_numeric($rate)) {
    watchdog('ccStore_exchange_rate', 'Unable to get current exchange rate', WATCHDOG_ERROR);
    $rate = FALSE;
  }
  return $rate;
}

/**
 * Convert an orders balance to cryptocurrency
 *
 * @param $order
 */
function ccStore_payment_amount_to_coin($order) {
  //Check if order exists
  try {
      $result = db_select('uc_payment_cc')
        ->fields('uc_payment_cc', array(
          'cc_coinname_short',
          'cc_coin_amount'))
        ->condition('order_id', $order->order_id, '=')
        ->condition('cc_coinname_short', $order->cc_coinname_short, '=')
        ->execute()
        ->fetchAssoc();
  } catch (exception $e) {
    //  watchdog('uc_cc_payment_amount_to_coin', 'Could not query database: !fault', $e->getMessage());
  }

  //Don't calculate new rate if cc_coin_amount is already set and coin is the same
  if(isset($result['cc_coin_amount']) AND ($order->cc_coinname_short == $result['cc_coinname_short'])) {
    return $result['cc_coin_amount'];
  } else {
    //Get current exchange rate
    $rate = ccStore_exchange_rate($order);
    $coin_total = round($order->order_total / $rate, 4, PHP_ROUND_HALF_UP);
    return $coin_total;
  }

  return FALSE;
}



/***********************
*  ccStore vs UC_CC
**********************/
/*
*  Grab User's enabled coin types 
*/
function getCoinRate($coin){
global $user;
    $result = db_select('cc_coins')
      ->fields('ccdev_coin', array(
        'rate'))
      ->condition('coin_code', $coin, '=')
      ->execute()
      ->fetchAssoc();
    if(isset($result)) {
		return $result['rate'];
	}
}

/*
*  Grab User's enabled coin types 
*/
function getAvailableCoins(){
	$AllCoin = array();
	$ClientCoins = array();
	$query = db_select('cc_coins', 'u');
	$query->fields('u', array('coin_code', 'coin_name', 'rate','coin_image'));
   	$result = $query->execute();
	foreach($result as $cn){
		$ClientCoins['coin_code'] = $cn->coin_code;
		$ClientCoins['coin_name'] = $cn->coin_name;
		$ClientCoins['rate'] = $cn->rate;
		$ClientCoins['coin_image'] = $cn->coin_image;
		array_push($AllCoin, $ClientCoins);
	}
	return $AllCoin;
}

