<?php


function trade_callback($form, &$form_state){
	// module_load_include('inc', 'cgTrading', 'includes/service');
	//fillTest();
	$commands = array();
	$popup['content'] = array('#markup' => t('<div id="popup_content"> test'));
           
	$commands[] = ajax_command_append('#popup_content', drupal_render($popup['content']));
	print ajax_render($result);
	drupal_exit();
}

function trade_validate(){
	var_dump('trade validated');
	break;
}

function trade_submit(){
	var_dump('trade submitted');
	break;

}
