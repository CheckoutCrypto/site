<?php

/**
 * Form submit handler: Submits basic_add_form information.
 */
function OTP_form_submit($ajax, $data) {
	ctools_add_js('ajax-responder');
	ctools_include('modal');

	$commands[] = ctools_modal_command_dismiss();
	print ajax_render($commands);
	drupal_exit();
}

/**
 * Validation handler for ccdev_balance_add_form form.
 *
 * We pass things straight through to the Field API to handle validation
 * of the attached fields.
 */
function ccdev_balance_form_validate($form, &$form_state) {
  field_attach_form_validate('ccdev_balance', $form_state['values']['basic_entity'], $form, $form_state);
}

function withdraw_form_validate($form, &$form_state) {
    global $user;
	$minAmt = $form_state['values']['min_amount'];
	$maxAmt = $form_state['values']['max_amount'];
	$withdraw_amount = $form_state['input']['withdraw_amount'];
	$withdraw_address = $form_state['input']['withdraw_address'];
	$coin_address_code = $form_state['values']['coin_address_code'];
	$balance = $form_state['values']['total_balance'];

	if($form_state['values']['pref_otp'] == "twofa"){
		$pin = $form_state['values']['twofa_pin'];
        $otpArr = get_otp_type($user->uid);
        $twofa = $otpArr['twofa_key'];
        $validateTwoFact = ccValidateTwoFact($pin, $twofa);

		if($validateTwoFact == true){

		module_load_include('inc', 'ccBalance', 'includes/cc-php/validate');

		$result = checkAddress($withdraw_address, $coin_address_code);
			if($result == true){
				if($withdraw_amount > $balance) {
					form_set_error('withdraw_amount', t('Error, insufficient funds'));
				}
				if($withdraw_amount < $minAmt || $withdraw_amount > $maxAmt){
					form_set_error('withdraw_amount', t('Error, amount not within acceptable range'));
				}

			}else{
				form_set_error('withdraw_address', t('Error, incorrect address'));
			}
		}else{
				form_set_error('twofa_key', t('Error, incorrect pin'));
		}
	}else{

		module_load_include('inc', 'ccBalance', 'includes/cc-php/validate');

		$result = checkAddress($withdraw_address, $coin_address_code);
			if($result == true){
				if($withdraw_amount > $balance) {
					form_set_error('withdraw_amount', t('Error, insufficient funds'));
				}
				if($withdraw_amount < $minAmt || $withdraw_amount > $maxAmt){
					form_set_error('withdraw_amount', t('Error, amount not within acceptable range'));
				}

			}else{
				form_set_error('withdraw_address', t('Error, incorrect address'));
			}

	}

}


function autopay_form_validate($form, &$form_state) {
        global $user;
		$minAmt = $form_state['values']['min_amount'];
		$maxAmt = $form_state['values']['max_amount'];
        $autopay_amount = $form_state['input']['coin_autopay'];
        $autopay_address = $form_state['input']['coin_autoaddress'];
        $coin_address_code = $form_state['values']['coin_address_code'];
		$balance = $form_state['values']['total_balance'];

		if($form_state['values']['pref_otp'] == "twofa"){
		$pin = $form_state['values']['twofa_pin'];
	    $otpArr = get_otp_type($user->uid);
        $twofa = $otpArr['twofa_key'];

		$validateTwoFact = ccValidateTwoFact($pin, $twofa);
		if($validateTwoFact == true){

		module_load_include('inc', 'ccBalance', 'includes/cc-php/validate');
		$result = checkAddress($autopay_address, $coin_address_code);
			if($result == true){

				if($autopay_amount > $balance) {
					form_set_error('withdraw_amount', t('Error, insufficient funds'));
				}
				else if($autopay_amount > $maxAmt) {  // max autopay 1,00,000
					form_set_error('autopay_amount', t('Error, fee must be smaller than '.$maxAmt));
				}
				else if($autopay_amount < $minAmt ){
					form_set_error('autopay_amount', t('Error, fee must be larger than '.$minAmt));
				}

			}else{
				form_set_error('autopay_address', t('Error, invalid address'));
			}
		}else{
				form_set_error('twofa_key', t('Error, incorrect pin'));
		}
	}else{

		module_load_include('inc', 'ccBalance', 'includes/cc-php/validate');
		$result = checkAddress($autopay_address, $coin_address_code);
	
			if($result == true){

				if($autopay_amount > $balance) {
					form_set_error('withdraw_amount', t('Error, insufficient funds'));
				}
				else if($autopay_amount > $maxAmt) {  // max autopay 1,00,000
					form_set_error('autopay_amount', t('Error, fee must be smaller than '.$maxAmt));
				}
				else if($autopay_amount < $minAmt ){
					form_set_error('autopay_amount', t('Error, fee must be larger than '.$minAmt));
				}

			}else{
				form_set_error('autopay_address', t('Error, invalid address'));
			}
	}


}

