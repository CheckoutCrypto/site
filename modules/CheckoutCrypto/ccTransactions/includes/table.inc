<?php

function getTransactionsTable(){
	global $user;
	module_load_include('inc', 'ccCoin', 'includes/cc-php/lib');
	$header = array(
		array('data' => 'Sent', 'field' => 'amount', 'id' => 'trans_amount_head'),   // https://coingateway.net/downloads/images/contents/input.png 
		array('data' => 'Recipient', 'field' => 'receiver', 'id' => 'trans_receiver_head',),  /// <img src="https://coingateway.net/downloads/images/contents/transact.png" />
		array('data' => 'Date', 'field' => 'timestamp',  'sort' => 'desc', 'id' => 'trans_time_head',),  /// <img src="https://coingateway.net/downloads/images/contents/clock.png" />

);
	// $header = validateSort($head_item, $sort);
$result = db_select('ccdev_transactions')
		->extend('PagerDefault')
		 ->extend('TableSort')
			->fields('ccdev_transactions', array('coin_code', 'receiver', 'amount', 'timestamp'))
		->limit(5)
		 ->orderByHeader($header);

	$results =   $result->execute();
	$rows = array();
	$coins = getAllCoinCodes();
	foreach($results as $row){
			
	$coin_img = getIndividualCoinImg($coins, $row->coin_code);

		$rows[] = array(
			'data' => array(
					array('data' => '<img src="'. $coin_img. '" id="coinLogoTrans"/>'.  $row->amount ),
					array('data' => $row->receiver, 'name' => 'trans_receiver_col' ),
					array('data' => $row->timestamp, ),
			 ),
 		 );
	}
	
	$content['ourtitle'] = array('#markup'=> '<h2 id="transacthead" class="text-center"> Transactions </h2>');
	$content['somebutton'] = array('#markup'=> '<input type="submit" name="show_address" value="Show Address" id="submit_trans"/>');
	$content['anotherbutton'] = array('#markup'=> '<input type="submit" name="show_address" value="View All" id="viewall_right" />');
    // Put our entities into a themed table. See theme_table() for details.
    $content['entity_table'] = array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#header' => $header,
      '#attributes' => array(
          'id' => 'sort-table trans_table')
    );

    //Add pagination to table
  /*  $content['pager'] = array(
      '#theme' => 'pager');  */
    

  return $content;
}
