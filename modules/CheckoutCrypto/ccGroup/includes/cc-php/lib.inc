<?php


/// MAKE LINK FOR ADD COIN
function _ccGroup_make_link($args = '') {
// Set a default value if no text in supplied.
  if (!(empty($args))) {
     $link_text = $args['title'];
     $group_id = $args['group_id'];
   } else {
     return FALSE;
   }
   return '<div id="'. $group_id.'-modal-link">' . l($link_text, 'ccMod/ccGroup/any/nojs/'. $group_id, array('attributes' => array('class' => 'ctools-use-modal'))) . '</div>';
}


function ccGroupRefresh() {
    module_load_include('inc', 'ccAccount', 'includes/cc-php/cc');
	$accountdata = array();
	 $accountdata = getServerApiKey("rate");
	$apikey  = $accountdata['api_key'];
    $ccApi = new CoingatewayAPI($apikey);
    $response = $ccApi->query(array('action' => 'refreshworker', 'type' => 'groups', 'apikey' => $apikey));
    return $response;
} 


/*
* Grab group data
*/
function getGroupData($grpid){
	$grpdata = array();
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'ccdev_groups')
	  ->entityCondition('bundle', 'ccdev_groups_bundle')
	 ->propertyCondition('basic_id', $grpid);
	$result = $query->execute();
	if (isset($result['ccdev_groups'])) {
	  $site_nids = array_keys($result['ccdev_groups']);
	  $allsites = entity_load('ccdev_groups', $site_nids);
		foreach($allsites as $site){
			$grpdata['basic_id'] = $site->basic_id;
			$grpdata['grp_name'] = $site->grp_name;
			$grpdata['grp_description'] = $site->grp_description;
			$grpdata['grp_type'] = $site->grp_type;
			$grpdata['grp_withdraw_fee'] = $site->grp_withdraw_fee;
			$grpdata['grp_trade_fee'] = $site->grp_trade_fee;
			$grpdata['grp_exchange_fee'] = $site->grp_exchange_fee;
			$grpdata['grp_monthly_fee'] = $site->grp_monthly_fee;
			$grpdata['grp_max_transactions'] = $site->grp_max_transactions;
			$grpdata['grp_max_emails'] = $site->grp_max_emails;
			$grpdata['grp_payment_length'] = $site->grp_payment_length;
			$grpdata['grp_size'] = $site->grp_size;
			$grpdata['created'] = $site->created;
		} 
	}
	return $grpdata;
}

/*
* Grab group data
*/
function getAllGroups(){
	$groups = array();
	$grpdata = array();
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'ccdev_groups')
	  ->entityCondition('bundle', 'ccdev_groups_bundle');
	$result = $query->execute();
	if (isset($result['ccdev_groups'])) {
	  $site_nids = array_keys($result['ccdev_groups']);
	  $allsites = entity_load('ccdev_groups', $site_nids);
		foreach($allsites as $site){
			$grpdata['basic_id'] = $site->basic_id;
			$grpdata['grp_name'] = $site->grp_name;
			$grpdata['grp_description'] = $site->grp_description;
			$grpdata['grp_type'] = $site->grp_type;
			$grpdata['grp_withdraw_fee'] = $site->grp_withdraw_fee;
			$grpdata['grp_trade_fee'] = $site->grp_trade_fee;
			$grpdata['grp_exchange_fee'] = $site->grp_exchange_fee;
			$grpdata['grp_monthly_fee'] = $site->grp_monthly_fee;
			$grpdata['grp_max_transactions'] = $site->grp_max_transactions;
			$grpdata['grp_max_emails'] = $site->grp_max_emails;
			$grpdata['grp_payment_length'] = $site->grp_payment_length;
			$grpdata['grp_size'] = $site->grp_size;
			$grpdata['created'] = $site->created;
			array_push($groups, $grpdata);
		} 
	}
	return $groups;
}

/*
* Get a user's group
*/
function getUserGroup($userid){
	$grpdata = array();
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'ccdev_billing_summary')
	  ->entityCondition('bundle', 'ccdev_billing_summary_bundle')
	 ->propertyCondition('user_id', $userid);
	$result = $query->execute();
	if (isset($result['ccdev_billing_summary'])) {
	  $site_nids = array_keys($result['ccdev_billing_summary']);
	  $allsites = entity_load('ccdev_billing_summary', $site_nids);
		foreach($allsites as $site){
			$grpdata['grp_id'] = $site->grp_id;
			$grpdata['paid_amt'] = $site->paid_amt;
			$grpdata['billing_trans'] = $site->billing_trans;
			$grpdata['total_trans'] = $site->total_trans;
			$grpdata['total_email_trans'] = $site->total_email_trans;
			$grpdata['last_paid_date'] = $site->last_paid_date;
			$grpdata['total_paid_amt'] = $site->total_paid_amt;
			$grpdata['billing_cycle'] = $site->billing_cycle;
		} 
	}
	return $grpdata;
}


