<?php

function coin_info_page(){
	module_load_include('inc', 'ccCoin', 'includes/cc-php/entity');
  $content['preface'] = array(
    '#type' => 'item',
    '#markup' => t('View and manage coins'),
  );
  if (user_access('administer ccdev_coin entities')) {
    $content['preface']['#markup'] = t('You can administer these and add fields and change the view !link.',
      array('!link' => l(t('here'), 'admin/structure/ccdev_coin/manage'))
    );
  }
  $content['table'] = ccdev_coin_list_entities();
	return $content;
}
