<?php


function service_info_page(){
  	module_load_include('inc', 'ccService', 'includes/lib');

	ctools_include('modal');
	ctools_modal_add_js();
	$coin_code = "pot";
	$link = 'Choose a package that meets your requirements. ';
  	$content['preface'] = array(
    '#type' => 'item',
    '#markup' => $link, 
  	);

	$content += service_table();
  ///	$content['table'] = ccdev_send_list_entities();

  return $content;
}

function service_complete_page(){
    $content['preface']['#markup'] = t('Service Charge Complete.  Remember, you will be billed, 30 days from today, at this time. Make sure you have enough coin to cover the bill for the following month.'    );
  	return $content;
}

function service_fund_complete(){
	ctools_include('modal');
	ctools_modal_add_js();
  	module_load_include('inc', 'ccService', 'includes/lib');
    $content['preface']['#markup'] = t('Account Fund Complete! You may now finish the '. _ccService_make_link(array('group' => '2','title' => 'Service Charge'))   );
  	return $content;
}


function service_table(){
  global $user;

  $content = array();
  $rows = array();
 $header = array();
  	module_load_include('inc', 'ccGroup', 'includes/cc-php/lib');
	$groups = getAllGroups();
    $header = array(
      'group_name' => array(
        'data' => t('Name'),
        'type' => 'property',
        'specifier' => 'grp_name',
        'field' => 'grp_name'
      ),
  	 'group_type' => array(
        'data' => t('Type'),
        'type' => 'property',
        'specifier' => 'grp_type',
        'field' => 'grp_type'
      ),
  	 'group_description' => array(
        'data' => t('Description'),
        'type' => 'property',
        'specifier' => 'grp_description',
        'field' => 'grp_description'
      ),

  	 'group_max_trans' => array(
        'data' => t('Max Trans'),
        'type' => 'property',
        'specifier' => 'grp_max_transactions',
        'field' => 'grp_max_transactions'
      ),

  	 'group_max_emails' => array(
        'data' => t('Max Emails'),
        'type' => 'property',
        'specifier' => 'grp_max_emails',
        'field' => 'grp_max_emails'
      ),
  	 'group_payment_length' => array(
        'data' => t('Billing(Days)'),
        'type' => 'property',
        'specifier' => 'grp_payment_length',
        'field' => 'grp_payment_length'
      ),
  	 'group_cost' => array(
        'data' => t('Cost'),
        'type' => 'property',
        'specifier' => 'grp_cost',
        'field' => 'grp_cost'
      ),
  	 'group_price' => array(
        'data' => t('Price($)'),
        'type' => 'property',
        'specifier' => 'grp_price',
        'field' => 'grp_price'
      ),

	);

  if (!empty($groups)) {
    foreach ($groups as $grp) {
	      // Create tabular rows for our entities.
		$rows[] = array(
		  'data' => array(
			'grp_name' => $grp['grp_name'],		
			'grp_type' => $grp['grp_type'],		
			'grp_description' => $grp['grp_description'],
			'grp_max_transactions' => $grp['grp_max_transactions'],		
			'grp_max_emails' => $grp['grp_max_emails'],			
			'grp_payment_length' => $grp['grp_payment_length'],					
			'grp_cost' => $grp['grp_cost'],
			'grp_price' => $grp['grp_price'],
			'Purchase' => _ccService_make_link(array('group' => $grp['basic_id'],'title' => 'Purchase')),
			),
	     );
    }

    // Put our entities into a themed table. See theme_table() for details.
    $content['entity_table'] = array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#header' => $header,
      '#attributes' => array(
          'id' => 'sort-table')
    );
}
	return $content;

}
