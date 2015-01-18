<?php

function genTradeAddress($request, $ignore_amt) {
    module_load_include('inc', 'ccAccount', 'includes/cc-php/cc');
     module_load_include('inc', 'cgTrading', 'includes/lib');
	global $user;
	if($user->uid){
		$apikey = getUserKey($user->uid);
	}else{
		$apikey = getDefaultKey();
	}
    try {
        $cgApi = new CoingatewayAPI();
        $response = $cgApi->query(array('action' => 'gettradeaddress','apikey' => $apikey, 'coin' => $request['coin'],'amount' => $request['amount'], 'coin_trade' => $request['coin_trade'], 'address' => $request['address'], 'coin_amt_type' => $request['coin_amt_type'], 'ignore_amt' => $ignore_amt));
    } catch (exception $e) {
        watchdog('uc_cc_ccApiNewOrder', 'API query for new order failed: !fault', $e->getMessage());
    }

    if(isset($response['response']['address'])) {
        $result['address'] = $response['response']['address'];
        $result['coin_in'] = $response['response']['deposit_coin'];
        $result['coin_out'] = $response['response']['receive_coin'];
        $result['deposit_amt'] = $response['response']['deposit_amt'];
        $result['receive_amt'] = $response['response']['receive_amt'];
        $result['success'] = TRUE;
        return $result;
    } else {
        $result['success'] = FALSE;
       return $result;
    } 
}
function getTradeStatus($queue_id, $coin) {
    module_load_include('inc', 'cgTrading', 'includes/cc');
      module_load_include('inc', 'cgTrading', 'includes/lib');
	global $user;
	if($user->uid){
		$apikey = getUserKey($user->uid);
	}else{
		$apikey = getDefaultKey();
	}
    try {
        $cgApi = new CoingatewayAPI();
        $response = $cgApi->query(array('action' => 'gettradestatus','apikey' => $apikey, 'orderid' => $queue_id, 'coin' => $coin));
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
	if($response['response']['status'] == "error"){
	    $result['balance'] = FALSE;
	    $result['status'] = 'error';
	    $result['coin'] = $response['response']['coin'];
	}
        $result['success'] = TRUE;
        return $result;
    } else {
        $result['success'] = FALSE;
       return $result;
    }
}


function getTradeReceived($request) {
    module_load_include('inc', 'ccAccount', 'includes/cc-php/cc');
     module_load_include('inc', 'cgTrading', 'includes/lib');
	global $user;
	if($user->uid){
		$apikey = getUserKey($user->uid);
	}else{
		$apikey = getDefaultKey();
	}
    try {
        $cgApi = new CoingatewayAPI();
        $response = $cgApi->query(array('action' => 'gettradereceived','apikey' => $apikey, 'coin' => $request['coin'], 'address' => $request['address'], 'confirms' =>  $request['confirms']));
    } catch (exception $e) {
        watchdog('uc_cc_ccApiAddressBalance', 'API query for balance failed: !fault', $e->getMessage());
    }
    if(isset($response['response']['status'])) {
        if($response['response']['status'] == "complete"){
			$result['balance'] = $response['response']['balance'];
			$result['fee'] = $response['response']['fee'];
			$result['txid'] = $response['response']['txid'];
		        $result['status'] = 'complete';
		}else if($response['response']['status'] == "success"){
			$result['balance'] = $response['response']['balance'];
			$result['fee'] = $response['response']['fee'];
			$result['txid'] = $response['response']['txid'];
		        $result['status'] = 'complete';
		} else if($response['response']['status'] == "pending"){
			$result['balance'] = $response['response']['balance'];
			$result['fee'] = $response['response']['fee'];
			$result['txid'] = $response['response']['txid'];
		        $result['status'] = 'pending';
		}
		else if($response['response']['status'] == "maxconfirm"){
			$result['balance'] = $response['response']['balance'];
			$result['fee'] = $response['response']['fee'];
			$result['txid'] = $response['response']['txid'];
		        $result['status'] = 'maxconfirm';
		}
		else if($response['response']['status'] == "remittance"){
			$result['balance'] = $response['response']['balance'];
			$result['coin'] = $response['response']['coin'];
		         $result['status'] = 'remittance';
		}else if($response['response']['status'] == "incomplete"){
			$result['balance'] = $response['response']['balance'];
			$result['remaining'] = $response['response']['expected'] - $response['response']['balance'];
			$result['coin'] = $response['response']['coin'];
		        $result['status'] = 'incomplate';
		}else if($response['response']['status'] == "remittance"){
			$result['balance'] = $response['response']['balance'];
			$result['remaining'] = $response['response']['balance'] - $response['response']['expected'];
			$result['expected'] = $response['response']['expected'];
			$result['coin'] = $response['response']['coin'];
		        $result['status'] = 'remittance';
		}else if($response['response']['status'] == "error"){
		    $result['balance'] = FALSE;
		    $result['status'] = 'error';
		    $result['coin'] = $response['response']['coin'];
		}
	}else{
        $result['status'] = FALSE;
	}
	return $result;
}
