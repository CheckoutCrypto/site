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
