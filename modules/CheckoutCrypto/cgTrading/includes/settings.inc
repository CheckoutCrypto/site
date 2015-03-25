<?php

function trading_info(){
$info['ccdev_trades'] = array(
    // A human readable label to identify our entity.
    'label' => t('Trading'),

    // The controller for our Entity, extending the Drupal core controller.
    'controller class' => 'cgTradingBasicController',

    // The table for this entity defined in hook_schema()
    'base table' => 'ccdev_trades',

    // Returns the uri elements of an entity.
    'uri callback' => 'ccdev_trades_uri',

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
        'label' => 'trade bundle',
        'admin' => array(
          'path' => 'admin/structure/ccdev_trades/manage',
          'access arguments' => array('administer ccTrading entities'),
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
 * Implementation of hook_preprocess().
 */
function trading_theme(&$variables, $hook){
  $settings = array(
    'CToolsModal' => array(
      'loadingText' => t('Loading...'),
      'closeText' => t('Close'),
      'modalSize' => array(
        'type' => 'fixed',
        'height' => 450,
        'width' => 540,
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

function trading_permissions(){
  $permissions = array(
    'administer ccdev_trades entities' => array(
      'title' => t('Administer trading entities'),
    ),
    'view any ccdev_trades entity' => array(
      'title' => t('View any trading entity'),
    ),
    'edit any ccdev_trades entity' => array(
      'title' => t('Edit any trading entity'),
    ),
    'create ccdev_trades entities' => array(
      'title' => t('Create trading Entities'),
    ),
  );
  return $permissions;
}

function trading_menu(){
$items['Trading'] = array(
    'title' => 'Trading',
    'page callback' => 'cgTrading_info_page',
    'access arguments' => array('view any ccdev_trades entity'),
    'menu_name' => 'main-menu',
 	'weight' => 3,
  );
  $items['Trading/transactions'] = array(
    'title' => 'Transactions',
    'page callback' => 'cgTrading_trans_page',
    'access arguments' => array('view any ccdev_trades entity'),
    'menu_name' => 'main-menu', // You'll need to have a menu named
  );
  $items['Trading/complete/%/%'] = array(
    'title' => 'Trade Completed',
	'page arguments' => array(2, 3),
    'page callback' => 'cgTrading_complete_page',
    'access arguments' => array('view any ccdev_trades entity'),
  );

  $items['Trading/details'] = array(
    'title' => 'TradingProcessor',
    'page callback' => 'trade_process',
    'access arguments' => array('view any ccdev_trades entity'),
 	  'type' => MENU_DEFAULT_LOCAL_TASK,
  );

  // This provides a place for Field API to hang its own
  // interface and has to be the same as what was defined
  // in basic_entity_info() above.
  $items['admin/structure/ccdev_trades/manage'] = array(
    'title' => 'Administer ccdev_trades entity type',
    'page callback' => 'ccdev_trades_list_entities',
    'access arguments' => array('administer ccdev_trades entities'),
  );

  // List of all ccdev_work_orders entities.
  $items['admin/structure/ccdev_trades/manage/list'] = array(
    'title' => 'List',
    'type' => MENU_DEFAULT_LOCAL_TASK,
  );

  // The page to view our entities - needs to follow what
  // is defined in basic_uri and will use load_basic to retrieve
  // the necessary entity info. e.g. view specific trade
  $items['Trading/basic/%ccdev_trades'] = array(
    'title callback' => 'ccdev_trades_title',
    'title arguments' => array(2),
    'page callback' => 'ccdev_trades_view',
    'page arguments' => array(2),
    'access arguments' => array('view any ccdev_trades entity'),
  );

  // Add example entities. // default trade callback
  $items['cgTrading/basic/add'] = array(
    'title' => 'Add Trade(disabled)',
    'page callback' => 'ccdev_trades_add',
    'access arguments' => array('create ccdev_trades entities'),
  );

  return $items;
}
