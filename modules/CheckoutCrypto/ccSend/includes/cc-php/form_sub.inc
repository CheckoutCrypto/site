<?php


function send_funds_validate($form, &$form_state){

	module_load_include('inc', 'ccSend', 'includes/cc-php/lib');
	global $user;
	$coin_code = $form_state['values']['coin_code'];
	$coin_amt = $form_state['values']['coin_amt'];
	$email = $form_state['values']['recip_email'];
	$name = $form_state['values']['recip_name'];
	$msg = $form_state['values']['recip_msg'];

	$emailIn = sanitizeEmail($email);
	$balance = VerifyBalance($coin_amt, $coin_code, $user->uid);
	$nameIn = sanitizeName($name);
	$msgIn = sanitizeMsg($msg);
	$amtIn = sanitizeAmount($coin_amt); 
	$minMax = sanitizeAmountSize($coin_amt, $coin_code);


	if($emailIn != true){
		form_set_error('recip_email', t('Error, incorrect characters in input'));
	}
	if($nameIn != true){
		form_set_error('recip_name', t('Error, incorrect characters in input, A-Z, 0-9, Max 30 characters'));
	}
	if($amtIn != true){
		form_set_error('coin_amt', t('Error, incorrect characters in input, 0-9.00000'));
	}
	if($balance != true){
		form_set_error('coin_amt', t('Error, Balance contains insufficient funds'));
	}
	if(isset($minMax)){
		form_set_error('coin_amt', t('Error, Minimum for this coin is '). $minMax);
	}
	if($msgIn != true){
		form_set_error('recip_msg', t('Error, incorrect characters in input'));
	} 

	addEmailTrans($user->uid);
}

/**
 * Form submit handler: Submits basic_add_form information.
 */
function send_funds_submit($form, &$form_state) {
	global $user;
	module_load_include('inc', 'ccSend', 'includes/cc-php/lib');
	module_load_include('inc', 'ccAccount', 'includes/cc-php/lib');
 // $entity = $form_state['values']['basic_entity'];
  $entity->recip_name = $form_state['values']['recip_name'];
  $entity->recip_email = $form_state['values']['recip_email'];
  $entity->recip_msg = $form_state['values']['recip_msg'];
  $entity->coin_code = $form_state['values']['coin_code'];
  $entity->coin_amt = $form_state['values']['coin_amt'];
 // field_attach_submit('ccdev_send', $entity, $form, $form_state);
 // $entity = ccdev_send_save($entity);
  $form_state['redirect'] = 'ccSend/basic/' . $entity->basic_id; 
	ctools_add_js('ajax-responder');
	ctools_include('modal');

	// double check balance + santize input first!!!
	$sendFundID = writeSendFunds($entity);  
	writeOTP($entity, $sendFundID);
	$commands[] = ctools_modal_command_dismiss();
	return $commands;
}


/**
 * Validation handler for Send funds form info
 */
function ccdev_send_form_validate($form, &$form_state) {
  field_attach_form_validate('ccdev_send', $form_state['values']['basic_entity'], $form, $form_state);
}

/**
 * Form submit handler: Submits Send funds form info
 */
function ccdev_send_form_submit($form, &$form_state) {
  $entity = $form_state['values']['basic_entity'];
  $entity->recip_name = $form_state['values']['recip_name'];
  $entity->recip_email = $form_state['values']['recip_email'];
  $entity->recip_msg = $form_state['values']['recip_msg'];
  $entity->coin_code = $form_state['values']['coin_code'];
  $entity->coin_amt = $form_state['values']['coin_amt'];
  field_attach_submit('ccdev_send', $entity, $form, $form_state);
  $entity = ccdev_send_save($entity);
  $form_state['redirect'] = 'ccSend/basic/' . $entity->basic_id; 
}

/**
 * Form submit handler: Submits OTP Form info
 */
function send_OTP_form_submit($ajax, $data) {
	ctools_add_js('ajax-responder');
	ctools_include('modal');

	$commands[] = ctools_modal_command_dismiss();
	print ajax_render($commands);
	drupal_exit();
}

