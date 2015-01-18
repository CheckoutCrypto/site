<?php

function account_info(){
 $info['ccdev_accounts'] = array(
    'label' => t('checkout crypto account Entity'),
    'controller class' => 'ccAccountBasicController',
    'base table' => 'ccdev_accounts',
    'uri callback' => 'ccdev_accounts_uri',
    'fieldable' => TRUE,
    'entity keys' => array(
      'id' => 'basic_id' ,
      'bundle' => 'bundle_type',
    ),
    'bundle keys' => array(
      'bundle' => 'bundle_type',
    ),
    'static cache' => TRUE,
    'bundles' => array(
      'ccdev_account_bundle' => array(
        'label' => 'Account bundle',
        'admin' => array(
          'path' => 'admin/structure/ccdev_accounts/manage',
          'access arguments' => array('administer ccdev_accounts entities'),
        ),
      ),
    ),
    'view modes' => array(
      'tweaky' => array(
        'label' => t('Tweaky'),
        'custom settings' => FALSE,
      ),
    ),
  );
$info['ccdev_billing'] = array(
    'label' => t('checkout crypto account Entity'),
    'controller class' => 'ccAccountBasicController',
    'base table' => 'ccdev_billing',
    'uri callback' => 'ccdev_billing_uri',
    'fieldable' => TRUE,
    'entity keys' => array(
      'id' => 'basic_id' ,
      'bundle' => 'bundle_type',
    ),
    'bundle keys' => array(
      'bundle' => 'bundle_type',
    ),
    'static cache' => TRUE,
    'bundles' => array(
      'ccdev_billing_bundle' => array(
        'label' => 'Billing bundle',
        'admin' => array(
          'path' => 'admin/structure/ccdev_billing/manage',
          'access arguments' => array('administer ccdev_accounts entities'),
        ),
      ),
    ),
    'view modes' => array(
      'tweaky' => array(
        'label' => t('Tweaky'),
        'custom settings' => FALSE,
      ),
    ),
  );

$info['ccdev_billing_summary'] = array(
    'label' => t('checkout crypto account Entity'),
    'controller class' => 'ccAccountBasicController',
    'base table' => 'ccdev_billing_summary',
    'uri callback' => 'ccdev_billing_summary_uri',
    'fieldable' => TRUE,
    'entity keys' => array(
      'id' => 'basic_id' ,
      'bundle' => 'bundle_type',
    ),
    'bundle keys' => array(
      'bundle' => 'bundle_type',
    ),
    'static cache' => TRUE,
    'bundles' => array(
      'ccdev_billing__summary_bundle' => array(
        'label' => 'Billing Summary Bundle',
        'admin' => array(
          'path' => 'admin/structure/ccdev_billing_summary/manage',
          'access arguments' => array('administer ccdev_accounts entities'),
        ),
      ),
    ),
    'view modes' => array(
      'tweaky' => array(
        'label' => t('Tweaky'),
        'custom settings' => FALSE,
      ),
    ),
  );
	return $info;
}

