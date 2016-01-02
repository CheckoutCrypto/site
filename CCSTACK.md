##Start MySQL, PHPMyAdmin, API, Site 

Download checkoutcrypto's fig script.

```
wget https://raw.githubusercontent.com/CheckoutCrypto/site/master/fig.yml
```

Start the CheckoutCrypto stack, with:

```
sudo fig up
```

##Start Bitcoin Daemon

```
docker run --name bitcoin -d -it -p 21234:21234 -v /home/your_user/yourcryptofolder/bitcoin/:/bitcoin/ -v  /home/your_user/.bitcoin/:/root/.bitcoin/ checkoutcrypto/bitcoin
```

```
docker exec -it bitcoin /bitcoin/bin/bitcoind
```

##Start Worker

```
docker run -d -it -p 12311:12311 --name worker --link mysql:mysql checkoutcrypto/worker-qt /worker/workServer
```

```
docker inspect bitcoin
docker inspect worker
docker inspect mysql
```

Note the IPv4 address of all 3

##RPC DATA
Get/Edit the RPC info from bitcoin container with:

```
docker exec -it bitcoin vi /root/.bitcoin/bitcoin.conf
```

Don't forget to insert your worker's container IP, under 

```
rpcallowip=
```

##Worker config

```
docker exec -it worker ./workServer
```
```
********************************
================================
=======  CheckoutCrypto Worker  =========
================================
*********************************
1) Add/Edit Remote Database
2) Add/Edit Coin Daemon
3) Add/Edit API Key
4) Run Server
Enter Choice(0-4):
```

Add the site's MySQL user/pass(option 1) with:
```
user: site
pass: password
database: site
```
To change these values, edit site/bootup.sh or access them through 

Next Input all Coin data into CheckoutCrypto Worker config(option 2)


##API Key
Open the workServer again this time, go to option 3, to Generate an API Key, for accessing worker. Then we need to place that key in our API config (within our API container).  Run:

```
docker exec -it api vi /var/www/html/config/ccapiconfig.php
```

Insert your worker's API key:
```
$apikey = "";
```

and your worker's IP(default 127.0.0.1)
```
$workerserver = '';
```


##Run the CheckoutCrypto Worker Server

Once you've configured the mysql database, the RPC cryptocoins, the API key, run the server with:
```
docker exec -it worker ./workServer -server -pass test
```

##access container pages

###Site
Install Drupal -database is pre-setup just enter site details(title,email,admin username,password)
```
http://127.0.0.1:82/site/install.php
```
after install view site at
```
http://127.0.0.1:82/site/
```
Don't forget to enable modules: ctools, jQuery update, CheckoutCrypto modules: Accounts, Admin, Balances, Coins, Groups, OTP, Trading, Transactions, Wallets, Worker

Visit Account page to generate an API key
Visit Coins page to enable coins

###API
API access example(need to generate an API key and enable a coin, first)
```
http://127.0.0.1:83/api.php?apikey=YOURGENERATEDKEY&action=getbalance&coin=YOURCOIN
```

###API Docs

Slate API Documentation found at:
```
http://127.0.0.1:4567
```

###PHPMYADMIN
```
http://127.0.0.1:81
```
Default user and pass
```
username: root
password: password
```
