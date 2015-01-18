jQuery(document).ready(function ($) {
//var $ = jQuery.noConflict();

$('#edit-submit').mousedown(function() {
  console.log('in2');
  $('#cc-wrapper input').val('test hello');
});

$("#edit-submit").submit(function(){
  console.log('in3');
})

console.log('in');
});
