<?php

function send_info(){
$info['ccdev_send'] = array(
    // A human readable label to identify our entity.
    'label' => t('SendByEmail'),

    // The controller for our Entity, extending the Drupal core controller.
    'controller class' => 'ccSendBasicController',

    // The table for this entity defined in hook_schema()
    'base table' => 'ccdev_send',

    // Returns the uri elements of an entity.
    'uri callback' => 'ccdev_send_uri',

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
      'Send_bundle' => array(
        'label' => 'Send bundle',
        // 'admin' key is used by the Field UI to provide field and
        // display UI pages.
        'admin' => array(
          'path' => 'admin/structure/ccdev_send/manage',
          'access arguments' => array('administer ccSend entities'),
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

function send_theme(){
  $settings = array(
    'CToolsModal' => array(
      'loadingText' => t('Loading...'),
      'closeText' => t('Close'),
      'modalSize' => array(
        'type' => 'fixed',
        'height' => 700,
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

function send_menu(){
module_load_include('inc', 'ccSend', 'includes/cc-php/form_sub');
 $items['ccSend'] = array(
    'title' => 'Send',
    'page callback' => 'ccSend_info_page',
    'access arguments' => array('view any ccdev_send entity'),
  );
  $items['ccSend/complete'] = array(
    'title' => 'Complete',
    'page callback' => 'ccSend_complete_page',
    'access arguments' => array('access content'),
	   'type' => MENU_CALLBACK,
  );
  $items['ccSend/auth'] = array(
    'title' => 'Validate OTP',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ccOTP_validate_form'),
    'access arguments' => array('access content'),
  	'type' => MENU_CALLBACK,
  );

  // This provides a place for Field API to hang its own
  // interface and has to be the same as what was defined
  // in basic_entity_info() above.
  $items['admin/structure/ccdev_send/manage'] = array(
    'title' => 'Administer ccdev_send entity type',
    'page callback' => 'ccdev_send_list_entities',
    'access arguments' => array('administer ccdev_send entities'),
  );

  // Add example entities.
  $items['admin/structure/ccdev_send/manage/add'] = array(
    'title' => 'Add Send',
    'page callback' => 'ccdev_send_add',
    'access arguments' => array('create ccdev_send entities'),
    'type' => MENU_LOCAL_ACTION,
  );

  // List of all ccdev_send entities.
  $items['admin/structure/ccdev_send/manage/list'] = array(
    'title' => 'List',
    'type' => MENU_DEFAULT_LOCAL_TASK,
  );

  // The page to view our entities - needs to follow what
  // is defined in basic_uri and will use load_basic to retrieve
  // the necessary entity info.
  $items['ccSend/basic/%ccdev_send'] = array(
    'title callback' => 'ccdev_send_title',
    'title arguments' => array(3),
    'page callback' => 'ccdev_send_view',
    'page arguments' => array(3),
    'access arguments' => array('view any ccdev_send entity'),
  );

  // 'View' tab for an individual entity page.
  $items['ccSend/basic/%ccdev_send/view'] = array(
    'title' => 'View',
    'type' => MENU_DEFAULT_LOCAL_TASK,
    'weight' => -10,
  );

  // 'Edit' tab for an individual entity page.
  $items['ccSend/basic/%ccdev_send/edit'] = array(
    'title' => 'Edit',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ccdev_send_form', 3),
    'access arguments' => array('edit any ccdev_send entity'),
    'type' => MENU_LOCAL_TASK,
  );

  // Add example entities.
  $items['ccSend/basic/add'] = array(
    'title' => 'Add Send',
    'page callback' => 'ccdev_send_add',
    'access arguments' => array('create ccdev_send entities'),
  );
  $items['ccSend/email/%ctools_js/%'] = array(
    'page callback' => 'ccSend_funds_callback',
    'page arguments' => array(3,4),
    'access callback' => TRUE,
    'type' => MENU_CALLBACK,
  );
  return $items;
}

function send_permissions(){
  $permissions = array(
    'administer ccdev_send entities' => array(
      'title' => t('Administer ccdev_send entities'),
    ),
    'view any ccdev_send entity' => array(
      'title' => t('View any ccSend entity'),
    ),
    'edit any ccdev_send entity' => array(
      'title' => t('Edit any ccSend entity'),
    ),
    'create ccdev_send entities' => array(
      'title' => t('Create any ccSend entity'),
    ),
  );
  return $permissions;
}
