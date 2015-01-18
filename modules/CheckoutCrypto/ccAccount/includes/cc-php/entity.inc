<?php

function display_billing_summary_entity(){
global $user;
module_load_include('inc','ccAccount','includes/cc-php/entity_load');
  $content = array();
  $rows = array();
  $TableHeader = array(
      'paid_amt' => array(
        'data' => t('Amount Paid'),
        'type' => 'property',
        'specifier' => 'paid_amt',
        'field' => 'paid_amt'
      ),
      'billing_trans' => array(
        'data' => t('Cycle Trans'),
        'type' => 'property',
        'specifier' => 'billing_trans',
        'field' => 'billing_trans'
      ),
      'total_trans' => array(
        'data' => t('Total Trans'),
        'type' => 'property',
        'specifier' => 'total_trans',
        'field' => 'total_trans'
      ),
      'total_email_trans' => array(
        'data' => t('Total Emails'),
        'type' => 'property',
        'specifier' => 'total_email_trans',
        'field' => 'total_email_trans'
      ),
      'last_paid_date' => array(
        'data' => t('Last Paid'),
        'type' => 'property',
        'specifier' => 'last_paid_date',
        'field' => 'last_paid_date'
      ),
	  'total_paid_amt' => array(
        'data' => t('Total Paid'),
        'type' => 'property',
        'specifier' => 'total_paid_amt',
        'field' => 'total_paid_amt'
    	),
	  'billing_cycle' => array(
        'data' => t('Date'),
        'type' => 'property',
        'specifier' => 'billing_cycle',
        'field' => 'billing_cycle'
    	),
  );

  $sqlHeader = array(
      'grp_name' => array(
        'data' => t('Package'),
        'type' => 'property',
        'specifier' => 'grp_id',
        'field' => 'grp_id'
      ),
      'paid_coin' => array(
        'data' => t('Coin'),
        'type' => 'property',
        'specifier' => 'grp_id',
        'field' => 'grp_id'
      ),
      'paid_amt' => array(
        'data' => t('Amount Paid'),
        'type' => 'property',
        'specifier' => 'paid_amt',
        'field' => 'paid_amt'
      ),
      'billing_trans' => array(
        'data' => t('Monthly Trans'),
        'type' => 'property',
        'specifier' => 'billing_trans',
        'field' => 'billing_trans'
      ),
      'total_trans' => array(
        'data' => t('Total Trans'),
        'type' => 'property',
        'specifier' => 'total_trans',
        'field' => 'total_trans'
      ),
      'total_email_trans' => array(
        'data' => t('Total Emails'),
        'type' => 'property',
        'specifier' => 'total_email_trans',
        'field' => 'total_email_trans'
      ),
      'last_paid_date' => array(
        'data' => t('Last Bill'),
        'type' => 'property',
        'specifier' => 'last_paid_date',
        'field' => 'last_paid_date'
      ),
  );


	$AccHeader= array();
  	$entities = ccdev_accounts_load_multiple(FALSE, array(), FALSE, $AccHeader);
 if (!empty($entities)) {
    foreach ($entities as $ent) {
  $sumEntity = ccdev_billing_summary_load_multiple(FALSE, array(), FALSE, $sqlHeader);

  if (!empty($sumEntity)) {
		foreach ($sumEntity as $sum) {
			module_load_include('inc','ccAccount','includes/cc-php/lib');
			$groupInfo = getGroupInfo($sum->grp_id);

			if($user->uid == $sum->user_id || user_access('administer ccdev_accounts entities')) {
				  // Create tabular rows for our entities.
				  $rows[] = array(
					'data' => array(
					'grp_name' => $groupInfo['grp_name'],
					'paid_coin' => $ent->default_coin,
					'paid_amt' => $sum->paid_amt,
					'billing_trans' => $sum->billing_trans,
					'total_trans' => $sum->total_trans,
					'total_email_trans' => $sum->total_email_trans,
					'last_paid_date' => $sum->last_paid_date,
					),
				  );
			}
		}

    // Put our entities into a themed table. See theme_table() for details.
    $content['entity_table'] = array(
      '#theme' => 'table',
	 '#header' => $sqlHeader,
      '#rows' => $rows,
      '#attributes' => array(
          'id' => 'sort-table')
    );

    //Add pagination to table
    $content['pager'] = array(
      '#theme' => 'pager');
  }
  else {
    // There were no entities. Tell the user.
    $content[] = array(
      '#type' => 'item',
      '#markup' => t('No ccdev_accounts entities currently exist.'),
    );
  }
}
}

	return $content;
}


