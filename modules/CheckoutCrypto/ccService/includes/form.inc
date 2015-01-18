<?php

/**
 * Form for checkout crypto payment
 */
function ccService_form($form, $form_state) {

    if(isset($_SESSION['cart_order'])) { //locate the current order from the session
        $order = uc_order_load(intval($_SESSION['cart_order']));
     } else {
       // watchdog('ccStore_form', 'Could not load current order: !fault', $e->getMessage());
     }

    $cc_class_sel = 'uc_cc_show';
    $cc_class_pay = 'uc_cc_hide';        

    // Initiate form and add wrappers
    $form = array();
    $form['wrapper_header'] = array('#markup' => t('<div id="cc-wrapper"><div id="cc_pay"></div><div id="cc-border">'));

	//$form['ccStore_payment_processing_wrapper'] = array('#markup' => t('<div id="cc_payment_processing_wrapper"></div>'));

	/// double check this pushes to the form array
	$form += coinWrapper($cc_class_sel);
	$form += serviceWrapper($cc_class_pay);
	$form += paymentWrapper($cc_class_pay);
  	$form['wrapper_end'] = array('#markup' => t('</div></div>'));
  	return $form; 
}

/*
* Payment Wrapper
*  Create a html div wrapper with a title, button, hidden variable
*/
function paymentWrapper($cc_class_pay){
	///// start payment processing wrapper
	$form['ccStore_payment_wrapper'] = array('#markup' => t('<div id="cc_payment_processing_wrapper" class="'.$cc_class_pay.'">'));
	$form['ccStore_information'] = array('#markup' => t('<p id="cc_payment_information">Checking User Account Balance....</p>'));
    $form['ccStore_payment_address'] = array(
        '#type' => 'textfield',
        '#value' => t(''),
        '#attributes' => array('readonly' => 'readonly','size' => 50),
        '#prefix' => '<div id="uc_cc_payment_address_container" >',
        '#suffix' => '</div>',
        );
    $form['ccStore_payment_qr_address'] = array(
      '#markup' => '<div id="uc_cc_payment_qr_address_container" class="'.$cc_class_pay.'"></div>'
    );
    $form['actions']['reselect'] = array('#markup' => '<br><div id="cc_reselect_coin" class="uc_cc_show"><a id="cc_coin_reselect" class="btn btn-primary" style="cursor: pointer">Change currency</a>');  
    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
        '#ajax' => array(
            'callback' => 'ccStore_form_submit',),
    );
    $form['ccStore_progress_status'] = array(
      '#markup' => '<div id="cc-payment-status" ><div id="cc_progress_status">This window will auto-refresh status until order is complete</div><div id="cc_progress_timer"></div>',
    );
   ///// End payment processing wrapper 
   $form['ccStore_payment_wrapper_end'] = array('#markup' => t('</div>'));
	return $form;
}

/*
* Service charge Wrapper
*  Create a html div wrapper with a title, button, hidden variable
*/
function serviceWrapper($cc_class_pay){

	///// start service charge wrapper
	$form['cc_service_payment_wrapper'] = array('#markup' => t('<div id="cc_service_payment_wrapper" class="'.$cc_class_pay.'">'));
	$form['cc_service_payment'] = array('#markup' => t('<div id="cc_service_information">Checking Balance</div>'));
	$form['cc_service_charge'] = array(
		'#markup' => '<div id="cc_coin_charge" class="uc_cc_show"><a id="cc_coin_charge" class="btn btn-primary" style="cursor: pointer">Service Charge</a></div>',
      	'#value' => t('Service Charge'),
        '#ajax' => array(
            'callback' => 'service_charge_submit'),);
	$form['uc_cc_payment_type'] = array(
		   '#type' => 'hidden',
		   '#value' => t(''),
		   );
  // $form['uc_cc_service_fund'] = array('#markup' => '<div id="cc_coin_fund" class="uc_cc_show"><a id="cc_coin_fund" class="btn btn-primary" style="cursor: pointer">Fund Account</a></div><br />');  

	/////  End service charge wrapper
   $form['uc_cc_service_payment_wrapper_end'] = array('#markup' => t('</div>'));
	return $form;
}


