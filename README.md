#CheckoutCrypto's Drupal, Apache, Site

##Install
There are two methods of install

1.  Git(below)
2.  [Docker CheckoutCrypto Stack instructions](https://github.com/CheckoutCrypto/site/blob/master/CCSTACK.md)

###Prerequisite repositories:

* [worker](https://github.com/CheckoutCrypto/worker.git)
* [api](https://github.com/CheckoutCrypto/crypto-api)
* [site](https://github.com/CheckoutCrypto/site.git)
* [demo](https://github.com/CheckoutCrypto/checkoutcrypto-drupal.git)

###Git Procedure
git clone site module, copy contents(modules, themes and .git folder) to a fresh drupal site root path at /var/www/yoursite/sites/all   

cd /var/www/yoursite/sites/all && git submodule init && git submodule update

Login to your drupal site as administraitor, visit the admin->modules menu, enable all checkoutcrypto modules except:

####Enable

- Account, Admin, Balance, Coins, Groups, OTP, Wallets, Trading, Transactions, Worker

####Ignore / View and develop

- Hosting(under development), Send payment by email(under development), cgPopup (a ctools modal example module, created by me for developers), service payments.

#####Modifications for your API URL

 You need to modify the ccAccount module's [API connection](https://github.com/CheckoutCrypto/site/blob/master/modules/CheckoutCrypto/ccAccount/includes/cc-php/cc.inc) (it's done automatically in docker build, not git).

```
$base_url = '';
```

to your **API host's** IP address.

 
###Drupal installation
Site files located at /var/www/html/site - includes all necessary modules, submodules and repositories.

Follow at [Step 4 of Drupal Install Guide](
https://www.drupal.org/node/251031), as settings.php is prefilled by site docker image.  All you need to do is visit http://localhost:83/site/install.php (or whichever port you selected), continue with the admin and site setup.

##CheckoutCrypto + Modules
The last steps are to: enable the correct modules(Most of CheckoutCrypto, Ctools, Jquery_update, etc), theme(CheckoutCrypto), adjust the module blocks.

##Post-installation
1) enable all modules, fix configurations e.g. smtp, site config, theme settings, blocks, etc.

2)enable Mod_rewrite:

```
sudo a2enmod rewrite
sudo service apache2 restart
```

3) go to admin -> configuration -> clean urls,  hit the check for enable cleanurls;

4) You need to add all coins to the ccdev_coins table(site's Coins page). Add each coin's RPC config data to offline worker cache menu(worker option 2).

5) You need to add a "default" type group to the ccdev_groups table.

6) You need to select a user for use as a "hot wallet", you need to get that userid from the users table, copy it to the api configuration (api/config/ccapiconfig.php, within api repository).

see [site documentation](https://github.com/CheckoutCrypto/site/blob/master/modules/CheckoutCrypto/docs/README.txt) or [development doc](https://github.com/CheckoutCrypto/site/blob/master/modules/CheckoutCrypto/docs/ccDocs.pdf)

###API

1.  cd /var/www/ &&  git clone https://github.com/CheckoutCrypto/crypto-api.git && sudo chown ccuser:ccuser ./api -R
2. cd ./api && git submodule init && git submodule update
3. cd /var/www/api/config/ && gedit ./dbconfig.php  add your drupal database and username/password
4. gedit ./ccapiconfig.php set the worker port, address, apikey, hotwallet.

see [API Docs](https://github.com/CheckoutCrypto/crypto-api/blob/master/README.md)
or [API Calls](https://github.com/CheckoutCrypto/site/blob/master/modules/CheckoutCrypto/docs/API_CALLS.md)

###Worker

1. git clone from repo
2. cd ./worker && qmake && make
3. run with ./workServer
3. create/copy service to /etc/init.d/worker
4. sudo /usr/sbin/update-rc.d worker defaults (to set it to start on restart)

see [Worker Docs](https://github.com/CheckoutCrypto/worker/blob/master/README.md)

##Client Platforms
See [Drupal ](https://github.com/CheckoutCrypto/checkoutcrypto-drupal) 
[Wordpress ](https://github.com/CheckoutCrypto/checkoutcrypto-wordpress) 
[OpenCart ](https://github.com/CheckoutCrypto/checkoutcrypto-opencart) CheckoutCrypto repositories

###Instructions for any given crypto daemon

1. git clone  daemon's repo
2. install all dependencies
3. cd ./anycoin/src  ./configure && make
4. configure nano ~/.anycoin/anycoin.conf
ensure rpcuser and pass are unique and save
add rpcallowip=10.0.0.1 or w.e your ip
5. add daemon service linked to daemon binary in /etc/init.d
6.  make service start on restart sudo /usr/sbin/update-rc.d anycoin defaults
7. start coin and ensure rpc connection to local network

###Additional notes:
Get all the validation codes, for the ccdev_coins table, by inserting any address [here](http://darkgamex.ch:2751/chain/Anoncoin/q/decode_address/PH4C5dGxdxKCN7Ru71Hn9yyj9SuxMATsh3)

##Contributing
See [CONTRIBUTING](https://github.com/CheckoutCrypto/site/blob/master/CONTRIBUTING.md)

## Creators
**Grant Hutchinson**

##License
[Licensed under the Apache 2.0 License](https://github.com/CheckoutCrypto/site/blob/master/COPYRIGHT), with one small reservation.