function display_billing_entity(){

  global $user;
module_load_include('inc','ccAccount','includes/cc-php/entity_load');
  $content = array();
  $rows = array();

  $header = array(
      'grp_name' => array(
        'data' => t('Package'),
        'type' => 'property',
        'specifier' => 'grp_name',
        'field' => 'grp_name'
      ),
      'paid_amt' => array(
        'data' => t('Amount Paid'),
        'type' => 'property',
        'specifier' => 'paid_amt',
        'field' => 'paid_amt'
      ),
      'paid_coin' => array(
        'data' => t('Coin Paid'),
        'type' => 'property',
        'specifier' => 'paid_coin',
        'field' => 'paid_coin'
      ),
	  'paid_date' => array(
        'data' => t('Date'),
        'type' => 'property',
        'specifier' => 'paid_date',
        'field' => 'paid_date'
    	),
  );

  $sumEntity = ccdev_billing_load_multiple(FALSE, array(), FALSE, $header);

  if (!empty($sumEntity)) {
    foreach ($sumEntity as $sum) {
	if($user->uid == $sum->user_id || user_access('administer ccdev_accounts entities')) {
	      // Create tabular rows for our entities.
	      $rows[] = array(
		'data' => array(
		'grp_name' => $sum->grp_name,
		'paid_amt' => $sum->paid_amt,
		'paid_coin' => $sum->paid_coin,
		'paid_date' => $sum->paid_date,
		),
	      );
	}
    }


    // Put our entities into a themed table. See theme_table() for details.
    $content['entity_table'] = array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#header' => $header,
      '#attributes' => array(
          'id' => 'sort-table')
    );

    //Add pagination to table
    $content['pager'] = array(
      '#theme' => 'pager');

  }
  else {
    // There were no entities. Tell the user.
    $content[] = array(
      '#type' => 'item',
      '#markup' => t('No ccdev_accounts entities currently exist.'),
    );
  }
	return $content;
}

function display_account_entity(){

  global $user;
	module_load_include('inc','ccAccount','includes/cc-php/entity_load');
  $content = array();
  $rows = array();

  $header = array(
      'api_key' => array(
        'data' => t('API key'),
        'type' => 'property',
        'specifier' => 'api_key',
        'field' => 'api_key'
      ),
      'total_balance' => array(
        'data' => t('Account Value(BTC)'),
        'type' => 'property',
        'specifier' => 'total_balance',
        'field' => 'total_balance'
      ),
      'total_transactions' => array(
        'data' => t('Total TX'),
        'type' => 'property',
        'specifier' => 'total_transactions',
        'field' => 'total_transactions'
      ),
      'created' => array(
        'data' => t('Created'),
        'type' => 'property',
        'specifier' => 'created',
        'field' => 'created'
    ),
  );

  $entities = ccdev_accounts_load_multiple(FALSE, array(), FALSE, $header);
  if (!empty($entities)) {
    foreach ($entities as $entity) {
	if($user->uid == $entity->user_id || user_access('administer ccdev_accounts entities')) {
	      // Create tabular rows for our entities.
	      $rows[] = array(
		'data' => array(
		'api_key' => l($entity->api_key, 'Account/basic/' . $entity->basic_id),
		'total_balance' => $entity->total_balance,
		'total_transactions' => $entity->total_transactions,
		'created' => $entity->created,
		),
	      );
	}
    }

    // Put our entities into a themed table. See theme_table() for details.
    $content['entity_table'] = array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#header' => $header,
      '#attributes' => array(
          'id' => 'sort-table')
    );

    //Add pagination to table
    $content['pager'] = array(
      '#theme' => 'pager');

  }
  else {
    // There were no entities. Tell the user.
    $content[] = array(
      '#type' => 'item',
      '#markup' => t('No Account settings currently exist, you need to !link to begin.', array('!link' => l(t('Manage your coin preferences'), 'Coin'))),
    );
  }
	return $content;

}
