<?php

function service_info(){
$info['ccdev_service'] = array(
    // A human readable label to identify our entity.
    'label' => t('ServiceCharge'),

    // The table for this entity defined in hook_schema()
    'base table' => 'payment_cc',
  );

  return $info;
}

function service_theme(){
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

function service_menu(){
 $items['ccService'] = array(
    'title' => 'Packages',
    'page callback' => 'ccService_info_page',
    'access arguments' => array('view any ccdev_service entity'),
  );
  $items['ccService/complete'] = array(
    'title' => 'Complete',
    'page callback' => 'ccService_complete_page',
    'access arguments' => array('access content'),
	   'type' => MENU_CALLBACK,
  );
  $items['ccService/fund/complete'] = array(
    'title' => 'Complete',
    'page callback' => 'ccService_fund_complete',
    'access arguments' => array('access content'),
	   'type' => MENU_CALLBACK,
  );

  $items['ccService/service/charge'] = array(
    'page callback' => 'ccService_callback',
    'access arguments' => array('access content'),
    'type' => MENU_CALLBACK,
  );

  $items['ccService/%ctools_js/%'] = array(
    'page callback' => 'ccService_funds_callback',
    'page arguments' => array(1,2),
    'access callback' => TRUE,
    'type' => MENU_CALLBACK,
  );
  return $items; 
}

function service_permissions(){
  $permissions = array(
    'administer ccdev_service entities' => array(
      'title' => t('Administer ccdev_service entities'),
    ),
    'view any ccdev_service entity' => array(
      'title' => t('View any ccService entity'),
    ),
    'edit any ccdev_service entity' => array(
      'title' => t('Edit any ccService entity'),
    ),
    'create ccdev_service entities' => array(
      'title' => t('Create any ccService entity'),
    ),
  );
  return $permissions;
}
