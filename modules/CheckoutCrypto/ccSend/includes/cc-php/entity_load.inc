<?php

/**
 * Fetch a basic object.
 */
function ccdev_send_load($basic_id = NULL, $reset = FALSE) {
  $basic_ids = (isset($basic_id) ? array($basic_id) : array());
  $basic = ccdev_send_load_multiple($basic_ids, array(), $reset);
  return $basic ? reset($basic) : FALSE;
}

/**
 * Loads multiple basic entities.
 */
function ccdev_send_load_multiple($basic_ids = FALSE, $conditions = array(), $reset = FALSE, $header = FALSE) {
    global $user;

    $scope = 10; //how many results will be returned
    if($basic_ids) {
        $basic_id = end($basic_ids);
    } else {
        $basic_id = 1; //starting point of results
    }

    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type','ccdev_send')
        ->propertyCondition('uid', $user->uid)
        ->propertyCondition('basic_id', $basic_id, '>=')
        ->addMetaData('account', user_load($user->uid)); // Run the query in the current user's context
    $query->pager($scope);
    if($header) {
        $query->tablesort($header);
    }
    $result = (array)$query->execute();
	if($result){
		$result = $result['ccdev_send'];
	
		$basic_ids = (array)array_keys($result);
	}
    $entities = entity_load('ccdev_send', $basic_ids, $conditions, $reset);
	
    return $entities;
}
