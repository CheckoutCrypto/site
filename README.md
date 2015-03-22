#CheckoutCrypto's Drupal, Apache, Site

##Install
There are two methods of install

1.  Git
2.  Docker

##Git install

###Prerequisite repositories:

* worker: https://github.com/CheckoutCrypto/worker.git
* api: https://github.com/CheckoutCrypto/crypto-api
* site: https://github.com/CheckoutCrypto/site.git
* demo: https://github.com/CheckoutCrypto/checkoutcrypto-drupal.git

###Git Procedure
git clone site module, copy contents(modules, themes and .git folder) to a fresh drupal site root path at /var/www/yoursite/sites/all   

cd /var/www/yoursite/sites/all && git submodule init && git submodule update

Login to your drupal site as administraitor, visit the admin->modules menu, enable all checkoutcrypto modules except for Hosting(under development), Send payment by email(under development), cgPopup (a ctools example module, created by me for developers to see a working code for a vanilla ctools modal popup). 

1. You need to add all coins to the ccdev_coins table. Add their rpc info to offline worker cache menu, afterwords(worker option 2).
2. You need to add a "default" type group to the ccdev_groups table.
3. You need to select a user for use as a "hot wallet", you need to get that userid from the users table, copy it to the api configuration (api/config/ccapiconfig.php, within api repository).

Thorough, site documentation, found in ./modules/CheckoutCrypto/docs/ccDocs.pdf

##Docker install
###Required Docker Containers

* CheckoutCrypto [API](https://registry.hub.docker.com/u/checkoutcrypto/api/)
* CheckoutCrypto Worker [Dart ](https://registry.hub.docker.com/u/checkoutcrypto/worker-dart/)  [Qt](https://registry.hub.docker.com/u/checkoutcrypto/worker-qt/)

###Required DB Containers
Run MySQL daemon container with mysql-server (pre-exposed port 3306)

```
docker run --name mysql -e MYSQL_ROOT_PASSWORD=somepass -d mysql
```

Run PHPMyAdmin daemon container with mysql connection(exposed port 80 mapped to 81)

```
docker run -d --link mysql:mysql -e MYSQL_USERNAME=root --name phpmyadmin -p 81:80 corbinu/docker-phpmyadmin
```

###CheckoutCrypto Site Container

* Option 1 Run CheckoutCrypto site daemon container with mysql  (exposed port 80 mapped to 82):

```
sudo docker run -d -it --name cc-site --link mysql:mysql -p 81:80 checkoutcrypto/site
```

Then simply access it from the container's public IP with port 80.  Change :82:80  e.g. hostport:containerport 

* Option 2 Development

```
git clone https://github.com/CheckoutCrypto/site
cd ./site
docker build -t mytestsite .
```

Finally you can run the docker, linked to the site with:

```
docker run -d --link mysql:mysql -p 81:80 --name cc-site checkoutcrypto/site
```

####View/Install CheckoutCrypto Site

visit: http://localhost:81/site/install.php (or whatever container port you chose above) in the browser of an exposed, host, machine, to instantly install the site database tables. All mysql var are preinstalled, assuming you linked it correctly with --link mysql 


###Optional Access

Single run, login to a current container, with bash

```
docker run -it checkoutcrypto/site /bin/bash
```

Access a currently running checkoutcrypto/site container

```
docker exec -it cc-site /bin/bash
```

Site files located at /var/www/html/site - includes all necessary modules, submodules and repositories.  
 
###Drupal installation
Follow beginning at [Step 2](
https://www.drupal.org/documentation/install/create-database), their is no mysql included in this package.

##CheckoutCrypto + Modules
Assuming you followed all the instructions and initialized the source files, configured your database, the last thing you need to do (other than SSL and apache mod rewrite) is to enable the correct modules(Most of CheckoutCrypto, Ctools, Jquery_update, etc), theme(bootstrap) and finally, adjust the module blocks.

##Post-installation
1) enable all modules, fix configurations e.g. smtp, site config, theme settings, blocks, etc.

2)enable Mod_rewrite:

```
sudo a2enmod rewrite
sudo service apache2 restart
```

3) go to admin -> configuration -> clean urls,  hit the check for enable cleanurls;

4) You need to add all coins to the ccdev_coins table. Add their rpc info to offline worker cache 
menu, afterwords(worker option 2).

5) You need to add a "default" type group to the ccdev_groups table.

6) You need to select a user for use as a "hot wallet", you need to get that userid from the users table, copy it to the api configuration (api/config/ccapiconfig.php, within api repository).

Thorough, site documentation, found in [./modules/CheckoutCrypto/docs/ccDocs.pdf](https://github.com/CheckoutCrypto/site/blob/master/modules/CheckoutCrypto/docs/ccDocs.pdf)

###ccdev_coins table
Get all the validation codes, by inserting any address here: 

http://darkgamex.ch:2751/chain/Anoncoin/q/decode_address/PH4C5dGxdxKCN7Ru71Hn9yyj9SuxMATsh3

##API Docker
See CheckoutCrypto [API repository](https://registry.hub.docker.com/u/checkoutcrypto/api/)

###API Git 

1.  cd /var/www/ &&  git clone https://github.com/CheckoutCrypto/crypto-api.git && sudo chown ccuser:ccuser ./api -R
2. cd ./api && git submodule init && git submodule update
3. cd /var/www/api/config/ && gedit ./dbconfig.php  add your drupal database and username/password
4. gedit ./ccapiconfig.php set the worker port, address, apikey, hotwallet.

##Worker
See CheckoutCrypto Worker [Dart ](https://registry.hub.docker.com/u/checkoutcrypto/worker-dart/)  [Qt](https://registry.hub.docker.com/u/checkoutcrypto/worker-qt/)

###Worker Git

1. git clone from repo
2. cd ./worker && qmake && make
3. run with ./workServer
3. create/copy service to /etc/init.d/worker
4. sudo /usr/sbin/update-rc.d worker defaults (to set it to start on restart)

##Client Platforms
See [Drupal ](https://github.com/CheckoutCrypto/checkoutcrypto-drupal) 
[Wordpress ](https://github.com/CheckoutCrypto/checkoutcrypto-wordpress) 
[OpenCart ](https://github.com/CheckoutCrypto/checkoutcrypto-opencart) CheckoutCrypto repositories

##Bitcoin Daemon
See [CheckoutCrypto's Bitcoin docker](https://registry.hub.docker.com/u/checkoutcrypto/bitcoin/) instructions for one method.

###Instructions for any given daemon

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

##License
[Licensed under GPLv3](https://github.com/CheckoutCrypto/site/blob/master/COPYRIGHT) with one small reservation.

