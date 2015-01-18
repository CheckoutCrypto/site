<?php

function getWalletTable(){
	global $user;
	module_load_include('inc', 'ccCoin', 'includes/cc-php/lib');
	$header = array(
		array('data' => 'Amount', 'field' => 'balance_total', 'id' => 'wall_amount_head'),   // https://coingateway.net/downloads/images/contents/input.png 
		array('data' => 'Address', 'field' => 'walletaddress', 'id' => 'wall_address_head',),  /// <img src="https://coingateway.net/downloads/images/contents/transact.png" />
		array('data' => 'Date', 'field' => 'timestamp',  'sort' => 'desc', 'id' => 'wall_update_head',),  /// <img src="https://coingateway.net/downloads/images/contents/clock.png" />

);
	// $header = validateSort($head_item, $sort);
$result = db_select('ccdev_wallets')
		->extend('PagerDefault')
		->extend('TableSort')
			->fields('ccdev_wallets', array('balance_total', 'coins_enabled', 'walletaddress', 'timestamp'))
		->limit(5)
		 ->orderByHeader($header);

	$results =   $result->execute();
	$rows = array();
	$coins = getAllCoinCodes();
	foreach($results as $row){
			
	$coin_img = getIndividualCoinImg($coins, $row->coins_enabled);

		$rows[] = array(
			'data' => array(
					array('data' => '<img src="'. $coin_img. '" id="coinLogoTrans"/>'.  $row->balance_total, ),
					array('data' => $row->walletaddress, 'name' => 'wall_address_col' ),
					array('data' => $row->timestamp, ),
			 ),
 		 );
	}
	$content['ourtitle'] = array('#markup'=> '<h2 id="wallethead" class="text-center"> Wallets </h2>');
	$content['somebutton'] = array('#markup'=> '<input type="submit" name="show_address" value="Show Address" id="submit_wall"/>');
$content['anotherbutton'] = array('#markup'=> '<input type="submit" name="show_address" value="View All" id="viewall_left" />');
    // Put our entities into a themed table. See theme_table() for details.
    $content['entity_table'] = array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#header' => $header,
      '#attributes' => array(
          'id' => 'sort-table wall_table')
    );

    //Add pagination to table
  /*  $content['pager'] = array(
      '#theme' => 'pager'); */
    

  return $content;
}
