<?php

function popup_page(){

  $content['preface'] = array(
    '#type' => 'item',
    '#markup' => t('The Trading Entity'),
  );
  if (user_access('administer ccdev_popup entities')) {
    $content['preface']['#markup'] = t('You can administer these and add fields and change the view !link.',
      array('!link' => l(t('here'), 'admin/structure/ccdev_work_orders/manage'))
    );
  }
  $content['stuff'] = array(
    '#type' => 'item',
    '#markup' => t('we can put all the html in here'),
  );

  return $content;
}
