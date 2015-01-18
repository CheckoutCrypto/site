<?php

/**
 * Returns a render array with all ccdev_coin entities.
 */
function ccdev_coin_list_entities() {

  global $user;

  $content = array();
  $rows = array();
  module_load_include('inc', 'ccCoin', 'includes/cc-php/entity_load');
	module_load_include('inc', 'ccCoin', 'includes/cc-php/lib');
  ctools_include('modal');
  ctools_modal_add_js();

  $header = array(
      'coin_name' => array(
        'data' => t('Name'),
        'type' => 'property',
        'specifier' => 'coin_name',
        'field' => 'coin_name',
        'sort' => 'desc'
      ),
      'coin_code' => array(
        'data' => t('Code'),
        'type' => 'property',
        'specifier' => 'coin_code',
        'field' => 'coin_code'
      ),
      'coin_rate' => array(
        'data' => t('Rate'),
        'type' => 'property',
        'specifier' => 'coin_rate',
        'field' => 'coin_rate'
      ),
      'coin_rate_btc' => array(
        'data' => t('Rate(btc)'),
        'type' => 'property',
        'specifier' => 'coin_rate_btc',
        'field' => 'coin_rate_btc'
      ),
      'coin_fee' => array(
        'data' => t('Fee'),
        'type' => 'property',
        'specifier' => 'coin_fee',
        'field' => 'coin_fee'
      ),
      'coin_txfee' => array(
        'data' => t('Tx Fee'),
        'type' => 'property',
        'specifier' => 'coin_txfee',
        'field' => 'coin_txfee'
      ),
  	'add_coin' => array(
        'data' => t('Control'),
        'type' => 'property',
        'specifier' => 'add_coin',
        'field' => 'add_coin'
      ),
  );

  ctools_include('modal');
  ctools_modal_add_js();
  // Load all of our entities.
  $entities = ccdev_coin_load_multiple(FALSE, array(), FALSE, $header);
  if (!empty($entities)) {
    foreach ($entities as $entity) {
      // Create tabular rows for our entities.
if (user_access('administer ccdev_accounts entities')) {
      $rows[] = array(
        'data' => array(
	'coin_name' => $entity->coin_name,
	'coin_code' => $entity->coin_code,  
	'coin_rate' => $entity->coin_rate, 
	'coin_rate_btc' => $entity->coin_rate_btc, 
	'coin_fee' => $entity->coin_fee, 
	'coin_txfee' => $entity->coin_txfee, 
	'add_coin' => _ccCoin_make_link(array('coin_code' => $entity->coin_code,'title' => 'Manage')),

'' => _ccCoin_make_edit_link(array('coin_code' => $entity->coin_code,'title' => 'Edit')),
        ),
      );
}else if ($user->uid) {
      $rows[] = array(
        'data' => array(
	'coin_name' => $entity->coin_name,
	'coin_code' => $entity->coin_code,  
	'coin_rate' => $entity->coin_rate, 
	'coin_rate_btc' => $entity->coin_rate_btc, 
	'coin_fee' => $entity->coin_fee, 
	'coin_txfee' => $entity->coin_txfee, 
	'add_coin' => _ccCoin_make_link(array('coin_code' => $entity->coin_code,'title' => 'Manage')),
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

  }else {
    // There were no entities. Tell the user.
    $content[] = array(
      '#type' => 'item',
      '#markup' => t('No ccdev_coin entities currently exist.'),
    );
  }
  return $content;
}
