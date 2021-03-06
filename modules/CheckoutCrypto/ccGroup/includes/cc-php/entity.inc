<?php


/**
 * Returns a render array with all entity_example_basic entities.
 */
function ccdev_groups_list_entities() {
  module_load_include('inc', 'ccGroup', 'includes/cc-php/entity_load');
  module_load_include('inc', 'ccGroup', 'includes/cc-php/lib');
  global $user;

  ctools_include('modal');
  ctools_modal_add_js();

  $content = array();
  $rows = array();
  $header = array(
      'grp_name' => array(
        'data' => t('Name'),
        'type' => 'property',
        'specifier' => 'grp_name',
        'field' => 'grp_name'
      ),
      'grp_description' => array(
        'data' => t('Description'),
        'type' => 'property',
        'specifier' => 'grp_description',
        'field' => 'grp_description'
      ),
      'grp_type' => array(
        'data' => t('Type'),
        'type' => 'Type',
        'specifier' => 'grp_type',
        'field' => 'grp_type'
      ),
      'grp_withdraw_fee' => array(
        'data' => t('withdraw'),
        'type' => 'property',
        'specifier' => 'grp_withdraw_fee',
        'field' => 'grp_withdraw_fee'
      ),
     'grp_exchange_fee' => array(
        'data' => t('exchange'),
        'type' => 'property',
        'specifier' => 'grp_exchange_fee',
        'field' => 'grp_exchange_fee'
      ),
     'grp_trade_fee' => array(
        'data' => t('trade'),
        'type' => 'property',
        'specifier' => 'grp_trade_fee',
        'field' => 'grp_trade_fee'
      ),
     'grp_monthly_fee' => array(
        'data' => t('monthly'),
        'type' => 'property',
        'specifier' => 'grp_monthly_fee',
        'field' => 'grp_monthly_fee'
      ),
      'grp_max_transactions' => array(
        'data' => t('Max Transactions'),
        'type' => 'property',
        'specifier' => 'max_trans',
        'field' => 'max_trans'
      ),
      'grp_max_emails' => array(
        'data' => t('Max Transactions'),
        'type' => 'property',
        'specifier' => 'max_emails',
        'field' => 'max_emails'
      ),
      'grp_payment_length' => array(
        'data' => t('Length(Days)'),
        'type' => 'property',
        'specifier' => 'grp_payment_length',
        'field' => 'grp_payment_length'
      ),
      'grp_size' => array(
        'data' => t('Size(people)'),
        'type' => 'property',
        'specifier' => 'grp_size',
        'field' => 'grp_size'
      ),

      'created' => array(
        'data' => t('Created'),
        'type' => 'property',
        'specifier' => 'created',
        'field' => 'created'
      ),
  );


  $entities = ccdev_groups_load_multiple(FALSE, array(), FALSE, $header);
  if (!empty($entities)) {
    foreach ($entities as $entity) {
	if(user_access('administer ccdev_groups entities')) {
	      // Create tabular rows for our entities.
	      $rows[] = array(
		'data' => array(
		'grp_name' => l($entity->grp_name, 'ccMods/ccGroup/basic/' . $entity->grp_name),
		'grp_description' => $entity->grp_description,
		'grp_type' => $entity->grp_type,
		'grp_withdraw_fee' => $entity->grp_withdraw_fee,
		'grp_exchange_fee' => $entity->grp_exchange_fee,
		'grp_trade_fee' => $entity->grp_trade_fee,
		'grp_monthly_fee' => $entity->grp_monthly_fee,
		'grp_max_trans' => $entity->grp_max_transactions,
		'grp_max_emails' => $entity->grp_max_emails,
		'grp_payment_length' => $entity->grp_payment_length,
		'grp_size' => $entity->grp_size,
		'grp_created' => $entity->grp_payment_length,
		'manage' => _ccGroup_make_link(array('group_id' => $entity->basic_id,'title' => 'Manage')),
		),
	      );
	}else{
		$rows[] = array(
		'data' => array(
		'grp_name' => l($entity->grp_name, 'ccMods/ccGroup/basic/' . $entity->grp_name),
		'grp_description' => $entity->grp_description,
		'grp_type' => $entity->grp_type,
		'grp_withdraw_fee' => $entity->grp_withdraw_fee,
		'grp_exchange_fee' => $entity->grp_exchange_fee,
		'grp_trade_fee' => $entity->grp_trade_fee,
		'grp_monthly_fee' => $entity->grp_monthly_fee,
		'grp_max_trans' => $entity->grp_max_transactions,
		'grp_max_emails' => $entity->grp_max_emails,
		'grp_payment_length' => $entity->grp_payment_length,
		'grp_size' => $entity->grp_size,
		'grp_created' => $entity->grp_payment_length,
		'manage' => _ccGroup_make_link(array('group_id' => $entity->basic_id,'title' => 'Manage')),
		),
	      );

		}
    }

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
      '#markup' => t('No ccdev_groups entities currently exist.'),
    );
  }
  return $content;
}
