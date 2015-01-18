<?php


/**
 * Form submit handler: Submits basic_add_form information.
 */
function ccdev_hosting_form_submit($form, &$form_state) {

 $entity = $form_state['values']['basic_entity'];
$entity->site_name = $form_state['values']['site_name'];
$entity->site_description = $form_state['values']['site_description'];
$entity->site_domain = $form_state['values']['site_domain'];
$entity->site_cms = $form_state['values']['site_cms'];

$entity->group_price = $form_state['values']['group_price'];

/*
$entity->site_mysql_table = $form_state['values']['site_mysql_table'];  
$entity->site_mysql_admin = $form_state['values']['site_mysql_admin'];
$entity->site_mysql_pass = $form_state['values']['site_mysql_pass'];   */ /// encrypt 


  field_attach_submit('ccdev_hosting', $entity, $form, $form_state);
  $entity = ccdev_hosting_save($entity);
  $form_state['redirect'] = 'ccMods/ccHosting/basic/' . $entity->basic_id;
}


function manage_form_submit($form, &$form_state){
global $user;
$site_name = $form_state['values']['site_name'];
$site_description = $form_state['values']['site_description'];
$site_domain = $form_state['values']['site_domain'];
$site_cms = $form_state['values']['site_cms'];
 try {
       db_update('ccdev_hosting')->fields(array(
            'site_name' => $site_name,
            'site_description' => $site_description,
			'site_domain' => $site_domain,
            'site_cms' => $site_cms,
          ))
		->condition('basic_id', $form_state['values']['basic_id'], '=')
		->execute();
      } catch (exception $e) {
			var_dump($e);
            watchdog('ccdev_hosting', 'Could not insert order into database: !fault', $e->getMessage());
            return FALSE;
      }


ctools_add_js('ajax-responder');
ctools_include('modal');
 $commands[] = ctools_modal_command_dismiss();
print ajax_render($commands);
drupal_exit();
}

