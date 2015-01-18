<?php


/*
*   Generate QR with a bitcoin address, default size = 150
*/
function generateQR($address, $size){
    	$url_qr_base = 'https://chart.googleapis.com/chart?cht=qr';
    	$url_qr_args = '&chs='.$size;
   	$url_qr_args .= '&choe=UTF8';
    	$url_qr_args .= '&chld=L';
    	$url_qr_args .= '&chl='.$address;
    	$url_qr = $url_qr_base.$url_qr_args;
    	$url_qr_output = '<img src="'.$url_qr.'">';
	return $url_qr_output;
}

/*
*   Ctools Trade Error Modal
*/
function popupError($form, &$form_state){
	$popup['wrapper'] = array('#markup' => t('<div id="popup_wrapper" class="popup_wrapper">'));
	$popup['header'] =array('#markup' => t('<div id="popup_header" class="popup_header"></div>'));
	$popup['title'] =array('#markup' => t('<div id="popup_title" class="popup_title"></div>'));
	$popup['content_description'] = array('#markup' => '<div id="popup_content_desc">');
	$count = 0;
	foreach($form_state['errors'] as $err){
		$popup['errors'][$count] = array('#markup' => '<p>'.$err['msg'].'</p><br>'); 
		$count++;
	}
	$popup['content_description_close'] = array('#markup' => t('</div>'));
	$popup['content'] = array('#markup' => t('<div id="popup_content">'));
	$popup['content_close'] = array('#markup' => t('</div>'));
	$popup['content_footer'] =array('#markup' => t('<div id="popup_content_foot" class="popup_content_foot"></div>'));
	$popup['footer'] = array('#markup' => t('<div id="popup_footer" class="popup_footer"></div>'));
	$popup['wrapper_end'] = array('#markup' => t('</div>'));

	return $popup;
}

/*
*   Ctools Trade Modal
*/
function popupTheme($popup, &$form_state){
	ctools_include('ajax');
    	ctools_include('modal');
    	ctools_modal_add_js();
	module_load_include('inc', 'cgTrading', 'includes/api');

		drupal_add_js(drupal_get_path('module','cgTrading').'/theme/cgPopup.js');
		global $base_url;
		$my_settings = array(
		  'baseUrl' => $base_url,
		 );
		$time_limit = 900;
		$cg_settings = array(
		    'time_limit' => $time_limit
		);
		drupal_add_js(array('cgTrading' => $my_settings), 'setting');
		drupal_add_js(array('cgTrading' => $cg_settings), 'setting');

	if(empty($form_state['input']['trade_queue'])){
	$coinDep = $form_state['request']['coin'];
	$coinRec = $form_state['request']['coin_trade'];	
	$coin_img = $form_state['request']['coin_img'];
	$coin_to_img = $form_state['request']['coin_trade_img'];
	$address = $form_state['request']['address'];
	$addressRec = $form_state['request']['addressRec'];
	$amountDep = $form_state['request']['amount'];
	$amountRec = $form_state['request']['amountRec'];
	$amtType = $form_state['request']['coin_amt_type'];

	$popup = array();
	$popup['#method'] = 'post';
	$popup['#action'] = url('Trading/details');
	$genQR = generateQR($address, 150);

	$popup['wrapper'] = array('#markup' => t('<div id="popup_wrapper" class="popup_wrapper">'));
	$popup['header'] =array('#markup' => t('<div id="popup_header" class="popup_header"></div>'));
	$popup['title'] =array('#markup' => t('<div id="popup_title"></div>'));
	$popup['content'] = array('#markup' => t('<div id="popup_content">'));
	$popup['content_qr'] = array('#markup' => t('<div id="qr_address_container">'.$genQR.'</div>'));
	$popup['content_close'] = array('#markup' => t('</div>'));
	$popup['footer'] = array('#markup' => t('<div id="popup_footer" class="popup_footer"></div>'));
	
	$popup['info'] =array('#markup' => t('<div id="popup_info">SEND EXACTLY <p id="amtsend">'. $amountDep.' '.$coinDep.'</p> TO THE ADDRESS BELOW </div>'));
   $popup['payment_address'] = array(
        '#type' => 'textfield',
        '#value' => $address,
        '#attributes' => array('readonly' => 'readonly','size' => 50,),
        '#prefix' => '<div id="payment_address_container" >',
        '#suffix' => '</div>',
        );
		
	$popup['sendinfo'] =array('#markup' => t('<div id="popup_info">RECIPIENT RECEIVES <p id="amtsend">'. $amountRec.' '.$coinRec.'</p> IN ADDRESS BELOW </div>'));	
	$popup['recipient'] =array(
	    '#type' => 'textfield',
        '#value' => $addressRec,
		'#attributes' => array('readonly' => 'readonly','size' => 50, 'onclick'=>'copyToClipboard(1)',),
		'#prefix' => '<div id="payment_address_container" >',
		'#suffix' => '</div>',
		);
	
	$popup['coinswitch'] = array( '#markup' => t('<div id="container34"><div id="imageswitch"><img src="'.$coin_img.'" id="coinfrom"/><img src="http://i.imgur.com/76lcX9S.png" id="arrowto"><img src="'.$coin_to_img.'" id="cointo"/></div></div>'),);
	
	$popup['content_footer'] =array('#markup' => t('<div id="popup_content_foot"></div>'));
	$popup['wrapper_end'] = array('#markup' => t('</div>'));
	//// hidden stored Address variable
  	 $popup['trade_address'] = array(
       '#type' => 'hidden',
       '#value' => $address,
       );
	//// hidden stored ReceivedAddress variable
   	$popup['addressRec'] = array(
       '#type' => 'hidden',
       '#value' => $addressRec,
       );
	//// hidden stored Coin FROM variable
  	 $popup['coin_from'] = array(
       '#type' => 'hidden',
       '#value' => $form_state['request']['coin'],
       );
	//// hidden stored Coin TO variable
   	$popup['coin_to'] = array(
       '#type' => 'hidden',
       '#value' => $form_state['request']['coin_trade'],
       );
	$popup['awaitingpayment'] = array( '#markup' => t('<div id="awaiting_payment"> WAITING FOR PAYMENT </div>'),);

	$popup['footer1'] = array( '#markup' => t('<footer id="popup_content_foot" style="position: relative;font-size: 11px !important;z-index: 1 !important;text-align: center !important;margin-top: 200px;"><a href="https://www.coingateway.net/" target="_parent">POWERED BY COINGATEWAY.NET</a></footer>'),);
	}else{
		$popup['popup_error'] = array( '#markup' => t('<div id="popup_wrapper"> <p id="errormes"> Trade Expired!</p> </div>'),);
	}

	return $popup;
}


