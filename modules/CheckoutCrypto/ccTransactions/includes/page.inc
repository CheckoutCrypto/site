<?php

function trans_page(){
	module_load_include('inc', 'ccTrans', 'includes/entity');
  $content['preface'] = array(
    '#type' => 'item',
    '#markup' => t('View past transactions for your store.'),
  );
  if (user_access('administer ccdev_transactions entities')) {
    $content['preface']['#markup'] = t('You can administer these and add fields and change the view !link.',
      array('!link' => l(t('here'), 'admin/structure/ccdev_transactions/manage'))
    );
  }
  $content['table'] = ccdev_transactions_list_entities();

  return $content;
}
