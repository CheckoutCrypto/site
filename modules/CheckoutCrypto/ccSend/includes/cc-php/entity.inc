<?php

function send_list(){
   	module_load_include('inc', 'ccSend', 'includes/cc-php/entity_load');
   	module_load_include('inc', 'ccSend', 'includes/cc-php/lib');
  global $user;

  $content = array();
  $rows = array();

  ctools_include('modal');
  ctools_modal_add_js();

  //Build header
  $header = array(
      'recip_name' => array(
        'data' => t('Email'),
        'type' => 'property',
        'specifier' => 'recip_email',
        'field' => 'recip_email'
      ),
      'recip_email' => array(
        'data' => t('Name'),
        'type' => 'property',
        'specifier' => 'coin_code',
        'field' => 'coin_code'
      ),
      'recip_msg' => array(
        'data' => t('Message'),
        'type' => 'property',
        'specifier' => 'recip_msg',
        'field' => 'recip_msg'
      ),
      'coin_code' => array(
        'data' => t('Coin'),
        'type' => 'property',
        'specifier' => 'coin_code',
        'field' => 'coin_code'
      ),
      'coin_amt' => array(
        'data' => t('AMT'),
        'type' => 'property',
        'specifier' => 'coin_amt',
        'field' => 'coin_amt'
      ),
      'recip_address' => array(
        'data' => t('Coin Address'),
        'type' => 'property',
        'specifier' => 'recip_address',
        'field' => 'recip_address'
      ), 
      'sent' => array(
        'data' => t('Date Sent'),
        'type' => 'property',
        'specifier' => 'sent',
        'field' => 'sent'
      ),
      'retrieved' => array(
        'data' => t('Date Retrieved'),
        'type' => 'property',
        'specifier' => 'retrieved',
        'field' => 'retrieved'
      ),
  );

  // Load entities
  $entities = ccdev_send_load_multiple(FALSE, array(), FALSE, $header);
  if (!empty($entities)) {
    foreach ($entities as $entity) {
	if($user->uid == $entity->uid || user_access('administer ccdev_send entities')) {
	      // Create tabular rows for our entities.
	      $rows[] = array(
		'data' => array(
		'recip_email' => $entity->recip_email,
		'recip_name' => $entity->recip_name,  
		'recip_msg' => $entity->recip_msg, 
		'coin_code' => $entity->coin_code,
		'coin_amt' => $entity->coin_amt, 
		'recip_address' => $entity->recip_address,
		'sent' => $entity->sent, 
		'retrieved' => $entity->retrieved, 
		// 'cancel' => 'cancel',
		//'remove' => '[x]',
		// 'withdraw' => _ccSend_make_link(array('coin_code' => $entity->coin_code,'title' => 'withdraw')),
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
      '#markup' => t('No ccdev_send entities currently exist.'),
    );
  }
  return $content;
}
