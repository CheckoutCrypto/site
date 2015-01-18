<?php

/*
*  Grab User's enabled coin types 
*/
function getAvailableCoins(){
	$AllCoin = array();
	$ClientCoins = array();
	$query = db_select('ccdev_coin', 'u');
	$query->fields('u', array('coin_code', 'coin_name', 'coin_rate','coin_image'));
   	$result = $query->execute();
	foreach($result as $cn){
		$ClientCoins['coin_code'] = $cn->coin_code;
		$ClientCoins['coin_name'] = $cn->coin_name;
		$ClientCoins['rate'] = $cn->coin_rate;
		$ClientCoins['coin_image'] = $cn->coin_image;
		array_push($AllCoin, $ClientCoins);
	}
	return $AllCoin;
}


function _ccSend_make_link($args = '') {

    $fee = (float)0.01;
    $txfee = (float)0.01;
    drupal_add_js(drupal_get_path('module','ccSend').'/js/ccSend.js');
    drupal_add_js(array('ccSend' => array('fee' => $fee,'txfee' => $txfee)), array('type' => 'setting'));

// Set a default value if no text in supplied.
  if (!(empty($args))) {
     $link_text = $args['title'];
     $coin_code = $args['coin_code'];
   } else {
     return FALSE;
   }
   return '<div id="'.$coin_code.'-modal-link">' . l($link_text, 'ccSend/email/nojs/'.$coin_code, array('attributes' => array('class' => 'ctools-use-modal'))) . '</div>';
 }

function otp_insert($args){


    try {
        $result = db_insert('ccdev_otp')->fields(array(
				'bundle_type' => 'otp_bundle',
                'uid' => $args['uid'],
        		'coin_name' => $args['coin_name'],
        		'coin_code' => $args['coin_code'],
        		'coin_amount' => $args['coin_amount'],
      		  	'coin_address' => $args['coin_address'],
       		 	'callback_action' => $args['callback_action'],
				'sent' => '1',
				'valid' => '0',
			 	'created' => date("Y-m-d H:i:s"),
       		 	'secret' => $args['secret'],
        		'data' => $args['data'],
            ))
            ->execute();
        } catch (exception $e) {
            var_dump($e);
            break;
            watchdog('ccdev_otp', 'Could not insert OTP Gen into database: !fault', $e->getMessage());
            return FALSE;
        }
		return $result;
}
/**
 * Write New Send Funds entry
 */
function writeSendFunds($entity){
global $user; 
$date = date("Y-m-d H:m:s", strtotime('-1 hours', time()));
try {
        $result = db_insert('ccdev_send')->fields(array(
                        'bundle_type' =>  'Send_bundle',
                        'uid' => $user->uid,
						'otp_id' => '0',
                        'recip_email' => $entity->recip_email,
                        'recip_name' => $entity->recip_name,
                        'recip_msg' => $entity->recip_msg,
                        'coin_code' => $entity->coin_code,
                        'coin_amt' => $entity->coin_amt,
                        'recip_address' => '0',
                        'sent' => $date,
                        'retrieved' => $entity->retrieved,
            ))
            ->execute();
        } catch (exception $e) {
                var_dump($e);
                break;
		}
		return $result;
}

/**
 * update insert Send Funds Entry
 */
function updateSendFundsOTP($otp_insert, $basic_id){

 	try {
          db_update('ccdev_send')->fields(array(
            'otp_id' => $otp_insert,
          ))
		->condition('basic_id', $basic_id, '=')
		->execute();
      } catch (exception $e) {
            watchdog('ccdev_send', 'Could not update sendfunds in database: !fault', $e->getMessage());
            return FALSE;
      }
}


/**
 * update insert Send Funds Entry
 */
function updateSendFunds($basic_id, $address){

 	try {
          db_update('ccdev_send')->fields(array(
            'recip_address' => $address,
            'retrieved' => date("Y-m-d H:i:s"),
          ))
		->condition('otp_id', $basic_id, '=')
		->execute();
      } catch (exception $e) {
            watchdog('ccdev_send', 'Could not update sendfunds in database: !fault', $e->getMessage());
            return FALSE;
      }
}

/**
 * generate OTP URL
 */
function get_otp_url($signature, $basic_id) {
    global $base_url;
    $url = $base_url.'?q=ccSend/auth/'.$signature.'/id='. $basic_id;
    return $url;
}

/**
 * Database Write and generate OTP settings, send email
 */
function writeOTP($entity, $sendFundID){
		module_load_include('inc', 'ccOTP', 'includes/mail');
		module_load_include('inc', 'ccOTP', 'includes/lib');
		global $user;
        $action = 'send_funds';
   		$dbArgs = array();
        $args = array('action' => $action);
        $otpArgs = ccOTP_otp_generate($args);
        //Generate the address to send to user via email
        $dbArgs['uid'] = $user->uid;
        $dbArgs['callback_action'] = $action;
        $dbArgs['secret'] = $otpArgs['secret'];
        $dbArgs['data'] = $otpArgs['data'];
        $dbArgs['coin_name'] = $entity->coin_code;
        $dbArgs['coin_code'] = $entity->coin_code;
        $dbArgs['coin_amount'] = $entity->coin_amt;
        $dbArgs['coin_address'] = '';

		 $inserted = otp_insert($dbArgs);
        if(isset($inserted)) {
			updateSendFundsOTP($inserted, $sendFundID); 
       		 $url = get_otp_url($otpArgs['signature'], $inserted);
            if($url) {
                $dbArgs['mail'] = $entity->recip_email;
                $dbArgs['otp_url'] = $url;
                $dbArgs['otp_type'] = 'send_funds';
                $dbArgs['subject_tag'] = 'Send Funds';
				$dbArgs['mail_msg'] = $entity->recip_msg;
				$dbArgs['mail_recip_name'] = $entity->recip_name;
                ccOTP_mail_send($dbArgs);
				return true;
            }
        } 
	return false;
}

/*
*  Sanitize Send by Email Form
*/
function sanitizeEmail($email){
	if(!empty($email)) {
		if (filter_var($email, FILTER_VALIDATE_EMAIL)) {	
			return true;
		}
	}
	return false;
}

function sanitizeName($name){
	if(!empty($name)) {
		if(preg_match("/^[A-Z0-9]+$/i", $name) && strlen($name) <= 30){
					return true;
		}
	}
	return false;
}

function sanitizeMsg($msg){
	if(!empty($msg)) {
		if(preg_match("/^[A-Z0-9,.\'?:;-_=+!@#$%^&()\s*]+$/i", $msg) && strlen($name) < 250){
					return true;
		}
	}
	return false;
}

function sanitizeAmount($amt){
	if(!empty($amt)) {
        	if(preg_match("/^[0-9]{0,}\.[0-9]{1,8}|[0-9]{1,}+$/", $amt)) {
				return true;	
		}
	}
	return false;
}

function sanitizeAmountSize($amt, $coin_code){
		module_load_include('inc', 'ccCoin', 'includes/cc-php/lib');
		$coindata = getCoinData($coin_code);
		
		if($amt <= $coindata['max_amount']){
			if($amt >= $coindata['min_amount']){
			}else{
				return $coindata['min_amount'];
			}
		}else {
				return $coindata['max_amount'];	
		}
}

function verifyBalance($amount, $coincode, $user){
    module_load_include('inc', 'ccBalance', 'includes/cc-php/lib');
	 $balance = getBalance($user, $coincode);
	 $calcTotal = calcTotal($amount, $coincode, $user);
	if(!empty($balance) AND $balance > $calcTotal){
		return true;
	}else{
		return $balance;
	} 
}

