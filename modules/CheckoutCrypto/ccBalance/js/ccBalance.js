jQuery( document ).ready(function($) {

	function checkBalance() {
     	 var txfee = $('#coin_txfee').val();
		var fee = $('#coin_fee').val();
		var coinbalance = $('#total_balance').val();
		var amount = $('#edit-withdraw-amount').val();
		var address = $('#edit-withdraw-address').val();


		var TotalFee = parseFloat((amount * fee)/ (100));
		var TotalSub = parseFloat(TotalFee) + (parseFloat(txfee) * 2) + parseFloat(amount);
		var Remain = parseFloat(coinbalance) - parseFloat(TotalSub);

		/* console.log( coinbalance);
		console.log( txfee);
		console.log( fee);

		console.log( TotalFee);
		console.log( TotalSub);
		console.log( Remain); */


		$('.cc-withdraw-fee').text(parseFloat(TotalFee));
      $('.cc-withdraw-tx-fee').text(parseFloat(txfee)*2);

		if(Remain >= 0){
  			 $('.cc-withdraw-balance').text(parseFloat(Remain));
		}else{
			var BalanceFixed = parseFloat(amount) - parseFloat( Remain) * -1;
			console.log( Remain);
			$('#edit-withdraw-amount').val(parseFloat(BalanceFixed));
  			
		 $('.cc-withdraw-balance').text("remaining balance " +((parseFloat(Remain)*-1) -(parseFloat(TotalFee) + parseFloat(txfee)))) ;
		} 
		/*$.getScript('sites/all/modules/CheckoutCrypto/ccBalance/js/index.js', function() {
			validate(address, '37');
		}); 
$.getScript('sites/all/modules/CheckoutCrypto/ccBalance/js/index.js', function(){
var result = validate(address, '37');
console.log(result);
}); as 
 /*var newscript = document.createElement('script');
     newscript.type = 'text/javascript';
     newscript.async = true;
     newscript.src = 'sites/all/modules/CheckoutCrypto/ccBalance/js/index.js';
  (document.getElementsByTagName('head')[0]||document.getElementsByTagName('body')[0]).appendChild(newscript);
 		
		newscript.onLoad = function () {
		var result  = validate(address, '37');
			};
*/
	}  
$('#POT-modal-link a').mousedown(function() { //TODO
    setTimeout(function() {
        $('#coin_balance').mousedown(function() {
          $('#edit-withdraw-amount').val($('#coin_balance').text());

		  checkBalance();
        });
    }, 1000); //TODO
});

function hasHtml5Validation () {
 return typeof document.createElement('input').checkValidity === 'function';
}

if (hasHtml5Validation()) {
    $('form#withdraw-form').submit(function (e) {

   if (!this.checkValidity()) {
     // Prevent default stops form from firing
     e.preventDefault();
     $(this).addClass('invalid');
     $('#status').html('invalid');
   } else {
     $(this).removeClass('invalid');
     $('#status').html('submitted');
   }
 });
$('form#autopay-form').submit(function (e) {

   if (!this.checkValidity()) {
     // Prevent default stops form from firing
     e.preventDefault();
     $(this).addClass('invalid');
     $('#status').html('invalid');
   } else {
     $(this).removeClass('invalid');
     $('#status').html('submitted');
   }
 });
}
});
