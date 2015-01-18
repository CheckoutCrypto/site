jQuery( document ).ready(function($) {
	var tab = 'spend';
	$('[name="tab"]').val(tab);  // set tab in form
	var coincode = 'BTC';
	var coinreceive = 'BTC';
	var spCoinsList = {};
	var exCoinsList = {};
	var spCoinsLength = 0;
	var exCoinsLength = 0;
	var cointype = 'BTC';					
	var drupalCoins = Drupal.settings.cgTrading.coins;
	var filter = '';
	var coin;
	var formatCoin;
	var prefix;
	var slideIndex = 0;
	var initSlick = false;

	for(key in drupalCoins)
	{	
		if(drupalCoins[key]["coin_code"] != "BTC"){ 
			spCoinsList[spCoinsLength] = drupalCoins[key]["coin_code"];
			spCoinsLength++;
		}
		exCoinsList[key] = drupalCoins[key]["coin_code"];
		exCoinsLength++;
	}
		/// START TABS - default hide the other tabs
		$("#exchangeTAB").hide();
		$("#fiatTAB").hide();

		$("#e1").select2();  // dropdown init
		$("#e2").select2();  // dropdown init
		$("#e3").select2();  // dropdown init

		$('h2#recText').html("ENTER " + coinreceive + " ADDRESS HERE");   /// Default Exchange Receive Coin 
		$("h2#input_coin").html('<h2 id="input_coin"> Input Coin: '+ coincode + '</h2>');  /// Default Exchange Input Coin 
	 	$('.form-item-coin-type').hide();  // amount_option radios
	 	$('.form-item-coin-type2').hide();  // amount_option radios
		$('[name="coin_amt_type"]').val('BTC');  // set default amt_type

 		$("#spendBtn").click(function(){
			tab = 'spend';	
			if(initSlick == true){
				var ival = 500;
				$(".center").slickPrev(); /// reinitalize the slick menu
				 setTimeout(function(){
							$(".center").slickNext(); /// reinitalize the slick menu
				 },ival); 
				initSlick = false;
			}
			$('[name="tab"]').val(tab);  // set tab in form
			$("#exchangeTAB").hide();
			$("#spendTAB").show();
	 		$('.form-item-coin-type2').hide();  // amount_option radios
			$('h2#recText').html("ENTER BTC ADDRESS HERE");   /// Default Exchange Receive Coin 
			$("#fiatTAB").hide();
			$("#inlineex").css( "background", "#144576" );
			$("#inlineexx").css( "background", "#11365A" );
			$("#inlineexxx").css( "background", "rgb(23, 23, 23)" );
		});
 		$("#exchangeBtn").click(function(){
			tab = 'exchange';
			if(initSlick == false){
				var ival = 500;
				$(".center_exchange_lt").slickPrev(); /// reinitalize the slick menu
				$(".center_ex").slickPrev(); /// reinitalize the slick menu
				 setTimeout(function(){
							$(".center_exchange_lt").slickNext(); /// reinitalize the slick menu
							$(".center_ex").slickNext(); /// reinitalize the slick menu
				 },ival); 
				initSlick = true;
			}
			$('[name="tab"]').val(tab);  // set tab in form
			$("#spendTAB").hide();
	 		$('.form-item-coin-type').hide();  // amount_option radios
			$("#exchangeTAB").show();
			$("#fiatTAB").hide();
			$("#inlineex").css( "background", "#11365A" );
			$("#inlineexx").css( "background", "#144576" );
			$("#inlineexxx").css( "background", "rgb(23, 23, 23)" );
		});
 		$("#fiatBtn").click(function(){
			tab = 'fiat';
			$('[name="tab"]').val(tab);  // set tab in form
			$("#exchangeTAB").hide();
			$("#spendTAB").hide();
			$("#fiatTAB").show();
			$("#inlineex").css( "background", "rgb(23, 23, 23)" );
			$("#inlineexx").css( "background", "rgb(23, 23, 23)" );
			$("#inlineexxx").css( "background", "rgba(29, 29, 29, 1)" );
		});
	/// END TABS
	//// Start Coin Select
		$(".coinLogo").click(function()
		{	
			coin = $(this).attr('id');
			if(tab == "exchange"){
				prefix = "_exchange"
				formatCoin = coin.replace(prefix, "");
				filter = coin.indexOf('_receive_exchange');

				if(filter == "-1"){
					filter = coin.indexOf(prefix);
					coincode = coin.substr(0, filter);
					setInputCoin(coincode);
					setAmtType(coincode);
					centerExchangeCoin(coincode, prefix);
				}else{
					prefix = "_receive_exchange"
					formatCoin = coin.replace(prefix, "");
					coinreceive = coin.substr(0, filter);
					setOutputCoin(coinreceive);
					centerExchangeCoinReceive(coinreceive, prefix);
				}

			}		
			else if(tab == "spend"){
				prefix = "_sell"
				formatCoin = coin.replace(prefix, "");        
				filter = coin.indexOf('_receive_spend');

				if(filter == "-1"){
					filter = coin.indexOf('_sell');
					coincode = coin.substr(0, filter);
					setInputCoin(coincode);
					setAmtType(coincode);
				}else{
					coinreceive = coin.substr(0, filter);
        			$('[name="coin_to"]').val(coinreceive);
				}
				centerSpendCoin(coincode, prefix);
			}	
			else if(tab == "fiat"){
				filter = coin.indexOf('_fiat');
				coincode = coin.substr(0, filter);
	 			$('.form-item-coin-type').show();
        			$('[name="coin_from"]').val(coincode);
			}	
		});  /// End Coin Select

		/// Radio selects
		/// SPEND amount type selections
		$('#edit-coin-type').click(function(){
			// alert('test');
			cointype = $("input[name='coin_type']:checked").val();
			if (cointype) {
			   if(cointype == "usd" || cointype.toLowerCase() == "usd"){
					document.getElementById('recAmount_spend').innerHTML = "USD";
				}else if(cointype == "coin"){
					document.getElementById('recAmount_spend').innerHTML = coincode;
					cointype = coincode;
				}else if(cointype == "btc" || cointype.toLowerCase() == "btc"){
					document.getElementById('recAmount_spend').innerHTML = "BITCOIN";
				}
				$('[name="coin_amt_type"]').val(cointype);
			}

		});
		/// EXCHANGE amount type selections
		$('#edit-coin-type2').click(function(){
			// alert('test');
			cointype = $("input[name='coin_type2']:checked").val();
			if (cointype) {
			   if(cointype == "usd" || cointype.toLowerCase() == "usd"){
					document.getElementById('recAmount_exchange').innerHTML = "USD";
				}else if(cointype == "coin"){
					document.getElementById('recAmount_exchange').innerHTML = coincode;
					cointype = coincode;
				}else if(cointype == "btc" || cointype.toLowerCase() == "btc"){
					document.getElementById('recAmount_exchange').innerHTML = "BITCOIN";
				}
				$('[name="coin_amt_type"]').val(cointype);
			}

		});
	//// Slick Coin Spinner Spend LEFT
   $('.center').slick({
        centerMode: true,
        infinite: true,
        centerPadding: '45px',
        slidesToShow: 13,
		initialSlide: 0,

		onAfterChange: function(slider,index) 
		{
			/// if tab == spend
			if(tab == "spend"){
				prefix = "_sell";
				coin = spCoinsList[index]+prefix;

				filter = coin.indexOf(prefix);
					coincode = coin.substr(0, filter);
					setInputCoin(coincode);
					setMiddleCoin(coincode, prefix, spCoinsLength, spCoinsList);
					setAmtType(coincode);
			}

		},
    });
	//// Slick Coin Spinner Exchange LEFT
   $('.center_exchange_lt').slick({
      centerMode: true,
      infinite: true,
      centerPadding: '45px',
      slidesToShow: 13,
		initialSlide: 0,

		onAfterChange: function(slider,index) 
		{
			if(tab == "exchange"){
					prefix = "_exchange";
					coin = exCoinsList[index]+prefix;
					filter = coin.indexOf(prefix);
					coincode = coin.substr(0, filter);
					setInputCoin(coincode);
					setAmtType(coincode);
					setMiddleCoin(coincode, prefix, exCoinsLength, exCoinsList);
			}
		}
	});
	//// Slick Coin Spinner Center
   $('.center_ex').slick({
        centerMode: true,
        infinite: true,
        centerPadding: '45px',
        slidesToShow: 2,
		
		onAfterChange: function(slider,index) 
		{
			if(tab == "exchange"){
				prefix = "_receive_exchange";
				coin = exCoinsList[index]+prefix;
				filter = coin.indexOf('_receive_exchange');
				coinreceive = coin.substr(0, filter);
				setOutputCoin(coinreceive);
				setMiddleCoin(coinreceive, prefix, exCoinsLength, exCoinsList);
			}
		}

	});


//// SPEND DROP MENU
  $("#e1").on("select2-selecting", function(e) {
		coincode = e.val;
		if(tab == "spend"){
				prefix = "_sell"
				setInputCoin(coincode);
				setAmtType(coincode);
				centerSpendCoin(coincode, prefix);
		}
	})
//// RECEIVE - EXCHANGE DROP MENU
  $("#e3").on("select2-selecting", function(e) {
		coinreceive = e.val;
		if(tab == "exchange"){	
					prefix = "_receive_exchange"
					setOutputCoin(coinreceive);
					setAmtType(coincode);
					centerExchangeCoinReceive(coinreceive);
			}
	})
//// EXCHANGE DROP MENU
 $("#e2").on("select2-selecting", function(e) {
		coincode = e.val;
		if(tab == "exchange"){
					prefix = "_exchange"
					setInputCoin(coincode);
					centerExchangeCoin(coincode, prefix);
			}
	})
//// Set IDs and var for INPUT
	function setInputCoin(coincode){
		if(tab == "spend"){
				$("#e1").select2("val", coincode);   ///  drop down
				$("h2#input_coin").html('<h2 id="input_coin"> Input Coin: '+ coincode + '</h2>');
	 			$('.form-item-coin-type').show();
		    	$('[name="coin_from"]').val(coincode);
		}else{  // exchange
				$("#e2").select2("val", coincode);   ///  drop down
        		$('[name="coin_from"]').val(coincode);
				$("h2#input_coin").html('<h2 id="input_coin"> Input Coin: '+ coincode + '</h2>');
	 			$('.form-item-coin-type2').show();
		    	$('[name="coin_from"]').val(coincode);
		}
	}
//// Set IDs and var for OUTPUT
	function setOutputCoin(coinreceive){
		if(tab == "exchange"){

				$("#e3").select2("val", coinreceive);   ///  drop down
        		$('[name="coin_to"]').val(coinreceive);
				$("h2#output_coin").html('<h2 id="output_coin"> Output Coin: '+ coinreceive + '</h2>');
				$('h2#recText').html("ENTER " + coinreceive + " ADDRESS HERE");
		}

	}
//// Center Spend Coin, Menu Left
	function centerSpendCoin(coincode, prefix){
			for(key in spCoinsList)
				{
					if(spCoinsList[key] == coincode)
					{
						$('.center').slickGoTo(key);

					}
				}
			setMiddleCoin(coincode, prefix, spCoinsLength, spCoinsList);
	}
//// Center Exchange Coin, Menu Left
	function centerExchangeCoin(coincode, prefix){
			for(key in exCoinsList)
				{
					if(exCoinsList[key] == coincode)
					{
						$('.center_exchange_lt').slickGoTo(key);
					}
				}
			setMiddleCoin(coincode, prefix, exCoinsLength, exCoinsList);
	}
//// Center Exchange Coin, Menu Right
	function centerExchangeCoinReceive(coincode, prefix){
			for(key in exCoinsList)
				{
					if(exCoinsList[key] == coincode)
					{
						$('.center_ex').slickGoTo(key);
					}
				}
			setMiddleCoin(coincode, prefix, exCoinsLength, exCoinsList);
	}
//// Center Set The CSS around the middle coin
	function setMiddleCoin(coin, prefix, coinsLength, coinsList){
				coin = coin + prefix;
						for (var i = 0; i <= coinsLength; i++) {
							formatCoin = coinsList[i]+prefix;
							if(formatCoin != coin)
							{
								$("#"+formatCoin).css( "-webkit-filter", "grayscale(100%)" );
			//					$("#"+formatCoin).css( "filter", "url(grayscale.svg#greyscale)" );
					
								$("#"+formatCoin).css( "-moz-transform", "scale(1)" );
								$("#"+formatCoin).css( "-ms-transform", "scale(1)" );
								$("#"+formatCoin).css( "-o-transform", "scale(1)" );
								$("#"+formatCoin).css( "-webkit-transform", "scale(1)" );
								$("#"+formatCoin).css( "transform", "scale(1)" );
							}
						}
			
				$("#"+coin).css( "-webkit-filter", "grayscale(0%)" );
			//	$("#"+coin).css( "filter", "none" );
			
				$("#"+coin).css( "-moz-transform", "scale(1.08)" );
				$("#"+coin).css( "-ms-transform", "scale(1.08)" );
				$("#"+coin).css( "-o-transform", "scale(1.08)" );
				$("#"+coin).css( "-webkit-transform", "scale(1.08)" );
				$("#"+coin).css( "transform", "scale(1.08)" );
	}
//// Set Default Coin Amt Send Type
	function setAmtType(coincode){
			if(tab == "spend"){
					$('label[for="edit-coin-type-coin"]').html('<input type="radio" id="edit-coin-type-coin" name="coin_type" value="coin" class="form-radio">' + coincode);/// set radio amt_type spend
			}else if(tab == "exchange"){
				$('label[for="edit-coin-type2-coin"]').html('<input type="radio" id="edit-coin-type2-coin" name="coin_type2" value="coin" class="form-radio">' + coincode);/// set radio amt_type spend
			}
	}
});


