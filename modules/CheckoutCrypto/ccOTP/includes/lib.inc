<?php


/* Generate Random Password */
function random_password($length) {
  $chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_-=+;:,.?";
  $password = substr( str_shuffle( $chars ), 0, $length );
  return $password;
}

//// Generate OTP 
function ccOTP_otp_generate($args) {
  $gen = array();

  //Generate a random secret key for this instance
  $secret = random_password(32);
  $gen['secret'] = base64_encode($secret);

  //Generate string for url request
  $data = random_password(16);
  $gen['data'] = base64_encode($data); //store the data to verify later

  $message = hash_hmac('sha256', $data, $secret);
  $gen['signature'] = urlencode(base64_encode($message));

  return $gen;
}

/// Insert new OTP, merge/update if exists, return inserted ID
function ccOTP_otp_insert($args) {
                $date = date("Y-m-d H:i:s");

        try {
            $result = db_select('ccdev_auth')
              ->fields('ccdev_auth', array(
               'pending_otp'))
              ->condition('user_id', $args['uid'], '=')
              ->execute()
              ->fetchAssoc();
        } catch (exception $e) {
             watchdog('ccdev_auth', 'Could not select pending_otp from ccdev_auth !fault', $e->getMessage());
            return FALSE;
        }
        
        if(isset($result['pending_otp']) AND intval($result['pending_otp']) <= 10) {
            try {
                db_update('ccdev_auth')
                    ->fields(array(
                        'pending_otp' => '1',
                    ))
                    ->condition('user_id', $args['uid'], '=')
                    ->execute();
            } catch (exception $e) {
                 watchdog('ccdev_auth', 'Could not update pending_otp: !fault', $e->getMessage());
                return FALSE;
            }
        }

        try {
              $result = db_merge('ccdev_otp')
				->key(array('coin_code' => $args['coin_code'], 'uid' => $args['uid'], 'uid' => $args['uid'], 'callback_action' => $args['callback_action']))
				->insertFields(array(
				'bundle_type' => 'otp_bundle',
                'uid' => $args['uid'],
        		'coin_name' => $args['coin_name'],
        		'coin_code' => $args['coin_code'],
        		'coin_amount' => $args['coin_amount'],
      		  	'coin_address' => $args['coin_address'],
       		 	'callback_action' => $args['callback_action'],
				'sent' => '1',
				'valid' => '0',
			 	'created' => $date,
       		 	'secret' => $args['secret'],
        		'data' => $args['data'],
              ))
			->updateFields(array(
        		'coin_code' => $args['coin_code'],
        		'coin_amount' => $args['coin_amount'],
      		  	'coin_address' => $args['coin_address'],
					//'sent' => +1,
					'valid' => '0',
                 	'created' => $date,
        			'secret' => $args['secret'],
        			'data' => $args['data'],
				))

			 ->execute();
          } catch (exception $e) {
                watchdog('ccdev_otp', 'Could not insert OTP Gen into database: !fault', $e->getMessage());
                return FALSE;
          }
        //// get the basic_id of our newly created OTP
        try {
            $result = db_select('ccdev_otp')
              ->fields('ccdev_otp', array(
               'basic_id'))
              ->condition('created', $date, '=')
              ->execute()
              ->fetchAssoc();
        } catch (exception $e) {
             watchdog('ccdev_otp', 'Could not select pending_otp from ccdev_otp');
            return FALSE;
        }
          if(isset($result)) {
                return $result['basic_id'];
          }
}

/// UPDATE OTP set valid
function ccOTP_otp_setValid($args) {
    global $user;
    try {
        db_update('ccdev_otp')
            ->fields(array(
			    'valid' => '1',
            ))
            ->condition('basic_id', $args['basic_id'], '=')
            ->condition('coin_code', $args['coin_code'], '=')
            ->execute();
    } catch (exception $e) {
        watchdog('ccdev_otp', 'Could not insert order into database: !fault', $e->getMessage());
        return FALSE;
    }

  return TRUE;
}

/// validate auth method change
function ccOTP_validateAuth($userid){
		    try {
		        db_update('ccdev_auth')->fields(array(
		         'validated' => 1,
		       ))
		       ->condition('user_id', $userid, '=')
		       ->execute();
		    } catch (exception $e) {
		        //var_dump($e);
				return false;

		    }
	return true;
}

///  Decode OTP and verify
function ccOTP_otp_decode($args) {
    $signature = base64_decode(urldecode($args['signature'])); //urldecode must happen before base64_decode
    $secret = base64_decode($args['secret']);
    $data = base64_decode($args['data']);

    $msg = hash_hmac('sha256', $data, $secret);

    if($signature == $msg) {
        return TRUE;
    }
}

