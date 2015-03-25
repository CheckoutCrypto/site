<?php


function trading_block_info(){
    $block['trading'] = array(
        'info' => t('Spend/Exchange Block'),
        'cache' => DRUPAL_NO_CACHE,
    );
    $block['trade_trans'] = array(
        'info' => t('Trade Transactions'),
        'cache' => DRUPAL_NO_CACHE,
    );
    return $block;
}

function trading_block_view($block_key){
    $block = array();

    if($block_key == 'trading'){ //We only want to define the content of OUR block
		module_load_include('inc', 'cgTrading', 'includes/forms');
		$tradeForm = drupal_get_form('trading_form');
		$content = drupal_render($tradeForm);

        $block['subject'] = t('');
		$block['content'] = $content; 
    	return $block;
	}

    else if($block_key == 'trade_trans'){ //We only want to define the content of OUR block
		module_load_include('inc', 'cgTrading', 'includes/table');
 		drupal_add_css(drupal_get_path('module', 'cgTrading') . '/theme/style_trans.css', 'file');

        $block['subject'] = t('');
		$block['content'] = getTradeTable(); 
    	return $block;
	}
}

function trading_block_setup(&$blocks, $theme, $code_blocks){
        if (isset($blocks['cgTrading']['trading'])) {
            $blocks['cgTrading']['trading']['status'] = 1;
            $blocks['cgTrading']['trading']['region'] = 'content';
            $blocks['cgTrading']['trading']['weight'] = 2;
            $blocks['cgTrading']['trading']['visibility'] = BLOCK_VISIBILITY_LISTED;
            $blocks['cgTrading']['trading']['pages'] = '<front>';
        }
        if (isset($blocks['cgTrading']['trade_trans'])) {
            $blocks['cgTrading']['trade_trans']['status'] = 1;
            $blocks['cgTrading']['trade_trans']['region'] = 'content';
            $blocks['cgTrading']['trade_trans']['weight'] = 2;
            $blocks['cgTrading']['trade_trans']['visibility'] = BLOCK_VISIBILITY_LISTED;
            $blocks['cgTrading']['trade_trans']['pages'] = '<front>';
        }
}
