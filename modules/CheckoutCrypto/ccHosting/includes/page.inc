<?php

function hosting_page(){
		$content['no_coins']['#markup'] = t('<div class="alert alert-info">Looking to add !link.</div>', //TODO add check if user has api key already
		  array('!link' => l(t('Hosting?'), 'ccMods/ccHosting/basic/add'))
		);
  if (user_access('administer ccdev_hosting entities')) {
    $content['preface']['#markup'] = t('You can administer these and add fields and change the view !link.',
      array('!link' => l(t('here'), 'admin/structure/ccdev_hosting/manage'))
    );
  }
  module_load_include('inc','ccHosting','includes/entity');
  $content['table'] = ccdev_hosting_list_entities();

  return $content;
}