///  Generate OTP Auth URL
function ccOTP_otp_get_auth_url($signature, $basic_id) {
    global $base_url;
    $url = $base_url.'?q=ccSend/auth/'.$signature.'/id='. $basic_id;
    return $url;
}

/// get specific user's API key
function getSpecificApiKey($uid){
  try {
      $validType = array();
      $result = db_select('ccdev_accounts')
        ->fields('ccdev_accounts', array(
          'api_key',
		 'walletname'))
        ->condition('user_id', $uid, '=')
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


function gen_two_factor() {
    global $user;

    module_load_include('inc','ccOTP','includes/GAuth/GoogleAuthenticator');
	$ga = new PHPGangsta_GoogleAuthenticator();
    $secret = $ga->createSecret();

    if($secret) {
        return $secret;
    }

    return FALSE;
}

function validate2Factor($userid, $secret, $twofa){
	module_load_include('inc','ccOTP','includes/GAuth/GoogleAuthenticator');
	$ga = new PHPGangsta_GoogleAuthenticator();
	$checkResult = $ga->verifyCode($secret, $twofa, 2);  
	if ($checkResult) {
	    return TRUE;
	}

    return FALSE;
}


function get_otp_type($userid){
  //get the user's preferred OTP method and secret key
  try {
      $validType = array();
      $result = db_select('ccdev_auth')
        ->fields('ccdev_auth', array(
          'pref_otp',
          'validated',                
          'twofa_key'))
        ->condition('user_id', $userid, '=')
        ->range(0,1)
        ->execute()
      ->fetchAssoc();
  } catch (exception $e) {
      watchdog('ccdev_auth', 'Could not query database: !fault', $e->getMessage());
  }
  if(isset($result)) {
	$validType['pref_otp'] = $result['pref_otp'];
    $validType['twofa_key'] = $result['twofa_key'];
    $validType['validated'] = $result['validated'];
    return $validType;
  }
  return FALSE;
}

function update_otp_pref($otp_pref, $secret, $validated, $userid){
    try {
        db_merge('ccdev_auth')
          ->key(array('user_id' => $userid))
          ->insertFields(array(
            'bundle_type' => 'ccdev_auth',
            'pref_otp' => $otp_pref,
            'twofa_key' => $secret,
            'validated' => $validated,
            'user_id' => $userid,
          ))
          ->updateFields(array(
            'twofa_key' => $secret,
            'pref_otp' => $otp_pref,
            'validated' => $validated,
          ))
          ->execute();
    } catch (exception $e) {
         watchdog('ccdev_auth', 'Could not merge otp update: !fault', $e->getMessage());
        return FALSE;
    }
}

function set_otp_pref($otp_pref){
	module_load_include('inc', 'ccOTP', 'includes/mail');
    global $user;
    $validated = 0;
   $otpDetails = get_otp_type($user->uid);

    if($otp_pref == 'twofa') {
        $secret = $otpDetails['twofa_key'];

        if(!($secret)) {
            $secret = gen_two_factor();
            $validated = 0;
        }
    } else {
        $otp_pref = 'email';
        $secret = '';
        $validated = 1;
    }

    $otp_current = $otpDetails['pref_otp'];
    if($otp_pref != $otp_current && isset($otp_current)) { //if NULL then user just registered
        $validated = 0;

        $action = 'auth_change_'.$otp_pref;
        $args = array('action' => $action);
        $otpArgs = ccOTP_otp_generate($args);

        $dbArgs['uid'] = $user->uid;
        $dbArgs['callback_action'] = $action;
        $dbArgs['secret'] = $otpArgs['secret'];
        $dbArgs['data'] = $otpArgs['data'];
        $dbArgs['coin_name'] = '';
        $dbArgs['coin_code'] = '';
        $dbArgs['coin_amount'] = 0;
        $dbArgs['coin_address'] = '';
		
		$inserted = ccOTP_otp_insert($dbArgs);
        if(isset($inserted)) {
       		 $url = ccOTP_otp_get_auth_url($otpArgs['signature'], $inserted);
            if($url) {
                $args = array();
                $args['mail'] = $user->mail;
                $args['otp_url'] = $url;
                $args['otp_type'] = 'auth_method';
                $args['subject_tag'] = 'Authentication method change';

                ccOTP_mail_send($args);
            }
        }
    }
	update_otp_pref($otp_pref, $secret, $validated, $user->uid);
}

function ccOTP_remove($user, $coin, $action, $id = null){
	try {
          $num_deleted = db_delete('ccdev_otp')
  		->condition('basic_id', $id)
  		->condition('uid', $user)
		->condition('coin_code', $coin)
		->condition('callback_action', $action)
  		->execute();
	}catch (exception $e) {
            watchdog('ccdev_otp', 'Could not remove OTP: !fault', $e->getMessage());
            return FALSE;
    }

        try {
            db_update('ccdev_auth')->fields(array(
             'pending_otp' => 0,
           ))
           ->condition('user_id', $user, '=')
           ->execute();
        } catch (exception $e) {
            //var_dump($e);
        }
	return true;
}

function sanitizeOTP($args){
 	if(!empty($args['signature'])) {
        	$uid = $args['signature'];
				if(preg_match("/^[A-Z0-9=]+$/i", $uid)){
				 	if(!empty($args['basic_id'])) {
						$id = $args['basic_id'];
						if(preg_match("/^[0-9]{1,10}+$/", $id)) {
							return true;
						}

					}
				}
	}


}

//// check if a requested OTP is a valid OTP in our database
function ccOTP_otp_validate($args) {
  $signature = $args['signature'];
/// reminder, sanitize basic_id
  global $user;
$date = date("Y-m-d H:m:s", strtotime('-1 hours', time()));
  //get all the current user's requests
  try {
      $result = db_select('ccdev_otp')
        ->fields('ccdev_otp', array(
 		  'uid',
          'coin_name',
          'coin_amount',
          'coin_code',
          'coin_address',
          'callback_action',
          'data',
          'secret'))
        ->condition('basic_id', $args['basic_id'], '=')
       ->condition('created', $date, '>=') //validity is 1 hour
        ->range(0,10) //max 10 results
        ->execute();
  } catch (exception $e) {
      watchdog('ccOTP_otp_validate', 'Could not query database: !fault', $e->getMessage());
  }
while ($rows = $result->fetchAssoc()) {
  if(is_array($rows) AND count($rows) > 0) { //check that object is array and populated
      if(isset($rows['data']) AND isset($rows['secret'])) {
          $args['signature'] = $signature;
          $args['secret'] = $rows['secret'];
          $args['data'] = $rows['data'];
          if(ccOTP_otp_decode($args)) {
              $return = array();
              $return['action'] = $rows['callback_action'];
              $return['basic_id'] =  $args['basic_id'];
              $return['uid'] = $rows['uid'];
              $return['coin_name'] = $rows['coin_name'];
              $return['coin_code'] = $rows['coin_code'];
              $return['coin_amount'] = $rows['coin_amount'];
              $return['coin_address'] = $rows['coin_address'];
              return $return; //success!
          }
      }
  }
}
  return FALSE;
}

//// get a specific coin's address validation address code
function getSpecificAddressCode($coin){
	global $user;
			/// query withdraw address code
			$query = new EntityFieldQuery();
			$query->entityCondition('entity_type', 'ccdev_coin')
			  ->entityCondition('bundle', 'coin_bundle')
			 ->propertyCondition('coin_code', $coin)
			  ->addMetaData('account', user_load($user->uid)); // Run the query as user 1.
			$result = $query->execute();
			  if (isset($result['ccdev_coin'])) {
				  $coin_nids = array_keys($result['ccdev_coin']);
				  $coins = entity_load('ccdev_coin', $coin_nids);
		      	foreach ($coins as $coin) {
					$coin_name = $coin->coin_name;
				  	$fee = $coin->coin_fee;
				  	$TxFee = $coin->coin_txfee;
					$minAmt = $coin->min_amount;
					$maxAmt = $coin->max_amount;
					$address_code = $coin->coin_validate;
		      	}
			}
	return $address_code;
}

//// check if an OTP exists at all in db
function ccOTP_otp_checkExists() {
  global $user;

  //get all the current user's requests
  try {
      $result = db_select('ccdev_otp')
        ->fields('ccdev_otp', array(
          'coin_name',
          'coin_amount',
          'coin_code',
          'coin_address',
          'callback_action',
          'data',
          'secret'))
        ->condition('uid', $user->uid, '=')
        ->range(0,1) //max 10 results
        ->execute();
  } catch (exception $e) {
      watchdog('ccOTP_otp_validate', 'Could not query database: !fault', $e->getMessage());
  }
while ($rows = $result->fetchAssoc()) {
  if(is_array($rows) AND count($rows) > 0) { //check that object is array and populated
      if(isset($rows['data']) AND isset($rows['secret']) ) {
              return $rows['sent']; //success!
      }
  }
}
}
