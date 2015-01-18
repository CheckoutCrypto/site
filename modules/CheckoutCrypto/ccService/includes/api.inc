<?php

function ccApiNewOrder($coin, $amount) {
    module_load_include('inc', 'ccAccount', 'includes/cc');
    module_load_include('inc', 'ccService', 'includes/lib');
	$apikey = getUserKey();
    try {
        $ccApi = new CheckoutCryptoApi();
        $response = $ccApi->query(array('action' => 'getnewaddress','apikey' => $apikey, 'coin' => $coin,'amount' => $amount));
    } catch (exception $e) {
        watchdog('ccApiNewOrder', 'API query for new order failed: !fault', $e->getMessage());
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


function ccApiOrderStatus($queue_id, $coin) {
    module_load_include('inc', 'ccAccount', 'includes/cc');
    module_load_include('inc', 'ccService', 'includes/lib');
	$apikey = getUserKey();
    try {
        $ccApi = new CheckoutCryptoApi();
        $response = $ccApi->query(array('action' => 'getstatus','apikey' => $apikey, 'queueid' => $queue_id, 'coin' => $coin));
    } catch (exception $e) {
        watchdog('ccApiOrderStatus', 'API query for status failed: !fault', $e->getMessage());
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

function ccApiAddressBalance($coin_name, $coin_amount, $address) {
   module_load_include('inc', 'ccAccount', 'includes/cc');
    module_load_include('inc', 'ccService', 'includes/lib');
	$apikey = getUserKey();

    try {
        $ccApi = new CheckoutCryptoApi();
        $response = $ccApi->query(array('action' => 'getreceivedbyaddress','apikey' => $apikey, 'coin' => $coin_name, 'address' => $address, 'amount' => $coin_amount, 'confirms' => '1'));
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


function ccApiServiceCharge($gid, $coin){
   module_load_include('inc', 'ccAccount', 'includes/cc');
    module_load_include('inc', 'ccService', 'includes/lib');
    module_load_include('inc', 'ccAccount', 'includes/cc-php/lib');
	$apikey  = getServerKey();
global $user;
	try {
        $ccApi = new CheckoutCryptoApi();
        $response = $ccApi->query(array('action' => 'servicecharge','apikey' => $apikey, 'coin'=>$coin, 'gid'=>$gid, 'uid'=>$user->uid));
    } catch (exception $e) {
        watchdog('ccApiServiceCharge', 'API query for new order failed: !fault', $e->getMessage());
    }
		if($response['response']['status'] == "success") {	
			return true;
		
	}
	return false;
}
