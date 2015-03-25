<?php

function coin_info(){
	$info['ccdev_coin'] = array(
    'label' => t('Coins'),

    'controller class' => 'ccCoinBasicController',

    'base table' => 'ccdev_coin',

    'uri callback' => 'ccdev_coin_uri',

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
      'coin_bundle' => array(
        'label' => 'coin bundle',
        'admin' => array(
          'path' => 'admin/structure/ccdev_coin/manage',
          'access arguments' => array('administer ccCoin entities'),
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
	$info['ccdev_fiat'] = array(
    'label' => t('Fiat'),

    'controller class' => 'ccCoinBasicController',

    'base table' => 'ccdev_fiat',

    'uri callback' => 'ccdev_fiat_uri',

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
      'fiat_bundle' => array(
        'label' => 'fiat bundle',
        'admin' => array(
          'path' => 'admin/structure/ccdev_fiat/manage',
          'access arguments' => array('administer ccCoin entities'),
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

function coin_menu(){
$items['Coin'] = array(
    'title' => 'Coins',
    'page callback' => 'ccCoin_info_page',
    'access arguments' => array('view any ccdev_coin entity'),
	'menu_name' => 'main-menu',
  );

  $items['admin/structure/ccdev_coin/manage'] = array(
    'title' => 'Administer ccdev_coin entity type',
    'page callback' => 'ccdev_manage_coin',
    'access arguments' => array('administer ccdev_coin entities'),
  );

  // Add example entities.
  $items['admin/structure/ccdev_coin/manage/add'] = array(
    'title' => 'Add Coin',
    'page callback' => 'ccdev_coin_add',
    'access arguments' => array('create ccdev_coin entities'),
    'type' => MENU_LOCAL_ACTION,
  );

  // List of all ccdev_coin entities.
  $items['admin/structure/ccdev_coin/manage/list'] = array(
    'title' => 'List',
    'type' => MENU_DEFAULT_LOCAL_TASK,
  );

  $items['Coin/basic/%ccdev_coin'] = array(
    'title callback' => 'ccdev_coin_title',
    'title arguments' => array(2),
    'page callback' => 'ccdev_coin_view',
    'page arguments' => array(2),
    'access arguments' => array('view any ccdev_coin entity'),
  );

  // 'View' tab for an individual entity page.
  $items['Coin/basic/%ccdev_coin/view'] = array(
    'title' => 'View',
    'type' => MENU_DEFAULT_LOCAL_TASK,
    'weight' => -10,
  );

  // 'Edit' tab for an individual entity page.
  $items['Coin/basic/%ccdev_coin/edit'] = array(
    'title' => 'Edit',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ccCoin_editcoin_form', 3),
    'access arguments' => array('edit any ccdev_coin entity'),
    'type' => MENU_DEFAULT_LOCAL_TASK,
  );
  $items['Coin/addcoin/%ctools_js'] = array(
    'page callback' => 'ccCoin_addcoin_callback',
    'page arguments' => array(2,3),
    'access callback' => TRUE,
    'type' => MENU_CALLBACK,
  );
  $items['Coin/editcoin/%ctools_js'] = array(
    'page callback' => 'ccCoin_editcoin_callback',
    'page arguments' => array(2,3),
    'access callback' => TRUE,
    'type' => MENU_CALLBACK,
  );
	return $items;
}

function coin_theme(){
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
	return $settings;
}

function coin_permissions(){
  $permissions = array(
    'administer ccdev_coin entities' => array(
      'title' => t('Administer ccdev_coin entities'),
    ),
    'view any ccdev_coin entity' => array(
      'title' => t('View any Entity Example Basic entity'),
    ),
    'edit any ccdev_coin entity' => array(
      'title' => t('Edit any Entity Example Basic entity'),
    ),
    'create ccdev_coin entities' => array(
      'title' => t('Create Entity Example Basic Entities'),
    ),
  );
	return $permissions;
}
