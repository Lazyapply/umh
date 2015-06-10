DEBUG_MODE_ON = 1;




$(document).ready(function(){
	//modallogin
	$('.modal-trigger').leanModal();


});

function o(valor){ (DEBUG_MODE_ON) ? console.log(valor) : false; }

//----- START AJAX ------------------------------------------------


function getAjax(){

	var obj;

	if(window.XMLHttpRequest){
		obj = new XMLHttpRequest();
	}
	else{
		try{
			obj = new ActiveXObject("Microsoft.XMLHTTP");
		}
		catch (e){
			alert("Este navegador no es compatible con AJAX");
		}
	}

	return obj;
}

var oXML = getAjax();

function addAjaxData(target, data){
	document.getElementById(target).innerHTML = data;
}

function getAjaxHandler(target){
	switch(oXML.readyState){

		case 2:
		case 3:
			addAjaxData(target, '<img id="preloader" class="loader-little centered" src="/img/preloader.gif" alt="loader"/>');
		break;

		case 4:
			addAjaxData(target, oXML.responseText);
			
		break;
	}

}

//----- END AJAX ------------------------------------------------