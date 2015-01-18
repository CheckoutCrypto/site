<?php

/**
 * CheckoutCrypto Hosting info.
 */
error_reporting(~0); ini_set('display_errors', 1);
function hosting_info(){
  $info['ccdev_hosting'] = array(
    'label' => t('checkout crypto Hosting Entity'),

    'controller class' => 'ccHostingBasicController',

    'base table' => 'ccdev_hosting',

    'uri callback' => 'ccdev_hosting_uri',

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
      'ccdev_hosting_bundle' => array(
        'label' => 'Hosting bundle',
        'admin' => array(
          'path' => 'admin/structure/ccdev_hosting/manage',
          'access arguments' => array('administer ccdev_hosting entities'),
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

/**
 * CheckoutCrypto Hosting permissions.
 */
function hosting_permissions(){
  $permissions = array(
    'administer ccdev_hosting entities' => array(
      'title' => t('Administer ccdev_hosting entities'),
    ),
    'user ccdev_hosting entities' => array(
      'title' => t('view any ccdev_hosting entities'),
    ),
    'view any ccdev_hosting entity' => array(
      'title' => t('View any ccHosting Basic entity'),
    ),
    'edit any ccdev_hosting entity' => array(
      'title' => t('Edit any ccHosting Basic entity'),
    ),
    'create ccdev_hosting entities' => array(
      'title' => t('Create ccHosting Basic Entities'),
    ),
  );
  return $permissions;
}

/**
 * CheckoutCrypto Hosting menu.
 */
function hosting_menu(){
$items['ccMods/ccHosting'] = array(
    'title' => 'Hosting',
    'page callback' => 'ccHosting_info_page',
    'access arguments' => array('view any ccdev_hosting entity'),
  );

  $items['admin/structure/ccdev_hosting/manage'] = array(
    'title' => 'Administer Hosting',
    'page callback' => 'ccdev_hosting_list_entities',
    'access arguments' => array('administer ccdev_hosting entities'),
  );

  $items['admin/structure/ccdev_hosting/manage/add'] = array(
    'title' => 'Add a Hosting Entity',
    'page callback' => 'ccdev_hosting_add',
    'access arguments' => array('create ccdev_hosting entities'),
    'type' => MENU_LOCAL_ACTION,
  );

  $items['admin/structure/ccdev_hosting/manage/list'] = array(
    'title' => 'List',
    'type' => MENU_DEFAULT_LOCAL_TASK,
  );

  $items['ccMods/ccHosting/basic/%ccdev_hosting'] = array(
    'title callback' => 'ccdev_hosting_title',
    'title arguments' => array(3),
    'page callback' => 'ccdev_hosting_view',
    'page arguments' => array(3),
    'access arguments' => array('view any ccdev_hosting entity'),
  );

  // 'View' tab for an individual entity page.
  $items['ccMods/ccHosting/basic/%ccdev_hosting/view'] = array(
    'title' => 'View',
    'type' => MENU_DEFAULT_LOCAL_TASK,
    'weight' => -10,
  );

  // 'Edit' tab for an individual entity page.
  $items['ccMods/ccHosting/basic/%ccdev_hosting/edit'] = array(
    'title' => 'Edit',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ccdev_hosting_form', 3),
    'access arguments' => array('edit any ccdev_hosting entity'),
    'type' => MENU_LOCAL_TASK,
  );

  // 'Manage' link for an individual entity page.
  $items['ccMod/ccHosting/any/%ctools_js'] = array(
    'page callback' => 'ccHosting_manage_callback',
    'page arguments' => array(3,4),
    'access callback' => TRUE,
    'type' => MENU_CALLBACK,
  );

  // Add example entities.
  $items['ccMods/ccHosting/basic/add'] = array(
    'title' => 'Add new host',
    'page callback' => 'ccdev_hosting_add',
    'access arguments' => array('create ccdev_hosting entities'),
  );

$items['admin/config/people/ccHosting'] = array(
  'title' => 'ccHosting',
  'description' => 'Configuration for the Hosting module.',
  'page callback' => 'drupal_get_form',
  'page arguments' => array('ccHosting_settings_form'),
  'access arguments' => array('administer users'),
  'type' => MENU_NORMAL_ITEM,
);

  return $items;
}
