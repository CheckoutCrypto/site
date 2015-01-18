<?php


/**
 * Fetch a basic object.
 */
function ccdev_coin_load($basic_id = NULL, $reset = FALSE) {
  $basic_ids = (isset($basic_id) ? array($basic_id) : array());
  $basic = ccdev_coin_load_multiple($basic_ids, array(), $reset);
  return $basic ? reset($basic) : FALSE;
}

/**
 * Loads multiple basic entities.
 */
function ccdev_coin_load_multiple($basic_ids = FALSE, $conditions = array(), $reset = FALSE) {
  return entity_load('ccdev_coin', $basic_ids, $conditions, $reset);
}
