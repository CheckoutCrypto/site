<?php

function balance_info_page(){
  $content['preface'] = array(
    '#type' => 'item',
    '#markup' => t('View and manage withdraw and autopayment for enabled coins. !link',
        array('!link' => l(t('Manage coins'), 'Coin'))),
  );

  if (user_access('administer ccdev_balance entities')) {
    $content['preface']['#markup'] = t('You can administer these and add fields and change the view !link.',
      array('!link' => l(t('here'), 'admin/structure/ccdev_balance/manage'))
    );
  }
    module_load_include('inc', 'ccBalance', 'includes/cc-php/entity');
  $content['table'] = ccdev_balance_list_entities();
	return $content;
}