/*
*  Ajax Trade Submit
*/
function timer_form($form, $form_state){
	 module_load_include('inc','cgTrading','includes/api');
	 module_load_include('inc','cgTrading','includes/lib');
	module_load_include('inc', 'ccCoin', 'includes/cc-php/lib');
		$coins = getAllCoinCodes();
		$errorCount = 0;

		$coin = validateTradeCoin($coins, $_POST['coin_from']);
		if($coin == false){
			$errorCount++;
		}else{
			$coin_to = validateTradeCoin($coins, $_POST['coin_to']);

			if($coin_to == false){
				$errorCount++;
			}else{
				$address = validateTradeAddress($_POST['trade_address'], $coin);
			}
		}

	if($errorCount == 0){
		$status = getTradeStage($address);
		if($status == 1){
			$confirms = '1';
		}else{
			$confirms = '0';
		}
		$request = array('coin' => $coin, 'address' => $address, 'confirms' => $confirms);	
	
		$receive = getTradeReceived($request);
			sleep(5);
		if($receive['status'] == "complete"){
			sleep(1);
			ctools_include('ajax');
				 ctools_add_js('ajax-responder');
			$commands = array();
			//$commands[] = ajax_command_replace('#awaiting_payment','<div id="awaiting_payment"> Payment Complete </div>');
		     	$commands[] = ctools_ajax_command_redirect('Trading/complete/'.$coin.'/'.$address);
			print ajax_render($commands);
			drupal_exit();
				/// redirect to page
		}else if($receive['status'] == "maxconfirm"){
				$commands = array();
				$commands[] = ajax_command_replace('#awaiting_payment','<div id="awaiting_payment"> Payment Received, Waiting for MAX Confirm </div>');
				print ajax_render($commands);
				drupal_exit();
				/// redirect to page
		} else if($receive['status'] == "pending"){
				$commands = array();
				$commands[] = ajax_command_replace('#awaiting_payment','<div id="awaiting_payment"> WAITING FOR PAYMENT </div>');
				print ajax_render($commands);
				drupal_exit();
		}else if($receive['status'] == "incomplete"){
				$commands = array();
				$commands[] = ajax_command_replace('#popup_info','<div id="popup_info">Not Enough despoited ('.$receive['balance'].' '. $receive['receive_coin'] .' ), please deposit remaining '.$receive['remaining'].'</div>');
				print ajax_render($commands);
				drupal_exit();
		}else if($receive['status'] == "remittance"){
				$commands = array();
				$commands[] = ajax_command_replace('#popup_info','<div id="popup_info">You deposited more than the required amount ('.$receive['expected'].' '. $receive['receive_coin'] .' ), please enter remittance address to receive the remaining '.$receive['remaining'].' '. $receive['receive_coin'].'</div>');
				print ajax_render($commands);
				drupal_exit();
		}else if($receive['status'] == "error_max"){
				$commands = array();
				$commands[] = ajax_command_replace('#popup_info','<div id="popup_info"> API Disabled/Offline </div>');
				print ajax_render($commands);
				drupal_exit();
		}else if($receive['status'] == "validation"){
				$commands = array();
				$commands[] = ajax_command_replace('#awaiting_payment','<div id="awaiting_payment"> Trade Validation Error </div>');
				print ajax_render($commands);
				drupal_exit();
		}else {
				$commands = array();
				$commands[] = ajax_command_replace('#awaiting_payment','<div id="awaiting_payment"> WAITING FOR PAYMENT </div>');
				print ajax_render($commands);
				drupal_exit();
		}
	} /// end condition for validation of all parameters (errorCount)
}

