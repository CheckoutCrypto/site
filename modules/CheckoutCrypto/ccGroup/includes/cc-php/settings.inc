<?php


/**
 * Checkoutcrypto permissions
 */
function group_permissions(){
  $permissions = array(
    'administer ccdev_groups entities' => array(
      'title' => t('Administer ccdev_groups entities'),
    ),
    'user ccdev_groups entities' => array(
      'title' => t('view any ccdev_groups entities'),
    ),
    'view any ccdev_groups entity' => array(
      'title' => t('View any ccGroup Basic entity'),
    ),
    'edit any ccdev_groups entity' => array(
      'title' => t('Edit any ccGroup Basic entity'),
    ),
    'create ccdev_groups entities' => array(
      'title' => t('Create ccGroup Basic Entities'),
    ),
  );
  return $permissions;
}

/**
 * Checkout crypto settings form.
 */
function group_info(){
 $info['ccdev_groups'] = array(
    // A human readable label to identify our entity.
    'label' => t('checkout crypto Groups Entity'),

    // The controller for our Entity, extending the Drupal core controller.
    'controller class' => 'ccGroupBasicController',

    // The table for this entity defined in hook_schema()
    'base table' => 'ccdev_groups',

    // Returns the uri elements of an entity.
    'uri callback' => 'ccdev_groups_uri',

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

    // FALSE disables caching. Caching functionality is handled by Drupal core.
    'static cache' => TRUE,

    // Bundles are alternative groups of fields or configuration
    // associated with a base entity type.
    'bundles' => array(
      'ccdev_groups_bundle' => array(
        'label' => 'Groups bundle',
        // 'admin' key is used by the Field UI to provide field and
        // display UI pages.
        'admin' => array(
          'path' => 'admin/structure/ccdev_groups/manage',
          'access arguments' => array('administer ccdev_groups entities'),
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
 * Checkoutcrypto Menu
 */
function group_menu(){
     module_load_include('inc', 'ccGroup', 'includes/cc-php/entity');
     module_load_include('inc', 'ccGroup', 'includes/cc-php/entity_load');
 $items['ccMods/ccGroup'] = array(
    'title' => 'Groups',
    'page callback' => 'ccGroup_info_page',
    'access arguments' => array('view any ccdev_groups entity'),
  );

  $items['admin/structure/ccdev_groups/manage'] = array(
    'title' => 'Administer Groups',
    'page callback' => 'ccGroup_admin_page',
    'access arguments' => array('administer ccdev_groups entities'),
  );

  $items['admin/structure/ccdev_groups/manage/add'] = array(
    'title' => 'Add a Groups Entity',
    'page callback' => 'ccdev_groups_add',
    'access arguments' => array('create ccdev_groups entities'),
    'type' => MENU_LOCAL_ACTION,
  );

  $items['admin/structure/ccdev_groups/manage/list'] = array(
    'title' => 'List',
    'type' => MENU_DEFAULT_LOCAL_TASK,
  );

  $items['ccMods/ccGroup/basic/%ccdev_groups'] = array(
    'title callback' => 'ccdev_groups_title',
    'title arguments' => array(3),
    'page callback' => 'ccdev_groups_view',
    'page arguments' => array(3),
    'access arguments' => array('view any ccdev_groups entity'),
  );

  $items['ccMods/ccGroup/basic/%ccdev_groups/view'] = array(
    'title' => 'View',
    'type' => MENU_DEFAULT_LOCAL_TASK,
    'weight' => -10,
  );

  $items['ccMods/ccGroup/basic/%ccdev_groups/edit'] = array(
    'title' => 'Edit',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ccdev_groups_form', 3),
    'access arguments' => array('edit any ccdev_groups entity'),
    'type' => MENU_LOCAL_TASK,
  );

  $items['ccMod/ccGroup/any/%ctools_js'] = array(
    'page callback' => 'ccGroup_manage_callback',
    'page arguments' => array(3,4),
    'access callback' => TRUE,
    'type' => MENU_CALLBACK,
  );

  $items['ccMods/ccGroup/basic/add'] = array(
    'title' => 'Add new Group',
    'page callback' => 'ccdev_groups_add',
    'access arguments' => array('create ccdev_groups entities'),
  );

$items['admin/config/people/ccGroup'] = array(
  'title' => 'ccGroup',
  'description' => 'Configuration for the Groups module.',
  'page callback' => 'drupal_get_form',
  'page arguments' => array('ccGroup_settings_form'),
  'access arguments' => array('administer users'),
  'type' => MENU_NORMAL_ITEM,
);

  return $items;
}
