CheckoutCrypto Site
===================

git clone site module, copy contents(modules, themes and .git folder) to a fresh drupal site root path at /var/www/yoursite/sites/all   

cd /var/www/yoursite/sites/all && git submodule init && git submodule update

Login to your drupal site as administraitor, visit the admin->modules menu, enable all checkoutcrypto modules except for Hosting(under development), Send payment by email(under development), cgPopup (a ctools example module, created by me for developers to see a working code for a vanilla ctools modal popup). 

When you created the drupal site database, all your modules will be written to it, all worker+api completed queries happen on that database. You need to create 2 seperate mysql accounts with permissions for portions of that database.  For the basic install, create a worker and api user, give them full permissions and ensure their ip locations are correct.

Place the api mysql user in the api configs - see api/README.txt
Place the worker mysql user in the worker input menu - see worker/README.txt

You need to add all coins to the ccdev_coins table. Add their rpc info to offline worker cache menu, afterwords(worker option 2).
You need to add a "default" type group to the ccdev_groups table.
You need to select a user for use as a "hot wallet", you need to get that userid from the users table, copy it to the api configuration (api/config/ccapiconfig.php, within api repository).

Thorough, site documentation, found in ./modules/CheckoutCrypto/docs/ccDocs.pdf

DEVELOPER VPS DEPENDENCIES + NOTES
============================
 Requirements:  Ubuntu 14.04 LAMP Server with Mate

Libraries:
===========
git drush phpmyadmin qt5-default qt5-qmake libqt5sql5 libqt5sql5-mysql libqt5sql5-sqlite build-essential libmysqlclient-dev curl php5-curl monit


Repos:
========
worker: https://github.com/CheckoutCrypto/worker.git
api: https://github.com/CheckoutCrypto/crypto-api
site: https://github.com/CheckoutCrypto/site.git
demo: https://github.com/CheckoutCrypto/checkoutcrypto-drupal.git


Procedure:
===========
1. create a new unix account (adduser), add root access (visudo)  e.g. ccuser
2. sudo apt-get install tasksel  && sudo tasksel  (select lamp server, then done)
3. Set mysql pass for root, completed install
4. sudo apt-get install git drush phpmyadmin qt5-default qt5-qmake libqt5sql5 libqt5sql5-mysql build-essential libmysqlclient-dev curl php5-curl


Site:
=========
1. sudo mkdir /var/www/site  && sudo chown ccuser:ccuser site -R
2. cd /var/www/site && drush core-quick-drupal  (hit y to questions)
3. cd ./quick-*/drupal && cp * -R ../../ && cp .* -R ../../
4. cd /var/www/site && rm quick* -R
5. gedit /etc/apache2/sites-available/000-default.conf  (edit default apache config)

	so it looks like this:

	DocumentRoot /var/www

<Directory /var/www>
    AllowOverride All
</Directory>


5. save, sudo service apache2 reload/restart
6. cd ./sites/default && cp ./default.settings.php ./settings.php && chmod 777 ./settings.php (reset config)
7. chmod 777 ./files -r  (set permissions of cache) 
8. visit http://yourip/site/install.php to install.
9. visit http://yourip/phpmyadmin login and create a new database with a user who is privileged to access it.
10. Follow instructions at drupal menu, install.
11. cd /var/www/site/sites/all/ && git clone https://github.com/CheckoutCrypto/site.git
12. cp ./dev/* . -R && cp ./dev/.* . -R
13. git submodule init && git submodule update
14. enable all modules, fix configurations e.g. smtp, site config, theme settings, blocks, etc.

enable Mod_rewrite:
 	sudo a2enmod rewrite
	sudo service apache2 restart

(don't forget, ensure .htaccess is in site root, sometimes it doesn't copy).
then go to admin -> configuration -> clean urls,  hit the check for enable cleanurls;


Demo
=============
Instructions using drush make, assuming.
1. cd /var/www/ && sudo mkdir demo && sudo chown ccuser:ccuser ./demo -R
2. cd /var/www/demo && drush make sitemakefile  (save below to a file).

; This file was auto-generated by drush make
core = 7.x

api = 2
projects[drupal][version] = "7.31"

; Modules
projects[ctools][version] = "1.4"

; Please fill the following out. Type may be one of get, git, bzr or svn,
; and url is the url of the download.

projects[colorbox][version] = "2.7"

projects[entity][version] = "1.5"

projects[jquery_update][version] = "2.4"

projects[libraries][version] = "2.2"

projects[rules][version] = "2.7"

projects[ubercart][version] = "3.6"

projects[token][version] = "1.5"

projects[views][version] = "3.8"

; Themes
projects[bootstrap][version] = "3.0"

; Modules
; Please fill the following out. Type may be one of get, git, bzr or svn,
; and url is the url of the download.
projects[ccStore][download][type] = "git"
projects[ccStore][download][url] = "https://github.com/CheckoutCrypto/checkoutcrypto-drupal.git"
projects[ccStore][type] = "module"

4. cd ./sites/default && cp ./default.settings.php ./settings.php && chmod 777 ./settings.php (reset config)
5. chmod 777 ./files -r  (set permissions of cache) 
6. visit http://yourip/site/install.php to install.
7. visit http://yourip/phpmyadmin login and create a new database with a user who is privileged to access it.
8. Follow instructions at drupal menu, install.


API
=====
1.  cd /var/www/ &&  git clone https://github.com/CheckoutCrypto/crypto-api.git && sudo chown ccuser:ccuser ./api -R
2. cd ./api && git submodule init && git submodule update
3. cd /var/www/api/config/ && gedit ./dbconfig.php  add your drupal database and username/password
4. gedit ./ccapiconfig.php set the worker port, address, apikey, hotwallet.


Worker
========

1. git clone from repo
2. cd ./worker && qmake && make
3. run with ./workServer
3. create/copy service to /etc/init.d/worker
4. sudo /usr/sbin/update-rc.d worker defaults (to set it to start on restart)



DAEMONS
============
Instructions for any given daemon
1) git clone  daemon's repo
2) install all dependencies
3) cd ./anycoin/src  ./configure && make
4) configure nano ~/.anycoin/anycoin.conf
ensure rpcuser and pass are unique and save
add rpcallowip=10.0.0.1 or w.e your ip
5) add daemon service linked to daemon binary in /etc/init.d
6)  make service start on restart sudo /usr/sbin/update-rc.d anycoin defaults
7) start coin and ensure rpc connection to local network

ccdev_coins table
==================
Get all the validation codes, by inserting any address here: 

http://darkgamex.ch:2751/chain/Anoncoin/q/decode_address/PH4C5dGxdxKCN7Ru71Hn9yyj9SuxMATsh3
