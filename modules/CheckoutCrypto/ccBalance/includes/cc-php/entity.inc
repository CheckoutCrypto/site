<?php


/**
 * Returns a render array with all ccdev_balance entities.
 *
 * In this basic example we know that there won't be many entities,
 * so we'll just load them all for display. See pager_example.module
 * to implement a pager. Most implementations would probably do this
 * with the contrib Entity API module, or a view using views module,
 * but we avoid using non-core features in the Examples project.
 *
 * @see pager_example.module
 */
function ccdev_balance_list_entities() {
  global $user;

  $content = array();
  $rows = array();
    module_load_include('inc', 'ccBalance', 'includes/cc-php/entity_load');
    module_load_include('inc', 'ccBalance', 'includes/cc-php/lib');
  ctools_include('modal');
  ctools_modal_add_js();

  //Build header
  $header = array(
      'coin_name' => array(
        'data' => t('Coin'),
        'type' => 'property',
        'specifier' => 'coin_name',
        'field' => 'coin_name'
      ),
      'coin_code' => array(
        'data' => t('Code'),
        'type' => 'property',
        'specifier' => 'coin_code',
        'field' => 'coin_code'
      ),
      'coin_pending' => array(
        'data' => t('Pending'),
        'type' => 'property',
        'specifier' => 'coin_pending',
        'field' => 'coin_pending'
      ),
      'coin_withdraw' => array(
        'data' => t('Withdrawn'),
        'type' => 'property',
        'specifier' => 'coin_withdraw',
        'field' => 'coin_withdraw'
      ),
      'coin_balance' => array(
        'data' => t('Balance'),
        'type' => 'property',
        'specifier' => 'coin_balance',
        'field' => 'coin_balance'
      ),
      'coin_autopay' => array(
        'data' => t('Autopay'),
        'type' => 'property',
        'specifier' => 'coin_autopay',
        'field' => 'coin_autopay'
      ), 
      'coin_autoaddress' => array(
        'data' => t('Auto address'),
        'type' => 'property',
        'specifier' => 'coin_autoaddress',
        'field' => 'coin_autoaddress'
      ), 
  );

  // Load entities
  $entities = ccdev_balance_load_multiple(FALSE, array(), FALSE, $header);
  if (!empty($entities)) {
    foreach ($entities as $entity) {
	if($user->uid == $entity->uid || user_access('administer ccdev_balance entities')) {
	      // Create tabular rows for our entities.
	      $rows[] = array(
		'data' => array(
		'coin_name' => $entity->coin_name,
		'coin_code' => $entity->coin_code,  
		'coin_pending' => $entity->coin_pending, 
		'coin_withdraw' => $entity->coin_withdraw,
		'coin_balance' => $entity->coin_balance, 
		'coin_autopay' => $entity->coin_autopay,
		'coin_autoaddress' => $entity->coin_autoaddress,
		'withdraw' => _ccBalance_make_link(array('coin_code' => $entity->coin_code,'title' => 'withdraw')),
		'autopayment' => _ccBalance_make_link_autopay(array('coin_code' => $entity->coin_code,'title' => 'autopayment')),
		'deposit' => _ccBalance_make_link_deposit(array('coin_code' => $entity->coin_code,'title' => 'deposit')),
		'autotrade' => _ccBalance_make_link_autotrade(array('coin_code' => $entity->coin_code,'title' => 'autotrade')),
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
      '#markup' => t('No ccdev_balance entities currently exist.'),
    );
  }
  return $content;
}
