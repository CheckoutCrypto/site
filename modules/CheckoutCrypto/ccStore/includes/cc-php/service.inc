<?php
/**
 * Author: Grant Hutchinson - CheckoutCrypto - dreamcode@checkoutcrypto.com
 * Copyright 2014 Apache 2.0 Licensed
 **/

function coinSelectWrapper($cc_class_sel){
    global $base_url;
    module_load_include('inc', 'ccStore', 'includes/cc-php/lib');
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
		 #cc_coin_'.$coin_code.' { background:url("'.$base_url.'/sites/default/files'. $coin_image.'") left no-repeat; }
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


function paymentWrapper($cc_class_pay){
	///// start payment processing wrapper
	$form['ccStore_payment_wrapper'] = array('#markup' => t('<div id="cc_payment_processing_wrapper" class="'.$cc_class_pay.'">'));
	$form['ccStore_payment_information'] = array('#markup' => '<div id="cc_payment_information"><p></p></div>');
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

function fillPaymentWrapper($coin_name_full, $coin_name, $coin_amount){
	$form['ccStore_payment_information'] = array('#markup' => '<div id="cc_payment_information"><p>Selected currency: <strong>'
		.$coin_name_full.'</strong><br>Please send <strong>'.$coin_name.' '.$coin_amount.'</strong> to the following address</p></div>');
           
	$commands[] = ajax_command_replace('#cc_payment_information', drupal_render($form['ccStore_payment_information']));
	ajax_render($commands);
}

function fillQrWrapper($address){
	 module_load_include('inc', 'ccStore', 'includes/cc-php/lib');
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

	$commands[] = ajax_command_replace('#uc_cc_payment_address_container', drupal_render($form['ccStore_payment_address']));
	$commands[] = ajax_command_replace('#uc_cc_payment_qr_address_container', drupal_render($form['ccStore_payment_qr_address']));              
	print ajax_render($commands);
    drupal_exit(); 
}


function fillTimeLimitWrapper($msg){
	$form['ccStore_payment_information'] = array('#markup' => '<div id="cc_payment_information">'.$msg.'</div>');
	$commands[] = ajax_command_replace('#cc_payment_information', drupal_render($form['ccStore_payment_address']));
    print ajax_render($commands);
    drupal_exit(); 
}

