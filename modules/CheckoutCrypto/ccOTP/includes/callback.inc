<?php



function ccOTP_generate_callback($formArgs) {
	module_load_include('inc', 'ccOTP', 'includes/mail');
	module_load_include('inc', 'ccOTP', 'includes/lib');
    global $user;
	$form_state = array();
    $dbArgs = array();

    $args = array('action' => $formArgs['callback_action']);
    $otpArgs = ccOTP_otp_generate($args);

	$dbArgs['uid'] = $user->uid;
	$dbArgs['coin_name'] = $formArgs['coin_name'];
	$dbArgs['coin_code'] = $formArgs['coin_code'];
	$dbArgs['coin_amount'] = $formArgs['coin_amount'];
	$dbArgs['coin_address'] = $formArgs['coin_address'];
	$dbArgs['callback_action'] = $formArgs['callback_action'];

    $args = array('action' => $formArgs['callback_action']);
    $otpArgs = ccOTP_otp_generate($args);
    $dbArgs['secret'] = $otpArgs['secret'];
    $dbArgs['data'] = $otpArgs['data'];


		$inserted = ccOTP_otp_insert($dbArgs);
        if(isset($inserted)) {
       		 $url = ccOTP_otp_get_auth_url($otpArgs['signature'], $inserted);
            if($url) {
            //successfully inserted, send mail and inform user
            $form_state['otp_generated'] = TRUE;
            $form_state['otp_url'] = $url;
            $form_state['rebuild'] = TRUE;

            $args = array();
            $args['mail'] = $user->mail;
            $args['otp_url'] = $url;
            $args['coin_name'] = $formArgs['coin_name'];
            $args['coin_code'] = $formArgs['coin_code'];
            $args['coin_amount'] = $formArgs['coin_amount'];
            $args['coin_address'] = $formArgs['coin_address'];
            $args['subject_tag'] = $formArgs['callback_action'];

            return ccOTP_mail_send($args);
        } else {
            return FALSE; //either insert failed or too many confirmation emails where sent
        }
    }

    return FALSE;
}
