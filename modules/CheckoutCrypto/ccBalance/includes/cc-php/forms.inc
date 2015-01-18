<?php


/**
 * Drupal form to be put in a modal.
 */
function withdraw_form($form, $form_state) {
	module_load_include('inc', 'ccBalance', 'includes/cc-php/forms_sub');
    	module_load_include('inc', 'ccBalance', 'includes/cc-php/lib');
  	$form = array();
  	$form['cc_wrapper'] = array('#markup' => t('<div id="cc-wrapper" style="width:400px;height=300px;text-align:center;">'));
	/// check if client reached max trans
	$maxTrans = checkMaxTrans();
	if($maxTrans != true){
		$form['error'] = array('#markup' => t('<div class="cc-withdraw"><p class="cc-withdraw-balance"><strong>You have reached the Max transactions, please upgrade/downgrade your </strong><a id="coin_balance" name="coin_balance" href="#">service package</a>'));
		return $form;
	}
	

	global $user;
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'ccdev_balance')
	  ->entityCondition('bundle', 'balance_bundle')
	 ->propertyCondition('coin_code', $form_state['coincode'])
	->propertyCondition('uid', $user->uid)
	  ->addMetaData('account', user_load($user->uid)); // Run the query as user 1.
	$result = $query->execute();
	if (isset($result['ccdev_balance'])) {
  	$wallet_nids = array_keys($result['ccdev_balance']);
  	$wallets = entity_load('ccdev_balance', $wallet_nids);
 	 foreach($wallets as $wallet){
		$balance = $wallet->coin_balance;
	}
  	$form['balance'] = array('#markup' => t('<div class="cc-withdraw"><p class="cc-withdraw-balance"><strong>'.$form_state['coincode'].':</strong> Balance=<a id="coin_balance" name="coin_balance" href="#">'.$balance.'</a>'));
	} 
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'ccdev_coin')
	  ->entityCondition('bundle', 'coin_bundle')
	 ->propertyCondition('coin_code', $form_state['coincode'])
	  ->addMetaData('account', user_load($user->uid)); // Run the query as user 1.
	$result = $query->execute();
  	 if(isset($result['ccdev_coin'])) {
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
 		$form['fee'] = array('#markup' => t('<div class="cc-withdraw-fee">Withdraw Fee: '.$fee.' </div>'));
  		$form['txfee'] = array('#markup' => t('<div class="cc-withdraw-tx-fee">Trans Fee: '.$TxFee.' </div>'));
  		$form['min_withdaw'] = array('#markup' => t('<div class="cc-withdraw-range">Range(Min-Max):('.$minAmt));
  		$form['max_withdraw'] = array('#markup' => t(' - '.$maxAmt.')</div><br/>'));
	} 
	$form['coin_name'] = array(
      	'#type' => 'hidden',
      	'#required' => TRUE,
	'#attributes' => array('id' => 'coin_name'),
      	'#default_value' => $coin_name,
  	);
	$form['coin_fee'] = array(
      	'#type' => 'hidden',
      	'#required' => TRUE,
	'#attributes' => array('id' => 'coin_fee'),
      	'#default_value' => $fee,
  	);
  	$form['coin_txfee'] = array(
     	'#type' => 'hidden',
      	'#required' => TRUE,
	'#attributes' => array('id' => 'coin_txfee'),
      	'#default_value' => $TxFee,
  	);
  	$form['min_amount'] = array(
      	'#type' => 'hidden',
      	'#required' => TRUE,
	'#attributes' => array('id' => 'min_amount'),
      	'#default_value' => $minAmt,
  	);
  	$form['max_amount'] = array(
      	'#type' => 'hidden',
      	'#required' => TRUE,
	'#attributes' => array('id' => 'max_amount'),
      	'#default_value' => $maxAmt,
  	);
  	$form['total_balance'] = array(
      	'#type' => 'hidden',
      	'#required' => TRUE,
	'#attributes' => array('id' => 'total_balance'),
      	'#default_value' => $balance,
  	);

  	$form['coin_address_code'] = array(
      	'#type' => 'hidden',
      	'#required' => TRUE,
      	'#default_value' => $address_code,
  	);

  	$otpArr = get_otp_type($user->uid);
	if(isset($otpArr['pref_otp'])){
	 $pref_otp = $otpArr['pref_otp'];
	}else{
		$pref_otp = 'email';
	}
	if($otpArr['pref_otp'] == "twofa"){
	  $form['twofa_pin'] = array(
		  '#type' => 'textfield',
		  '#title' => t('2FA KEY'),
		  '#required' => TRUE,
		  '#attributes' => array('title' => 'Valid characters are 0-9', 'placeholder' => 'TwoFactor', 'pattern' => '^[0-9]{1,10}+$', 'size' => 10, 'step' => '0.01', 'required' => 'required'),
		 '#default_value' => '',
	  ); 
	  $form['twofa_key'] = array(
		  '#type' => 'hidden',
		  '#required' => TRUE,
		  '#default_value' =>  $pref_otp,
	  );
	}
	  $form['pref_otp'] = array(
		  '#type' => 'hidden',
		  '#required' => TRUE,
		  '#default_value' => $pref_otp,
	  );


  	$form['withdraw_amount'] = array(
      	'#type' => 'textfield',
      	'#title' => t('Withdraw Amount'),
      	'#required' => TRUE,
      	'#attributes' => array('title' => 'Valid characters are 0-9', 'placeholder' => 'Withdraw amount',
		'pattern' => '[0-9]+([\.|,][0-9]+)?', 'step' => '0.01', 'required' => 'required'),
     	'#default_value' => '',
  	); 

  	$form['withdraw_address'] = array(
      	'#type' => 'textfield',
      	'#title' => t('Withdraw Address'),
      	'#required' => TRUE,
      	'#attributes' => array('title' => 'Must be a valid address', 'placeholder' => 'Withdraw address', 'autofocus' => 'autofocus', 
		'pattern' => '^[A-Za-z0-9_.]+$', 'required' => 'required'),
      	'#default_value' => '',
  	);

  	$form['submit'] = array(
      	'#type' => 'submit',
      	'#value' => t('Submit'),
  	);
  	return $form;
}

