jQuery( document ).ready(function($) {

function hasHtml5Validation () {
 return typeof document.createElement('input').checkValidity === 'function';
}

if (hasHtml5Validation()) {
    $('#trading-form').submit(function (e) {
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
