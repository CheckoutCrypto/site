<?php

/**
 * Returns a render array with all ccdev_transactions entities.
 */
function ccdev_transactions_list_entities() {
	module_load_include('inc', 'ccTrans', 'includes/entity_load');
  global $user;

  $content = array();
  $rows = array();
 $header = array();
      //'#header' => array(t('ID'), t('userid'), t('coin_id'), t('amount'), t('sender'), t('receiver'), t('tranid'), t('status'), t('timestamp'),),

    $header = array(
      'timestamp' => array(
        'data' => t('Date + Time'),
        'type' => 'property',
        'specifier' => 'timestamp',
        'field' => 'timestamp'
      ),
      'receiver' => array(
        'data' => t('Receiving Address'),
        'type' => 'property',
        'specifier' => 'receiver',
        'field' => 'receiver'
      ),
      'tranid' => array(
        'data' => t('Transaction ID'),
        'type' => 'property',
        'specifier' => 'tranid',
        'field' => 'tranid'
      ),
      'amount' => array(
        'data' => t('Amount'),
        'type' => 'property',
        'specifier' => 'amount',
        'field' => 'amount'
      ),     
      'fee' => array(
        'data' => t('Fee'),
        'type' => 'property',
        'specifier' => 'amount',
        'field' => 'amount'
      ), 
      'coin_code' => array(
        'data' => t('Coin'),
        'type' => 'property',
        'specifier' => 'coin_code',
        'field' => 'coin_code'
      ), 
	'status' => array(
        'data' => t('Status'),
        'type' => 'property',
        'specifier' => 'status',
        'field' => 'status'
      ),

  );
  //Load entities
  $entities = ccdev_transactions_load_multiple(FALSE, array(), FALSE, $header);
  if (!empty($entities)) {
    foreach ($entities as $entity) {
	if($user->uid == $entity->uid || user_access('administer ccdev_trans entities')) {
	      // Create tabular rows for our entities.
		$rows[] = array(
		  'data' => array(
			'timestamp' => $entity->timestamp,		
			'receiver' => $entity->receiver,
		    'tranid' => $entity->tranid,
			'amount' => $entity->amount,
  			'fee' => $entity->fee,
			'coin_code' => $entity->coin_code,
			'status' => $entity->status,
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

/*
    // Put our entities into a themed table. See theme_table() for details.
    $content['entity_table'] = array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#header' => array(t('ID'), t('userid'), t('coin_id'), t('amount'), t('sender'), t('receiver'), t('tranid'), t('status'), t('timestamp'),),
    );
*/
  }
  else {
    // There were no entities. Tell the user.
    $content[] = array(
      '#type' => 'item',
      '#markup' => t('No ccdev_transactions entities currently exist.'),
    );
  }
  return $content;
}
