<?php

function balance_info(){
  $info['ccdev_balance'] = array(
    'label' => t('Balance'),

    'controller class' => 'ccBalanceBasicController',

    'base table' => 'ccdev_balance',

    'uri callback' => 'ccdev_balance_uri',

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
      'balance_bundle' => array(
        'label' => 'balance bundle',
        'admin' => array(
          'path' => 'admin/structure/ccdev_balance/manage',
          'access arguments' => array('administer ccBalance entities'),
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


function balance_menu(){
    module_load_include('inc', 'ccBalance', 'includes/cc-php/entity');
$items['Account/Balance'] = array(
    'title' => 'Balance',
    'page callback' => 'ccBalance_info_page',
    'access arguments' => array('view any ccdev_balance entity'),
    'menu_name' => 'main-menu', // You'll need to have a menu named
 	'weight' => 2,
  );

  $items['admin/structure/ccdev_balance/manage'] = array(
    'title' => 'Administer ccdev_balance entity type',
    'page callback' => 'ccdev_balance_list_entities',
    'access arguments' => array('administer ccdev_balance entities'),
  );

  // Add example entities.
  $items['admin/structure/ccdev_balance/manage/add'] = array(
    'title' => 'Add Balance',
    'page callback' => 'ccdev_balance_add',
    'access arguments' => array('create ccdev_balance entities'),
    'type' => MENU_LOCAL_ACTION,
  );

  // List of all ccdev_balance entities.
  $items['admin/structure/ccdev_balance/manage/list'] = array(
    'title' => 'List',
    'type' => MENU_DEFAULT_LOCAL_TASK,
  );

  $items['Balance/basic/%ccdev_balance'] = array(
    'title callback' => 'ccdev_balance_title',
    'title arguments' => array(2),
    'page callback' => 'ccdev_balance_view',
    'page arguments' => array(2),
    'access arguments' => array('view any ccdev_balance entity'),
  );

  // 'View' tab for an individual entity page.
  $items['Balance/basic/%ccdev_balance/view'] = array(
    'title' => 'View',
    'type' => MENU_DEFAULT_LOCAL_TASK,
    'weight' => -10,
  );

  // 'Edit' tab for an individual entity page.
  $items['Balance/basic/%ccdev_balance/edit'] = array(
    'title' => 'Edit',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ccdev_balance_form', 3),
    'access arguments' => array('edit any ccdev_balance entity'),
    'type' => MENU_LOCAL_TASK,
  );

  $items['Balance/withdraw/%ctools_js/%'] = array(
    'page callback' => 'ccBalance_withdraw_callback',
    'page arguments' => array(2,3),
    'access callback' => TRUE,
    'type' => MENU_CALLBACK,
  );
 $items['Balance/deposit/%ctools_js/%'] = array(
    'page callback' => 'ccBalance_deposit_callback',
    'page arguments' => array(2,3),
    'access callback' => TRUE,
    'type' => MENU_CALLBACK,
  );
$items['Balance/autotrade/%ctools_js/%'] = array(
    'page callback' => 'ccBalance_deposit_callback',
    'page arguments' => array(2,3),
    'access callback' => TRUE,
    'type' => MENU_CALLBACK,
  );
  $items['Balance/autopay/%ctools_js/%'] = array(
    'page callback' => 'ccBalance_autopay_callback',
    'page arguments' => array(2,3),
    'access callback' => TRUE,
    'type' => MENU_CALLBACK,
  );
 $items['Balance/details'] = array(
    'title' => 'DepositProcessor',
    'page callback' => 'deposit_process',
    'access arguments' => array('view any ccdev_balance entity'),
 	  'type' => MENU_DEFAULT_LOCAL_TASK,
  );
 /*  $items['Balace/Deposit'] = array(
    'title' => 'Balance Deposit',
    'page callback' => 'ccBalance_deposit_page',
    'access arguments' => array('view any ccdev_balance entity'),
  ); */

	return $items;
}

function balance_theme(){
 $settings = array(
    'CToolsModal' => array(
      'loadingText' => t('Loading...'),
      'closeText' => t('Close'),
      'modalSize' => array(
        'type' => 'fixed',
        'height' => 500,
        'width' => 500,
      ),
      'modalOptions' => array(
        'opacity' => .6,
        'background-color' => '#000',
      ),
      'animation' => 'fadeIn',
      'animationSpeed' => 'slow',
      'closeImage' => theme('image', array(
        'path' => ctools_image_path('icon-close-window.png'),
        'title' => t('Close window'),
        'alt' => t('Close window'),
      )),
      'throbber' => theme('image', array(
          'path' => ctools_image_path('throbber.gif'),
          'title' => t('Loading...'),
          'alt' => t('Loading'),
      )),
    ),
  );	
  drupal_add_js($settings, 'setting');
}

function balance_permissions(){
  $permissions = array(
    'administer ccdev_balance entities' => array(
      'title' => t('Administer ccdev_balance entities'),
    ),
    'view any ccdev_balance entity' => array(
      'title' => t('View any ccBalance entity'),
    ),
    'edit any ccdev_balance entity' => array(
      'title' => t('Edit any ccBalance entity'),
    ),
    'create ccdev_balance entities' => array(
      'title' => t('Create any ccBalance entity'),
    ),
  );
return $permissions;
}
