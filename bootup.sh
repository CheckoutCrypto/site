#/bin/bash

SQL_USER='site'
SQL_PASS='password'
SQL_NAME='site'
SQL_IP=$MYSQL_PORT_3306_TCP_ADDR

mysql -h$SQL_IP -uroot -p$MYSQL_ENV_MYSQL_ROOT_PASSWORD -e "CREATE USER $SQL_USER@'%' IDENTIFIED BY '$SQL_PASS'; GRANT ALL PRIVILEGES ON * . * TO  $SQL_USER@'%' IDENTIFIED BY '$SQL_PASS'; CREATE DATABASE IF NOT EXISTS  $SQL_NAME"
echo "<?php \$databases = array (
  'default' =>
  array (
    'default' =>
    array (
    	'database' => '$SQL_NAME',
    	'username' => '$SQL_USER',
    	'password' => '$SQL_PASS',
    	'host' => '$SQL_IP',
      'port' => '3306',
      'driver' => 'mysql',
      'prefix' => false,
    ),
  ),
);
\$drupal_hash_salt = ''; " > /var/www/html/site/sites/default/settings.php

/usr/sbin/apache2ctl -D FOREGROUND

