<?php




if($args) { //arguments received, build email

    //title
    $title = 'Coingateway.net '.$args['subject_tag'].' request is pending confirmation';

    //logo
    $logo = '<img style="width: 200px;display: block;  margin-left: auto;  margin-right: auto;" src="https://www.coingateway.net/drupal/sites/default/files/gatewaylogo_0.png">';

    //request info
    $recipient = "";
	if(isset($args['actions'])){
    $address = $args['coin_address'];
	}else{
	 $address = '';
	}
    $coin_amount = $args['coin_amount'];
    $coin_name = $args['coin_code'];
	if(isset($args['actions'])){
	if($args['action'] == 'send_funds'){
		$content = $args['mail_msg'];
		$recipient = $args['mail_recip_name'];
	}
	}else{
    	$content = 'A request which needs your confirmation has been created. To confirm the request please click this link or copy the address and visit the it in your browser.';
	}
    //Insert OTP URL
    $link = $args['otp_url'];

    $footer = $args['footer'];
    $footer_link = $args['footer_link'];
    $footer_link_text = $args['footer_link_text'];

} else {
    $content = 'An unknown error has occurred. Please try making your request again. If you received this message repeatedly please send an email to <a href="mailto:support@coingateway.net">support@coingateway.net</a> to inform the CoinGateway developers of this problem. We apologize for the inconvenience.';
}

?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xmlns="http://www.w3.org/1999/xhtml" style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; margin: 0; padding: 0;">
  <head>
        <meta name="viewport" content="width=device-width" />
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
        <title><?php echo $title ?></title>
    </head>
    <body style=" background-color: #f6f6f6; font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; -webkit-font-smoothing: antialiased; -webkit-text-size-adjust: none; width: 100% !important; height: 100%; margin: 0; padding: 0;">

    <!-- body -->
    <table class="body-wrap" style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; width: 100%; margin: 0; padding: 20px;">
        <tr style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; margin: 0; padding: 0;">
           <td style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; margin: 0; padding: 0;"></td>
           <td class="container" bgcolor="#FFFFFF" style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; display: block !important; max-width: 600px !important; clear: both !important; margin: 0 auto; padding: 20px; border: 10px solid #E8E8E8;">
            <div class="logo" style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; max-width: 600px; display: block; margin: 0 auto; padding: 0;">
                
				<?php echo $logo ?>
				<div style="font-family:'Helvetica Neue','Helvetica',Helvetica,Arial,sans-serif;font-size:1px;display:block;min-height:0;width:100%;max-height:0;line-height:0;clear:both;border-top-width:1px;border-top-color:#ccc;margin:8px auto;padding:0;border-style:solid none none"></div>
            </div>
            <!-- content -->
            <div class="content" style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; max-width: 600px; display: block; margin: 0 auto; padding: 0;">
                <table style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; width: 100%; margin: 0; padding: 0;">
                    <tr style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; margin: 0; padding: 0;">
                        <td style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; margin: 0; padding: 0;">
                            <h2 style="font-family:sans-serif;font-size: 11px;line-height: 25px;text-align: center;color: #FFFFFF;margin:0px 0 10px;border-radius:2px;text-transform:uppercase;margin-bottom:12.5px;margin-top:20px;font-weight:bolder;background: #A9A9A9;padding: 10px;"><?php echo $title; ?></h2>
							<h3 style="font-family: 'Helvetica Neue', Helvetica, Arial, 'Lucida Grande', sans-serif; font-size: 28px; line-height: 1.2; color: #000; font-weight: 200; margin: 0px 0 10px; padding: 0;"><?php echo $recipient; ?></h3>
                            <p style="font-family:'Helvetica Neue','Helvetica',Helvetica,Arial,sans-serif;font-size: 14px;line-height:1.6;font-weight:normal;margin:0 0 10px;padding: 10px;color: rgb(174, 168, 168);">
                                <?php echo $content; ?>
                            <p style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 14px; line-height: 1.6; font-weight: bold; margin: 0 0 10px; padding: 0;"><?php echo $coin_name.' '.$coin_amount; ?></p>
                            <p style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 14px; line-height: 1.6; font-weight: bold; margin: 0 0 10px; padding: 0;"><?php echo $address; ?></p>
                            </p>
                            <table style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; width: 100%; margin: 0; padding: 0;">
                                <tr style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; margin: 0; padding: 0;">
                                    <td class="padding" style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; margin: 0; padding: 10px 0;text-align:center;">
                                        <p style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 14px; line-height: 1.6; font-weight: normal; margin: 0 0 10px; padding: 0;">
                                            <a href="<?php echo $link; ?>" class="btn-primary" style="font-family:'Helvetica Neue','Helvetica',Helvetica,Arial,sans-serif;font-size:100%;line-height:2;color:#fff;text-decoration:none;font-weight:bold;text-align:center;display:inline-block;background-color:#195490;margin:0 10px 0 0;padding:10px;border:none;border-radius:4px;background:#195490;text-transform:uppercase;padding-left:25px;padding-right:25px;display: block;  margin-left: auto;  margin-right: auto;width: 140px;">Confirm request</a>
                                        </p>
                                    </td>
                                </tr>
                            </table>
                        </td>
                        </td>
                    </tr>
                </table>
            </div>
            <!-- /content -->
            </td>
            <td style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; margin: 0; padding: 0;"></td>
            </tr></table><!-- /body -->
            <!-- footer -->
            <table class="footer-wrap" style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; width: 100%; clear: both !important; margin: 0; padding: 0;">
                <tr style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; margin: 0; padding: 0;">
                    <td style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; margin: 0; padding: 0;"></td>
                    <td class="container" style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; display: block !important; max-width: 600px !important; clear: both !important; margin: 0 auto; padding: 0;">

                        <!-- content -->
                        <div class="content" style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; max-width: 600px; display: block; margin: 0 auto; padding: 0;">
                            <table style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; width: 100%; margin: 0; padding: 0;">
                                <tr style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; margin: 0; padding: 0;">
                                    <td align="center" style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; margin: 0; padding: 0;">
                                    <p style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 12px; line-height: 1.6; color: #666; font-weight: normal; margin: 0 0 10px; padding: 0;"><?php echo $footer; ?> <a href="<?php echo $footer_link; ?>" style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; color: #999; margin: 0; padding: 0;"><link style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; margin: 0; padding: 0;"><?php echo $footer_link_text; ?> </link></a>
                                        </p>
                                    </td>
                                </tr>
                            </table>
                        </div>
                    <!-- /content -->
                    </td>
                    <td style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 100%; line-height: 1.6; margin: 0; padding: 0;"></td>
                </tr>
        </table>
    <!-- /footer -->
    </body>
</html>
