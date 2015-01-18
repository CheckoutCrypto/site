<?php

function _ccService_make_link($args = '') {

    $fee = (float)0.01;
    $txfee = (float)0.01;
    drupal_add_js(drupal_get_path('module','ccService').'/theme/ccService.js');
    drupal_add_js(array('ccService' => array('fee' => $fee,'txfee' => $txfee)), array('type' => 'setting'));

// Set a default value if no text in supplied.
  if (!(empty($args))) {
     $link_text = $args['title'];
     $group = $args['group'];
   } else {
     return FALSE;
   }
   return '<div id="'.$group.'-modal-link">' . l($link_text, 'ccService/nojs/'.$group, array('attributes' => array('class' => 'ctools-use-modal'))) . '</div>';
 }

/*
*  Select Service Order
*/
function getOrder($userid, $grpid){
	$date = date("Y-m-d H:m:s", strtotime('-1 hours', time()));
	$order = array();
    $result = db_select('payment_cc')
      ->fields('payment_cc', array(
        'order_id',
		'user_id',
		'grp_id',
		'coin_name',
		'coin_code',
		'coin_address',
		'coin_amount',
		'pay_status',
		'pay_amount',
		'queue_id',
		'queue_address',
		'exchange_rate',
		'timestamp'	))
      ->condition('user_id', $userid, '=')
      ->condition('grp_id', $grpid, '=')
      ->condition('pay_status', 'payment_complete', '!=')
      ->execute()
      ->fetchAssoc();
    if(isset($result['order_id'])) {
		$order['order_id'] = $result['order_id'];
		$order['user_id'] = $result['user_id'];
		$order['grp_id'] = $result['grp_id'];

		$order['coin_name'] = $result['coin_name'];
		$order['coin_code'] = $result['coin_code'];
		$order['coin_amount'] = $result['coin_amount'];
		$order['coin_address'] = $result['coin_address'];

		$order['pay_status'] = $result['pay_status'];
		$order['pay_amount'] = $result['pay_amount'];

		$order['queue_id'] = $result['queue_id'];
		$order['queue_address'] = $result['queue_address'];

		$order['exchange_rate'] = $result['exchange_rate'];
		$order['timestamp'] = $result['timestamp'];

		return $order;
	}

}

/*
*  Insert Service Order
*/
function addOrder($status, $userid, $grpid, $amount, $coin, $rate){
	try {
		  db_insert('payment_cc')->fields(array(
        'order_id' => '0',
        'user_id' => $userid,
        'grp_id' => $grpid,
		'coin_name' => $coin,
		'coin_code' => $coin,
		'coin_address' => '',
		'coin_amount' => $amount,
		'pay_status' => $status,
		'pay_amount' => '0.0',
		'queue_id' => '',
		'queue_address' => '',
		'exchange_rate' => $rate,
		'timestamp' => date("Y-m-d H:i:s"),
		  ))->execute();

	  } catch (exception $e) {
		  watchdog('payment_cc', 'Could not insert order into database: !fault', $e->getMessage());
		  return FALSE;
	  }
}

/*
*  Update Service Order
*/
function updateOrder($basicid, $userid, $grpid, $queueid, $amt, $Received, $coincode, $status){
           try {
                db_update('payment_cc')
                    ->fields(array(
						'pay_status' => $status,
						'queue_id' => $queueid,
						'coin_amount' => $amt,
						'pay_amount' => $Received,
						'coin_code' => $coincode,
                    ))
                    ->condition('order_id', $basicid, '=')
                    ->condition('user_id', $userid, '=')
                    ->condition('grp_id', $grpid, '=')
                    ->execute();
            } catch (exception $e) {
                 watchdog('payment_cc', 'Could not update pending_otp: !fault', $e->getMessage());
                return FALSE;
            }
}

