<?php


function coin_block_info(){
    $block['rates'] = array(
        'info' => t('Coin Rates'),
        'cache' => DRUPAL_NO_CACHE,
    );
    return $block;
}

function coin_block_view($block_key){
    $block = array();
	
	 if($block_key == 'rates'){ //We only want to define the content of OUR block
		if (user_access('view any ccdev_coin entity')) {
			module_load_include('inc', 'ccCoin', 'includes/cc-php/table');
 			drupal_add_css(drupal_get_path('module', 'cgTrading') . '/theme/style_trans.css', 'file');

		   $block['subject'] = t('');
			$block['content'] = getRatesTable(); 
		 	return $block;
		}
	}
}