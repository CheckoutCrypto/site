jQuery( document ).ready(function($) {

console.log('test');
function copyToClipboard(text) {
    window.prompt("Copy to clipboard: Ctrl+C, Enter", text);
}
 
$('#edit-payment-address').click(function() {
    copyToClipboard('test')
});

});
