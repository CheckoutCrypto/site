<?php

function group_page(){

		$content['no_coins']['#markup'] = t('<div class="alert alert-info">Looking to !link.</div>', //TODO add check if user has api key already
		  array('!link' => l(t('Upgrade your service?'), 'ccMods/ccGroup/basic/add'))
		);
  if (user_access('administer ccdev_groups entities')) {
    $content['preface']['#markup'] = t('You can administer these and add fields and change the view !link.',
      array('!link' => l(t('here'), 'admin/structure/ccdev_groups/manage'))
    );
  }
  module_load_include('inc', 'ccGroup', 'includes/cc-php/entity');
  $content['table'] = ccdev_groups_list_entities();

  return $content;
}
