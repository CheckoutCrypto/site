<?php

function worker_page(){
  module_load_include('inc','ccWorker','includes/entity');
  $content['preface'] = array(
    '#type' => 'item',
    '#markup' => t('The wallet entity for coinproject'),
  );
  if (user_access('administer ccdev_work_orders entities')) {
    $content['preface']['#markup'] = t('You can administer these and add fields and change the view !link.',
      array('!link' => l(t('here'), 'admin/structure/ccdev_work_orders/manage'))
    );
  }
  $content['table'] = ccdev_work_orders_list_entities();

  return $content;
}
