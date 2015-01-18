<?php

/**
 * Returns a render array with all ccdev_wallets entities.
 */
function ccdev_wallets_list_entities() {
  	module_load_include('inc', 'ccWallets', 'includes/entity_load');
  global $user;

  $content = array();
  $rows = array();

  $header = array(
      'coins_enabled' => array(
        'data' => t('Coin'),
        'type' => 'property',
        'specifier' => 'coins_enabled',
        'field' => 'coins_enabled'
      ),
      'balance_total' => array(
        'data' => t('Balance'),
        'type' => 'property',
        'specifier' => 'basic_id',
        'field' => 'balance_total'
      ),
      'pending_total' => array(
        'data' => t('Pending'),
        'type' => 'property',
        'specifier' => 'basic_id',
        'field' => 'pending_total'
      ),
      'fee_total' => array(
        'data' => t('Total fees'),
        'type' => 'property',
        'specifier' => 'basic_id',
        'field' => 'fee_total'
      ),
      'walletaddress' => array(
        'data' => t('Address'),
        'type' => 'property',
        'specifier' => 'basic_id',
        'field' => 'walletaddress'
      ),
      'confirm' => array(
        'data' => t('Confirms'),
        'type' => 'property',
        'specifier' => 'basic_id',
        'field' => 'confirm'
      ),
      'timestamp' => array(
        'data' => t('Timestamp'),
        'type' => 'property',
        'specifier' => 'basic_id',
        'field' => 'timestamp'
    ),
  );

  // Load entities
  $entities = ccdev_wallets_load_multiple(FALSE, array(), FALSE, $header);
  if (!empty($entities)) {
    foreach ($entities as $entity) {

	  if($user->uid == $entity->uid || user_access('administer ccdev_wallets entities')) {
	      // Create tabular rows for our entities.
	      $rows[] = array(
		'data' => array(
		'coins_enabled' => $entity->coins_enabled,
		'balance_total' => $entity->balance_total,
		'pending_total' => $entity->pending_total,
		'fee_total' => $entity->fee_total,
		'walletaddress' => $entity->walletaddress,
		'confirm' => $entity->confirm,
		'timestamp' => $entity->timestamp,  
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
      '#markup' => t('No ccdev_wallets entities currently exist.'),
    );
  }
  return $content;
}

