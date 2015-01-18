<?php

function getRatesTable(){
	global $user;
	module_load_include('inc', 'ccCoin', 'includes/cc-php/lib');
	$header = array(
		array('data' => 'Coins', 'field' => 'coin_rate_btc', 'id' => 'rate_coin_head', 'sort' => 'desc'),
		// array('data' => 'USD', 'field' => 'coin_rate', 'id' => 'rate_usd_head',), 
	);
	// $header = validateSort($head_item, $sort);
$result = db_select('ccdev_coin')
		->extend('PagerDefault')
		->extend('TableSort');

	$result->fields('ccdev_coin', array('coin_code', 'coin_rate', 'coin_rate_btc'))
		->limit(4)
		 ->orderByHeader($header);

	$results =   $result->execute();
	$rows = array();
	$coins = getAllCoinCodes();
	foreach($results as $row){
			
	$coin_img = getIndividualCoinImg($coins, $row->coin_code);
		if($row->coin_code == "BTC"){
			$rate = '$ '.$row->coin_rate;
		}else{
			$rate = $row->coin_rate_btc . ' BTC';
		}
		$rows[] = array(
			'data' => array(
					array('data' => '<img src="'. $coin_img. '" id="coinLogoTrans"/>'.  $rate, ),
					// array('data' => $row->coin_rate ),
			 ),
 		 );
	}
	$content['ourtitle'] = array('#markup'=> '<h2 id="ratesheader" class="text-center"> Rates </h2>');
    // Put our entities into a themed table. See theme_table() for details.
    $content['entity_table'] = array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#header' => $header,
      '#attributes' => array(
          'id' => 'sort-table rate_table')
    );

    //Add pagination to table
  /*  $content['pager'] = array(
      '#theme' => 'pager'); */
    

  return $content;
}
