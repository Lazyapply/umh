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