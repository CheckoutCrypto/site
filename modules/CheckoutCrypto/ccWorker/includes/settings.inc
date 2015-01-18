<?php

function worker_info(){
$info['ccdev_work_orders'] = array(
    // A human readable label to identify our entity.
    'label' => t('Work Orders'),

    // The controller for our Entity, extending the Drupal core controller.
    'controller class' => 'ccWorkerBasicController',

    // The table for this entity defined in hook_schema()
    'base table' => 'ccdev_work_orders',

    // Returns the uri elements of an entity.
    'uri callback' => 'ccdev_work_orders_uri',

    // IF fieldable == FALSE, we can't attach fields.
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
      'worker_bundle' => array(
        'label' => 'Wallet bundle',
        'admin' => array(
          'path' => 'admin/structure/ccdev_work_orders/manage',
          'access arguments' => array('administer ccWorker entities'),
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

function worker_permissions(){
  $permissions = array(
    'administer ccdev_work_orders entities' => array(
      'title' => t('Administer ccdev_work_orders entities'),
    ),
    'view any ccdev_work_orders entity' => array(
      'title' => t('View any Entity Example Basic entity'),
    ),
    'edit any ccdev_work_orders entity' => array(
      'title' => t('Edit any Entity Example Basic entity'),
    ),
    'create ccdev_work_orders entities' => array(
      'title' => t('Create Entity Example Basic Entities'),
    ),
  );
  return $permissions;
}

function worker_menu(){
$items['ccMod/ccWorker'] = array(
    'title' => 'Workers',
    'page callback' => 'ccWorker_info_page',
    'access arguments' => array('view any ccdev_work_orders entity'),
  );

  // This provides a place for Field API to hang its own
  // interface and has to be the same as what was defined
  // in basic_entity_info() above.
  $items['admin/structure/ccdev_work_orders/manage'] = array(
    'title' => 'Administer ccdev_work_orders entity type',
    'page callback' => 'ccdev_work_orders_list_entities',
    'access arguments' => array('administer ccdev_work_orders entities'),
  );

  // Add example entities.
  $items['admin/structure/ccdev_work_orders/manage/add'] = array(
    'title' => 'add wallet(disabled)',
    'page callback' => 'ccdev_work_orders_add',
    'access arguments' => array('create ccdev_work_orders entities'),
    'type' => MENU_LOCAL_ACTION,
  );

  // List of all ccdev_work_orders entities.
  $items['admin/structure/ccdev_work_orders/manage/list'] = array(
    'title' => 'List',
    'type' => MENU_DEFAULT_LOCAL_TASK,
  );

  // The page to view our entities - needs to follow what
  // is defined in basic_uri and will use load_basic to retrieve
  // the necessary entity info.
  $items['ccMod/ccWorker/basic/%ccdev_work_orders'] = array(
    'title callback' => 'ccdev_work_orders_title',
    'title arguments' => array(3),
    'page callback' => 'ccdev_work_orders_view',
    'page arguments' => array(3),
    'access arguments' => array('view any ccdev_work_orders entity'),
  );

  // 'View' tab for an individual entity page.
  $items['ccMod/ccWorker/basic/%ccdev_work_orders/view'] = array(
    'title' => 'View',
    'type' => MENU_DEFAULT_LOCAL_TASK,
    'weight' => -10,
  );

  // 'Edit' tab for an individual entity page.
  $items['ccMod/ccWorker/basic/%ccdev_work_orders/edit'] = array(
    'title' => 'Edit',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ccdev_work_orders_form', 3),
    'access arguments' => array('edit any ccdev_work_orders entity'),
    'type' => MENU_LOCAL_TASK,
  );

  // Add example entities.
  $items['ccMod/ccWorker/basic/add'] = array(
    'title' => 'Add Wallet(disabled)',
    'page callback' => 'ccdev_work_orders_add',
    'access arguments' => array('create ccdev_work_orders entities'),
  );

  return $items;
}
