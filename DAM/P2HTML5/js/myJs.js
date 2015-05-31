var DEBUG_MODE_ON = 1;
var iFrAudioPlayer 	= iFrAudioPlayer 	= document.getElementById("iAudioPlayer");
var iFrVideoPlayer 	= document.getElementById('iVideoPlayer');
// var aux 			= setInterval(function(){ini()},200);

function ini(){
	
	 resizeIframe(iFrAudioPlayer);
	 // resizeIframe(iFrVideoPlayer);
	 // o("cambio");
}

function resizeIframe(obj){
	obj.style.height = (obj.contentWindow.document.body.scrollHeight) + 'px';
}

function o(valor){ (DEBUG_MODE_ON) ? console.log(valor) : false; }

function CanvasDrawRectangle(){
	
}