jQuery( document ).ready(function($) {

	var wallClick = 0;
	var tranClick = 0;
	
	$('[name="wall_address_col"]').hide();
	$('th#wall_address_head').hide();
	$('[name="trans_receiver_col"]').hide();
	$('th#trans_receiver_head').hide();

	$("#submit_wall").click(function(){
		if(wallClick == 0){
			$('[name="wall_address_col"]').show();
			$('th#wall_address_head').show();
			wallClick = 1;		
			$('#rightblock').attr( 'style', 'margin-left: 10px');  /// move right block a bit when clicked
		}else if(wallClick == 1){
			$('[name="wall_address_col"]').hide();
			$('th#wall_address_head').hide();
			wallClick = 0;
			$('#rightblock').attr( 'style', 'margin-left: 0px');  /// move right block a bit when clicked
		}
	});
	$("#submit_trans").click(function(){
		if(tranClick == 0){
			$('[name="trans_receiver_col"]').show();
			$('th#trans_receiver_head').show();
			 tranClick = 1;		
		}else if(tranClick == 1){
			$('[name="trans_receiver_col"]').hide();
			$('th#trans_receiver_head').hide();
			tranClick = 0;
		}
	});
});
