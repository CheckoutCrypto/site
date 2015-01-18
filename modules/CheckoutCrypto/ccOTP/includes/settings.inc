<?php

function otp_theme(){
    $path = drupal_get_path('module', 'ccOTP') . '/templates';
    return array(
        'ccOTP_mail_template' => array(
                'template' => 'otp',
            'arguments' => array('message' => ''), //the '' is a default value
            'path' => $path,
        ),
    );
}

function otp_menu(){
	module_load_include('inc', 'ccOTP', 'includes/forms_sub');
	module_load_include('inc', 'ccOTP', 'includes/callback');
 $items['ccOTP/generate'] = array(
    'title' => 'Generate OTP',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ccOTP_generate_form'),
    'access arguments' => array('access content'),
  );

  $items['ccOTP/auth'] = array(
    'title' => 'Validate OTP',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ccOTP_validate_form'),
    'access arguments' => array('access content'),
  	'type' => MENU_DEFAULT_LOCAL_TASK,
  );

  $items['ccOTP/sf'] = array(
    'title' => 'Validate SendFund OTP',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ccOTP_validate_form'),
    'access arguments' => array('access content'),
 	  'type' => MENU_DEFAULT_LOCAL_TASK,
  );

  $items['ccOTP/enable/%ctools_js'] = array(
    'page callback' => 'otp_gauth_callback',
    'page arguments' => array(1),
    'access callback' => TRUE,
    'type' => MENU_CALLBACK,
  );
  return $items;
}

