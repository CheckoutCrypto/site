jQuery(document).ready(function ($) {

    var countdown;
    clearInterval(countdown);
    countdown = 0;
    
    var checker;
    clearInterval(checker);
    checker = 0;

    var expired_countdown_content = 'The time limit has been reached. Please close this window and submit your order to try again.';
    var iVal = 5000;
    var timeleft;
	var group;
	var days;
    var selCoin;
	var selAmount;
	var selValid;
        $('#ccStore_selected_coin').val('test');
	/////  Determine User's Chosen Coin's balance
	function ChargeOrNot(){
		group = (Drupal.settings.ccService.group);

 		$.ajax({
			type: 'POST',
			url: 'ccService/service/charge',
			dataType: 'json',
			data: 'type=balance&coin='+selCoin+'&grp='+group,
			  success:function(data) { 

				selMissing = data.missing;
				selValid = data.valid;
				selAmount = data.amount;
				selCoin = data.coin;
				days = data.days;

				console.log(selValid);
				if(selValid == true){

					$("#cc_service_payment_wrapper").fadeTo("slow", 1.00, function(){ //fade and toggle class
						 $(this).slideDown("slow");
						 $(this).toggleClass("uc_cc_show");
					});
					$('[name="uc_cc_payment_type"]').val("test");	
    	
					//DisplayCharge(selCoin, group);
	
				}else{
					$("#cc_payment_processing_wrapper").fadeTo("slow", 1.00, function(){ //fade and toggle class
						 $(this).slideDown("slow");
						 $(this).toggleClass("uc_cc_show");
					});  
					$("#edit-submit").hide();
					$("#cc_payment_information").show();

				} 
					//// Submit form + update timer
					checker = setInterval(submit_uc_cc_form, iVal);
					submit_uc_cc_form(); 
			  },
		  });
	}

	/////  Display the Service Charge Information
	function DisplayCharge(selCoin, group){
 		$.ajax({
			type: 'POST',
			url: 'ccService/service/charge',
			dataType: 'json',
			data: 'type=display_charge&coin='+selCoin+'&grp='+group,
			  success:function(data) { 

				console.log(data.valid);
			  },
		  });
	}
	/////  Make Final Service Charge
	function FinalCharge(){
 		$.ajax({
			type: 'POST',
			url: 'ccService/service/charge',
			dataType: 'json',
			data: 'type=final_charge&coin='+selCoin+'&grp='+group,
			  success:function(data) { 

				console.log(data.valid);
			  },
		  });
	}



    function timer() {
        timeleft = timeleft -1;
        if(timeleft <= 0)
        {
            console.log('time up');
            clearInterval(countdown);
            countdown = 0;
            clearInterval(checker);
            checker = 0;
            document.getElementById('cc-border').innerHTML = expired_countdown_content;

        }
        var minutes = Math.floor(timeleft/60);
        var seconds = timeleft%60;
        var seconds_string = "0" + seconds;
        seconds_string = seconds_string.substr(seconds_string.length - 2);
        if(  document.getElementById('cc_progress_timer') != null) {
			document.getElementById('cc_progress_timer').innerHTML = minutes + ":" + seconds_string;
		}else{
			timeleft = 0;	
		}
  }

  function submit_uc_cc_form() {
    if(typeof timeleft == 'undefined') {
      timeleft = (Drupal.settings.ccService.time_limit);

		console.log(group);
       countdown = setInterval(timer, 1000); //start timer
    } else {
        $('form#ccservice-form').submit();
    }
  }

    $("body").click(function(e) {

	///// condition: currency changes
      $("#cc_coin_reselect").mousedown(function() {
        console.log('reselect');
        clearInterval(checker); //reset timer
        checker = 0;
        document.getElementById('cc_payment_information').innerHTML = '<p>Please select another currency to continue checkout</p>'; 
		

        $("#cc_coin_select_wrapper").fadeTo("slow", 1.00, function(){ //fade and toggle class
             $(this).slideDown("slow");
             $(this).toggleClass("uc_cc_hide");
        });

    	 $("#cc_service_payment_wrapper").fadeTo("slow", 1.00, function(){ //fade and toggle class
             $(this).slideUp("slow");
             $(this).toggleClass("uc_cc_hide");
        });

        $("#cc_payment_processing_wrapper").fadeTo("slow", 1.00, function(){ //fade and toggle class
             $(this).slideUp("slow");
             $(this).toggleClass("uc_cc_show");
        });

      });

	///// condition: coin is selected
    if($(e.target).parent().is('#cc_coin_select_wrapper')) {
		selCoin = e.target.id;
        $('[name="ccStore_selected_coin"]').val(e.target.id);
       $("#cc_coin_select_wrapper").fadeTo("slow", 1.00, function(){ //fade and toggle class
             $(this).slideUp("slow");
             $(this).toggleClass("uc_cc_hidden");
        });  
		ChargeOrNot();
    }
	
  		$("#cc_coin_charge").mousedown(function() {
				FinalCharge();
			});

	});  /// end body

});
