<?php


/**
 * Form function to create an entity_example_basic entity.
 *
 * The pattern is:
 * - Set up the form for the data that is specific to your
 *   entity: the columns of your base table.
 * - Call on the Field API to pull in the form elements
 *   for fields attached to the entity.
 */
function ccdev_groups_form($form, &$form_state, $entity) {
  $form['grp_name'] = array(
  '#type' => 'textfield',
    '#title' => t('Group Name'),
    '#required' => TRUE,
    '#default_value' => $entity->grp_name,
  );
 $form['grp_description'] = array(
  '#type' => 'textfield',
    '#title' => t('Description'),
    '#required' => FALSE,
    '#default_value' => $entity->grp_description,
  );
 $form['grp_type'] = array(
  '#type' => 'textfield',
    '#title' => t('Type <hosting/API>'),
    '#required' => TRUE,
    '#default_value' => $entity->grp_type,
  );
 $form['grp_withdraw_fee'] = array(
  '#type' => 'textfield',
    '#title' => t('Withdraw Fee'),
    '#required' => TRUE,
    '#default_value' => $entity->grp_withdraw_fee,
  );
 $form['grp_trade_fee'] = array(
  '#type' => 'textfield',
    '#title' => t('Trade Fee'),
    '#required' => TRUE,
    '#default_value' => $entity->grp_trade_fee,
  );
 $form['grp_exchange_fee'] = array(
  '#type' => 'textfield',
    '#title' => t('Exchange Fee'),
    '#required' => TRUE,
    '#default_value' => $entity->grp_exchange_fee,
  );
 $form['grp_monthly_fee'] = array(
  '#type' => 'textfield',
    '#title' => t('Monthly Fee'),
    '#required' => TRUE,
    '#default_value' => $entity->grp_monthly_fee,
  );
 $form['grp_max_transactions'] = array(
  '#type' => 'textfield',
    '#title' => t('Max Transactions'),
    '#required' => TRUE,
    '#default_value' => $entity->grp_max_transactions,
  );
 $form['grp_max_emails'] = array(
  '#type' => 'textfield',
    '#title' => t('Max Emails'),
    '#required' => TRUE,
    '#default_value' => $entity->grp_max_emails,
  );
 $form['grp_payment_length'] = array(
  '#type' => 'textfield',
    '#title' => t('Payment Length'),
    '#required' => TRUE,
    '#default_value' => $entity->grp_payment_length,
  );

 $form['grp_SKU'] = array(
  '#type' => 'textfield',
    '#title' => t('Payment Length'),
    '#required' => TRUE,
    '#default_value' => $entity->grp_payment_length,
  );


  $form['basic_entity'] = array(
    '#type' => 'value',
    '#value' => $entity,
  );
  field_attach_form('ccdev_groups', $entity, $form, $form_state);

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Create Group'),
    '#weight' => 100,
  );

  return $form;
}


/**
 * Drupal form to be put in a modal.
 */
function ccGroup_manage_form($form, $form_state) {
     module_load_include('inc', 'ccGroup', 'includes/cc-php/lib');
  $form = array();
  //drupal_add_js(drupal_get_path('module','ccGroup').'/ccGroup.js', 'file');

  global $user;

$grpdata = array();
$grpdata = getGroupData($form_state['group_id']);
/*
/// THUMB
 $form['image'] = array('#markup' => t('<div id="cc-addcoin" style="height=200px;"><div id="cc-addcoin-thumb" style="background:url('.$coindata['coin_image'].') center no-repeat #fff; height:150px;"></div></div>'));
// RATE
$form['rate'] = array('#markup' => t('<div id="cc-addcoin-info" style="text-align:center;font:bold 25px arial,sans-serif; right center no-repeat #fff;"><p>'.$coindata['coin_name'].'<p></div>'));
/// DESC
$form['desc'] = array('#markup' => t('<div id="cc-addcoin-desc" style="float:left;text-align:center;width:250px;height=100px;font:15px arial,sans-serif;"><p>'.$coindata['coin_description'].'<p></div>')); */

	if(isset($grpdata)){

		$form['grp_name'] = array(
			'#type' => 'textfield',
			'#title' => t('Name'),
			'#required' => TRUE,
			'#default_value' => $grpdata['grp_name'],
		);
		$form['grp_description'] = array(
			'#type' => 'textfield',
			'#title' => t('Description'),
			'#required' => TRUE,
			'#default_value' => $grpdata['grp_description'],
		);
		$form['grp_type'] = array(
			'#type' => 'textfield',
			'#title' => t('Type'),
			'#required' => TRUE,
			'#default_value' => $grpdata['grp_type'],
		);

		$form['grp_withdraw_fee'] = array(
			'#type' => 'textfield',
			'#title' => t('Cost'),
			'#required' => TRUE,
			'#default_value' => $grpdata['grp_withdraw_fee'],
		);

		$form['grp_trade_fee'] = array(
			'#type' => 'textfield',
			'#title' => t('Cost'),
			'#required' => TRUE,
			'#default_value' => $grpdata['grp_trade_fee'],
		);

		$form['grp_exchange_fee'] = array(
			'#type' => 'textfield',
			'#title' => t('Cost'),
			'#required' => TRUE,
			'#default_value' => $grpdata['grp_exchange_fee'],
		);

		$form['grp_monthly_fee'] = array(
			'#type' => 'textfield',
			'#title' => t('Cost'),
			'#required' => TRUE,
			'#default_value' => $grpdata['grp_monthly_fee'],
		);

		$form['grp_max_transactions'] = array(
			'#type' => 'textfield',
			'#title' => t('Max Transactions'),
			'#required' => TRUE,
			'#default_value' => $grpdata['grp_max_transactions'],
		);

		$form['grp_max_email'] = array(
			'#type' => 'textfield',
			'#title' => t('Max Emails'),
			'#required' => TRUE,
			'#default_value' => $grpdata['grp_max_emails'],
		);

		$form['grp_payment_length'] = array(
			'#type' => 'textfield',
			'#title' => t('Payment Length'),
			'#required' => TRUE,
			'#default_value' => $grpdata['grp_payment_length'],
		);

		/////// required for form
		$form['basic_id'] = array(
			'#type' => 'value',
			'#value' => $form_state['group_id'],
		);
		$form['bundle_type'] = array(
			'#type' => 'value',
			'#value' => 'ccdev_groups_bundle',
		);
		$form['submit'] = array(
			'#type' => 'submit',
			'#value' => t('Save'),
			'#attributes' => array('class' => array('btn', 'btn-success'), 'style' => "float:right; padding: 5px 10px;"),
			'#theme' => "submit",
			'#prefix' => "<div class=''>",
			'#suffix' => "</div>",
			  '#ajax' => array(
			  'callback' => 'ccGroup_manage_form_submit',),
			); 
	}
  return $form;
}
