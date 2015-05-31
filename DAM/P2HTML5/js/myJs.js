var DEBUG_MODE_ON = 1;
var iFrAudioPlayer 	= iFrAudioPlayer 	= document.getElementById("iAudioPlayer");
var iFrVideoPlayer 	= document.getElementById('iVideoPlayer');
var canvas 			= document.getElementById('myCanvas');
// var aux 			= setInterval(function(){ini()},200);

function ini(){
	
	 resizeIframe(iFrAudioPlayer);
	 drawCanvas(canvas);
	 // resizeIframe(iFrVideoPlayer);
	 // o("cambio");
}

function resizeIframe(obj){
	obj.style.height = (obj.contentWindow.document.body.scrollHeight) + 'px';
}

function o(valor){ (DEBUG_MODE_ON) ? console.log(valor) : false; }

function CanvasDrawRectangle(objcanvas, x, y, height, width){
	var ctx = objcanvas.getContext("2d");
	ctx.rect(x, y, width, height);
	ctx.strokeStyle = '#ff00ff';
	ctx.stroke();
}

function CanvasDrawLine(objcanvas, sx, sy, ex, ey){
	var ctx = objcanvas.getContext("2d");
	ctx.moveTo(sx,sy);
	ctx.lineTo(ex,ey);
	ctx.strokeStyle = '#ffaf00';
	ctx.stroke();
}

function drawCanvas(objcanvas){
	CanvasDrawRectangle(objcanvas, 5, 5, 50, 80);
	CanvasDrawLine(objcanvas, 0, 60, 100, 60);
}