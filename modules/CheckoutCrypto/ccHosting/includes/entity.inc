<?php

/**
 * Returns a render array with all entity_example_basic entities.
 */
function ccdev_hosting_list_entities() {
  module_load_include('inc','ccHosting','includes/entity_load');
  module_load_include('inc','ccHosting','includes/lib');
  global $user;

  ctools_include('modal');
  ctools_modal_add_js();

  $content = array();
  $rows = array();

  $header = array(
      'site_name' => array(
        'data' => t('Site Name'),
        'type' => 'property',
        'specifier' => 'site_name',
        'field' => 'site_name'
      ),
      'site_description' => array(
        'data' => t('Description'),
        'type' => 'property',
        'specifier' => 'total_balance',
        'field' => 'total_balance'
      ),
      'site_domain' => array(
        'data' => t('Domain'),
        'type' => 'property',
        'specifier' => 'site_domain',
        'field' => 'site_domain'
      ),
      'site_cms' => array(
        'data' => t('CMS'),
        'type' => 'property',
        'specifier' => 'site_cms',
        'field' => 'site_cms'
      ),
  );


  $entities = ccdev_hosting_load_multiple(FALSE, array(), FALSE, $header);
  if (!empty($entities)) {
    foreach ($entities as $entity) {
	if($user->uid == $entity->user_id || user_access('administer ccdev_hosting entities')) {
	      // Create tabular rows for our entities.
	      $rows[] = array(
		'data' => array(
		'site_name' => l($entity->site_name, 'ccMods/ccHosting/basic/' . $entity->site_name),
		'site_description' => $entity->site_description,
		'site_domain' => $entity->site_domain,
		'site_cms' => $entity->site_cms,
		'manage' => _ccHosting_make_link(array('site_id' => $entity->basic_id,'title' => 'Manage')),
		),
	      );
	}
    }

    // Put our entities into a themed table. See theme_table() for details.
    $content['entity_table'] = array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#header' => $header,
      '#attributes' => array(
          'id' => 'sort-table')
    );

    //Add pagination to table
    $content['pager'] = array(
      '#theme' => 'pager');

  }
  else {
    // There were no entities. Tell the user.
    $content[] = array(
      '#type' => 'item',
      '#markup' => t('No ccdev_hosting entities currently exist.'),
    );
  }
  return $content;
}
