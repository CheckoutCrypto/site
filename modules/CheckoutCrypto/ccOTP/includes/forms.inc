<?php

//// the form displayed on the page, when a user clicks the authentication link in their email
function otp_validate_form($form, &$form_state){
	 module_load_include('inc', 'ccOTP', 'includes/forms_sub');
	module_load_include('inc', 'ccOTP', 'includes/lib');
    module_load_include('inc', 'ccBalance', 'includes/cc-php/lib');

     $args = array();
     $request = array();

    //Check if form was submitted and the request was a success
    if(!empty($form_state['otp_validated'])) {
        $action = ucfirst($form_state['otp_validated']['action']); //make first char uppercase
        drupal_set_message(t('%action action was submitted successfully.', array('%action' => $action)));
    }
	$idpos = 0;
    if(arg(2)) {

        $args['signature'] = arg(2);
		$idpos = strrpos(arg(3), "id") + 3;
		$siglen = strlen(arg(3));
		$args['basic_id'] = substr(arg(3), $idpos, $siglen);
		if(sanitizeOTP($args)){
        	$request = ccOTP_otp_validate($args);

		}
    }

    if(!empty($request) AND $request !== FALSE ) {
		    $action = $request['action'];
		    $amount = $request['coin_amount'];
		    $name = $request['coin_name'];
			$form['action'] = array(
		       '#type' => 'hidden',
		        '#value' => $request['action'],
		    );
			$form['basic_id'] = array(
		       '#type' => 'hidden',
		        '#value' => $request['basic_id'],
		    );
			$form['uid'] = array(
		       '#type' => 'hidden',
		        '#value' => $request['uid'],
		    );
			$form['coin_name'] = array(
		       '#type' => 'hidden',
		        '#value' => $request['coin_name'],
		    );
			$form['coin_code'] = array(
		       '#type' => 'hidden',
		        '#value' => $request['coin_code'],
		    );
			$form['coin_amount'] = array(
		       '#type' => 'hidden',
		        '#value' => $request['coin_amount'],
		    );
	   if(substr($action,0,12) == 'auth_change_') {

		        $auth_action = substr($action,12);
		        if($auth_action == 'twofa') {
		            $form['request_info'] = array('#markup' => '<p><h3>Authentication method change to: <br><br><strong>Two-factor</strong></h3></p><br>');
		        } elseif ($auth_action == 'email') {
		            $form['request_info'] = array('#markup' => '<p><h3>Authentication method change to: <br><br><strong>Email</strong></h3></p><br>');
		        
				}		
				$form['submit'] = array(
				   '#type' => 'submit',
				    '#value' => t('Confirm request'),
				);  
		}else if($action == "send_funds"){
		 	$balance = getBalance($request['uid'], $request['coin_code']);
			$calcTotal = calcTotal($request['coin_amount'], $request['coin_code'], $request['uid']);
				if(!empty($balance) AND $balance > $calcTotal){
				    $form['request_info'] = array('#markup' => '<p><h3>'.ucfirst($action).'</h3></p><p>Currency: '.$name.'</p>Amount: '.$amount.'</p><br>');
					$form['coin_address'] = array(
					   '#type' => 'textfield',
				  		'#title' => t('Withdraw Address'),
			  			'#required' => TRUE,
			  			'#attributes' => array('title' => 'Must be a valid address', 'placeholder' => 'Withdraw address', 'autofocus' => 'autofocus', 'pattern' => '^[A-Za-z0-9_.]+$', 'required' => 'required'),
			  			'#default_value' => '',
					);
				}else{  // balance is not enough to complete
					$form['request_info'] = array('#markup' => '<p>Their is not enough funds in this account to complete this transaction. Please contact the sender and try again.</p>');
				} 
		}else{ 
				    $form['request_info'] = array('#markup' => '<p><h3>'.ucfirst($action).'</h3></p><p>Currency: '.$name.'</p>Amount: '.$amount.'</p><br>');
				    /// shouldn't this auto confirm request?
			$form['coin_address'] = array(
		   	'#type' => 'hidden',
			'#value' => $request['coin_address'],
			);
		}
				$form['submit'] = array(
				   '#type' => 'submit',
				    '#value' => t('Confirm request'),
				);
    } else { //no such request
        $form['request_info'] = array('#markup' => '<p>Invalid request link</p>');
    } 


		
    return $form;
}