/**
 * Drupal form to be put in a modal.
 */
function autopay_form($form, $form_state) {
	module_load_include('inc', 'ccBalance', 'includes/cc-php/forms_sub');
    	module_load_include('inc', 'ccBalance', 'includes/cc-php/lib');
  	$form = array();
  	$form['cc_wrapper'] = array('#markup' => t('<div id="cc-wrapper" style="width:400px;height=300px;text-align:center;">'));
	/// check if client reached max trans
	$maxTrans = checkMaxTrans();
	if($maxTrans != true){
		$form['error'] = array('#markup' => t('<div class="cc-withdraw"><p class="cc-withdraw-balance"><strong>You have reached the Max transactions, please upgrade/downgrade your </strong><a id="coin_balance" name="coin_balance" href="#">service package</a>'));
		return $form;
	}
	global $user;
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'ccdev_balance')
	  ->entityCondition('bundle', 'balance_bundle')
	 ->propertyCondition('coin_code', $form_state['coincode'])
	->propertyCondition('uid', $user->uid)
	  ->addMetaData('account', user_load($user->uid)); // Run the query as user 1.
	$result = $query->execute();
	if (isset($result['ccdev_balance'])) {
	  	$accounts_nids = array_keys($result['ccdev_balance']);
	  	$accounts = entity_load('ccdev_balance', $accounts_nids);
		foreach($accounts as $act){
			$autopay = $act->coin_autopay;
			$autoaddress = $act->coin_autoaddress;
			$balance = $act->coin_balance;
		}
		$form['balance'] = array('#markup' => t('<div class="cc-withdraw"><p class="cc-withdraw-balance"><strong>'.$form_state['coincode'].':</strong> Balance=<a id="coin_balance" name="coin_balance" href="#">'.$balance.'</a>'));
	}  
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'ccdev_coin')
  	->entityCondition('bundle', 'coin_bundle')
	 ->propertyCondition('coin_code', $form_state['coincode'])
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
  		$form['fee'] = array('#markup' => t('<div class="cc-withdraw-fee">Withdraw Fee: '.$fee.' </div>'));
  		$form['txfee'] = array('#markup' => t('<div class="cc-withdraw-tx-fee">Trans Fee: '.$TxFee.' </div>'));
  		$form['min_withdaw'] = array('#markup' => t('<div class="cc-withdraw-range">Range(Min-Max):('.$minAmt));
  		$form['max_withdraw'] = array('#markup' => t(' - '.$maxAmt.')</div><br/>'));
	} 
 	$form['coin_address_code'] = array(
      	'#type' => 'hidden',
      	'#required' => TRUE,
	'#default_value' => $address_code,
  	);
 	$form['coin_name'] = array(
      	'#type' => 'hidden',
      	'#required' => TRUE,
      	'#default_value' => $coin_name,
  	);
  	$form['coin_fee'] = array(
      	'#type' => 'hidden',
      	'#required' => TRUE,
	'#attributes' => array('id' => 'coin_fee'),
      	'#default_value' => $fee,
  	);
  	$form['coin_txfee'] = array(
      	'#type' => 'hidden',
      	'#required' => TRUE,
	'#attributes' => array('id' => 'coin_txfee'),
      	'#default_value' => $TxFee,
  	);
  	$form['min_amount'] = array(
      	'#type' => 'hidden',
      	'#required' => TRUE,
	'#attributes' => array('id' => 'min_amount'),
      	'#default_value' => $minAmt,
  	);
  	$form['max_amount'] = array(
      	'#type' => 'hidden',
      	'#required' => TRUE,
	'#attributes' => array('id' => 'max_amount'),
      	'#default_value' => $maxAmt,
  	);
  	$form['total_balance'] = array(
      	'#type' => 'hidden',
      	'#required' => TRUE,
	'#attributes' => array('id' => 'total_balance'),
      	'#default_value' => $balance,
  	);
  	$form['coin_autopay'] = array(
	'#type' => 'textfield',
	'#title' => t('AutoPay Amount'),
	'#required' => TRUE,
	'#attributes' => array('title' => 'Valid characters are 0-9', 'placeholder' => 'Withdraw amount', 'pattern' => '[0-9]+([\.|,][0-9]+)?', 'step' => '0.01', 'required' => 'required'),
	 '#default_value' => $autopay,
	  ); 
	$form['coin_autoaddress'] = array(
	'#type' => 'textfield',
	'#title' => t('AutoPay Address'),
	'#required' => TRUE,
	 '#attributes' => array('title' => 'Must be a valid address', 'placeholder' => 'AutoPay address', 'autofocus' => 'autofocus', 'pattern' => '^[A-Za-z0-9_.]+$', 'required' => 'required'),
	'#default_value' => $autoaddress,
	  );

	  $otpArr = get_otp_type($user->uid);
	if(isset($otpArr['pref_otp'])){
		$pref_otp = $otpArr['pref_otp'];
	}else{
		$pref_otp = 'email';
	}
	if($otpArr['pref_otp'] == "twofa"){
	  $form['twofa_pin'] = array(
		  '#type' => 'textfield',
		  '#title' => t('2FA KEY'),
		  '#required' => TRUE,
		  '#attributes' => array('title' => 'Valid characters are 0-9', 'placeholder' => 'TwoFactor', 
			'pattern' => '^[0-9]{1,10}+$', 'size' => 10, 'step' => '0.01', 'required' => 'required'),
		 '#default_value' => '',
	  ); 
	  $form['twofa_key'] = array(
		  '#type' => 'hidden',
		  '#required' => TRUE,
		  '#default_value' => $otpArr['twofa_key'],
	  );
	}

	  $form['pref_otp'] = array(
		  '#type' => 'hidden',
		  '#required' => TRUE,
		  '#default_value' => $pref_otp,
	  );

	  $form['submit'] = array(
		  '#type' => 'submit',
		  '#value' => t('Submit'),
	  );
	  return $form;
}


