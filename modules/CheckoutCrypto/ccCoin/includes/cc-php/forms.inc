<?php

/**
 * Form function to create an ccdev_coin entity.
 */
function ccdev_coin_form($form, &$form_state, $entity) {
	module_load_include('inc', 'ccCoin', 'includes/cc-php/forms_sub');
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
  $form['coin_rate'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin Rate'),
    '#required' => TRUE,
    '#default_value' => $entity->coin_rate,
  );
  $form['coin_rate_btc'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin Avg Rate(BTC)'),
    '#required' => TRUE,
    '#default_value' => $entity->coin_rate_btc,
  );
  $form['coin_rate_sell'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin Sell Rate(BTC)'),
    '#required' => TRUE,
    '#default_value' => $entity->coin_rate_sell,
  );
  $form['coin_rate_buy'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin Buy Rate(BTC)'),
    '#required' => TRUE,
    '#default_value' => $entity->coin_rate_buy,
  );
  $form['market_sell_depth'] = array(
    '#type' => 'textfield',
    '#title' => t('Market Sell Depth'),
    '#required' => TRUE,
    '#default_value' => $entity->market_sell_depth,
  );
  $form['market_buy_depth'] = array(
    '#type' => 'textfield',
    '#title' => t('Market Buy Depth'),
    '#required' => TRUE,
    '#default_value' => $entity->market_buy_depth,
  );
  $form['exchange_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Exchange row id'),
    '#required' => TRUE,
    '#default_value' => $entity->exchange_id,
  );
  $form['exchange_spec'] = array(
    '#type' => 'textfield',
    '#title' => t('Exchange Specifier'),
    '#required' => TRUE,
    '#default_value' => $entity->exchange_spec,
  );
  $form['coin_community'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin Community'),
    '#required' => TRUE,
    '#default_value' => $entity->coin_community,
  );
  $form['coin_fee'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin Fee'),
    '#required' => TRUE,
    '#default_value' => $entity->coin_fee,
  );
  $form['coin_txfee'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin TX Fee'),
    '#required' => TRUE,
    '#default_value' => $entity->coin_txfee,
  );
  $form['coin_MxConf'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin MAX Confirms'),
    '#required' => TRUE,
    '#default_value' => $entity->coin_MxConf,
  );
$form['coin_enabled'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin Enabled'),
    '#required' => TRUE,
    '#default_value' => $entity->coin_enabled,
  );
  $form['min_amount'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin MIN amount'),
    '#required' => TRUE,
    '#default_value' => $entity->min_amount,
  );

  $form['max_amount'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin MAX amount'),
    '#required' => TRUE,
    '#default_value' => $entity->max_amount,
  );
  $form['coin_validate'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin Address validation code'),
    '#required' => TRUE,
    '#default_value' => $entity->coin_validate,
  );
  $form['coin_image'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin Image'),
    '#required' => false,
    '#default_value' => $entity->coin_image,
  );
  $form['coin_description'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin Description (max 200)'),
    '#required' => TRUE,
    '#default_value' => $entity->coin_description,
  );
  $form['basic_entity'] = array(
    '#type' => 'value',
    '#value' => $entity,
  );

  field_attach_form('ccdev_coin', $entity, $form, $form_state);

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 100,
  );
  $form['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
    '#submit' => array('ccdev_coin_edit_delete'),
    '#weight' => 200,
  ); 

  return $form;
}

/**
 * Drupal form to be put in a modal.
 */
function addcoin_form($form, &$form_state) {
 	module_load_include('inc', 'ccCoin', 'includes/cc-php/forms_sub');
	module_load_include('inc', 'ccCoin', 'includes/cc-php/lib');
   drupal_add_js(drupal_get_path('module','ccCoin').'/ccCoin.js', 'file');

  	global $user;

	$coindata = array();
	$coindata = getCoinData($form_state['coincode']);

	/// THUMB
	 $form['image'] = array('#markup' => t('<div id="cc-addcoin" style="height=200px;"><div id="cc-addcoin-thumb" style="background:url('.$coindata['coin_image'].') center no-repeat #fff; height:150px;"></div></div>'));
	// RATE
	$form['rate'] = array('#markup' => t('<div id="cc-addcoin-info" style="text-align:center;font:bold 25px arial,sans-serif; right center no-repeat #fff;"><p>'.$coindata['coin_name'].'<p></div>'));
	/// DESC
	$form['desc'] = array('#markup' => t('<div id="cc-addcoin-desc" style="float:left;text-align:center;width:250px;height=100px;font:15px arial,sans-serif;"><p>'.$coindata['coin_description'].'<p></div>'));

	$form['coin_name'] = array(
		'#type' => 'value',
		'#value' => $coindata['coin_name'],
	);
	$form['coin_code'] = array(
		'#type' => 'value',
		'#value' => $form_state['coincode'],
	);
	$account = getAccountData($form_state['coincode']);
	if(!isset($account) OR $account == FALSE){
		$form['account_found'] = array(
		'#type' => 'value',
		'#value' => false,
		);
		$form['submit'] = array(
		    '#type' => 'submit',
		    '#value' => t('Enable'),
		'#attributes' => array('class' => array('btn', 'btn-success'), 'style' => "float:right; padding: 5px 10px;"),
		'#theme' => "submit",
		'#prefix' => "<div class='submit-button-custom'>",
		'#suffix' => "</div>",
		  '#ajax' => array(
		  'callback' => 'ccCoin_addcoin_form_submit',),
		); 
	} else {
		$form_state['ajax_commands'] = array(
		'#type' => 'value',
		    '#value' => true,
		);
		$form['account_found'] = array(
		'#type' => 'value',
		'#value' => true,
		);
		$form['submit'] = array(
		        '#type' => 'submit',
		        '#value' => t('Enabled'),
		  '#attributes' => array('class' => array('btn', 'btn-success','disabled'),'style' => "float:right; padding: 5px 10px;"),
		  '#theme' => "submit",
		  '#prefix' => "<div class='submit-button-custom'>",
		  '#suffix' => "</div>",
			'#ajax' => array(
			'callback' => 'ccCoin_addcoin_form_submit',),
		); 
	} 
  return $form;
}

