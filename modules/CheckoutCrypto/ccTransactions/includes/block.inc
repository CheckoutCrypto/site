<?php


function transactions_block_info(){
    $block['transactions'] = array(
        'info' => t('Transactions Block'),
        'cache' => DRUPAL_NO_CACHE,
    );
    return $block;
}

function transactions_block_view($block_key){
    $block = array();
	
	 if($block_key == 'transactions'){ //We only want to define the content of OUR block
		module_load_include('inc', 'ccTrans', 'includes/table');
 		drupal_add_css(drupal_get_path('module', 'cgTrading') . '/theme/style_trans.css', 'file');

        $block['subject'] = t('');
		$block['content'] = getTransactionsTable(); 
    	return $block;
	}
}
