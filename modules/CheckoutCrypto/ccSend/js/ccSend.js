jQuery( document ).ready(function($) {


function hasHtml5Validation () {
 return typeof document.createElement('input').checkValidity === 'function';
}

if (hasHtml5Validation()) {
    $('form#ccsend-funds').submit(function (e) {

   if (!this.checkValidity()) {
     // Prevent default stops form from firing
     e.preventDefault();
     $(this).addClass('invalid');
     $('#status').html('invalid');
	console.log('test');
   } else {
     $(this).removeClass('invalid');
     $('#status').html('submitted');
   }
 });

}

});