/**
 * Form function to create an ccdev_coin entity.
 */
function editcoin_form($form, &$form_state) {
	module_load_include('inc', 'ccCoin', 'includes/cc-php/lib');
	$coindata = array();
	$coindata = getCoinData($form_state['coincode']);
  $form['coin_enabled'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin Enabled'),
    '#required' => TRUE,
    '#default_value' => $coindata['coin_enabled'],
  );
  $form['coin_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin Name'),
    '#required' => TRUE,
    '#default_value' => $coindata['coin_name'],
  );
  $form['coin_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin Code'),
    '#required' => TRUE,
    '#default_value' => $coindata['coin_code'],
  );
  $form['coin_rate'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin Dollar Rate'),
    '#required' => TRUE,
    '#default_value' => $coindata['coin_rate'],
  );
  $form['coin_rate_btc'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin BTC Rate'),
    '#required' => TRUE,
    '#default_value' => $coindata['coin_rate_btc'],
  );
  $form['coin_rate_sell'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin SELL Rate'),
    '#required' => TRUE,
    '#default_value' => $coindata['coin_rate_sell'],
  );
  $form['coin_rate_buy'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin BUY Rate'),
    '#required' => TRUE,
    '#default_value' => $coindata['coin_rate_buy'],
  );

  $form['market_sell_depth'] = array(
    '#type' => 'textfield',
    '#title' => t('Market SELL Depth'),
    '#required' => TRUE,
    '#default_value' => $coindata['market_sell_depth'],
  );
  $form['market_buy_depth'] = array(
    '#type' => 'textfield',
    '#title' => t('Market BUY Depth'),
    '#required' => TRUE,
    '#default_value' => $coindata['market_buy_depth'],
  );
  $form['exchange_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Exchange row id'),
    '#required' => TRUE,
    '#default_value' => $coindata['exchange_id'],
  );
  $form['exchange_spec'] = array(
    '#type' => 'textfield',
    '#title' => t('Exchange Specifier'),
    '#required' => TRUE,
    '#default_value' => $coindata['exchange_spec'],
  );

  $form['coin_community'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin Community'),
    '#required' => TRUE,
    '#default_value' => $coindata['coin_community'],
  );
  $form['coin_fee'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin Fee'),
    '#required' => TRUE,
    '#default_value' => $coindata['coin_fee'],
  );
  $form['coin_txfee'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin TX Fee'),
    '#required' => TRUE,
    '#default_value' => $coindata['coin_txfee'],
  );
  $form['coin_MxConf'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin MAX Confirms'),
    '#required' => TRUE,
    '#default_value' => $coindata['coin_MxConf'],
  );
  $form['coin_enabled'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin Enabled'),
    '#required' => TRUE,
    '#default_value' => $coindata['coin_enabled'],
  );
  $form['min_amount'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin MIN Amount'),
    '#required' => TRUE,
    '#default_value' => $coindata['min_amount'],
  );
  $form['max_amount'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin MAX Amount'),
    '#required' => TRUE,
    '#default_value' => $coindata['max_amount'],
  );
  $form['coin_validate'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin Address validation code'),
    '#required' => TRUE,
    '#default_value' => $coindata['coin_validate'],
  );
  $form['coin_image'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin Image'),
    '#required' => false,
    '#value' => $coindata['coin_image'],
  );
  $form['coin_description'] = array(
    '#type' => 'textfield',
    '#title' => t('Coin Description (max 200)'),
    '#required' => TRUE,
    '#default_value' => $coindata['coin_description'],
  );
    $form_state['ajax_commands'] = array(
	'#type' => 'value',
        '#value' => true,
    );
//  field_attach_form('ccdev_coin', $coindata, $form, $form_state);

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
 	'#ajax' => array(
	  'callback' => 'editcoin_form_submit',),
    '#weight' => 100,
  );
  $form['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
    '#submit' => array('ccdev_coin_edit_delete'),
    '#weight' => 200,
  ); 

  return $form;
}
