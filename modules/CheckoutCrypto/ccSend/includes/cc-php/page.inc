<?php


function send_info_page(){
   	module_load_include('inc', 'ccSend', 'includes/cc-php/lib');
	$coin_code = "pot";
	$link = 'dont know a wallet address? No problem, '._ccSend_make_link(array('coin_code' => $coin_code,'title' => 'Send Funds'));
  	$content['preface'] = array(
    '#type' => 'item',
    '#markup' => $link, 
  	);
  	$content['table'] = ccdev_send_list_entities();

  return $content;
}

function send_complete_page(){
    $content['preface']['#markup'] = t('Coin Send Completed!  It may take a few moments for the funds to transfer to your wallet.'    );
  	return $content;
}
