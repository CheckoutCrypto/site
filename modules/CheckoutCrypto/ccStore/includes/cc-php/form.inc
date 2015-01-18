<?php

/**
 * Author: Grant Hutchinson - CheckoutCrypto - dreamcode@checkoutcrypto.com
 * Copyright 2014 Apache 2.0 Licensed
 **/


/**
 * Form for checkout crypto payment
 */
function ccStore_form($form, $form_state) {

    module_load_include('inc', 'ccStore', 'includes/cc-php/service');

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
	array_push($form, coinSelectWrapper($cc_class_sel));
	array_push($form, paymentWrapper($cc_class_pay));
  	$form['wrapper_end'] = array('#markup' => t('</div></div>'));
  	return $form; 
}



function ccStore_cart_form($order){
    drupal_add_css('sites/all/modules/checkoutcrypto/CheckoutCrypto/ccStore/ccStore.css', 'file');

    global $base_path;
    global $base_url;
    module_load_include('inc', 'ccStore', 'includes/cc-php/lib');
    $coins = getAvailableCoins();
    $modp = drupal_get_path('module','ccStore');

    $payment_form = array();
    $payment_form['cc-notice'] = array(
        '#markup' => '<p>' . t('This store supports cryptocurrency payments, you can pay the current market exchange rate of your order from %currency to any of the accepted currencies, Once the order is confirmed you will receive the address to send to.', array('%currency' => $order->currency)) . '</p>'
    );
    $payment_form['cc-notice-coins-wrapper'] = array('#markup' => '<div id="cc_coin_enabled_wrapper">');
    foreach($coins as $coin){
        $coin_code = strtolower($coin['coin_code']);
        $coin_image = $coin['coin_image'];
        $payment_form['cc-notice-coins'.$coin_code] = array(
            '#markup' => t('<div id="cc_coin_preview_'.$coin_code.'" class="cc_coin_coins_preview"><img src="'.$base_url.'/sites/default/files'.$coin_image.'" width="50" height="50" /></div>')
        );
    }
    $payment_form['cc-notice-coins-wrapper-end'] = array('#markup' => '</div>');

	return $payment_form;
}




