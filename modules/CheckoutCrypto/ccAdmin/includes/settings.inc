<?php


function admin_info(){
  $info['ccdev_admin'] = array(
    // A human readable label to identify our entity.
    'label' => t('checkout crypto account Entity'),

    // The controller for our Entity, extending the Drupal core controller.
    'controller class' => 'ccAdminBasicController',

    // The table for this entity defined in hook_schema()
    'base table' => 'ccdev_admin',

    // Returns the uri elements of an entity.
    'uri callback' => 'ccdev_admin_uri',

    // IF fieldable == FALSE, we can't attach fields.
    'fieldable' => TRUE,

    'entity keys' => array(
      // The 'id' (basic_id here) is the unique id.
      'id' => 'basic_id' ,
      // Bundle will be determined by the 'bundle_type' field.
      'bundle' => 'bundle_type',
    ),
    'bundle keys' => array(
      'bundle' => 'bundle_type',
    ),

    'static cache' => TRUE,

    'bundles' => array(
      'admin_bundle' => array(
        'label' => 'Admin bundle',
        'admin' => array(
          'path' => 'admin/structure/ccdev_admin/manage',
          'access arguments' => array('administer ccdev_admin entities'),
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

function admin_menu(){
  $items['admin/APIAdmin'] = array(
    'title' => 'Admin',
    'page callback' => 'ccAdmin_info_page',
    'access arguments' => array('view any ccdev_admin entity'),
  );

  // This provides a place for Field API to hang its own
  // interface and has to be the same as what was defined
  // in basic_entity_info() above.
  $items['admin/structure/ccdev_admin/manage'] = array(
    'title' => 'Administer ccAdmin',
    'page callback' => 'ccdev_admin_list_entities',
    'access arguments' => array('administer ccdev_admin entities'),
  );

  // Add example entities.
  $items['admin/structure/ccdev_admin/manage/add'] = array(
    'title' => 'Add a ccAdmin Basic Entity',
    'page callback' => 'ccdev_admin_add',
    'access arguments' => array('create ccdev_admin entities'),
    'type' => MENU_LOCAL_ACTION,
  );

  // List of all entity_example_basic entities.
  $items['admin/structure/ccdev_admin/manage/list'] = array(
    'title' => 'List',
    'type' => MENU_DEFAULT_LOCAL_TASK,
  );

  // The page to view our entities - needs to follow what
  // is defined in basic_uri and will use load_basic to retrieve
  // the necessary entity info.
  $items['admin/APIAdmin/basic/%ccdev_admin'] = array(
    'title callback' => 'ccdev_admin_title',
    'title arguments' => array(3),
    'page callback' => 'ccdev_admin_view',
    'page arguments' => array(3),
    'access arguments' => array('view any ccdev_admin entity'),
  );

  // 'View' tab for an individual entity page.
  $items['admin/APIAdmin/basic/%ccdev_admin/view'] = array(
    'title' => 'View',
    'type' => MENU_DEFAULT_LOCAL_TASK,
    'weight' => -10,
  );

  // 'Edit' tab for an individual entity page.
  $items['admin/APIAdmin/basic/%ccdev_admin/edit'] = array(
    'title' => 'Edit',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ccdev_admin_form', 3),
    'access arguments' => array('edit any ccdev_admin entity'),
    'type' => MENU_LOCAL_TASK,
  );

  // Add example entities.
  $items['admin/APIAdmin/basic/add'] = array(
    'title' => 'some page',
    'page callback' => 'ccdev_admin_add',
    'access arguments' => array('create ccdev_admin entities'),
  );

$items['admin/config/people/ccAdmin'] = array(
  'title' => 'ccAdmin',
  'description' => 'Configuration for the ccAdmin module.',
  'page callback' => 'drupal_get_form',
  'page arguments' => array('ccAdmin_settings_form'),
  'access arguments' => array('administer users'),
  'type' => MENU_NORMAL_ITEM,
);

	return $items;
}

function admin_permissions(){
  $permissions = array(
    'administer ccdev_admin entities' => array(
      'title' => t('Administer ccdev_admin entities'),
    ),
    'user ccdev_admin entities' => array(
      'title' => t('view any ccdev_admin entities'),
    ),
    'view any ccdev_admin entity' => array(
      'title' => t('View any ccAdmin Basic entity'),
    ),
    'edit any ccdev_admin entity' => array(
      'title' => t('Edit any ccAdmin Basic entity'),
    ),
    'create ccdev_admin entities' => array(
      'title' => t('Create ccAdmin Basic Entities'),
    ),
  );
	return $permissions;
}


function admin_settings_form(){
  $form = array();

  $maintenance_users = array('rate' => 'rate', 'withdraw' => 'withdraw', 'editcoin' => 'editcoin', 'refreshworker' => 'refreshworker', 'all' => 'all');

  $form['ccAdmin_maintenance_api_keys_section'] = array(
    '#type' => 'fieldset',
    '#title' => t('Server maintenance api key generation'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['ccAdmin_maintenance_api_keys_section']['ccAdmin_maintenance_api_keys'] = array(
    '#type' => 'radios',
    '#title' => t('Regenerate key for user'),
    '#default_value' => variable_get('ccAdmin_maintenance_api_keys', "user1"),
    '#options' => $maintenance_users,
    '#required' => TRUE,
  );

  $form['#validate'][] = 'ccAdmin_settings_form_validate';
 return system_settings_form($form);
}

function admin_settings_form_validate($form, &$form_state) {
  $maintenance_users = array('rate' => 'rate', 'withdraw' => 'withdraw', 'editcoin' => 'editcoin', 'refreshworker' => 'refreshworker', 'all' => 'all');

  $c = $form_state['values']['ccAdmin_maintenance_api_keys'];
  if (!(in_array($c, $maintenance_users))) {
    if(!($c == 'all')) { 
      form_set_error('ccAdmin_maintenance_api_keys', t('Invalid maintenance user specified'));
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
	module_load_include('inc','ccAccount','includes/cc-php/lib');
  if (!count(form_get_errors())) {
    try {
      ccInsertMaintainers($c);
    } catch (exception $e) {
      //var_dump($e);
    }  
  }

}
