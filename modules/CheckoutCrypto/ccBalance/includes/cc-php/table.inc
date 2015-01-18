<?php

function getBalanceTable(){
	global $user;
	module_load_include('inc', 'ccCoin', 'includes/cc-php/lib');
	$header = array(
		array('data' => t('Balance'), 'field' => 'coin_balance', 'id' => 'tabhead'),   // https://coingateway.net/downloads/images/contents/input.png 
		array('data' => '', 'field' => '', 'id' => 'tabhead',),

);
	// $header = validateSort($head_item, $sort);
$result = db_select('ccdev_balance')
		->extend('PagerDefault')
		 ->extend('TableSort');

	$result->condition('uid', $user->uid, '=')
		->fields('ccdev_balance', array('coin_code', 'coin_balance'))
		->limit(5)
		 ->orderByHeader($header);

	$results =   $result->execute();
	$rows = array();
	$coins = getAllCoinCodes();
	foreach($results as $row){
			
	$coin_img = getIndividualCoinImg($coins, $row->coin_code);

		$rows[] = array('<img src="'. $coin_img. '" id="coinLogoTrans"/>'.  $row->coin_balance,
 					'<a href="Balance/Menu" class="ctools-use-modal">Menu</a>', 
		);
	}

	$content['ourtitle'] = array('#markup'=> '<h2 id="balancehead" class="text-center"> Balance </h2>');

    // Put our entities into a themed table. See theme_table() for details.
    $content['entity_table'] = array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#header' => $header,
      '#attributes' => array(
          'id' => 'sort-table trans_table')
    );

    /* //Add pagination to table
    $content['pager'] = array(
      '#theme' => 'pager'); */
    

  return $content;
}
