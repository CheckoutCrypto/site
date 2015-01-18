<?php


function popup_block_info(){
    $block['popup'] = array(
        'info' => t('Spend/Exchange Block'),
        'cache' => DRUPAL_NO_CACHE,
    );
    return $block;
}

function popup_block_view($block_key){
    $block = array();

    if($block_key == 'popup'){ //We only want to define the content of OUR block
		module_load_include('inc', 'cgPopup', 'includes/forms');
		//This is the title of the block.
		$popupPage = drupal_get_form('popup_page_form');
		//$content = drupal_render($tradeForm);

        $block['subject'] = t('');
		$block['content'] = $popupPage;
    return $block;
	}
}
