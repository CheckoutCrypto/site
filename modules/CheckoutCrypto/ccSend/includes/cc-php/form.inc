<?php


function ccsend_funds($form, $form_state){
module_load_include('inc', 'ccSend', 'includes/cc-php/lib');
module_load_include('inc', 'ccAccount', 'includes/cc-php/lib');
global $user;

$userBilling = getBillingSummary($user->uid);
$grpData = getGroupInfo($userBilling['grp_id']);


if( $userBilling['total_email_trans'] <= $grpData['grp_max_emails']){

  $form['recip_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Recipient Name'),
      '#attributes' => array('title' => 'Valid characters are a-z,0-9', 'placeholder' => 'Name', 'type' => 'name', 'pattern' => '[a-zA-Z0-9]+', 'required' => 'required' ), 
    '#required' => TRUE,
   // '#default_value' => $entity->recip_name,
  );
///  'step' => '0.01',
   // '#default_value' => $entity->recip_email,
  $form['recip_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Recipient Email'),
    '#required' => TRUE,
      '#attributes' => array('title' => 'Valid email example something@something.com', 'placeholder' => 'Email', 'type' => 'email', 'pattern' => '[^@]+@[^@]+\.[a-zA-Z]{2,6}', 'required' => 'required' ), 
  );
  $form['recip_msg'] = array(
    '#type' => 'textarea',
    '#title' => t('Message'),
    '#required' => TRUE,
      '#attributes' => array('title' => 'Valid characters are a-z,0-9, capitals, punctuation', 'placeholder' => 'Message', 'pattern' => '/^[A-Z0-9,.\'[]{}?:;-_=+!@#%^&()]+$/i','required' => 'required'),
  );
	$selCoin = array();
	$coins = getAvailableCoins();
	foreach($coins as $cn){
		$selCoin[$cn['coin_code']] = $cn['coin_code'];
	}
  $form['coin_code'] = array(
  '#type' => 'select',
  '#title' => 'Coin',
  '#options' => $selCoin,
 '#attributes' =>  array('required' => 'required' ), 
  '#required' => TRUE,
  );

  $form['coin_amt'] = array(
    '#type' => 'textfield',
    '#title' => t('Amount'),
      '#attributes' => array('title' => 'Valid characters are 0-9', 'placeholder' => 'Withdraw amount', 'pattern' => '[0-9]+([\.|,][0-9]+)?', 'step' => '0.01', 'required' => 'required'),
    '#required' => TRUE,
   // '#default_value' => $entity->coin_amt,
  );

  $form['basic_entity'] = array(
    '#type' => 'value',
    //'#value' => $entity,
  );

 // field_attach_form('ccdev_send', $entity, $form, $form_state);

    $form['submit'] = array(
      '#type' => 'submit',
       '#value' => t('Enabled'),
	  '#attributes' => array('class' => array('btn', 'btn-success','enabled'),'style' => "float:right; padding: 5px 10px;"),
	  '#theme' => "submit",
	  '#prefix' => "<div class='submit-button-custom'>",
	  '#suffix' => "</div>",

    ); 
  $form['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
    '#submit' => array('ccdev_send_edit_delete'),
    '#weight' => 200,
  ); 
}else{

	$form['error'] = array(
    '#markup' => '<p>You have hit the maximum email transfers, please contact the administraitor to upgrade your package</p>',
	);


}
  return $form;
}


/**
 * Form function to create a SendFunds transactions
 */
function ccdev_send_form($form, &$form_state, $entity) {
module_load_include('inc', 'ccSend', 'includes/cc-php/lib');
  $form['recip_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Recipient Name'),
    '#required' => TRUE,
    '#default_value' => $entity->recip_name,
  );
  $form['recip_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Recipient Email'),
    '#required' => TRUE,
    '#default_value' => $entity->recip_email,
  );
  $form['recip_msg'] = array(
    '#type' => 'textarea',
    '#title' => t('Message'),
    '#required' => TRUE,
    '#default_value' => $entity->recip_msg,
  );
	$selCoin = array();
	$coins = getAvailableCoins();
	foreach($coins as $cn){
		$selCoin[$cn['coin_code']] = $cn['coin_code'];
	}
  $form['coin_code'] = array(
  '#type' => 'select',
  '#title' => 'Coin',
  '#options' => $selCoin,
  '#required' => TRUE,
  );

  $form['coin_amt'] = array(
    '#type' => 'textfield',
    '#title' => t('Amount'),
    '#required' => TRUE,
    '#default_value' => $entity->coin_amt,
  );

  $form['basic_entity'] = array(
    '#type' => 'value',
    '#value' => $entity,
  );

  field_attach_form('ccdev_send', $entity, $form, $form_state);

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 100,
  );
  $form['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
    '#submit' => array('ccdev_send_edit_delete'),
    '#weight' => 200,
  ); 

  return $form;
}


function send_OTP_form($form, $form_state) {
  $form['otp_message'] = array(
'#markup' => t('<div>CheckoutCrypto Email Confirmation still pending.  Check your email or contact us if you cannot get email access: </div>'));

    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Done'),
	'#attributes' => array('style' => "float:right; padding: 5px 10px;"),
	'#theme' => "submit",
	'#prefix' => "<div class='submit-button-custom'>",
	'#suffix' => "</div>",
	  '#ajax' => array(
	  'callback' => 'send_OTP_form_submit',),
    ); 

	return $form;
}
