<?php

function wallets_info(){
 $info['ccdev_wallets'] = array(
    'label' => t('Wallets'),

    'controller class' => 'ccWalletsBasicController',

    'base table' => 'ccdev_wallets',

    'uri callback' => 'ccdev_wallets_uri',

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
      'wallet_bundle' => array(
        'label' => 'Wallet bundle',
        'admin' => array(
          'path' => 'admin/structure/ccdev_wallets/manage',
          'access arguments' => array('administer ccWallets entities'),
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

function wallets_permissions(){
  $permissions = array(
    'administer ccdev_wallets entities' => array(
      'title' => t('Administer ccdev_wallets entities'),
    ),
    'view any ccdev_wallets entity' => array(
      'title' => t('View any Entity Example Basic entity'),
    ),
    'edit any ccdev_wallets entity' => array(
      'title' => t('Edit any Entity Example Basic entity'),
    ),
    'create ccdev_wallets entities' => array(
      'title' => t('Create Entity Example Basic Entities'),
    ),
  );
  return $permissions;
}

function wallets_menu(){
	module_load_include('inc', 'ccCoin', 'includes/entity');
 $items['Account/Wallets'] = array(
    'title' => 'Wallets',
    'page callback' => 'ccWallets_info_page',
    'access arguments' => array('view any ccdev_wallets entity'),
	'menu_name' => 'main-menu',
 	'weight' => 4,
  );

  $items['admin/structure/ccdev_wallets/manage'] = array(
    'title' => 'Administer ccdev_wallets entity type',
    'page callback' => 'ccdev_wallets_list_entities',
    'access arguments' => array('administer ccdev_wallets entities'),
  );

  // Add example entities.
  $items['admin/structure/ccdev_wallets/manage/add'] = array(
    'title' => 'add wallet(disabled)',
    'page callback' => 'ccdev_wallets_add',
    'access arguments' => array('create ccdev_wallets entities'),
    'type' => MENU_LOCAL_ACTION,
  );

  // List of all ccdev_wallets entities.
  $items['admin/structure/ccdev_wallets/manage/list'] = array(
    'title' => 'List',
    'type' => MENU_DEFAULT_LOCAL_TASK,
  );

  $items['Wallets/basic/%ccdev_wallets'] = array(
    'title callback' => 'ccdev_wallets_title',
    'title arguments' => array(2),
    'page callback' => 'ccdev_wallets_view',
    'page arguments' => array(2),
    'access arguments' => array('view any ccdev_wallets entity'),
  );

  $items['Wallets/basic/%ccdev_wallets/view'] = array(
    'title' => 'View',
    'type' => MENU_DEFAULT_LOCAL_TASK,
    'weight' => -10,
  );

  // 'Edit' tab for an individual entity page.
  $items['Wallets/basic/%ccdev_wallets/edit'] = array(
    'title' => 'Edit',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ccdev_wallets_form', 2),
    'access arguments' => array('edit any ccdev_wallets entity'),
    'type' => MENU_LOCAL_TASK,
  );

  // Add example entities.
  $items['Wallets/basic/add'] = array(
    'title' => 'Add Wallet(disabled)',
    'page callback' => 'ccdev_wallets_add',
    'access arguments' => array('create ccdev_wallets entities'),
  );

  return $items;
}
