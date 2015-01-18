<?php

class CheckoutCryptoApi {

  public function __construct() {
    //construct
  }

  public function query($params) {

    if(isset($params['apikey']) AND isset($params['action'])) {
        $action = $params['action'];
        $apikey = $params['apikey'];
    }

    $base_url = 'https://coingateway.net/api/';
    $arguments = '?apikey='.$apikey;
    switch ($action) {
      case 'getnewaddress':
        $coin_name = $params['coin'];
        $coin_amount = $params['amount'];
        $arguments .= '&action='.$action.'&coin='.$coin_name.'&amount='.$coin_amount;
        $url = $base_url . $arguments;
        $result = $this->urlRequest($url);
        break;
      case 'send':
        $coin_amount = $params['amount'];
        $coin_name = $params['coin'];
		$sender = $params['address'];
        $arguments .= '&action='.$action.'&coin='.$coin_name.'&amount='.$coin_amount.'&address='.$sender;
        $url = $base_url . $arguments;
        $result = $this->urlRequest($url);
        break;
      case 'getstatus':
        $orderid = $params['orderid'];
        $coin_name = $params['coin'];
        $arguments .= '&action='.$action.'&queueid='.$orderid.'&coin='.$coin_name;
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
        $amount = $params['amount'];
        $address = $params['address'];
        $confirms = $params['confirms'];
        $arguments .= '&action='.$action.'&coin='.$coin_name.'&address='.$address.'&confirms='.$confirms.'&amount='.$amount;
        $url = $base_url . $arguments;
        $result = $this->urlRequest($url);
        break;
     case 'getrate':
        $coin_name = $params['coin'];
        $arguments .= '&action='.$action.'&coin='.$coin_name.'&rate=USD';
        $url = $base_url . $arguments;
        $result = $this->urlRequest($url);
		break;
      case 'refreshcoins':
        $arguments .= '&action='.$action;
        $url = $base_url . $arguments;
        $result = $this->urlRequest($url);
		break;
      case 'servicecharge':
        $coin_name = $params['coin'];
        $gid = $params['gid'];
        $uid = $params['uid'];
        $arguments .= '&action='.$action.'&coin='.$coin_name.'&uid='.$uid.'&gid='.$gid;
        $url = $base_url . $arguments;
        $result = $this->urlRequest($url);
		break;
    }
    if(isset($result)) {
        $return = json_decode($result, true);
        return $return;
    }
    return FALSE;
  }

  function urlRequest($url) {
    try {
      $curl = curl_init();

      $opts = array(
          CURLOPT_URL             => $url,
          CURLOPT_SSL_VERIFYPEER  => 2, //set to true for production
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
