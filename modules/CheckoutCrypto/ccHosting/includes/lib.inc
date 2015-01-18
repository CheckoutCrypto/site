<?php


/// MAKE LINK FOR ADD COIN
function _ccHosting_make_link($args = '') {
// Set a default value if no text in supplied.
  if (!(empty($args))) {
     $link_text = $args['title'];
     $site_id = $args['site_id'];
   } else {
     return FALSE;
   }
   return '<div id="'. $site_id.'-modal-link">' . l($link_text, 'ccMod/ccHosting/any/nojs/'. $site_id, array('attributes' => array('class' => 'ctools-use-modal'))) . '</div>';
}

/*
* Grab site data
*/
function getSiteData($siteid){
$sitedata = array();
$query = new EntityFieldQuery();
$query->entityCondition('entity_type', 'ccdev_hosting')
  ->entityCondition('bundle', 'ccdev_hosting_bundle')
 ->propertyCondition('basic_id', $siteid);
$result = $query->execute();
if (isset($result['ccdev_hosting'])) {
  $site_nids = array_keys($result['ccdev_hosting']);
  $allsites = entity_load('ccdev_hosting', $site_nids);
	foreach($allsites as $site){
		$sitedata['basic_id'] = $site->basic_id;
		$sitedata['site_name'] = $site->site_name;
		$sitedata['site_domain'] = $site->site_domain;
		$sitedata['site_description'] = $site->site_description;
		$sitedata['site_cms'] = $site->site_cms;
		$sitedata['site_mysql_admin'] = $site->site_mysql_admin;
		$sitedata['site_mysql_pass'] = $site->site_mysql_pass;
		$sitedata['site_mysql_table'] = $site->site_mysql_table;
		$sitedata['created'] = $site->created;
	} 
}
return $sitedata;
}

