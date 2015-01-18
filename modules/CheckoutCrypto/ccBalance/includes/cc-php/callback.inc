<?php

/**
 * Ajax menu callback.
 */
function ccBalance_withdraw_callback($ajax, $coincode = NULL) {
var_dump('test');
break;
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
 
    $form_state = array(
      'ajax' => TRUE,
      'title' => t('Withdraw Form'),
      'coincode' => $coincode,
    );

/// check if we have a pending OTP still awaiting confirmation
$sent = ccOTP_otp_checkExists();
if(isset($sent)) {
   // Use ctools to generate ajax instructions for the browser to create
    // a form in a modal popup.
    $output = ctools_modal_form_wrapper('OTP_form', $form_state);
}else{
    // Use ctools to generate ajax instructions for the browser to create
    // a form in a modal popup.
    $output = ctools_modal_form_wrapper('withdraw_form', $form_state);
 }
    // If the form has been submitted, there may be additional instructions
    // such as dismissing the modal popup.
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
 
    // Return the ajax instructions to the browser via ajax_render().
    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('withdraw_form');
  }
}

/**
 * Ajax menu callback.
 */
function ccBalance_autopay_callback($ajax, $coincode = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
 
    $form_state = array(
      'ajax' => TRUE,
      'title' => t('AutoPayment Form'),
      'coincode' => $coincode,
    );
/// check if we have a pending OTP still awaiting confirmation
$sent = ccOTP_otp_checkExists();
if(isset($sent)) {
   // Use ctools to generate ajax instructions for the browser to create
    // a form in a modal popup.
    $output = ctools_modal_form_wrapper('OTP_form', $form_state);
}else{
    // Use ctools to generate ajax instructions for the browser to create
    // a form in a modal popup.
    $output = ctools_modal_form_wrapper('autopay_form', $form_state);
 }
    // If the form has been submitted, there may be additional instructions
    // such as dismissing the modal popup.
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
 
    // Return the ajax instructions to the browser via ajax_render().
    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('autopay_form');
  }
}

