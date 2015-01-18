<?php


function popup_page_form($form, &$form_state){
       ctools_include('ajax');
       ctools_include('modal');
       ctools_modal_add_js();
	$form = array();
	$form['content'] = array(
		'#markup' => t('test'),
	);
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('PAY NOW'),
		'#attributes' => array('id' => 'payButton', 'class' => array('ctools-use-modal')), 
	); 
	return $form;
}

function popup_page_form_submit($form, &$form_state){
	module_load_include('inc', 'cgPopup', 'includes/service');
	ctools_include('ajax');
    ctools_include('modal');
    ctools_modal_add_js();

	drupal_add_js(drupal_get_path('module','cgPopup').'/theme/cgPopup.js');
	global $base_url;
	$my_settings = array(
	  'baseUrl' => $base_url,
	 );
    $time_limit = 900;
    $cg_settings = array(
        'time_limit' => $time_limit
    );
	drupal_add_js(array('cgTrading' => $my_settings), 'setting');
	drupal_add_js(array('cgTrading' => $cg_settings), 'setting');


	   $form_state = array(
		  'ajax' => TRUE,
		  'title' => t('Checkout Crypto Payment Form'),
		  'cc_sel_coin' => 'BTC',
		);
		$output = ctools_modal_form_wrapper('my_popup_form', $form_state); 
	print ajax_render($output);

	drupal_exit();
}
