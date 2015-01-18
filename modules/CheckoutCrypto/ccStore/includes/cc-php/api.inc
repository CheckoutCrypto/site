<?php

/**
 * Author: Grant Hutchinson - CheckoutCrypto - dreamcode@checkoutcrypto.com
 * Copyright 2014 Apache 2.0 Licensed
 **/


function ccApiRefreshCoins(){
    module_load_include('inc', 'uc_cc', 'includes/cc-php/cc');
    module_load_include('inc', 'ccStore', 'includes/cc-php/lib');
    $apikey = variable_get('uc_cc_server_apikey', '');
	$count = 0;
    try {
        $ccApi = new CheckoutCryptoApi();
        $response = $ccApi->query(array('action' => 'refreshcoins','apikey' => $apikey));
    } catch (exception $e) {
        watchdog('uc_cc_ccApiRefreshCoins', 'API query for new order failed: !fault', $e->getMessage());
    }
    if(isset($response['response']['coins'])) {
		foreach($response['response']['coins'] as $coin){
			$coin_name = $coin['coin_name'];
			$coin_code = $coin['coin_code'];
			$coin_rate = $coin['rate'];
			$coin_image = $coin['coin_image'];
			$result = addCoin($coin_name, $coin_code, $coin_rate);
			cacheImage($coin_image);
			$count++;
		}
        return $result;
   } else {
        $result['success'] = FALSE;
       return $result;
   }

}

function cacheImage($coinUrl){
$directory = 'public://checkoutcrypto'; 
  if (!file_prepare_directory($directory, FILE_CREATE_DIRECTORY)) {
    $directory = NULL;
  }
  $file = system_retrieve_file($coinUrl, $directory, TRUE);
}

function ccApiNewOrder($request) {
    module_load_include('inc', 'ccStore', 'includes/cc-php/cc');
    module_load_include('inc', 'ccStore', 'includes/cc-php/lib');
	 $apikey = variable_get('uc_cc_server_apikey', '');
    try {
        $ccApi = new CheckoutCryptoApi();
        $response = $ccApi->query(array('action' => 'getnewaddress','apikey' => $apikey, 'coin' => $request['coin_name'],'amount' => $request['coin_amount']));
    } catch (exception $e) {
        watchdog('uc_cc_ccApiNewOrder', 'API query for new order failed: !fault', $e->getMessage());
    }
    if(isset($response['response']['queue_id'])) {
        $result['queue_id'] = $response['response']['queue_id'];
        $result['success'] = TRUE;
        return $result;
    } else {
        $result['success'] = FALSE;
       return $result;
    } 
}


function ccApiAddressBalance($request) {
    module_load_include('inc', 'ccStore', 'includes/cc-php/cc');
    module_load_include('inc', 'ccStore', 'includes/cc-php/lib');
	 $apikey = variable_get('uc_cc_server_apikey', '');

    try {
        $ccApi = new CheckoutCryptoApi();
        $response = $ccApi->query(array('action' => 'getreceivedbyaddress','apikey' => $apikey, 'coin' => $request['coin_name'], 'address' => $request['address'], 'amount' => $request['coin_amount'], 'confirms' => '1'));
    } catch (exception $e) {
        watchdog('uc_cc_ccApiAddressBalance', 'API query for balance failed: !fault', $e->getMessage());
    }

    if(isset($response['response']['orderid'])) {
        $result['queue_id'] = $response['response']['orderid'];
        $result['success'] = TRUE;
        return $result;
    } else {
        $result['success'] = FALSE;
       return $result;
    }
}

function ccApiExchangeRate($request) {
    module_load_include('inc', 'ccStore', 'includes/cc-php/cc');
    module_load_include('inc', 'ccStore', 'includes/cc-php/lib');
	 $apikey = variable_get('uc_cc_server_apikey', '');

    try {
        $ccApi = new CheckoutCryptoApi();
        $response = $ccApi->query(array('action' => 'getrate','apikey' => $apikey, 'coin' => $request['coin_name']));
    } catch (exception $e) {
        watchdog('uc_cc_ccApiExchangeRate', 'API query for exchange rate failed: !fault', $e->getMessage());
    }

    if(isset($response['response']['rates'])) {
        $result['rate'] = $response['response']['rates']['USD_'.$request['coin_name']];
        $result['success'] = TRUE;
        return $result;
    } else {
        $result['success'] = FALSE;
       return $result;
    }
}


function ccApiOrderStatus($queue_id, $coin) {
    module_load_include('inc', 'ccStore', 'includes/cc-php/cc');
    module_load_include('inc', 'ccStore', 'includes/cc-php/lib');
	 $apikey = variable_get('uc_cc_server_apikey', '');
    try {
        $ccApi = new CheckoutCryptoApi();
        $response = $ccApi->query(array('action' => 'getstatus','apikey' => $apikey, 'orderid' => $queue_id, 'coin' => $coin));
    } catch (exception $e) {
        watchdog('uc_cc_ccApiOrderStatus', 'API query for status failed: !fault', $e->getMessage());
    }
    if(isset($response['response']['status'])) {
        $result['status'] = $response['response']['status'];
        if(isset($response['response']['address'])) {
            $result['address'] = $response['response']['address'];
        } else {
            $result['address'] = FALSE;
        }
        if(isset($response['response']['balance'])) {
            $result['balance'] = $response['response']['balance'];
        } else {
            $result['balance'] = FALSE;
        }
        $result['success'] = TRUE;
        return $result;
    } else {
        $result['success'] = FALSE;
       return $result;
    }
}
