<?php

function trading_form($form, &$form_state){
	$path = drupal_get_path('module', 'cgTrading');
 	drupal_add_css(drupal_get_path('module', 'cgTrading') . '/theme/style1.css', 'file');
	//slick
	drupal_add_css($path.'/includes/slick/slick.css');
	drupal_add_js($path.'/includes/slick/slick.js');
	//search
	drupal_add_css($path.'/includes/css/select2.css');
	drupal_add_js($path.'/includes/js/select2.js');
	//end search
	drupal_add_js($path.'/includes/Trading.js');
   drupal_add_js(drupal_get_path('module','cgTrading').'/theme/cgTrading.js');
	module_load_include('inc', 'ccCoin', 'includes/cc-php/lib');
	module_load_include('inc', 'cgTrading', 'includes/layout');

   ctools_include('ajax');
	ctools_add_js('ajax-responder');
   ctools_include('modal');
   ctools_modal_add_js();

	global $base_url;
	$coins = getAllCoinData();  // should probably be a smaller query, just for images / names
	$my_settings = array(
	  'baseUrl' => $base_url,
	 );
	$request = array('coins' => $coins);
	drupal_add_js(array('cgTrading' => $my_settings), 'setting');
	drupal_add_js(array('cgTrading' => $request), 'setting');

	$form['trade_container'] = displayTradeContainer();
	$form['spend_tab'] = displaySpendTab($coins);
	$form['exchange_tab'] = displayExchangeTab($coins);
	//$form['fiat_tab'] = displayFiatTab($coins);

	//// Hidden var values we need
	$form['coin_deposit_address'] = array(
		'#type' => 'value',
		'#value' => 'Coin Address e.g. 1GetbDHnPWV7Efs5PAetHGZ7o2rpuCpm7A',
	);
	//// hidden stored coin variable
	$form['coin_to'] = array(
       '#type' => 'hidden',
       '#value' => t(''),
       );
   	$form['coin_from'] = array(
       '#type' => 'hidden',
       '#value' => t(''),
       );
	//// hidden stored tab variable
  	 $form['tab'] = array(
       '#type' => 'hidden',
       '#value' => t(''),
       );
	$form['coin_amt_type'] = array(
		'#type' => 'hidden',
		'#value' => t(''),
	);
	$form['trade_queue'] = array(
		'#type' => 'hidden',
		'#value' => t(''),
	);
  return $form;
}


