<?php

function account_info_page(){
	$numTrans = 0;
   $totBalance = 0; 
   $verify = 0; 
   $defCoin = "BTC"; 
    $apiKey = "none";
 	global $user;
  	module_load_include('inc','ccAccount','includes/cc-php/lib');
	drupal_add_js(drupal_get_path('module', 'ccAccount') .'/theme/dash_func.js');

	$keyexists = checkIfKeyExists();
	if($keyexists == false){
		$content['no_coins']['#markup'] = t('<div class="alert alert-info">Looking to generate an !link.</div>', //TODO add check if user has api key already
		  array('!link' => l(t('API key?'), 'Account/basic/add'))
		);
	}

	 $content['account_head'] = array('#markup' => t('<h3> Dashboard </h3>'), );

	$account = getAllAccountInfo($user->uid);
	$billing = getBillingSummary($user->uid);

	if(isset($billing['total_balance'])){
		$numTrans = $billing['total_trans'];
		$totBalance = $billing['total_balance'];
	}
	if(isset($account['api_key'])){
		$verify = $account['verified'];
		$defCoin = $account['default_coin'];
		$apiKey = $account['api_key'];
	}

	 	$content['account_balance'] = array('#markup' => t('<div class="container">
				<div class="row" id="dash_box"> 
					<div id="dash_box_title" class="col-md-4" >Balance</div>
					<div id="dash_box_title" class="col-md-4" >Verified</div>
					<div id="dash_box_title" class="col-md-4" >Num Transactions</div>
				</div> '),);	
	 	$content['account_trans'] = array('#markup' => t('
				<div class="row" id="dash_box"> 
					<div id="dash_box_inner" class="col-md-4" >'.$totBalance.'</div> 
					<div id="dash_box_inner" class="col-md-4" >'.$verify.'</div>
					<div id="dash_box_inner" class="col-md-4" >'.$numTrans.'</div>
				</div>'),);	
	 	$content['account_coin'] = array('#markup' => t('
				<div class="row" id="dash_box"> 
					<div id="dash_box_title" class="col-md-4" >Default Coin</div>
					<div id="dash_box_title" class="col-md-4" >API Key</div>
					<div id="dash_box_title" class="col-md-4" ></div>
				</div> '),);	
	 	$content['account_verified'] = array('#markup' => t('
				<div class="row" id="dash_box"> 
					<div id="dash_box_inner" class="col-md-4" >'.$defCoin.'</div>
					<div id="dash_box_inner" class="col-md-4" >'.$apiKey.'</div>
					<div id="dash_box_inner" class="col-md-4" ></div>

				</div> '),);	
		 $content['account_wrapper_close'] = array('#markup' => t('</div>'), );

	return $content;
}


function summary_page(){
  module_load_include('inc','ccAccount','includes/cc-php/entity');
  $content['table'] = display_billing_summary_entity();
  return $content;
}

function billing_page(){
  module_load_include('inc','ccAccount','includes/cc-php/entity');
 $content['menu_account'] = display_billing_menu();
  $content['table3'] =  display_billing_entity();
  return $content;
}

function display_billing_menu(){

    // There were no entities. Tell the user.
    $content[] = array(
      '#type' => 'item',
      '#markup' => t('<div class="round_menu">
		<div class="rounded">
			<a id="round_link" href="../Account"><p>Account</p></a>
		</div>
		<div class="rounded">
			<a id="round_link" href="./Dashboard"><p>Dashboard</p></a>
		</div>
		<div class="rounded">
			<a id="round_link" href="#"><p>Billing</p></a>
		</div>
	</div><br><br></><br>'),
    );

	return $content;
}
function display_account_menu(){

    // There were no entities. Tell the user.
    $content[] = array(
      '#type' => 'item',
      '#markup' => t('<div class="round_menu">
		<div class="rounded">
			<a id="round_link" href="Account"><p>Account</p></a>
		</div>
		<div class="rounded">
			<a id="round_link" href="Account/Dashboard"><p>Dashboard</p></a>
		</div>
		<div class="rounded">
			<a id="round_link" href="Account/Billing"><p>Billing</p></a>
		</div>
	</div><br><br></><br>'),
    );
	return $content;
}

function display_summary_menu(){
    // There were no entities. Tell the user.
    $content[] = array(
      '#type' => 'item',
      '#markup' => t('<div class="round_menu">
		<div class="rounded">
			<a id="round_link" href="../Account"><p>Account</p></a>
		</div>
		<div class="rounded">
			<a id="round_link" href="#"><p>Dashboard</p></a>
		</div>
		<div class="rounded">
			<a id="round_link" href="./Billing"><p>Billing</p></a>
		</div>
	</div><br><br></><br>'),
    );
	return $content;
}

