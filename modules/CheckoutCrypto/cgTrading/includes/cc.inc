<?php

class CoingatewayAPI {

  public function __construct() {
    //construct
  }

  public function query($params) {

    if(isset($params['apikey']) AND isset($params['action'])) {
        $action = $params['action'];
        $apikey = $params['apikey'];
    }

   $base_url = 'https://api.coingateway.net/';
    $arguments = '?apikey='.$apikey;

    switch ($action) {
      case 'getnewaddress':
        $coin_name = $params['coin'];
        $arguments .= '&action='.$action.'&coin='.$coin_name;
        $url = $base_url . $arguments;
        $result = $this->urlRequest($url);
        break;
      case 'send':
        $twofa = $params['twofa'];
        $coin_amount = $params['amount'];
        $coin_name = $params['coin'];
		$sender = $params['address'];
        $arguments .= '&action='.$action.'&twofa='.$twofa.'&coin='.$coin_name.'&amount='.$coin_amount.'&address='.$sender;
        $url = $base_url . $arguments;
        $result = $this->urlRequest($url);
        break;
    case 'pendwithdraw':
        $coin_amount = $params['amount'];
        $coin_name = $params['coin'];
		$sender = $params['address'];
		$action = 'send';
        $arguments .= '&action='.$action.'&coin='.$coin_name.'&amount='.$coin_amount.'&address='.$sender;
        $url = $base_url . $arguments;
        $result = $this->urlRequest($url);
        break;
    case 'sendfunds':
        $coin_amount = $params['amount'];
        $coin_name = $params['coin'];
		$sender = $params['address'];
		$action = 'sendfunds';
        $arguments .= '&action='.$action.'&coin='.$coin_name.'&amount='.$coin_amount.'&address='.$sender;
        $url = $base_url . $arguments;
        $result = $this->urlRequest($url);
        break;
      case 'getstatus':
        $orderid = $params['orderid'];
        $coin_name = $params['coin'];
        $arguments .= '&action='.$action.'&orderid='.$orderid.'&coin='.$coin_name;
        $url = $base_url . $arguments;
        $result = $this->urlRequest($url);
        break;
      case 'getbalance':
        $coin_name = $params['coin'];
        $arguments .= '&action='.$action.'&coin='.$coin_name;
        $url = $base_url . $arguments;
        $result = $this->urlRequest($url);
        break;
     case 'gettransaction':
        $coin_name = $params['coin'];
        $trans_id = $params['tranid'];
        $arguments .= '&action='.$action.'&coin='.$coin_name.'&tranid='.$trans_id;
        $url = $base_url . $arguments;
        $result = $this->urlRequest($url);
        break;
     case 'getreceivedbyaddress':
        $coin_name = $params['coin'];
        $address = $params['address'];
        $confirms = $params['confirms'];
        $arguments .= '&action='.$action.'&coin='.$coin_name.'&address='.$address.'&confirms='.$confirms;
        $url = $base_url . $arguments;
        $result = $this->urlRequest($url);
        break;
      case 'getrate':
        $coin_name = $params['coin'];
        $arguments .= '&action='.$action.'&coin='.$coin_name.'&rate=USD';
        $url = $base_url . $arguments;
        $result = $this->urlRequest($url);
		break;
     case 'refreshworker':
        $arguments .= '&action='.$action;
        $url = $base_url . $arguments;
        $result = $this->urlRequest($url);
		break;
     case 'gettradeaddress':
        $coin = $params['coin'];
        $coin_to = $params['coin_trade'];
        $amount = $params['amount'];
        $amt_type = $params['coin_amt_type'];
        $address = $params['address'];
		$ignore = $params['ignore_amt'];
        $arguments .= '&action='.$action.'&coin='.$coin.'&amount='.$amount.'&coin_trade='.$coin_to.'&address='.$address.'&ignore_amt='.$ignore.'&amt_type='.$amt_type;
        $url = $base_url . $arguments;
        $result = $this->urlRequest($url);
        break;
      case 'gettradestatus':
        $orderid = $params['orderid'];
        $coin_name = $params['coin'];
        $arguments .= '&action='.$action.'&queueid='.$orderid.'&coin='.$coin_name;
        $url = $base_url . $arguments;
        $result = $this->urlRequest($url);
        break;
     case 'gettradereceived':
        $coin_name = $params['coin'];
        $address = $params['address'];
        $confirms = $params['confirms'];
        $arguments .= '&action='.$action.'&coin='.$coin_name.'&address='.$address.'&confirms='.$confirms;
        $url = $base_url . $arguments;

        $result = $this->urlRequest($url);

        break;
    }
    if(isset($result)) {
        return json_decode($result, true);
    }
    return FALSE;
  }

  function urlRequest($url) {
    try {
      $curl = curl_init();

      $opts = array(
          CURLOPT_URL             => $url,
          CURLOPT_SSL_VERIFYPEER  => 2,
          CURLOPT_SSL_VERIFYHOST  => 2,
          CURLOPT_RETURNTRANSFER  => true, 
          CURLOPT_POST            => false,
          CURLOPT_HEADER         => false,
          CURLOPT_FOLLOWLOCATION => true,
          CURLOPT_ENCODING       => "",
          CURLOPT_AUTOREFERER    => true,
          CURLOPT_CONNECTTIMEOUT => 120,
          CURLOPT_TIMEOUT        => 120,
          CURLOPT_MAXREDIRS      => 10
      );

      curl_setopt_array($curl, $opts);
      $result = curl_exec($curl);
      if (FALSE === $result)
        throw new Exception(curl_error($curl), curl_errno($curl));

      curl_close($curl);
      return $result;

    } catch (exception $e) {
      trigger_error(sprintf(
        'Curl failed with error #%d: %s',
          $e->getCode(), $e->getMessage()),
          E_USER_ERROR);
    }
  }
}