function trading_form_submit($form, &$form_state){
	module_load_include('inc', 'ccCoin', 'includes/cc-php/lib');
	module_load_include('inc', 'cgTrading', 'includes/api');
	module_load_include('inc', 'cgTrading', 'includes/service');
	module_load_include('inc', 'cgTrading', 'includes/lib');
	$tab = '';
	$tabs = array('spend', 'exchange', 'fiat');
	$coin = '';
	$coins = getAllCoinCodes();
	$coin_to = 'BTC';
	$addressRec = '';
	$address = '';
	$amount = '';
	$errors = 0;
	//// get COIN
	ctools_include('ajax');
   ctools_include('modal');
	ctools_add_js('ajax-responder');
   ctools_modal_add_js();
	/// get TAB
	if(isset($form_state['input']['tab'])){
		$tab = $form_state['input']['tab'];
		if(!in_array($tab, $tabs)){
				ctools_modal_render('Error',  ' <p> YOU MUST SELECT A VALID TAB </p> ');
		}
	}
	/// Validate Spend Tab
	if($tab == "spend"){
				//// Validate Coin Field
				$coin = validateTradeCoin($coins, $form_state['input']['coin_from']);
				if($coin == false){
						$errArr[$errors]['title'] = 'Spend Error';
						$errArr[$errors]['msg'] = ' COIN IS INCORRECT ';
						$errors++;
				}
				else if($coin == NULL){
								$errArr[$errors]['title'] = 'Spend Error';
								$errArr[$errors]['msg'] = ' COIN IS MISSING ';
								$errors++;
				}
				else{
						$amount_type = $form_state['input']['coin_type'];
				}
				//// Validate Address Field
				$addressRec = validateTradeAddress($form_state['input']['address_spend'], $coin_to);
			  	if ($addressRec == false ){
					$errArr[$errors]['title'] = 'Spend Error';
					$errArr[$errors]['msg'] = ' INVALID ADDRESS ';
					$errors++;
				} else if ($addressRec == NULL){
					$errArr[$errors]['title'] = 'Spend Error';
					$errArr[$errors]['msg'] = ' <p> THE RECIPIENT ADDRESS IS MISSING </p> ';
					$errors++;
				}

				//// Validate Amount Field
				$amount = validateTradeAmount($form_state['input']['amount_spend']);
			 	if ($amount == false){
						$errArr[$errors]['title'] = 'Spend Error';
						$errArr[$errors]['msg'] = ' <p> YOU HAVE ENTERED AN INCORRECT SPEND AMOUNT </p> ';
						$errors++;
				} else if($amount == NULL){
						$errArr[$errors]['title'] = 'Spend Error';
						$errArr[$errors]['msg'] = ' <p> SPEND AMOUNT MISSING </p> ';
						$errors++;
				}
	
	}else if($tab == "exchange"){

				//// Validate Coin Field
				$coin = validateTradeCoin($coins, $form_state['input']['coin_from']);
				if($coin == false){
						$errArr[$errors]['title'] = 'Exchange Error';
						$errArr[$errors]['msg'] = ' DEPOSIT COIN IS INCORRECT ';
						$errors++;
				}
				else if($coin == NULL){
								$errArr[$errors]['title'] = 'Exchange Error';
								$errArr[$errors]['msg'] = 'DEPOSIT COIN IS MISSING ';
								$errors++;
				}
				else{
						$amount_type = $form_state['input']['coin_type'];
						$coin_to = validateTradeCoin($coins, $form_state['input']['coin_to']);
						if($coin_to == false){
								$errArr[$errors]['title'] = 'Exchange Error';
								$errArr[$errors]['msg'] = ' RECIPIENT COIN IS INCORRECT ';
								$errors++;
						}
						else if($coin_to == NULL){
								$errArr[$errors]['title'] = 'Exchange Error';
								$errArr[$errors]['msg'] = 'RECIPIENT COIN IS MISSING ';
								$errors++;
						}
						/// validate coins are not the same!
						if($coin == $coin_to){
								$errArr[$errors]['title'] = 'Exchange Error';
								$errArr[$errors]['msg'] = 'CANNOT EXCHANGE THE SAME COIN. ';
								$errors++;
						}
				}
		 		
				//// Validate Address Field
				$addressRec = validateTradeAddress($form_state['input']['address_exchange'], $coin_to);
			  	if ($addressRec == false ){
					$errArr[$errors]['title'] = 'Exchange Error';
					$errArr[$errors]['msg'] = ' INVALID ADDRESS ';
					$errors++;
				} else if ($addressRec == NULL){
					$errArr[$errors]['title'] = 'Exchange Error';
					$errArr[$errors]['msg'] = ' <p> THE RECIPIENT ADDRESS IS MISSING </p> ';
					$errors++;
				}

				//// Validate Amount Field
				$amount = validateTradeAmount($form_state['input']['amount_exchange']);
			 	if ($amount == false){
						$errArr[$errors]['title'] = 'Spend Error';
						$errArr[$errors]['msg'] = ' <p> YOU HAVE ENTERED AN INCORRECT SPEND AMOUNT </p> ';
						$errors++;
				} else if($amount == NULL){
						$errArr[$errors]['title'] = 'Spend Error';
						$errArr[$errors]['msg'] = ' <p> SPEND AMOUNT MISSING </p> ';
						$errors++;
				}
	}

	if($errors != 0){
		////  IF ERRORS!!!
		$form_state = array(
		 'ajax' => TRUE,
		  'title' => t('COINGATEWAY ERROR'),
		'errors' => $errArr,
		);
		$output = ctools_modal_form_wrapper('popupError', $form_state); 
	 	print ajax_render($output);

	}else{  /// NO General errors

		$amtType = $form_state['input']['coin_amt_type'];
		$tradeReq = array(
		'coin' => $coin, 'amount' => $amount, 'coin_trade' => $coin_to,
		'address'=> $addressRec, 'amountRec' => $conversion['amountRec'], 
		'coin_amt_type' => $amtType);	

			$form_state = array(
			  'ajax' => TRUE,
			  'title' => t('COINGATEWAY TRADE'),
			  'request' => $tradeReq,
			);

			module_load_include('inc', 'cgTrading', 'includes/api');
			$status = genTradeAddress($form_state['request'], 'true');

			if($status['success'] == TRUE){

				$address = $status['address'];
				$amountDep = $status['deposit_amt'];
				$coinDep = $status['coin_in'];
				$amountRec = $status['receive_amt'];
				$coinRec = $status['coin_out'];	
				$coinImgs = getTradeCoinImages($coin, $coin_to);

				$request = array(
				'coin' => $coinDep, 'coin_trade' => $coinRec, 
				'amount' => $amountDep, 'amountRec' => $amountRec, 
				'address' => $address, 'addressRec'=> $addressRec, 
				'coin_amt_type' => $amtType, 'coin_img' => $coinImgs['coin_to'],
				'coin_trade_img' => $coinImgs['coin_from']);	

				$form_state = array(
				  'ajax' => TRUE,
				  'title' => t('COINGATEWAY TRADE'),
				  'request' => $request,
				);
				$output = ctools_modal_form_wrapper('popupTheme', $form_state); 
			 	print ajax_render($output); 

			}else{
				$errArr[$errors]['title'] = 'Error';
				$errArr[$errors]['msg'] = ' <p id="errormes"> PLEASE ENTER A LOWER AMOUNT </p> 
				<p><a href="mailto:support@coingateway.net" id="reqfunds">REQUEST LIMIT INCREASE</a> </p> ';
				$errors++;

				////  API ERROR!!!
				$form_state = array(
				 'ajax' => TRUE,
				  'title' => t('COINGATEWAY ERROR'),
				'errors' => $errArr,
				);
				$output = ctools_modal_form_wrapper('popupError', $form_state); 
				 print ajax_render($output);
			}
	}
	drupal_exit();
}
