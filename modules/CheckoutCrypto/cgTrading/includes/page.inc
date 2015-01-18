<?php

function trading_page(){
		//slick
		drupal_add_css($path.'/includes/slick/slick.css');
		drupal_add_js($path.'/includes/slick/jquery-1.11.0.min.js');
		drupal_add_js($path.'/includes/slick/jquery-migrate-1.2.1.min.js');
		drupal_add_js($path.'/includes/slick/slick.min.js');
		//end slick
  if (user_access('administer ccdev_work_orders entities')) {
    $content['preface']['#markup'] = t('You can administer these and add fields and change the view !link.',
      array('!link' => l(t('here'), 'admin/structure/ccdev_work_orders/manage'))
    );
  }
  return $content;
}

function trading_complete($coin, $address){
	module_load_include('inc', 'ccCoin', 'includes/cc-php/lib');
	module_load_include('inc', 'cgTrading', 'includes/lib');
 	drupal_add_css(drupal_get_path('module', 'cgTrading') . '/theme/style_trans.css', 'file');
	$coins = getAllCoinCodes();
	$coin_in = '';  /// deposited coin
	$addressRec = ''; //// deposited address
	$counter = 0;

	//// VALIDATE Coin
	if(!empty($coin)){
		foreach($coins as $cn){
			if($cn['coin_code'] == $coin){
				$coin_in = $coin;
			}
		}
	}

	//// VALIDATE ADDRESS
	if(preg_match("/^[A-Z0-9]+$/i", $address)) {
			$validAddress = validateCoinAddress($coin_in, $address);
			if($validAddress == true){
				$addressDep = $address;
			}
	}

	/// Get completed trade and var
	$trade = getSpecificTrade($addressDep);

	$cointo = $trade['coin_to'];
	$amt_to = $trade['amount_to'];
	$coinfrom = $trade['coin_from'];
	$amt_from = $trade['amount_from'];
	$address_in = $trade['address_gen'];
	$address_out = $trade['address_out'];
	$txid = $trade['txid'];
	$timestamp = $trade['timestamp']; 
	
	
	$cointo_img = getIndividualCoinImg($coins, $cointo);
	$coinfrom_img = getIndividualCoinImg($coins, $coinfrom);
	
	
		$content['dash_col10_'.$counter] = array('#markup' => t('<div class="" id="compheader"> '), );
	 $content['completed_title'.$counter] = array(
		'#type' => 'item',
		'#markup' => t('<h2 style="font-size:24px;"> TRANSACTION MADE </h2>'),
	  );$content['dash_col10_close_'.$counter] = array('#markup' => t('</div>'),); //closes the column


 	$content['dash_wrapper_'.$counter] = array('#markup' => t('<div class="row" style="margin-top:40px;margin-bottom:20px;background: #2F3942;padding: 20px;border-radius: 2px;color: #FFFFFF;"> '), );
	$content['dash_col1_'.$counter] = array('#markup' => t('<div class="col-md-6"> '), );
	 $content['coin_in_'.$counter] = array(
		'#type' => 'item',
		'#markup' => t('<p style="background: #FFFFFF;color: #2F3942;font-weight: bold;padding: 20px;text-align: center;border-radius: 2px;"> YOU SENT </p><p id="coinlogoComp"><img src="../../.'.$coinfrom_img .'" id="coinLogoComp2" /><p id="coinlogoComp" style="background: #2B3238;padding: 10px;font-weight: bold;font-size: 16px;">'.$amt_from.'</p></p>'),
	  );
	$content['dash_col_close_'.$counter] = array('#markup' => t('</div>'),); //closes the column
	  
		  
	$content['dash_col4_'.$counter] = array('#markup' => t('<div class="col-md-6"> '), );
	 $content['coin_out_'.$counter] = array(
		'#type' => 'item',
		'#markup' => t('<p style="background: #FFFFFF;color: #2F3942;font-weight: bold;padding: 20px;text-align: center;border-radius: 2px;"> THEY RECEIVED </p><p id="coinlogoComp"><img src="../../.'.$cointo_img .'" id="coinLogoComp2" /><p id="coinlogoComp" style="background: #2B3238;padding: 10px;font-weight: bold;font-size: 16px;">'.$amt_to.'</p></p>'),
	  );$content['dash_col4_close_'.$counter] = array('#markup' => t('</div>'),); //closes the column
		  
	  
	$content['dash_col7_'.$counter] = array('#markup' => t('<div class="col-md-10 col-md-offset-1" style="margin-top: 10px;  text-align: center;">'), );
	 $content['tx_'.$counter] = array(
		'#type' => 'item',
		'#markup' => t('<p style="background: #FFFFFF;  padding: 10px;  color: #2F3942;font-weight: bold;border-radius: 2px;"> TXID SENT '.$timestamp.'<textarea rows="10" cols="50" onclick="this.focus();this.select()" readonly="readonly" style="padding: 5px;border:none; height: 30px; width: 100%;text-align: center;margin-top: 20px;font-size: 14px;color: white;border-radius: 2px;background: #2F3942;">'.$txid.'</textarea></p>'),
	  );$content['dash_col7_close_'.$counter]  = array('#markup' => t('</div>'),); //closes the column
		  
       $content['dash_wrapper_close_'.$counter] = array('#markup' => t('</div>'), ); 
	  	  $counter++;
  return $content; 
}

function trading_transactions(){
	module_load_include('inc', 'ccCoin', 'includes/cc-php/lib');
	module_load_include('inc', 'cgTrading', 'includes/table');
	module_load_include('inc', 'cgTrading', 'includes/lib');
 	drupal_add_css(drupal_get_path('module', 'cgTrading') . '/theme/style_trans.css', 'file');
	/// get every trade and var
	$counter = 0;
	$header = array();
$content['trade_header'] = array('#markup' => t('<br><br>'), ); 
	//$header = $_GET['sort'];
	$trades = getAllTrades(0,10, $header);
	$trades_table = getTradeTable(0,10);
$content['trade_table'] = $trades_table;
	$coins = getAllCoinCodes();

  return $content;
}


