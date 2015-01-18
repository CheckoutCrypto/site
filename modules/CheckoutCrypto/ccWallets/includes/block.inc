<?php


function wallet_block_info(){
    $block['wallet'] = array(
        'info' => t('Wallet Block'),
        'cache' => DRUPAL_NO_CACHE,
    );
    return $block;
}

function wallet_block_view($block_key){
    $block = array();
	
	 if($block_key == 'wallet'){ //We only want to define the content of OUR block
		module_load_include('inc', 'ccWallets', 'includes/table');
 		drupal_add_css(drupal_get_path('module', 'cgTrading') . '/theme/style_trans.css', 'file');

        $block['subject'] = t('');
		$block['content'] = getWalletTable(); 
    	return $block;
	}
}