function OTP_form($form, $form_state) {
    	module_load_include('inc', 'ccBalance', 'includes/cc-php/forms_sub');
	$form['otp_message'] = array(
	'#markup' => t('<div>CheckoutCrypto Email Confirmation still pending.  Check your email or contact us if you cannot get email access: </div>'));

    	$form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Done'),
	'#attributes' => array('style' => "float:right; padding: 5px 10px;"),
	'#theme' => "submit",
	'#prefix' => "<div class='submit-button-custom'>",
	'#suffix' => "</div>",
	'#ajax' => array(
	'callback' => 'OTP_form_submit',),
    ); 

	return $form;
}

/*
*   Deposit Form
*/
function Deposit_form($form, $form_state){
	ctools_include('ajax');
        ctools_include('modal');
	ctools_add_js('ajax-responder');
       	ctools_modal_add_js();

	//// Coin selector
 	$form['coinselector'] = array(
	'#markup' => t('')
	);
	////  Deposit form
	$form['summary'] = array( 
	'#markup' => t('<div class="dep_summary"></div>')
	);
	$form['address'] = array( 
	'#markup' => t('<div class="dep_address"></div>')
	);
	$form['qr_address'] = array( 
	'#markup' => t('<div id="dep_qr_address"></div>')
	);	
	////   Form Status
	$form['msg'] = array( 
	'#markup' => t('<div class="dep_msg"></div>')
	);
	$form['timer'] = array( 
	'#markup' => t('<div class="dep_timer"></div>')
	);

	 $popup['deposit_address'] = array(
       '#type' => 'hidden',
       '#value' => $form_state['request']['address'],
       );

	 $popup['deposit_coin'] = array(
       '#type' => 'hidden',
       '#value' => $form_state['request']['coin'],
       );
	return $form;
}

