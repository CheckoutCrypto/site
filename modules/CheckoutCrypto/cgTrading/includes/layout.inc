<?php

///------------------
/// INFO (title, description) BEGINS:
/// ----------------
function displayTradeContainer(){
	/// container wrapper open
	 $form['container_wrap_open'] = array('#markup' => t('<div class="container">'));
	/// container Title and description
	 $form['container_title'] = array('#markup' => t('<div id="headText" class="test55" style="margin-top:-10px;">
            </div>'));
	/// Buttons merchant options
	 $form['container_options'] = array('#markup' => t('<a type="button" class="btn btn-success getcoins" id="home_button" href="#" style="display:none;    
	">Start Spending</a>

	<a type="button" class="btn btn-success getcoins" id="home_button_merch" href="#" style="   display:none;  
	">Merchants</a>'));
	/// Tabs - header
	$form['container_tabs'] = array('#markup' => t('	<ul id="buttonTop" class="nothing" style="margin-left:5;">
			<li id="inlineex" style="background:#144576;"><a href="#" id="spendBtn">SPEND</a></li>
			<li id="inlineexx"><a href="#" id="exchangeBtn">EXCHANGE</a></li>
			
				</ul> '));
	$form['container_spinner'] = array('#markup' => t('<div id="spinner" style="display:none;">
				<center>
						<svg class="spinner" width="65px" height="65px" viewBox="0 0 66 66" xmlns="http://www.w3.org/2000/svg">
							<circle class="path" fill="none" stroke-width="6" stroke-linecap="round" cx="33" cy="33" r="30"></circle>
						</svg>
				</center>
			</div>'));
	/// container wrapper open
	 $form['container_wrap_close'] = array('#markup' => t('</div>'));
	return $form;
}

///------------------
/// SPENDTAB BEGIN:
/// ----------------
function displaySpendTab($coins){
	$form['container_spendtab'] = array('#markup' => t('
	
		
	<div id="spendTAB">
        <div id="coin_chooser" class="row" style="margin-top: 1px; margin-bottom: 60px;">
		<div class="col-lg-6" id="coins">
        <center>
        <h2 id="choose_title" style=" padding-top: 15px;font-size: 18px;font-weight: 400;margin-bottom: 12.5px;">CHOOSE THE COIN YOU WANT TO <b style="font-weight: 700;">SPEND</b> BELOW</h2>
		
		<section id="features" class="blue">
			<div class="content">
				<div class="slider center">
					
				'));
	$count = 0;
	/// Add our dynamic coin box
	foreach($coins as $coin){  
		if($coin['coin_code'] != "BTC"){  // remove BTC from SPEND coins
			$form['coinbox_1_'.$count] = array('#markup' => 	t('<div><h3><img class="coinLogo" id="'.$coin['coin_code'].'_sell" src="'.$coin['coin_image'].'"></h3></div>'));
			$count++;
		}
	}	
	$form['coinbox_btm'] = array('#markup' => t('</div>
			
		</section>
		</p>	
		
	<div id="inpout" style="display:none;margin-top: 20px;">
		<h2 id="input_coin" style="display:inline;font-size: 16px;padding-right: 15px;font-weight: 400;letter-spacing: 1px;color: rgb(163, 163, 163);"> INPUT COIN: </h2>
		<h2 id="output_coin" style="display:inline;font-size: 16px;padding-right: 15px;font-weight: 400;letter-spacing: 1px;color: rgb(163, 163, 163);"> 
			OUTPUT COIN: <b style="font-weight:400; color:#f7931a;">BITCOIN</b>
		</h2>
	</div>'));
	
	$form['coin_pop_box'] = array('#markup' => t('<select style="width:300px" id="e1">'));
	$count = 0;
	/// Add our dynamic coin box
	foreach($coins as $coin){  
		if($coin['coin_code'] != "BTC"){  // remove BTC from SPEND coins
			$form['coin_pop_box_'.$count] = array('#markup' => 	t('<option value="'.$coin['coin_code'].'">'.$coin['coin_name'].'</option>'));
			$count++;
		}
	}	
	$form['coin_pop_box_btm'] = array('#markup' => t('</select>'));
	
	$options = array(
	  'btc' => t('BTC'),
	  'coin' => t('Coin'), 
	  'usd' => t('USD'),
	);

	# the drupal checkboxes form field definition
	$form['coin_type'] = array(
	  '#prefix' => '<div id="occalculator">',
	  '#title' => t('(Optional) Conversion Calculator'),
	  '#type' => 'radios',
	  '#description' => t('Amount set in the following currency.'),
	  '#default_value' => t('btc'),
	  '#options' => $options,
	);

	$form['coinbox_btm_1_2']  = array('#markup' => t('</center></div>
	<div class="col-lg-6" id="bgenter">
	<center>'));

	$form['coinbox_btm2_5'] = array('#markup' => t('<div id="recipientsBox">
						<h2 style="font-size: 20px;font-weight: 300; color:white;" class="hometext" id="recText" >
							ENTER RECIPIENTS <b style="color: #4C7AA9;font-size: 20px; font-weight:700;">BITCOIN</b> ADDRESS HERE
						</h2>
						<div class="form-group"> '));
	/// INPUT - Withdraw Address
	$form['coin_address_spend'] = array(
		'#type' => 'textfield',
		'#title' => t('Coin Address'),
		'#title_display' => 'invisible',
		'#required' => false,
		'#default_value' => '',
		'#attributes' => array('id' => 'customer_address', 'placeholder' => 'Coin Address e.g. 1CDaN8NbNDjdbKtFdKiVh2MM9Gky6efncE', 'name' => 'address_spend', 'title' => 'Valid characters are a-z,0-9', 'type' => 'name', 'pattern' => '[a-zA-Z0-9]+', 'required' => 'required' ),
   );

	$form['coinbox_btm3'] = array('#markup' => t('</div></div>
		<div style="margin-top:30px">
        <h2 style="font-size: 20px;font-weight: 300;" class="hometext" id="">
			ENTER <b style="color: rgba(141, 198, 63, 1);font-size: 20px; font-weight:700;">'));
	
	$form['coin_amount_title'] =  array('#markup' => t('<div id="recAmount_spend">BITCOIN </div>'));

	$form['coin_amount_title_btm'] =  array('#markup' => t('</b> AMOUNT HERE</h2>
        <div id="amount_tab" class="form-group">'));
	/// INPUT - Coin Amount
	$form['coin_amt_spend'] = array(
		'#type' => 'textfield',
		'#title' => t('Coin Amount'),
		'#title_display' => 'invisible',
		'#required' => false,
'#default_value' => '',
		'#attributes' => array('id' => 'customer_amount', 'placeholder' => 'Amount here (e.g. 0.36)', 'name' => 'amount_spend',),  //  'title' => 'Valid characters are 0-9', 'pattern' => '[0-9]+([\.|,][0-9]+)?', 'step' => '0.01', 'required' => 'required'

	);
    $form['coinbox_btm4'] = array('#markup' => t('</div>'));
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('PAY NOW'),
		'#attributes' => array('id' => 'payButton', 'class' => array('ctools-use-modal')), 

	); 

   $form['coinbox_btm5'] = array('#markup' => t('</div></center></div></div></div>'));
	return $form;
}

///------------------
/// EXCHANGETAB BEGIN:
/// ----------------
function displayExchangeTab($coins){
       //Define the block content.
        $form['exchange_top'] = array('#markup' => t('<div id="exchangeTAB">
       <div id="coin_chooser" class="row" style="margin-top: 1px; margin-bottom: 60px;">
		<div class="col-lg-6" id="coins">
		<center>
		<h2 id="choose_title" style=" padding-top: 15px;font-size: 18px;font-weight: 400;margin-bottom: 12.5px;">CHOOSE THE COIN YOU WANT TO <b style="font-weight: 700;">EXCHANGE</b> BELOW</h2>
		
		<section id="features" class="blue">
			<div class="content">
				<div class="slider center_exchange_lt">'));

	$count = 0;
	/// Add our dynamic coin box
	foreach($coins as $coin){  
		$form['exbox_1_'.$count] = array('#markup' => 	t('<div><h3><img class="coinLogo" id="'.$coin['coin_code'].'_exchange" src="'.$coin['coin_image'].'"></h3></div>'));
		$count++;
	}	

	$form['exbox_btm'] = array('#markup' => t('</div></section></p>	
		<div id="inpout" style="display:none;margin-top: 20px;">
		<h2 id="input_coin" style="display:inline;font-size: 16px;padding-right: 15px;font-weight: 400;letter-spacing: 1px;color: rgb(163, 163, 163);"> INPUT COIN: </h2>
		<h2 id="output_coin" style="display:inline;font-size: 16px;padding-right: 15px;font-weight: 400;letter-spacing: 1px;color: rgb(163, 163, 163);"> 
			OUTPUT COIN: <b style="font-weight:400; color:#f7931a;">BITCOIN</b></h2>
	</div>'));
	
	$form['coin_pop_box_exc'] = array('#markup' => t('<select style="width:300px" id="e2">'));
	$count = 0;
	/// Add our dynamic coin box
	foreach($coins as $coin){  
		$form['coin_pop_box_exc_'.$count] = array('#markup' => 	t('<option value="'.$coin['coin_code'].'">'.$coin['coin_name'].'</option>'));
		$count++;
	}	
	$form['coin_pop_box_exc_btm'] = array('#markup' => t('</select>'));
	
	$form['exchange_scroller_btm'] = array('#markup' => t('
		<div id="inpout">
			<h2 id="input_coin"> Input Coin: </h2>
			<h2 id="output_coin"> Output Coin: <b>Bitcoin</b></h2>
		</div>'));
	$options = array(
	  'btc' => t('BTC'),
	  'coin' => t('Coin'), 
	  'usd' => t('USD'),
	);

	# the drupal checkboxes form field definition
	$form['coin_type2'] = array(
	  '#prefix' => '<div id="occalculator">',
	  '#title' => t('(Optional) Conversion Calculator'),
	  '#type' => 'radios',
	  '#description' => t('Amount set in the following currency.'),
	  '#default_value' => t('btc'),
	  '#options' => $options,
	);

	$form['exchange_scroller_btm_2'] = array('#markup' => t('	</center>
	</div>
		<div class="col-lg-6" id="bgenter">
		<center>
		<section id="features" class="blue">
			<div class="content">
				<div class="slider center_ex">
					
				'));
	$count = 0;
	/// Add our dynamic coin box
	foreach($coins as $coin){  
		$form['exchange_scroller_btm_2_'.$count] = array('#markup' => 	t('<div><h3><img class="coinLogo" id="'.$coin['coin_code'].'_receive_exchange" src="'.$coin['coin_image'].'"></h3></div>'));
		$count++;
	}

    $form['exchange_scroller_btm_3'] = array('#markup' => t('</div></div></section>'));


	$form['ex_coinbox_btm'] =  array('#markup' => t('</p>'));
	
	$form['ex_search_top'] = array('#markup' => t('<select style="width:300px" id="e3">'));
	$count = 0;
	/// Add our dynamic coin box
	foreach($coins as $coin){  
		$form['ex_search_top_'.$count] = array('#markup' => 	t('<option value="'.$coin['coin_code'].'">'.$coin['coin_name'].'</option>'));
		$count++;
	}	
	$form['ex_search_btm'] = array('#markup' => t('</select>'));
	

		
	$form['exchange_scroll_btm'] = array('#markup' => t('	
		<div id="recipientsBox">
		<h2 class="hometext" id="recText">ENTER <b>OUTPUT COIN</b> ADDRESS HERE</h2>					
		<div class="form-group">'));
	/// INPUT - Withdraw Address
	$form['coin_address_exchange'] = array(
		'#type' => 'textfield',
		'#title' => t('Coin Address'),
		'#title_display' => 'invisible',
		'#required' => false,
		'#value' => '',
		'#attributes' => array('id' => 'customer_address', 'placeholder' => 'Coin Address e.g. 1CDaN8NbNDjdbKtFdKiVh2MM9Gky6efncE', 'name' => 'address_exchange',) );  //  'title' => 'Valid characters are a-z,0-9', 'type' => 'name', 'pattern' => '[a-zA-Z0-9]+', 'required' => 'required' ),

	$form['coinbox_btm3'] = array('#markup' => t('</div></div>
		<div style="margin-top:30px">
		 <h2 style="font-size: 20px;font-weight: 300;" class="hometext" id="">ENTER <b style="color: rgba(141, 198, 63, 1);font-size: 20px; font-weight:700;">'));

	$form['coin_amount_title2'] =  array('#markup' => t('<div id="recAmount_exchange">BITCOIN</div>'));

	$form['coin_amount_title_btm2'] =  array('#markup' => t('	</b> AMOUNT HERE
		</h2>
        <div id="amount_tab" class="form-group">'));
	/// INPUT - Coin Amount
	$form['coin_amt_exchange'] = array(
		'#type' => 'textfield',
		'#title' => t('Coin Amount'),
		'#title_display' => 'invisible',
		'#required' => false,
'#default_value' => '',
		'#attributes' => array('id' => 'customer_amount', 'placeholder' => 'Amount here (e.g. 0.36)', 'name' => 'amount_exchange', ),  // 'title' => 'Valid characters are 0-9', 'pattern' => '[0-9]+([\.|,][0-9]+)?', 'step' => '0.01', 'required' => 'required'
	);
  	$form['submit_exchange'] = array(
		'#type' => 'submit',
		'#value' => t('PAY NOW'),
		'#attributes' => array('id' => 'payButton', 'class' => array('ctools-use-modal')), 
	);  
    $form['exchange_close']  = array('#markup' => t(' </div>
          </div>
		</center>
       </div>
	</div><div></div></div>'));

	return $form;
}

///------------------
/// FIATTAB BEGIN:
/// ----------------
function displayFiatTab($coins){

	$form['fiat_top'] = array('#markup' => 	t('<div id="fiatTAB">
		        <div id="coin_chooser" class="row">
					<div class="col-lg-6" id="coins">
		                <center>
	<h2 id="choose_title">Choose the coin you want to <b>spend</b> below</h2>
							<div id="coinBox">
	<p id="paraspace">'));
	$count = 0;
	/// Add our dynamic coin box
	foreach($coins as $coin){  
		$form['fiat_coinbox_1_'.$count] = array('#markup' => 	t('<img class="coinLogo" id="'.$coin['coin_code'].'_fiat" src="'.$coin['coin_image'].'">'));
		$count++;
	}	
	$count = 0;
	foreach($coins as $coin){  
		$form['fiat_coinbox_2_'.$count] = array('#markup' => t('<img class="coinLogo"  id="'.$coin['coin_code'].'_fiat" src="'.$coin['coin_image'].'">'));
		$count++;
	}

	$form['fiat_coinbox_beneath'] = array('#markup' => t('</p></div><div id="scrolls">'));
	/// Scroll Buttons - Left and Right
	$form['fiat_scrollL_1'] = array(
		'#type' => 'submit',
		'#value' => t('<'),
		'#attributes' => array('id' => 'scrollL', 'onclick' => 'return (false);'),
"#executes_submit_callback" => FALSE,
	  );

	$form['fiat_scrollR_1'] = array(
		'#type' => 'submit',
		'#value' => t('>'),
		'#attributes' => array('id' => 'scrollR', 'onclick' => 'return (false);'),
"#executes_submit_callback" => FALSE,
	  );
	$form['fiat_coinbox_beneath_2'] = array('#markup' => t('</div>
						<h5 id="clickright"> CLICK RIGHT TO LOAD MORE COINS... </h5>
											
						<div id="inpout">
							<h2 id="input_coin"> Input Coin: </h2>
							<h2 id="output_coin"> Output Coin: <b>Bitcoin</b></h2>
						</div>
						
	<div id="usdTab3" style="display:none;margin-top: 20px;float: left;margin-left: 60px;">
			<input type="checkbox" id="checkbox-1-1" class="regular-checkbox" /><label for="checkbox-1-1"></label>
			<h2 style="display:inline;color: rgb(122, 122, 122); padding-top: 10px;font-size: 15px;font-weight: 300;">Enter amount in <b id="usd9">USD</b><b style="font-weight:400; font-size:10px;"> ( OPTIONAL ) </b></h2>
	</div>
	<div id="coinTab3" style="display:none;margin-top: 10px;float: left;margin-left: 60px;">
			<input type="checkbox" id="checkbox-1-2" class="regular-checkbox" /><label for="checkbox-1-2"></label>
			<h2 style="display:inline;color: rgb(122, 122, 122); padding-top: 10px;font-size: 15px;font-weight: 300;">Enter your own coin <b id="amount9">AMOUNT</b><b style="font-weight:400; font-size:10px;"> ( OPTIONAL ) </b></h2>
	</div>
					</center>
                </div>

                <div class="col-lg-6" id="bgenter">
				<center>
					<h2 id="coinboxheader">Choose the coin you want <b>IN RETURN</b> below</h2>
										
						<div id="coinBoxSell">
							<img style="display:none;" class="coinLogo" onclick="coinSelectSell("usd")" id="usdSell" src="assets/img/usd.png">
							<img style="display:none;" class="coinLogo" onclick="coinSelectSell("ukash")" id="ukashSell" src="assets/img/ukash.png">
						</div>
						<div id="scrollsSell" style="display:none">'));
	$form['fiat_scrollL_2'] = array(
		'#type' => 'submit',
		'#value' => t('<'),
		'#attributes' => array('id' => 'scrollL', 'onclick' => 'return (false);'),
"#executes_submit_callback" => FALSE,
	  );

	$form['fiat_scrollR_2'] = array(
		'#type' => 'submit',
		'#value' => t('>'),
		'#attributes' => array('id' => 'scrollR', 'onclick' => 'return (false);'),
		"#executes_submit_callback" => FALSE,
	  );
	$form['fiat_coinbox_end'] = array('#markup' => t('</div></center><div style="margin-top:30px">'));
  	$form['submit_fiat'] = array(
		'#type' => 'submit',
		'#value' => t('PAY NOW'),
		'#attributes' => array('id' => 'payButton','class' => array('ctools-use-modal') ), 
	); 
    $form['fiat_close'] = array('#markup' => t('</div></div></div></div>'));
	return $form;
}
