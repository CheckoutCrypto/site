FROM ubuntu:14.04
MAINTAINER Grant Hutchinson <h.g.utchinson@gmail.com>


RUN apt-get update && \
    apt-get install -y apache2 mysql-client php5 php5-mysql php5-curl php5-gd curl wget git && \
	mkdir /var/www/html/site && cd /var/www/html/site && \
	wget http://ftp.drupal.org/files/projects/drupal-7.35.tar.gz && \
	tar -zxvf ./drupal*.tar.gz && \
	cp ./drupal*/*  . -r  && cp ./drupal*/.htaccess ./.htaccess && \
	cd ./sites/all && git clone https://github.com/CheckoutCrypto/site  && \
	cp ./site/* . -r && cp ./site/.git . -r && cp ./site/.gitmodules . -r && \
	cp ./site/.gitignore . -r && git submodule init && git submodule update   && \
	rm -r ./site  && rm -r /var/www/html/site/drupal* && \
	cd ../default && mkdir ./files  && \
	cp ./default.settings.php ./settings.php && \
	cd /var/www/html/ && \
	chmod 755 ./site -R && cd /var/www/html/site/sites/default && \
	chmod 777 ./settings.php && chmod 777 ./files && \
	cd ../all && cp ./bootup.sh /root/bootup.sh && rm Dockerfile && rm bootup.sh && \
    apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

EXPOSE 80
CMD ["/bin/bash", "/root/bootup.sh"]
