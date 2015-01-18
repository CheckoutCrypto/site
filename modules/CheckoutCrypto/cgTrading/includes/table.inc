<?php

function getTradeTable(){
		module_load_include('inc', 'ccCoin', 'includes/cc-php/lib');
	$header = array(
		array('data' => t('Amount'), 'field' => 'amount_to', 'id' => 'tabhead'),   // https://coingateway.net/downloads/images/contents/input.png 
		array('data' => 'TXID', 'field' => 'TXID', 'id' => 'tabhead',),  /// <img src="https://coingateway.net/downloads/images/contents/transact.png" />
		array('data' => 'Date', 'field' => 'timestamp',  'sort' => 'desc', 'id' => 'tabhead',),  /// <img src="https://coingateway.net/downloads/images/contents/clock.png" />

);
	// $header = validateSort($head_item, $sort);
$result = db_select('ccdev_trades')
		->extend('PagerDefault')
		 ->extend('TableSort');

	$result->condition('status', '2', '=')
			->fields('ccdev_trades', array('coin_to', 'amount_to', 'coin_from', 'amount_from', 'address_gen', 'address_out', 'txid', 'timestamp'))
		->limit(5)
		 ->orderByHeader($header);

	$results =   $result->execute();
	$rows = array();
	$coins = getAllCoinCodes();
	foreach($results as $row){
			
	$cointo_img = getIndividualCoinImg($coins,$row->coin_to);
	$coinfrom_img = getIndividualCoinImg($coins, $row->coin_from);

		$rows[] = array('<img src="'. $coinfrom_img. '" id="coinLogoTrans"/>'.  $row->amount_from . ' '. '<img src="'. $cointo_img. '" id="coinLogoTrans" />'. ' '.  $row->amount_to,
 					$row->txid, 
					$row->timestamp, 
		);
	}

    // Put our entities into a themed table. See theme_table() for details.
    $content['entity_table'] = array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#header' => $header,
      '#attributes' => array(
          'id' => 'sort-table trans_table')
    );

    //Add pagination to table
    $content['pager'] = array(
      '#theme' => 'pager');
    

  return $content;
}
