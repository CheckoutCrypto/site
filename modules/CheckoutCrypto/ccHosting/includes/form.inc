<?php

/**
 * Form function to create an entity_example_basic entity.
 */
function ccdev_hosting_form($form, &$form_state, $entity) {
  $form['site_name'] = array(
  '#type' => 'textfield',
    '#title' => t('Site Name'),
    '#required' => TRUE,
    '#default_value' => $entity->site_name,
  );
 $form['site_domain'] = array(
  '#type' => 'textfield',
    '#title' => t('Site Domain'),
    '#required' => TRUE,
    '#default_value' => $entity->site_domain,
  );
 $form['site_description'] = array(
  '#type' => 'textfield',
    '#title' => t('Description'),
    '#required' => FALSE,
    '#default_value' => $entity->site_description,
  );
 $form['site_cms'] = array(
  '#type' => 'textfield',
    '#title' => t('Site CMS'),
    '#required' => TRUE,
    '#default_value' => $entity->site_cms,
  );
 $form['group_price'] = array(
  '#type' => 'textfield',
    '#title' => t('Package'),
    '#required' => TRUE,
    '#default_value' => $entity->group_price,
  );

  $form['basic_entity'] = array(
    '#type' => 'value',
    '#value' => $entity,
  );
  field_attach_form('ccdev_hosting', $entity, $form, $form_state);

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Create Host'),
    '#weight' => 100,
  );

  return $form;
}

/**
 * Drupal form to be put in a modal.
 */
function manage_form($form, $form_state) {
  module_load_include('inc','ccHosting','includes/lib');
  $form = array();
  global $user;

	$sitedata = array();
	$sitedata = getSiteData($form_state['site_id']);

	if(isset($sitedata)){

		$form['site_name'] = array(
			'#type' => 'textfield',
			'#title' => t('Site Name'),
			'#required' => TRUE,
			'#default_value' => $sitedata['site_name'],
		);
		$form['site_description'] = array(
			'#type' => 'textfield',
			'#title' => t('Description'),
			'#required' => TRUE,
			'#default_value' => $sitedata['site_description'],
		);

		$form['site_domain'] = array(
			'#type' => 'textfield',
			'#title' => t('Domain'),
			'#required' => TRUE,
			'#default_value' => $sitedata['site_domain'],
		);

		$form['site_cms'] = array(
			'#type' => 'textfield',
			'#title' => t('CMS'),
			'#required' => TRUE,
			'#default_value' => $sitedata['site_cms'],
		);

		/////// required for form
		$form['basic_id'] = array(
			'#type' => 'value',
			'#value' => $form_state['site_id'],
		);
		$form['bundle_type'] = array(
			'#type' => 'value',
			'#value' => 'ccdev_hosting_bundle',
		);
		$form['submit'] = array(
			'#type' => 'submit',
			'#value' => t('Save'),
			'#attributes' => array('class' => array('btn', 'btn-success'), 'style' => "float:right; padding: 5px 10px;"),
			'#theme' => "submit",
			'#prefix' => "<div class=''>",
			'#suffix' => "</div>",
			  '#ajax' => array(
			  'callback' => 'manage_form_submit',),
			); 
	}
  return $form;
}
