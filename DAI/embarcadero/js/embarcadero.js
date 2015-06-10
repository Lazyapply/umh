$(document).ready(function(){
	//modallogin
	$('.modal-trigger').leanModal();


	 //start footer
		var bodyHeight = $("body").height();
		var vwptHeight = $(window).height();
		if (vwptHeight > bodyHeight) {
		$("footer#colophon").css("position","absolute").css("bottom",0).css("width","100%");
		}
	//end footer

});


function employeeAdd(){
	console.log("Entrando");
	var pattern = '^id_+.[A-Z]{2,4}$'; 
	$('input').each(function(){
     if( $(this).attr('id').match(pattern) ) {
          console.log("encontrado");
     }
  });
}