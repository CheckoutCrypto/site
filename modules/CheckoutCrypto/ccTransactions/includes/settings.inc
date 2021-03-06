<?php

function trans_permissions(){
  $permissions = array(
    'administer ccdev_transactions entities' => array(
      'title' => t('Administer ccdev_transactions entities'),
    ),
    'view any ccdev_transactions entity' => array(
      'title' => t('View any Transaction entity'),
    ),
    'edit any ccdev_transactions entity' => array(
      'title' => t('Edit any Transaction entity'),
    ),
    'create ccdev_transactions entities' => array(
      'title' => t('Create Transaction entity'),
    ),
  );
  return $permissions;
}

function trans_menu(){
	module_load_include('inc', 'ccTrans', 'includes/cc-php/entity');
  $items['Account/Transactions'] = array(
    'title' => 'Transactions',
    'page callback' => 'ccTrans_info_page',
    'access arguments' => array('view any ccdev_transactions entity'),
	'menu_name' => 'main-menu',
	'weight' => 5,
  );

  // This provides a place for Field API to hang its own
  // interface and has to be the same as what was defined
  // in basic_entity_info() above.
  $items['admin/structure/ccdev_transactions/manage'] = array(
    'title' => 'Administer Transactions',
    'page callback' => 'ccdev_transactions_list_entities',
    'access arguments' => array('administer ccdev_transactions entities'),
  );

  // Add example entities.
  $items['admin/structure/ccdev_transactions/manage/add'] = array(
    'title' => 'add transaction(disabled)',
    'page callback' => 'ccdev_transactions_add',
    'access arguments' => array('create ccdev_transactions entities'),
    'type' => MENU_LOCAL_ACTION,
  );

  // List of all ccdev_transactions entities.
  $items['admin/structure/ccdev_transactions/manage/list'] = array(
    'title' => 'List',
    'type' => MENU_DEFAULT_LOCAL_TASK,
  );

  // The page to view our entities - needs to follow what
  // is defined in basic_uri and will use load_basic to retrieve
  // the necessary entity info.
  $items['Transactions/basic/%ccdev_transactions'] = array(
    'title callback' => 'ccdev_transactions_title',
    'title arguments' => array(2),
    'page callback' => 'ccdev_transactions_view',
    'page arguments' => array(2),
    'access arguments' => array('view any ccdev_transactions entity'),
  );

  // 'View' tab for an individual entity page.
  $items['ccMod/ccTrans/basic/%ccdev_transactions/view'] = array(
    'title' => 'View',
    'type' => MENU_DEFAULT_LOCAL_TASK,
    'weight' => -10,
  );

  // 'Edit' tab for an individual entity page.
  $items['Transactions/basic/%ccdev_transactions/edit'] = array(
    'title' => 'Edit',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ccdev_transactions_form', 2),
    'access arguments' => array('edit any ccdev_transactions entity'),
    'type' => MENU_LOCAL_TASK,
  );

  return $items;
}

function trans_info(){
 $info['ccdev_transactions'] = array(
    // A human readable label to identify our entity.
    'label' => t('checkout crypto Transactions'),

    // The controller for our Entity, extending the Drupal core controller.
    'controller class' => 'ccTransBasicController',

    // The table for this entity defined in hook_schema()
    'base table' => 'ccdev_transactions',

    // Returns the uri elements of an entity.
    'uri callback' => 'ccdev_transactions_uri',

    // IF fieldable == FALSE, we can't attach fields.
    'fieldable' => TRUE,

    // entity_keys tells the controller what database fields are used for key
    // functions. It is not required if we don't have bundles or revisions.
    // Here we do not support a revision, so that entity key is omitted.
    'entity keys' => array(
      // The 'id' (basic_id here) is the unique id.
      'id' => 'basic_id' ,
      // Bundle will be determined by the 'bundle_type' field.
      'bundle' => 'bundle_type',
    ),
    'bundle keys' => array(
      'bundle' => 'bundle_type',
    ),

    // FALSE disables caching. Caching functionality is handled by Drupal core.
    'static cache' => TRUE,

    // Bundles are alternative groups of fields or configuration
    // associated with a base entity type.
    'bundles' => array(
      'transactions_bundle' => array(
        'label' => 'Transaction Bundle',
        // 'admin' key is used by the Field UI to provide field and
        // display UI pages.
        'admin' => array(
          'path' => 'admin/structure/ccdev_transactions/manage',
          'access arguments' => array('administer ccTrans entities'),
        ),
      ),
    ),
    // View modes allow entities to be displayed differently based on context.
    // As a demonstration we'll support "Tweaky", but we could have and support
    // multiple display modes.
    'view modes' => array(
      'tweaky' => array(
        'label' => t('Tweaky'),
        'custom settings' => FALSE,
      ),
    ),
  );

  return $info;
}
