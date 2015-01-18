<?php


/**
 * Implementation of hook_preprocess().
 */
function popup_theme(&$variables, $hook){
  $settings = array(
    'CToolsModal' => array(
      'loadingText' => t('Loading...'),
      'closeText' => t('Close'),
      'modalSize' => array(
        'type' => 'fixed',
        'height' => 450,
        'width' => 600, 
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

function popup_permissions(){
  $permissions = array(
    'administer ccdev_popup entities' => array(
      'title' => t('Administer popup entities'),
    ),
    'view any ccdev_popup entity' => array(
      'title' => t('View any popup entity'),
    ),
    'edit any ccdev_popup entity' => array(
      'title' => t('Edit any popup entity'),
    ),
    'create ccdev_popup entities' => array(
      'title' => t('Create popup Entities'),
    ),
  );
  return $permissions;
}

function popup_menu(){
$items['Popup'] = array(
    'title' => 'Popup',
    'page callback' => 'cgPopup_info_page',
    'access arguments' => array('view any ccdev_popup entity'),
  );
  $items['Popup/any'] = array(
    'page callback' => 'my_popup_form_callback',
    'access callback' => TRUE,
    'type' => MENU_CALLBACK,
  );
  return $items;
}