/*
*  Update Service Order
*/
function updateOrderAddress($basicid, $userid, $grpid, $queue_address, $address, $amtReceived, $status){
           try {
                db_update('payment_cc')
                    ->fields(array(
						'coin_address' => $address,
						'pay_status' => $status,
						'pay_amount' => $amtReceived,
						'queue_address' => $queue_address,
						'timestamp' => date("Y-m-d H:i:s"),
                    ))
                    ->condition('order_id', $basicid, '=')
                    ->condition('user_id', $userid, '=')
                    ->condition('grp_id', $grpid, '=')
                    ->execute();
            } catch (exception $e) {
                 watchdog('payment_cc', 'Could not update pending_otp: !fault', $e->getMessage());
                return FALSE;
            }
}

/*
* Get All a User's Coins + Balances
*/
function getAllUserCoin(){
	global $user;

	$AllCoin = array();
	$ClientCoins = array();
	try {
	$result = db_select('ccdev_balance')
		  ->fields('ccdev_balance', array('coin_code', 'coin_name', 'coin_balance'))
		  ->condition('uid', $user->uid, '=')
		    ->range(0,10) //max 10 results
		    ->execute();
	  } catch (exception $e) {
		  watchdog('ccdev_balance', 'Could not query database: !fault', $e->getMessage());
	  }
	while ($rows = $result->fetchAssoc()) {
	  if(is_array($rows) AND count($rows) > 0) { //check that object is array and populated
		  if(isset($rows['coin_balance']) AND isset($rows['coin_code'])) {
			$ClientCoins[$rows['coin_code']]['coin_code'] = $rows['coin_code'];
			$ClientCoins[$rows['coin_code']]['coin_name'] = $rows['coin_name'];
			$ClientCoins[$rows['coin_code']]['coin_balance'] =$rows['coin_balance'];
			array_push($AllCoin, $ClientCoins[$rows['coin_code']]); 
			}
		}
	}
	return $AllCoin;
}

/*
*  Grab User's Balance for enabled coin  
*/
function getBalanceByCoin($coin){
global $user;
    $result = db_select('ccdev_balance')
      ->fields('ccdev_balance', array(
        'coin_balance'))
      ->condition('coin_code', $coin, '=')
      ->condition('uid', $user->uid, '=')
      ->execute()
      ->fetchAssoc();
    if(isset($result)) {
		return $result['coin_balance'];
	}
}

/*
* Get User API Key so we can grab an address to deposit to their wallet.
*/
function getUserKey(){
	global $user;

	try {
     $result = db_select('ccdev_accounts')
        ->fields('ccdev_accounts', array(
          'api_key'))
        ->condition('user_id', $user->uid, '=')
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

/*
*  Determine the SKU of a given order, for our service charges we need the Group SKU
*/
function getGroupBySKU($orderid){

try {
    $result = db_select('uc_order_products')
      ->fields('uc_order_products', array(
        'model'))
      ->condition('order_id', $orderid, '=')
        ->execute()
      ->fetchAssoc();
  } catch (exception $e) {
      watchdog('uc_order_products', 'Could not query database: !fault', $e->getMessage());
  }
    if(isset($result['model'])) {
		$model = $result['model'];
		$final = db_select('ccdev_groups')
      ->fields('ccdev_groups', array(
        'basic_id'))
      ->condition('grp_SKU', $model, '=')
      ->execute()
      ->fetchAssoc();
 		if(isset($final)) {
			return $final['basic_id'];
		}
	}
}

/*
*  SANITIZE AJAX
*/  

function sanitizeType(){
	
	if(isset($_POST['type'])){
		if(preg_match("/^[A-Za-z]+$/i", $_POST['type'])){
			return $_POST['type'];
		}
	}
}

function sanitizeCoin(){
	if(isset($_POST['coin'])){
		if(preg_match("/^[A-Za-z_]+$/i", $_POST['coin'])){
				$coin = strtoupper(substr($_POST['coin'], 8, strlen( $_POST['coin'])));
			return $coin;
		}
	}
}

function sanitizeGroup(){
	if(isset($_POST['grp'])){
		 if(preg_match("/^[0-9]{0,}+$/", $_POST['grp'])){
			return $_POST['grp'];
		}
	}
}