/**
 * Form submit handler: Submits basic_add_form information.
 */
function autopay_form_submit($form, &$form_state) {
module_load_include('inc', 'ccOTP', 'includes/callback');
$address = $form_state['input']['coin_autoaddress'];
$amount = $form_state['input']['coin_autopay'];
$coin = $form_state['coincode'];
$coin_name = $form_state['values']['coin_name'];
$prefotp = $form_state['values']['pref_otp'];
  ctools_include('ajax');
  ctools_include('modal');
  ctools_add_js('ajax-responder');

if($prefotp == "twofa"){
  autopay_insert($coin, $amount, $address);

  $commands[] = ctools_modal_command_dismiss();
  $commands[] = ctools_ajax_command_redirect('Balance');
  drupal_set_message('autopay submitted successfully!');
}else{
   //Build array to insert into database
    $dbArgs = array();
	$dbArgs['coin_name'] = $coin_name;
	$dbArgs['coin_code'] = $coin;
	$dbArgs['coin_amount'] = $amount;
	$dbArgs['coin_address'] = $address;
	$dbArgs['callback_action'] = 'autopay';

    if(ccOTP_generate_callback($dbArgs)) {
        drupal_set_message('Autopay email sent. Check your email!');
    } else {
        drupal_set_message('Autopay email could not be sent!');
    }
    $commands[] = ctools_modal_command_dismiss();  
    $commands[] = ctools_ajax_command_redirect('Balance');  

}

  print ajax_render($commands);
  drupal_exit();
		
}
/**
 * Form submit handler: Submits basic_add_form information.
 */
function withdraw_form_submit($form, &$form_state) {
    module_load_include('inc', 'ccBalance', 'includes/cc-php/lib');
    module_load_include('inc', 'ccBalance', 'includes/cc-php/api');
    module_load_include('inc', 'ccOTP', 'includes/callback');
  $accountdata = getUserApiKey();
  $receiver = $form_state['values']['withdraw_address'];
  $sender = $accountdata['walletname'];
  $apikey = $accountdata['api_key'];
  $twofa = $form_state['values']['twofa_pin'];
  $amount = $form_state['values']['withdraw_amount'];
  $txfee = $form_state['values']['coin_txfee'];
  $ourfee = $form_state['values']['coin_fee'];
  	$coin_code = $form_state['coincode'];
	$coin_name = $form_state['values']['coin_name'];
	$pin = $form_state['values']['twofa_key'];
    $pref_otp = $form_state['values']['pref_otp'];
	$finalfee = ($amount * $ourfee)/100;
	$finalAmt = $finalFee + $amount;
    if($pref_otp == "email"){
    global $user;
    $dbArgs = array();

		$dbArgs['uid'] = $user->uid;
		$dbArgs['coin_name'] =  $coin_name;
		$dbArgs['coin_code'] =  $coin_code;
		$dbArgs['coin_amount'] = $amount;
		$dbArgs['coin_address'] = $receiver;
		$dbArgs['callback_action'] = 'withdraw';
		//// send email valid

     if(ccOTP_generate_callback($dbArgs)) {
        drupal_set_message('Withdraw Awaiting Confirmation, check your email!');
      } else {
        drupal_set_message('Withdraw email could not be sent!');
      }

      $commands[] = ctools_modal_command_dismiss();    
      $commands[] = ctools_ajax_command_redirect('Balance'); 

	  print ajax_render($commands);
	  drupal_exit();
    } else {

	  ctools_include('ajax');
	  ctools_include('modal');
	  ctools_add_js('ajax-responder');

	 $result  = ccWithdrawRequestTwoFact($apikey, $twofa, $receiver, $finalAmt, $coin_code);


	  $commands[] = ctools_modal_command_dismiss();
	  $commands[] = ctools_ajax_command_redirect('Balance');
	  drupal_set_message('Withdraw order submitted successfully!');

	  print ajax_render($commands);
	  drupal_exit();
	}
}