function Deposit_form_callback($form, $form_state){
	module_load_include('inc', 'ccBalance', 'includes/api');
	module_load_include('inc', 'cgTrading', 'includes/service');
	$address = genAddress();
	if(isset($address)){	
		$qraddress = generateQR($address, '150');
		$commands = array();
		$commands[] = ajax_command_replace('#dep_address','<div id="dep_address">'. $address .' </div>');
		$commands[] = ajax_command_replace('#dep_qr_address','<div id="dep_qr_address">'. $qraddress .' </div>');
		print ajax_render($commands);
	}
	drupal_exit();
}

/*
*   Autotrade Form
*/
function autotrade_form($form, $form_state){
	ctools_include('ajax');
        ctools_include('modal');
	ctools_add_js('ajax-responder');
       	ctools_modal_add_js();

	//// Coin selector
 	$form['coinselector'] = array(
	'#markup' => t('')
	);
	////  Deposit form
	$form['summary'] = array( 
	'#markup' => t('<div class="dep_summary"></div>')
	);

	 $popup['autotrade_coin_from'] = array(
       '#type' => 'hidden',
       '#value' => $form_state['request']['coin'],
       );

	 $popup['autotrade_coin_to'] = array(
       '#type' => 'hidden',
       '#value' => $form_state['request']['coin'],
       );
	return $form;
}


/**
 * Form function to create an ccdev_balance entity.
 */
function ccdev_balance_form($form, &$form_state, $entity) {
  $form['coin_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin Name'),
    '#required' => TRUE,
    '#default_value' => $entity->coin_name,
  );
  $form['coin_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin Code'),
    '#required' => TRUE,
    '#default_value' => $entity->coin_code,
  );
  $form['coin_balance'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin Balance'),
    '#required' => TRUE,
    '#default_value' => $entity->coin_balance,
  );

  $form['basic_entity'] = array(
    '#type' => 'value',
    '#value' => $entity,
  );

  field_attach_form('ccdev_balance', $entity, $form, $form_state);

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 100,
  );
  $form['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
    '#submit' => array('ccdev_balance_edit_delete'),
    '#weight' => 200,
  ); 

  return $form;
}


