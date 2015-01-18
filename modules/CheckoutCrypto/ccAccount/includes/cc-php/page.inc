<?php

function account_info_page(){
 	global $user;
  	module_load_include('inc','ccAccount','includes/cc-php/lib');
	drupal_add_js(drupal_get_path('module', 'ccAccount') .'/theme/dash_func.js');

	$keyexists = checkIfKeyExists();
	if($keyexists == false){
		$content['no_coins']['#markup'] = t('<div class="alert alert-info">Looking to generate an !link.</div>', //TODO add check if user has api key already
		  array('!link' => l(t('API key?'), 'Account/basic/add'))
		);
	}
  /* if (user_access('administer ccdev_accounts entities')) {
    $content['preface']['#markup'] = t('You can administer these and add fields and change the view !link.',
      array('!link' => l(t('here'), 'admin/structure/ccdev_accounts/manage'))
    );
  } */

	$account = getAllAccountInfo($user->uid);
	$billing = getBillingSummary($user->uid);
	
  $content['dash_title'] = array(
      '#type' => 'item',
      '#markup' => t('<div class="round_menu">
		<div class="round_title">
		<h1 id="dash"> Dashboard </h1>
		</div>
	</div>'),);
	
 	$content['dash_wrapper'] = array('#markup' => t('<div class="row"> '), );
	 	$content['dash_col1'] = array('#markup' => t('<div class="col-md-6"> '), );
	
	  $content['total_balance'] = array(
      '#type' => 'item',
      '#markup' => t('<div class="networth" id="usdhover">
	  <div class="usd-tile">
  		<i class="usd-tile1"></i>
  		</div>
		<div>
		<h3 id="miniboxtitle"> Account Worth (USD) </h3>
			<p>$ '. $account['total_balance'] . '</p>
			<div style="
    display: inline-block;
    width: 100%;
">
<button style="border-radius: 0px 0px 0px 2px;width: 50%;padding: 0px 0px;height: 30px;margin-top: -0px;" id="payButton4" type="submit" class="btn btn-warning btn-lg">DEPOSIT</button><button style="border-radius: 0px 0px 2px 0px;width: 50%;padding: 0px 0px;height: 30px;margin-top: -0px;" id="payButton5" type="submit" class="btn btn-warning btn-lg">WITHDRAW</button>
   </div>
		</div>
	</div></div>'),);   //// close column col-lrg-3

		$content['dash_col2'] = array('#markup' => t('<div id="restx" class="col-md-6"> '), );		
	
	  $content['total_trans'] = array(
      '#type' => 'item',
      '#markup' => t('<div style="background: rgba(41, 162, 215, 0.7);height: 65px;" class="networth" id="txhover">
	  <div class="tx-tile">
  		<i class="tx-tile1"></i>
  		</div>
		<div> 
		<h3 id="miniboxtitle"> Transactions Made </h3>
			<p> '. $billing['total_trans'] . '</p>
			<button style="border-radius: 0px 0px 2px 2px;  width: 100%;  padding: 0px 0px;  height: 30px;  margin-top: -0px;" id="payButton6" type="submit" class="btn btn-warning btn-lg">VIEW TRANSACTIONS</button>
		</div>
	</div></div>'),); //// close column col-lrg-3
	
		$content['dash_col3'] = array('#markup' => t('<div style="margin-top: 15px;" class="col-lg-4" id="resproblem2"> '), );		
	
	  $content['verified'] = array(
      '#type' => 'item',
      '#markup' => t('<div style="background: rgba(231, 76, 60, 0.7);height: 65px;" class="networth" id="verifiedhover">
	  <div class="verified-tile">
  		<i class="verified-tile1"></i>
  		</div>
		<div>
		<h3 id="miniboxtitle"> Verification Status </h3>
			<p>LEVEL '. $account['verified'] . '</p>
			<button style="border-radius: 0px 0px 2px 2px;" id="payButton2" type="submit" class="btn btn-warning btn-lg">UPLOAD DOCUMENTS</button>
		</div>
	</div></div>'),); //// close column col-lrg-3
	
	
			$content['dash_col4'] = array('#markup' => t('<div style="margin-top: 15px;" class="col-lg-4" id="resproblem4"> '), );		
	
	  $content['api_key'] = array(
      '#type' => 'item',
      '#markup' => t('<div style="background: rgba(54, 67, 89, 0.7);height: 65px;" class="networth" id="apihover">
	  <div class="api-tile">
  		<i class="api-tile1"></i>
  		</div>
		<div>
		<h3 id="miniboxtitle"> Your API Key </h3>
			<textarea rows="10" cols="50" onclick="this.focus();this.select()" readonly="readonly" id="textarea99" style="overflow: hidden;height: 50px; width:100%;text-align: center;padding: 5px;margin-top: 0px;font-size: 14px;color: #fff;border-radius: 0px 0px 4px 4px;background: #364359;">'. $account['api_key'] . '</textarea>
		</div>
	</div></div>'),); //// close column col-lrg-3
	
				$content['dash_col5'] = array('#markup' => t('<div style="margin-top: 15px;" class="col-lg-4" id="resproblem1"> '), );		
	
	  $content['default_coin'] = array(
      '#type' => 'item',
      '#markup' => t('<div style="background: rgba(58, 58, 58, 0.7);height: 65px;" class="networth" id="defcoinhover">
	  <div class="defcoin-tile">
  		<i class="defcoin-tile1"></i>
  		</div>
		<div>
		<h3 id="miniboxtitle"> Your Default </h3>
			<p> '. $account['default_coin'] . ' COIN</p>
			<button style="border-radius: 0px 0px 2px 2px;" id="payButton3" type="submit" class="btn btn-warning btn-lg">CHANGE</button>
		</div>
	</div></div>'),); //// close column col-lrg-3
	

	 $content['dash_wrapper_close'] = array('#markup' => t('</div> <br><br><br>'), );

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

function intranet_page(){

$block = array(
      //  '#markup' => t('<frame src="http://google.com" ></frame>'),
    );
    return $block;
}

function account2_info_page(){
  module_load_include('inc','ccAccount','includes/cc-php/lib');
	$keyexists = checkIfKeyExists();
	if($keyexists == false){
		$content['no_coins']['#markup'] = t('<div class="alert alert-info">Looking to generate an !link.</div>', //TODO add check if user has api key already
		  array('!link' => l(t('API key?'), 'Account/basic/add'))
		);
	}
  /* if (user_access('administer ccdev_accounts entities')) {
    $content['preface']['#markup'] = t('You can administer these and add fields and change the view !link.',
      array('!link' => l(t('here'), 'admin/structure/ccdev_accounts/manage'))
    );
  } */
  module_load_include('inc','ccAccount','includes/cc-php/entity');
  $content['account_link'] = array(
      '#type' => 'item',
      '#markup' => t('<div class="round_menu">
		<div class="round_title">
		<h3> Dashboard </h3>
		</div>
	</div><br><br></><br>'),);
  $content['table'] =  display_account_entity();
	return $content;
}


