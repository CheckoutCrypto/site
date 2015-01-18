<?php

function wallets_page(){
  $content['preface'] = array(
    '#type' => 'item',
    '#markup' => t('View your balances per wallet'),
  );
  if (user_access('administer ccdev_wallets entities')) {
    $content['preface']['#markup'] = t('You can administer these and add fields and change the view !link.',
      array('!link' => l(t('here'), 'admin/structure/ccdev_wallets/manage'))
    );
  }
  	module_load_include('inc', 'ccWallets', 'includes/entity');
  $content['table'] = ccdev_wallets_list_entities();

  return $content;
}