function account_menu(){
  $items['Account'] = array(
    'title' => 'Account',
    'page callback' => 'ccAccount_info_page',
    'access arguments' => array('view any ccdev_accounts entity'),
  );
  $items['Account/Billing'] = array(
    'title' => 'Billing',
    'page callback' => 'ccAccount_billing_page',
    'access arguments' => array('view any ccdev_accounts entity'),
  );
  $items['Account/Dashboard'] = array(
    'title' => 'Dashboard',
    'page callback' => 'ccAccount_summary_page',
    'access arguments' => array('view any ccdev_accounts entity'),
  );

  // This provides a place for Field API to hang its own
  // interface and has to be the same as what was defined
  // in basic_entity_info() above.
  $items['admin/structure/ccdev_accounts/manage'] = array(
    'title' => 'Administer Accounts',
    'page callback' => 'ccdev_accounts_list_entities',
    'access arguments' => array('administer ccdev_accounts entities'),
  );

  // Add example entities.
  $items['admin/structure/ccdev_accounts/manage/add'] = array(
    'title' => 'Add a ccAccount Basic Entity',
    'page callback' => 'ccdev_accounts_add',
    'access arguments' => array('create ccdev_accounts entities'),
    'type' => MENU_LOCAL_ACTION,
  );

  // List of all entity_example_basic entities.
  $items['admin/structure/ccdev_accounts/manage/list'] = array(
    'title' => 'List',
    'type' => MENU_DEFAULT_LOCAL_TASK,
  );

  // The page to view our entities - needs to follow what
  // is defined in basic_uri and will use load_basic to retrieve
  // the necessary entity info.
  $items['Account/basic/%ccdev_accounts'] = array(
    'title callback' => 'ccdev_accounts_title',
    'title arguments' => array(2),
    'page callback' => 'ccdev_accounts_view',
    'page arguments' => array(2),
    'access arguments' => array('view any ccdev_accounts entity'),
  );

  // 'View' tab for an individual entity page.
  $items['Account/basic/%ccdev_accounts/view'] = array(
    'title' => 'View',
    'type' => MENU_DEFAULT_LOCAL_TASK,
    'weight' => -10,
  );

  // 'Edit' tab for an individual entity page.
  $items['Account/basic/%ccdev_accounts/edit'] = array(
    'title' => 'Edit',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ccdev_accounts_form', 3),
    'access arguments' => array('edit any ccdev_accounts entity'),
    'type' => MENU_LOCAL_TASK,
  );

  // Add example entities.
  $items['Account/basic/add'] = array(
    'title' => 'Generate API key',
    'page callback' => 'ccdev_accounts_add',
    'access arguments' => array('create ccdev_accounts entities'),
  );

$items['admin/config/people/ccAccount'] = array(
  'title' => 'ccAccount',
  'description' => 'Configuration for the ccAccount module.',
  'page callback' => 'drupal_get_form',
  'page arguments' => array('ccAccount_admin_form'),
  'access arguments' => array('administer users'),
);
	return $items;
}

function account_permissions(){
  $permissions = array(
    'administer ccdev_accounts entities' => array(
      'title' => t('Administer ccdev_accounts entities'),
    ),
    'user ccdev_accounts entities' => array(
      'title' => t('view any ccdev_accounts entities'),
    ),
    'view any ccdev_accounts entity' => array(
      'title' => t('View any ccAccount Basic entity'),
    ),
    'edit any ccdev_accounts entity' => array(
      'title' => t('Edit any ccAccount Basic entity'),
    ),
    'create ccdev_accounts entities' => array(
      'title' => t('Create ccAccount Basic Entities'),
    ),
  );
	return $permissions;
}

function account_settings_form() {
  $form = array();

  $maintenance_users = array('rate' => 'rate', 'withdraw' => 'withdraw', 'editcoin' => 'editcoin', 'refreshworker' => 'refreshworker', 'all' => 'all');

  $form['ccAccount_maintenance_api_keys_section'] = array(
    '#type' => 'fieldset',
    '#title' => t('Server maintenance api key generation'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['ccAccount_maintenance_api_keys_section']['ccAccount_maintenance_api_keys'] = array(
    '#type' => 'radios',
    '#title' => t('Regenerate key for user'),
    '#default_value' => variable_get('ccAccount_maintenance_api_keys', "user1"),
    '#options' => $maintenance_users,
    '#required' => TRUE,
  );

  $form['#validate'][] = 'ccAccount_settings_form_validate';

  return system_settings_form($form);
}

/**
 * Validate cc payment method settings.
 * @param unknown_type $form
 * @param unknown_type $form_state
 */
function account_settings_form_validate($form, &$form_state) {
  $maintenance_users = array('rate' => 'rate', 'withdraw' => 'withdraw', 'editcoin' => 'editcoin', 'refreshworker' => 'refreshworker', 'all' => 'all');

  $c = $form_state['values']['ccAccount_maintenance_api_keys'];
  if (!(in_array($c, $maintenance_users))) {
    if(!($c == 'all')) { 
      form_set_error('ccAccount_maintenance_api_keys', t('Invalid maintenance user specified'));
    }
  }

  if(!(is_array($c))) {
    if($c == 'all') {
      unset($maintenance_users['all']);
      $c = $maintenance_users;
    } else {
      $c = array($c);
    }
  }

  if (!count(form_get_errors())) {
    try {
  	module_load_include('inc','ccAccount','includes/cc-php/lib');
      ccInsertMaintainers($c);
    } catch (exception $e) {
      //var_dump($e);
    }  
  }
}


