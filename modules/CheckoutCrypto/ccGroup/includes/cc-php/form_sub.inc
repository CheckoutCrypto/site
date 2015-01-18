<?php


function ccGroup_manage_form_submit($form, &$form_state){
     module_load_include('inc', 'ccGroup', 'includes/cc-php/lib');
	global $user;
	$grp_name = $form_state['values']['grp_name'];
	$grp_description = $form_state['values']['grp_description'];
	$grp_type = $form_state['values']['grp_type'];
	$grp_withdraw_fee = $form_state['values']['grp_withdraw_fee'];
	$grp_exchange_fee = $form_state['values']['grp_exchange_fee'];
	$grp_trade_fee = $form_state['values']['grp_trade_fee'];
	$grp_monthly_fee = $form_state['values']['grp_monthly_fee'];
	$grp_max_transactions = $form_state['values']['grp_max_transactions'];
	$grp_max_emails = $form_state['values']['grp_max_emails'];
	$grp_payment_length = $form_state['values']['grp_payment_length'];

 try {
       db_update('ccdev_groups')->fields(array(
            'grp_name' => $grp_name,
            'grp_description' => $grp_description,
			'grp_type' => $grp_type,
            'grp_trade_fee' => $grp_trade_fee,
            'grp_exchange_fee' => $grp_exchange_fee,
            'grp_withdraw_fee' => $grp_withdraw_fee,
            'grp_monthly_fee' => $grp_monthly_fee,
            'grp_max_transactions' => $grp_max_transactions,
            'grp_max_emails' => $grp_max_emails,
            'grp_payment_length' => $grp_payment_length,
          ))
		->condition('basic_id', $form_state['values']['basic_id'], '=')
		->execute();
      } catch (exception $e) {
			var_dump($e);
            watchdog('ccdev_groups', 'Could not insert order into database: !fault', $e->getMessage());
            return FALSE;
      }

ccGroupRefresh();
ctools_add_js('ajax-responder');
ctools_include('modal');
 $commands[] = ctools_modal_command_dismiss();
print ajax_render($commands);
drupal_exit();
}

