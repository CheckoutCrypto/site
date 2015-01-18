
CheckoutCrypto Drupal Client Prerequisite Extension Modules
==========================================================

Quickly extract the compressed modules to a folder, if you're using linux, you may wish to utilize the express installer provided.

sudo sh ./install.sh

If you prefer to extract them manually:

Extract each module, all at once, to ./sites/all/modules ./sites/all/themes/ ./sites/all/libraries 
(edit with your correct site directory).

for i in ./ccStore_extend/ccStore_modules/*.tar.gz; do sudo tar xvzf $i  -C /var/www/YOURSITE/sites/all/modules; done

for i in ./ccStore_extend/ccStore_theme/*.tar.gz; do sudo tar xvzf $i  -C /var/www/YOURSITE/sites/all/themes; done

Enable each of the modules that you just extracted, from the drupal Admin->Modules Menu.

Required, Enable:
-----------------
* UberCart Core - Cart, Order, Product, Store
* UberCart Care - Payment, Catalog, Product attributes, Reports, Roles, Shipping, Taxes, Tax report
* UberCart FulFillment, Ubercart Extras, if your business requires it.
* UberCart Payment - CheckoutCrypto

* cTools, Rules, Entity Api + Token, Entity Tokens, Libraries, Views
* jQuery update

If you need the latest version, use the links below to download each one and extract to its required directory.

The following modules are required installed in sites/all/modules (unless otherwise stated).
You understand each module is subject to its own licensing. CheckoutCrypto claims no ownership of these modules.

Required Drupal 7 Module Project Links
-------------------------------------

Jquery Update 1.7+
https://www.drupal.org/project/jquery_update

UberCart
https://www.drupal.org/project/ubercart

CheckoutCrypto Payment Module - see: checkoutcrypto.com/platforms 
https://downloads.checkoutcrypto.com/uc_cc.0.8.5.tar.gz

Rules
https://www.drupal.org/project/rules

Views
http://drupal.org/project/views

Ctools
https://www.drupal.org/project/ctools

Entity API + Tokens
https://www.drupal.org/project/entity


Recommended Drupal 7 Module Project Links
-------------------------------------

Libraries API sites/all/libraries 
https://www.drupal.org/project/libraries

Colorbox plugin  in sites/all/libraries/
https://github.com/jackmoore/colorbox/archive/1.x.zip
might not work

sudo apt-get install drush
drush colorbox-plugin

Colorbox
https://www.drupal.org/project/colorbox

Google Analytics
https://www.drupal.org/project/google_analytics

Token
https://www.drupal.org/project/token

bootstrap in sites/all/themes  (configure jquery version 1.10)
https://www.drupal.org/project/bootstrap
