ccStore 0.8.6 (uc_cc) Stable
==========
A payment method for the Ubercart shopping cart for Drupal.

New Version 0.8.6, renamed 'ccStore'.
Install/extract: ccStore or the previously named package, uc_cc (not both)

Features
--------

* Automatically generate payment address to customer on site at checkout and via email.

Requirements
------------

### PHP requirements:
* PHP5
* cURL support

Limitations
---------

* Orders for downloadables are not tagged as "shipped" once paid.
* No localization support.

Installation
------------

* Install Drupal 7.26 <http://drupal.org/documentation/install>.
* Install Ubercart 3 <http://www.ubercart.org/docs/user/8075/installing_ubercart>.
* Place the uc_cc module in <drupal>/sites/<yoursite>/modules/ to install for a single site, or <drupal>/sites/all/modules to install for all sites.

Configuration
-------------

* Log into your Drupal installation as an administrator.
* Navigate to Modules and enable the CheckoutCrypto module
* Navigate to Store->Configuration->Payment methods
* Find Checkout Crypto in the list and click on settings
 * Enter your CheckoutCrypto API key.
 * Click Save configuration
* You are now all set to accept cryptocurrency payments via CheckoutCrypto!

* Optional configuration
 * Set the default store currency to a crypto currency.
  * Navigate to Store->Configuration->Store
  * Click on Currency format"
  * Enter the "Default currency". For a list of supported formats see here: http://checkoutcrypto.com/docs/api
  * Save configuration

Cron
-------------

* Login to your server's shell, 
* copy getrate.php, ratesconfig.php, cryptorates.php to an appropriate folder for any user account, we'll call this $ABSOLUTEPATH, remember it or write it down.
* edit ratesconfig for your mysql database info, specifically the IP, table, user settings for your CMS

* edit getrate.php for any preferred coins you need to add/remove, if the row doesn't exist in table you'll have to create one in cc_coin.

* run the following, replace user with the preferred cron user.

 sudo su $USER -c "crontab -e"

* add a new line at the bottom of the file:

15,45 * * * * cd $ABSOLUTEPATH && php -f getrate.php 

Authors
-------

CheckoutCrypto - dev@checkoutcrypto.com

License
-------

uc_cc is free and unencumbered public domain software. For more
information, see <http://unlicense.org/> or the accompanying UNLICENSE file.

CheckoutCrypto: http://checkoutcrypto.com/
uc_cc: http://checkoutcrypto.com/clients/ubercart
Ubercart: http://www.ubercart.org/
Drupal: http://www.drupal.org/