/*
* Coin Choice Wrapper
*  Create a html div wrapper with a title, button, hidden variable
*/
function coinWrapper($cc_class_sel){
    global $base_url;
    module_load_include('inc', 'ccSend', 'includes/cc-php/lib');
	 $coins = getAvailableCoins();

	///// start Coin Select wrapper
   $form['ccStore_coin_select_wrapper'] = array('#markup' => t('<div id="cc_coin_select_wrapper" class="'.$cc_class_sel.'">'));
    $form['ccStore_payment_information'] = array(
      '#markup' => t('<div id="cc_coin_information"><p>Please select your preferred cryptocurrency to continue with payment</p></div>')
    );

    //Available coins
   foreach($coins as $coin){

       $coin_code = strtolower($coin['coin_code']);
	   $coin_image = $coin['coin_image'];
	   $coin_name = $coin['coin_name'];
  	   $form['ccStore_coin_select_'.$coin_code] = array('#markup' => t('<div class="cc_coin" id="cc_coin_'.$coin_code.'"></div>
		<style type="text/css">
		 #cc_coin_'.$coin_code.' { background:url("'.$coin_image.'") left no-repeat; }
		</style>'));
   }
	//// hidden stored coin variable
   $form['ccStore_selected_coin'] = array(
       '#type' => 'hidden',
       '#value' => t(''),
       );

   ///// End coin select wrapper 
   $form['ccStore_coin_select_wrapper_end'] = array('#markup' => t('</div>'));
	return $form;
}

function service_charge_submit($ajax, $data){

	$commands[] = ctools_modal_command_dismiss();
	print ajax_render($commands);
	drupal_exit();
}
function fillServiceWrapper($coin_code, $group){
   module_load_include('inc', 'ccGroup', 'includes/cc-php/lib');
	$groupdata = getGroupData($group);
	$form['cc_service_payment'] = array('#markup' => '<div id="cc_service_information">
										<p><br> Your account contains enough to fund this service charge. Press fund account to continue using this coin. ' .
										'This coin\'s wallet will be billed every '.$groupdata['grp_payment_length']. ' days in the amount of $'. $groupdata['grp_price'] .
										' using your '.$coin_code.' </p>');
    
	$form['cc_service_charge'] = array(
		'#markup' => '<div id="cc_coin_charge" class="uc_cc_show"><a id="cc_coin_charge" class="btn btn-primary" style="cursor: pointer">Service Charge</a></div>',
      	'#value' => t('Service Charge'),
        '#ajax' => array(
            'callback' => 'service_charge_submit'),);       
	$commands[] = ajax_command_replace('#cc_service_information', drupal_render($form['cc_service_payment']));
	$commands[] = ajax_command_replace('#cc_coin_charge', drupal_render($form['cc_service_charge']));
	print ajax_render($commands);
    drupal_exit();
}


function fillPaymentWrapper($balance, $coin_name_full, $coin_name, $coin_amount, $address){
	 module_load_include('inc', 'ccStore', 'includes/cc-php/lib');
	$form['ccStore_information'] = array('#markup' => '<div id="cc_payment_information"><p>Selected currency: <strong>'.$coin_name_full.'</strong><br>Your current account balance for this coin is: ' .
										$balance.'</p><br><p>Please send <strong>'.$coin_name.' '.$coin_amount.'</strong> to the following address</p></div>');

	$genQR = generateQR($address, 150);

	$form['ccStore_payment_address'] = array(
		      '#type' => 'textfield',
		      '#value' => t($address),
		      '#attributes' => array('readonly' => 'readonly','size' => 50),
		      '#prefix' => '<div id="uc_cc_payment_address_container">',
		      '#suffix' => '</div>',
	);
	$form['ccStore_payment_qr_address'] = array(
		  '#markup' => '<div id="uc_cc_payment_qr_address_container">'.$genQR.'</div>'
	 );
	$commands[] = ajax_command_replace('#cc_payment_information', drupal_render($form['ccStore_information']));
	$commands[] = ajax_command_replace('#uc_cc_payment_address_container', drupal_render($form['ccStore_payment_address']));
	$commands[] = ajax_command_replace('#uc_cc_payment_qr_address_container', drupal_render($form['ccStore_payment_qr_address']));              
	print ajax_render($commands);
    drupal_exit(); 
}

function fillQrWrapper($address){
	 module_load_include('inc', 'ccStore', 'includes/cc-php/lib');
	$form['ccStore_information'] = array('#markup' => '<div id="cc_payment_information"><p>Selected currency: <strong>'.$coin_name_full.'</strong><br>Your current account balance for this coin is: ' .
										$balance.'</p><br><p>Please send <strong>'.$coin_name.' '.$coin_amount.'</strong> to the following address</p></div>');

	$genQR = generateQR($address, 150);

	$form['ccStore_payment_address'] = array(
		      '#type' => 'textfield',
		      '#value' => t($address),
		      '#attributes' => array('readonly' => 'readonly','size' => 50),
		      '#prefix' => '<div id="uc_cc_payment_address_container">',
		      '#suffix' => '</div>',
	);
	$form['ccStore_payment_qr_address'] = array(
		  '#markup' => '<div id="uc_cc_payment_qr_address_container">'.$genQR.'</div>'
	 );
	$commands[] = ajax_command_replace('#cc_payment_information', drupal_render($form['ccStore_information']));
	$commands[] = ajax_command_replace('#uc_cc_payment_address_container', drupal_render($form['ccStore_payment_address']));
	$commands[] = ajax_command_replace('#uc_cc_payment_qr_address_container', drupal_render($form['ccStore_payment_qr_address']));              
	print ajax_render($commands);
    drupal_exit(); 
}



function ccservice_funds($form, &$form_state){
	$final = array();
	$result = array();
	$coins = array();
	$groups = array();
  	module_load_include('inc', 'ccService', 'includes/lib');
  	module_load_include('inc', 'ccGroup', 'includes/cc-php/lib');
	$coins = getAllUserCoin();
	$groups = getGroupData($form_state['group']);
	foreach($coins as $cn){
		$final['coin_code'] = $cn['coin_code'];
		$final['coin_balance'] = $cn['coin_amt'];
		array_push($result, $final);	
	}

	array_push($result, $groups);

	var_dump($result);
break;


 
  return $form;
}


