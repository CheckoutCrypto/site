#/bin/bash

SQL_USER='root';
SQL_PASS=$MYSQL_ENV_MYSQL_ROOT_PASSWORD;
SQL_NAME='site';
SQL_IP=$MYSQL_PORT_3306_TCP_ADDR;

mysql -h$SQL_IP -uroot -p$SQL_PASS -e "CREATE USER $SQL_USER@'%' IDENTIFIED BY '$SQL_PASS'; GRANT ALL PRIVILEGES ON * . * TO  $SQL_USER@'%' IDENTIFIED BY '$SQL_PASS'; CREATE DATABASE IF NOT EXISTS  $SQL_NAME"

echo "array(
    	'driver' => 'mysql',
    	'database' => $SQL_NAME,
    	'username' => $SQL_USER,
    	'password' => $SQL_PASS,
    	'host' => $SQL_IP,
    	'port' => 3306,
    	'prefix' => 'myprefix_',
    	'collation' => 'utf8_general_ci',
 	 );" >> settings.php

/usr/sbin/apache2ctl -D FOREGROUND

