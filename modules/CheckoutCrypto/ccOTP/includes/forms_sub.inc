<?php

function otp_gauth_form_validate($form, &$form_state) {
    $twofa = $form_state['input']['gauth_code'];

    global $user;
    $otpDetails = get_otp_type($user->uid);
    $result = validate2Factor($user->uid, $otpDetails['twofa_key'], $twofa);
    if($result === TRUE) {
        try {
            db_update('ccdev_auth')->fields(array(
             'validated' => 1,
           ))
           ->condition('user_id', $user->uid, '=')
           ->execute();
        } catch (exception $e) {
            //var_dump($e);
        }

        $commands[] = ctools_modal_command_dismiss();
        $commands[] = ctools_ajax_command_redirect('user/'.$user->uid.'/edit');
        drupal_set_message('Successfully enabled two-factor authentication');

        print ajax_render($commands);
        drupal_exit();
    } else {
        form_set_error('gauth_code', t('Invalid code!'));
    }
}

function ccOTP_validate_form_submit($form, &$form_state) { 
	module_load_include('inc', 'ccBalance', 'includes/cc-php/validate');
	module_load_include('inc', 'ccBalance', 'includes/cc-php/api');
	module_load_include('inc', 'ccOTP', 'includes/lib');

	$args = array();
	$args['basic_id'] =$form_state['values']['basic_id'];
	$args['uid'] =$form_state['values']['uid'];
    	$args['coin_code'] = $form_state['values']['coin_code'];
    	$args['coin_amount'] = $form_state['values']['coin_amount'];
	if(isset($form_state['values']['coin_address'])){
   	 $args['coin_address'] = $form_state['values']['coin_address'];
	}
    	$args['action'] = $form_state['values']['action'];

		$form_state['otp_validated'] = true;

		if($args['action'] == "autopay"){
			global $user;
			autopay_insert($args['coin_code'],$args['coin_amount'], $args['coin_address']);
		    ccOTP_remove($user->uid,  $args['coin_code'],  $args['action'], $args['basic_id']);
		    $form_state['redirect'] = 'Balance';
		    drupal_set_message('Autopay request successfully validated.');
		} elseif($args['action'] == 'withdraw') {  /// withdraw
			global $user;
			ccOTP_otp_setValid($args);
		    $accountdata = getSpecificApiKey($user->uid);
		    $response = ccWithdrawRequest($accountdata['api_key'], $args['coin_address'], $args['coin_amount'], $args['coin_code']);
			$form_state['redirect'] = 'Balance';
		    drupal_set_message('Successfully authorized withdrawal');
		} elseif(substr($args['action'],0,12) == 'auth_change_') {
			global $user;
			ccOTP_validateAuth($user->uid);
		    ccOTP_remove($user->uid,  $args['coin_code'],  $args['action'], $args['basic_id']);
		    drupal_set_message('Successfully authorized authentication method change');
		    $form_state['redirect'] = 'user/'.$user->uid.'/edit';

		}elseif($args['action'] == 'send_funds') {
			$withdraw_address =  $args['coin_address'];
			$withdraw_amount =  $args['coin_amount'];

			$address_code = getSpecificAddressCode($args['coin_code']);
			$validAddress = checkAddress($withdraw_address, $address_code);

			if($validAddress == true){
			module_load_include('inc', 'ccSend', 'includes/cc-php/lib');
				ccOTP_otp_setValid($args);
				// ccOTP_remove($args['uid'],  $args['coin_code'],  $args['action'], $args['basic_id']);
				$accountdata = getSpecificApiKey($args['uid']);
				ccSendFundsRequest($accountdata['api_key'], $args['coin_address'], $args['coin_amount'], $args['coin_code']);
				ccOTP_remove($args['uid'], $args['coin_code'], $args['action'], $args['basic_id']);
				updateSendFunds($args['basic_id'], $args['coin_address']);
				drupal_set_message('Successfully Withdrew Funds!');
				$form_state['redirect'] = 'ccSend/complete';

			}else{
				form_set_error('withdraw_address', t('Error, incorrect address'));
			}
		}
}

function ccOTP_generate_form_submit($form, &$form_state) {
	module_load_include('inc', 'ccOTP', 'includes/lib');
    global $user;

	$formArgs = array();
    //$formArgs = $form_state['values']['input'];

    $formArgs['coin_name'] = 'Potcoin';
    $formArgs['coin_code'] = 'POT';
    $formArgs['coin_amount'] = 50;
    $formArgs['coin_address'] = "PWRV6C7nSnt9ywKoF5Ag3a37v8Q6KG6Wii";
    $formArgs['callback_action'] = 'withdraw';
	
    $args = array('action' => $formArgs['callback_action']);
    $otpArgs = ccOTP_otp_generate($args);

    //Build array to insert into database
    $dbArgs = array();
    $dbArgs['uid'] = $user->uid;
    $dbArgs['coin_name'] = $formArgs['coin_name'];
    $dbArgs['coin_code'] = $formArgs['coin_code'];
    $dbArgs['coin_amount'] = $formArgs['coin_amount'];
    $dbArgs['coin_address'] = $formArgs['coin_address'];
    $dbArgs['action'] = $formArgs['callback_action'];
    $dbArgs['secret'] = $otpArgs['secret'];
    $dbArgs['data'] = $otpArgs['data'];


		$inserted = ccOTP_otp_insert($dbArgs);
        if(isset($inserted)) {
       		 $url = ccOTP_otp_get_auth_url($otpArgs['signature'], $inserted);
            if($url) {
            //successfully inserted, send mail and inform user

            $form_state['otp_generated'] = TRUE;
            $form_state['otp_url'] = $url;
            $form_state['rebuild'] = TRUE;

            $args = array();
            $args['mail'] = $user->mail;
            $args['otp_url'] = $url;
            $args['coin_name'] = $formArgs['coin_name'];
            $args['coin_code'] = $formArgs['coin_code'];
            $args['coin_amount'] = $formArgs['coin_amount'];
            $args['coin_address'] = $formArgs['coin_address'];
            $args['subject_tag'] = $formArgs['callback_action'];

            ccOTP_mail_send($args);
        }
    }
}



