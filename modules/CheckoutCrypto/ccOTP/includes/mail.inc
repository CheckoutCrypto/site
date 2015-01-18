<?php

function ccOTP_mail_send($args) {
  $module = 'ccOTP';
  $key = 'ccotp_url';

  $to = $args['mail'];
  $from = 'info@coingateway.net';

  if(isset($args['otp_type']) AND $args['otp_type'] == 'auth_method') {
      $params['otp_url'] = $args['otp_url'];
      $params['subject_tag'] = $args['subject_tag'];
      $params['coin_code'] = '';
      $params['coin_amount'] = '';
  } else {
      $params['coin_code'] = $args['coin_code'];
      $params['coin_name'] = $args['coin_name'];
      $params['coin_amount'] = $args['coin_amount'];
      $params['coin_address'] = $args['coin_address'];
      $params['otp_url'] = $args['otp_url'];
      $params['subject_tag'] = $args['subject_tag'];
	  if($args['otp_type'] == 'send_funds'){
  			$params['action'] = $args['otp_type'];
			$params['mail_recip_name'] = $args['mail_recip_name'];
			$params['mail_msg'] = $args['mail_msg'];
	  }
  }

  //footer
  $params['footer'] = 'If you did not request this please change your password immediately as your account may have been compromised. For further assistance contact';
  $params['footer_link'] = 'mailto:support@checkoutcrypto.com';
  $params['footer_link_text'] = 'support@checkoutcrypto.com';

  $language = language_default();

  $send = TRUE;

  $result = drupal_mail($module, $key, $to, $language, $params, $from, $send);
  return $result;
  if ($result['result'] == TRUE) {
      global $user;
      drupal_set_message(t('A verification email has been sent to %email', array('%email' => $user->mail)));
  } else {
      drupal_set_message(t('An exception has occurred and the request could not be made. Please contact support for assistance.'), 'error');
  }
}


function ccOTP_mail_alter(&$message) {
    if($message['key'] == 'ccotp_url') {
        $params = $message['params'];
		  $headers = array(
		    'MIME-Version' => '1.0',
		    'Content-Type' => 'text/html; charset=UTF-8; format=flowed',
		    'Content-Transfer-Encoding' => '8Bit',
		    'X-Mailer' => 'Drupal'
		  );
		  foreach ($headers as $key => $value) {
		    $message['headers'][$key] = $value;
		  }
        $subject_tag = $params['subject_tag'];
        $subject = 'New '.$subject_tag.' request pending confirmation';
        $message['subject'] = $subject;
        $message['body'][] = theme('ccOTP_mail_template', array('args' => $params));
    }
}
