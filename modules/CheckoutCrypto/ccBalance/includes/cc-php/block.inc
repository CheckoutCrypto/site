<?php


function balance_block_info(){
    $block['balance'] = array(
        'info' => t('Balance Block'),
        'cache' => DRUPAL_NO_CACHE,
    );
    return $block;
}

function balance_block_view($block_key){
    $block = array();

    if($block_key == 'balance'){ //We only want to define the content of OUR block
		if (user_access('view any ccdev_balance entity')) {
			module_load_include('inc', 'ccBalance', 'includes/cc-php/table');
	 		drupal_add_css(drupal_get_path('module', 'cgTrading') . '/theme/style_trans.css', 'file');

		   $block['subject'] = t('');
			$block['content'] = getBalanceTable(); 
		 	return $block;
		}
	}
}
