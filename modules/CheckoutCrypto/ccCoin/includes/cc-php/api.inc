<?php


function ccGetInitAddress($userid, $coin) {
    module_load_include('inc', 'ccBalance', 'includes/cc-php/lib');
    module_load_include('inc', 'ccAccount', 'includes/cc-php/cc');
	$accountdata = array();
	 $accountdata = getUserApiKey();
	$apikey  = $accountdata['api_key'];
    $ccApi = new CoingatewayAPI($apikey);
    $response = $ccApi->query(array('action' => 'getnewaddress','apikey' => $apikey, 'coin' => $coin));
    return $response;
} 

function ccGetAddress($coin) {
    module_load_include('inc', 'ccBalance', 'includes/cc-php/lib');
    module_load_include('inc', 'ccAccount', 'includes/cc-php/cc');
	$accountdata = array();
	 $accountdata = getUserApiKey();
	$apikey  = $accountdata['api_key'];
    $ccApi = new CoingatewayAPI($apikey);
    $response = $ccApi->query(array('action' => 'getnewaddress','apikey' => $apikey, 'coin' => $coin));
    return $response;
} 

function ccApiStatus($queue_id, $coin) {
    module_load_include('inc', 'ccBalance', 'includes/cc-php/lib');
    module_load_include('inc', 'ccAccount', 'includes/cc-php/cc');
	 $accountdata = getUserApiKey();
	$apikey  = $accountdata['api_key'];
    try {
        $ccApi = new CoingatewayAPI();
        $response = $ccApi->query(array('action' => 'getstatus','apikey' => $apikey, 'orderid' => $queue_id, 'coin' => $coin));
    } catch (exception $e) {
        watchdog('ccApiStatus', 'API query for status failed: !fault', $e->getMessage());
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

function ccRefreshRequest() {
    module_load_include('inc', 'ccBalance', 'includes/cc-php/lib');
    module_load_include('inc', 'ccAccount', 'includes/cc-php/cc');
	$accountdata = array();
	 $accountdata = getServerApiKey("rate");
	$apikey  = $accountdata['api_key'];
    $ccApi = new CoingatewayAPI($apikey);
    $response = $ccApi->query(array('action' => 'refreshworker', 'type' => 'coins', 'apikey' => $apikey));
    return $response;
} 
