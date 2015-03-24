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

Input everything into CheckoutCrypto Worker config:

```
docker exec -it worker ./workServer
```

##API Key
Finally, run the command above again, this time, go to option 3, to Generate an API Key, for accessing worker. Then we need to place that key in our API config (within our API container).  Run:

```
docker exec -it api vi /var/www/html/config/ccapiconfig.php
```

Change:
```
$apikey = "";
```

##Run the CheckoutCrypto Worker Server

```
docker exec -it worker ./workServer -server -pass test
```

