jQuery( document ).ready(function($) {

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
            document.getElementById('popup_wrapper').innerHTML = expired_countdown_content;

        }
        var minutes = Math.floor(timeleft/60);
        var seconds = timeleft%60;
        var seconds_string = "0" + seconds;
        seconds_string = seconds_string.substr(seconds_string.length - 2);
        if(  document.getElementById('popup_content_foot') != null) {
			document.getElementById('popup_content_foot').innerHTML = minutes + ":" + seconds_string;
		}else{
			 timeleft = 0;	
			document.getElementById('popup_content_foot').innerHTML = 'timer expired';
		}
  }

  function submit_uc_cc_form() {
    if(typeof timeleft == 'undefined') {
      timeleft = (Drupal.settings.cgTrading.time_limit);
       countdown = setInterval(timer, 1000); //start timer
    } else {
        $('form#popuptheme').submit(); 
		}
	}


	function copyToClipboard(text) {
		window.prompt("Copy to clipboard: Ctrl+C, Enter", text);
	}

	$('.form-item-payment-address').click(function() {
		console.log('address copied');
		copyToClipboard('testing')
	});

        $('[name="trade_queue"]').val('1');
        checker = setInterval(submit_uc_cc_form, iVal);
	     submit_uc_cc_form();
});
