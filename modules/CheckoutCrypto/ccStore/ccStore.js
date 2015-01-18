jQuery(document).ready(function ($) {

    var countdown;
    clearInterval(countdown);
    countdown = 0;
    
    var checker;
    clearInterval(checker);
    checker = 0;

    var timeleft;
    var expired_countdown_content = 'The time limit has been reached. Please close this window and submit your order to try again.';
    var iVal = 5000;
    var selCoin;

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
      timeleft = (Drupal.settings.ccStore.time_limit);
       countdown = setInterval(timer, 1000); //start timer
    } else {
        $('form#ccstore-form').submit();
    }
  }

    $("body").click(function(e) {


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

    if($(e.target).parent().is('#cc_coin_select_wrapper')) {
		selCoin = e.target.id;
		if(selCoin == "cc_coin_btc"){
			iVal = iVal * 2;
			timeleft = timeleft * 2;
		}

        $('[name="ccStore_selected_coin"]').val(e.target.id);
       $("#cc_coin_select_wrapper").fadeTo("slow", 1.00, function(){ //fade and toggle class
             $(this).slideUp("slow");
             $(this).toggleClass("uc_cc_hidden");
        });  
        
       $("#cc_payment_processing_wrapper").fadeTo("slow", 1.00, function(){ //fade and toggle class
             $(this).slideDown("slow");
             $(this).toggleClass("uc_cc_show");
         }); 
		$('#edit-submit--2').hide();
        checker = setInterval(submit_uc_cc_form, iVal);
        submit_uc_cc_form();
    }

	});  /// end body

});
