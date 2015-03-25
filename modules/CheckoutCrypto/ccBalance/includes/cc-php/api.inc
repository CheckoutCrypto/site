<?php


function genAddress($coin) {
    module_load_include('inc', 'ccAccount', 'includes/cc-php/cc');
     module_load_include('inc', 'cgTrading', 'includes/lib');
	$apikey = getUserApi();
    try {
        $cgApi = new CheckoutCryptoAPI();
        $response = $cgApi->query(array('action' => 'getnewaddress','apikey' => $apikey, 'coin' => $coin));
    } catch (exception $e) {
        watchdog('genAddress', 'API query for new order failed: !fault', $e->getMessage());
    }
    if(isset($response['response']['address'])) {
        $result['address'] = $response['response']['address'];
        $result['success'] = TRUE;
        return $result['address'];
    } else {
        $result['success'] = FALSE;
       return $result;
    } 
}

function ccWithdrawRequestTwoFact($apikey, $twofa, $RECIPIENT, $amount, $coin_code) {
    module_load_include('inc', 'ccAccount', 'includes/cc-php/cc');

    $ccApi = new CheckoutCryptoAPI($apikey);
	$response = $ccApi->query(array('action' => 'send','address' => $RECIPIENT, 'twofa' => $twofa,'apikey' => $apikey,'amount' => $amount, 'coin' => $coin_code));
    return $response;
} 

function ccWithdrawRequest($apikey, $RECIPIENT, $amount, $coin_code) {
    module_load_include('inc', 'ccAccount', 'includes/cc-php/cc');
    $ccApi = new CheckoutCryptoAPI($apikey);

	$response = $ccApi->query(array('action' => 'pendwithdraw','address' => $RECIPIENT, 'apikey' => $apikey,'amount' => $amount, 'coin' => $coin_code));
	return $response;
} 

function ccSendFundsRequest($apikey, $RECIPIENT, $amount, $coin_code) {
    module_load_include('inc', 'ccAccount', 'includes/cc-php/cc');
    $ccApi = new CheckoutCryptoAPI($apikey);

	$response = $ccApi->query(array('action' => 'sendfunds','address' => $RECIPIENT, 'apikey' => $apikey,'amount' => $amount, 'coin' => $coin_code));
	return $response;
} 

