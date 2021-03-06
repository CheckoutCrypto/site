<?php

function manage_coin_submit($data){
	ctools_add_js('ajax-responder');
	ctools_include('modal');
 	module_load_include('inc', 'ccBalance', 'includes/cc-php/lib');
 	module_load_include('inc', 'ccAccount', 'includes/cc-php/lib');
 	module_load_include('inc', 'ccCoin', 'includes/cc-php/api');
 	module_load_include('inc', 'ccCoin', 'includes/cc-php/lib');
	if($data['values']['account_found'] == true){
	//var_dump($data['values']['coin_name']);
	} else {
	  //$form_state['redirect'] = 'ccMod/ccCoin/basic/' . $entity->basic_id; 
		global $user;
		/// create new OTP row
			addUserOTP($user->uid, $data['values']['coin_code'], $data['values']['coin_name'] );
		/// create new balance row
			addUserBalance($user->uid, $data['values']['coin_code'], $data['values']['coin_name'] );

		$avail_key = getUserApiKey();
		if(!isset($avail_key['api_key'])){
		/// generate api key if none already there
			ccGenApiKey($user->uid, false, $data['values']['coin_code']);
		}
		/// generate new address for account (we need one to calculate balance)
		$response = ccGetAddress($data['values']['coin_code']);
		if(isset($response['response']['queue_id'])) {
				$result['queue_id'] = $response['response']['queue_id'];
				$result['success'] = TRUE;
				$address = ccApiStatus($result['queue_id'], $data['values']['coin_code']);
				/// do anything with address i.e. use for alternative coin storage
		}	

	}

}


/**
 * Validation handler for ccdev_coin_add_form form.
 */
function ccdev_coin_form_validate($form, &$form_state) {
  field_attach_form_validate('ccdev_coin', $form_state['values']['basic_entity'], $form, $form_state);
}

/**
 * Form submit handler: Submits basic_add_form information.
 */
function ccdev_coin_form_submit($form, &$form_state) {
  $entity = $form_state['values']['basic_entity'];
  $entity->coin_name = $form_state['values']['coin_name'];
  $entity->coin_code = $form_state['values']['coin_code'];
  $entity->coin_rate = $form_state['values']['coin_rate'];
  $entity->coin_rate_btc = $form_state['values']['coin_rate_btc'];
  $entity->coin_rate_sell = $form_state['values']['coin_rate_sell'];
  $entity->coin_rate_buy = $form_state['values']['coin_rate_buy'];
  $entity->market_sell_depth = $form_state['values']['market_sell_depth'];
  $entity->market_buy_depth = $form_state['values']['market_buy_depth'];
  $entity->exchange_id = $form_state['values']['exchange_id'];
  $entity->exchange_spec = $form_state['values']['exchange_spec'];
  $entity->coin_community = $form_state['values']['coin_community'];
  $entity->coin_fee = $form_state['values']['coin_fee'];
  $entity->coin_txfee = $form_state['values']['coin_txfee'];
  $entity->coin_MxConf = $form_state['values']['coin_MxConf'];
  $entity->coin_enabled = $form_state['values']['coin_enabled'];
  $entity->min_amount = $form_state['values']['min_amount'];
  $entity->max_amount = $form_state['values']['max_amount'];
  $entity->coin_validate = $form_state['values']['coin_validate'];
  $entity->coin_image = $form_state['values']['coin_image'];
  $entity->coin_description = $form_state['values']['coin_description'];
  field_attach_submit('ccdev_coin', $entity, $form, $form_state);
  $entity = ccdev_coin_save($entity);
  $form_state['redirect'] = 'ccMod/ccCoin/basic/' . $entity->basic_id; 
}

function editcoin_form_submit($form, &$form_state){
	module_load_include('inc', 'ccBalance', 'includes/cc-php/api');
	global $user;
	$value = $form_state['values']['coin_code'];
	$value2 = $form_state['values']['coin_txfee'];
	$value3 = $form_state['values']['coin_fee'];
	$value4 = $form_state['values']['min_amount'];
	$value5 = $form_state['values']['max_amount'];
	$value6 = $form_state['values']['coin_validate'];
	$value7 = $form_state['values']['coin_MxConf'];
	$value8 = $form_state['values']['coin_enabled'];
	$value9 = $form_state['values']['coin_image'];
	$value10 = $form_state['values']['coin_description'];

	$value11 = $form_state['values']['market_sell_depth'];
	$value12 = $form_state['values']['market_buy_depth'];
	$value13 = $form_state['values']['exchange_id'];
	$value14 = $form_state['values']['exchange_spec'];

	 try {
		      db_update('ccdev_coin')->fields(array(
				'market_sell_depth' => $value11,
				'market_buy_depth' => $value12,
				'exchange_id' => $value13,
				'exchange_spec' => $value14,
		        'coin_txfee' => $value2,
		        'coin_fee' => $value3,
				'min_amount' => $value4,
		        'max_amount' => $value5,
		        'coin_validate' => $value6,
				'coin_MxConf' => $value7,
		        'coin_enabled' => $value8,
		        'coin_image' => $value9,
		        'coin_description' => $value10,
		      ))
			->condition('coin_code', $value, '=')
			//->condition('uid', $user->uid, '=')
			->execute();
		  } catch (exception $e) {
				var_dump($e);
		        watchdog('ccdev_coin', 'Could not insert order into database: !fault', $e->getMessage());
		        return FALSE;
		  }

	$response = ccRefreshRequest();
	ctools_add_js('ajax-responder');
	ctools_include('modal');
	$commands[] = ctools_modal_command_dismiss();
	print ajax_render($commands);
	drupal_exit();
}
