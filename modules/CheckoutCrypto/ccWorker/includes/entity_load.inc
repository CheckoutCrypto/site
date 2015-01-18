<?php

/**
 * Returns a render array with all ccdev_work_orders entities.
 *
 * In this basic example we know that there won't be many entities,
 * so we'll just load them all for display. See pager_example.module
 * to implement a pager. Most implementations would probably do this
 * with the contrib Entity API module, or a view using views module,
 * but we avoid using non-core features in the Examples project.
 *
 * @see pager_example.module
 */
function ccdev_work_orders_list_entities() {
  $content = array();
$rows = array();
  // Load all of our entities.
  $entities = ccdev_work_orders_load_multiple();
  if (!empty($entities)) {
    foreach ($entities as $entity) {
      // Create tabular rows for our entities.
	if($user->uid == $entity->uid || user_access('administer ccdev_worker entities')) {
	      $rows[] = array(
		'data' => array(
		  'id' => $entity->basic_id,
		  'uid' => $entity->uid,
		'coin_name' => $entity->coin_name,
		'actions' => $entity->actions,
		'sender' => $entity->sender,
		'recipient' => $entity->recipient,
		'status' => $entity->status,
		'result' => $entity->result,
		'timestamp' => $entity->timestamp,  
		),
	      );
	}
    }
    // Put our entities into a themed table. See theme_table() for details.
    $content['entity_table'] = array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#header' => array(t('ID'), t('uid'), t('coin_name'), t('actions'), t('sender'), t('recipient'), t('amount'), t('status'), t('result'),t('timestamp'),),
    );
  }
  else {
    // There were no entities. Tell the user.
    $content[] = array(
      '#type' => 'item',
      '#markup' => t('No ccdev_work_orders entities currently exist.'),
    );
  }
  return $content;
}