//// Modify the prexisting drupal profile with our 2factor/email authentication method
function otp_profile_mod(&$form){

module_load_include('inc','ccOTP','includes/lib');
global $user;
  $otpDetails = get_otp_type($user->uid);

  if(isset($otpDetails['pref_otp'])) {
    $pref_otp = $otpDetails['pref_otp'];
    $validated = $otpDetails['validated'];
  } else {
    $pref_otp = 'email';
  }

  //Load js for gauth callback form
  ctools_include('modal');
  ctools_modal_add_js();

  $otp_type = array('email' => 'Email', 'twofa' => 'Two factor');

  $form['account']['ccAccount_otp'] = array(
    '#type' => 'fieldset',
    '#title' => t('Set your preferred withdraw/autopayment validaton method'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['account']['ccAccount_otp']['ccAccount_otp_selections'] = array(
    '#type' => 'radios',
    '#title' => t('Set Your Authentication Preference'),
    '#default_value' => $pref_otp,
    '#options' => $otp_type,
 	'#required' => false,
  );

  if($pref_otp == 'twofa') {

      $form['account']['otp_types']=array(
        '#type'=>'fieldset',
        '#title'=>t('Two factor authentication methods'),
        '#prefix' => '<div id="otp_types">',
        '#suffix' => '</div>',
      );

      if($validated == 1) {
          $form['account']['otp_types']['gauth']=array(
            '#type'=>'fieldset',
            '#title'=>t('Google Authenticator'),
            '#prefix' => '<div id="otp_types">',
            '#suffix' => '</div>',
         );

          $form['account']['otp_types']['gauth']['gauth_link'] = array(
              '#markup' => l(t('Activate'), 'ccOTP/enable/nojs', array('attributes' => array('class' => array('ctools-use-modal btn btn-primary')))),
          );
      } else {
          $form['account']['otp_types']['validate_info'] = array(
              '#markup' => t('This authentication method has not yet been confirmed. Please check the email sent to your email address for the link to activate this method.'),
          );
      }

  }

  $form['#submit'][] = 'ccOTP_user_profile_form_submit';
	return $form;
}


/// form for display 2factor and validating/verifying the qrcode. - in profile
function otp_gauth(){
global $user;
module_load_include('inc','ccOTP','includes/lib');
    $otpDetails = get_otp_type($user->uid);
    $secret = $otpDetails['twofa_key'];

    module_load_include('inc','ccOTP','includes/GAuth/GoogleAuthenticator');
    $ga = new PHPGangsta_GoogleAuthenticator();
    $url_qr = $ga->getQRCodeGoogleUrl('Coingateway_'.$user->uid.'', $secret);

    $url_qr_output = '<img src="'.$url_qr.'">';

    $form['gauth_wrapper'] = array('#markup' => '<div style="text-align: center">');

    $form['gauth_qrcode']=array(
       '#markup'=> $url_qr_output,
       '#prefix' => '<div id="otp_types_gauth_qrcode">',
       '#suffix' => '</div>',
   );

    $form['gauth_code']=array(
        '#type'=>'textfield',
        '#title'=> ' ',
        '#value' => '',
        '#attributes' => array(
            'placeholder' => 'Google Authenticator Code'),
    );

    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit code'),
    );

    $form['gauth_wrapper_end'] = array('#markup' => '</div>');

    return $form;
}


/// default OTP generate form
function otp_gen_form(){
    if(!empty($form_state['otp_generated'])) {
        $state = $form_state['otp_generated'];
            if($state === TRUE) {
                $url = $form_state['otp_url'];
                global $user;

            }
    }
    $form['submit'] = array(
        '#type' => 'submit',
            '#value' => t('Generate link'),
    );
    return $form;
}

function ccOTP_user_profile_form_submit($form, &$form_state) {
	module_load_include('inc', 'ccOTP', 'includes/lib');
    $otp_pref = ($form_state['values']['ccAccount_otp_selections']);
 		set_otp_pref($otp_pref);
}
