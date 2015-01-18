<?php


function my_popup_form($form, &$form_state){
       ctools_include('ajax');
       ctools_include('modal');
       ctools_modal_add_js();
	$form = array();
  $form['#method'] = 'post';
  $form['#action'] = url('Popup/any');
	$form['content'] = array(
		'#markup' => t('<div id="popup_content">testing</div>'),
	);
   $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
        '#ajax' => array(
            'callback' => 'my_popup_form_callback',
			 ),
    );
	return $form;
}


function fillTest(){
	$commands = array();
	$form['content'] = array('#markup' => '<p>Selected currency:</p>');
           
	$commands[] = ajax_command_replace('#popup_content', 'test');
	print ajax_render($commands);
	drupal_exit();
}
