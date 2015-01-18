<?php

/**
 * Loads multiple basic entities.
 */

function ccdev_hosting_load_multiple($basic_ids = FALSE, $conditions = array(), $reset = FALSE, $header = FALSE) {
    global $user;

    $scope = 10; //how many results will be returned
    if($basic_ids) {
        $basic_id = end($basic_ids);
    } else {
        $basic_id = 1; //starting point of results
    }

    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type','ccdev_hosting')
        ->propertyCondition('user_id', $user->uid)
        ->propertyCondition('basic_id', $basic_id, '>=')
        ->addMetaData('hosting', user_load($user->uid)); // Run the query in the current user's context
    $query->pager($scope);
    if($header) {
        $query->tablesort($header);
    }
    $result = (array)$query->execute();
	if($result){
		$result = $result['ccdev_hosting'];
		$basic_ids = (array)array_keys($result);
	}
    $entities = entity_load('ccdev_hosting', $basic_ids, $conditions, $reset);

    return $entities;
}

