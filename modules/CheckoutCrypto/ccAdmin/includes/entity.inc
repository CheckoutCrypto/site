<?php

function display_admin_entity(){
  $sqlHeader = array(
      'disable_all_coins' => array(
        'data' => t('Disable All Coins'),
        'type' => 'property',
        'specifier' => 'disable_all_coins',
        'field' => 'disable_all_coins'
      ),
      'disable_worker' => array(
        'data' => t('Disable Worker'),
        'type' => 'property',
        'specifier' => 'disable_worker',
        'field' => 'disable_worker'
      ),
  );



  $content = array();
global $user;
  // Load all of our entities.
$rows = array();
 /*	$entities = ccdev_admin_load_multiple(FALSE, array(), FALSE, $sqlHeader);
  if (!empty($entities)) {
    foreach ($entities as $entity) {
	      $rows[] = array(
			'data' => array(
				'disable_all_coins' => $entity->disable_all_coins,
				'disable_worker' => $entity->disable_worker,
			),
	      );
	}
  
    // Put our entities into a themed table. See theme_table() for details.
    $content['entity_table'] = array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#header' => array(t('DISABLE COIN'), t('DISABLE WORKER'), ),
    );
  }
  else {
    // There were no entities. Tell the user.
    $content[] = array(
      '#type' => 'item',
      '#markup' => t('No ccdev_admin entities currently exist.'),
    );
  }  */
	return $content;
}


/**
 * Fetch a basic object.
 */
function ccdev_admin_load($basic_id = NULL, $reset = FALSE) {
  $basic_ids = (isset($basic_id) ? array($basic_id) : array());
  $basic = ccdev_admin_load_multiple($basic_ids, array(), $reset);
  return $basic ? reset($basic) : FALSE;
}
