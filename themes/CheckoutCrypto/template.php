<?php
/**
 * @file
 * template.php
 */

/**
* Implements template_preprocess_page().
*/
function CheckoutCrypto_preprocess_page(&$vars) {
  // Remove the "No front page content has been created yet.".
  if (isset($vars['page']['content']['system_main']['default_message'])) {
    unset($vars['page']['content']['system_main']['default_message']);
  }
 ///  Remove "Welcome to Drupal Message"
 if (drupal_is_front_page()) {  drupal_set_title('');} 

}
