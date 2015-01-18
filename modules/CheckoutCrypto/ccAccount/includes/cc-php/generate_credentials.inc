<?php

Class ccCredentials {

  function generateAPI() {
    $randtime = time();
    $salt = bin2hex(openssl_random_pseudo_bytes(32));
    $password = sha1($salt.$randtime);
    return $password;
  }

  function generateWalletName() {
    $str = md5(time());
    return substr($str, 0, 8);
  }

}

?>
