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

function CanvasDrawRectangle(objcanvas, x, y, height, width, shadow){
	var ctx = objcanvas.getContext("2d");

	if(shadow == 1){
		ctx.shadowOffsetX = 5;
		ctx.shadowOffsetY = 5;
		ctx.shadowBlur = 10;
		ctx.shadowColor = "Brown";
		ctx.fillStyle = "Gold";
		ctx.fillRect(x, y, width, height);
	}
	else{
		ctx.rect(x, y, width, height);
		ctx.strokeStyle = '#ff00ff';
		ctx.stroke();
	}
	o(shadow);
}




function CanvasDrawArc(objCanvas, cx, cy, r, sa, ea){
	var ctx = objCanvas.getContext("2d");
	ctx.beginPath();
	ctx.arc(cx, cy, r, sa, ea);
	ctx.strokeStyle = '#000';
	ctx.stroke();
}

function CanvasDrawLinearGradient(objCanvas, x1, y1, x2, y2, color1, color2){
	var ctx = objCanvas.getContext("2d");
	var grd = ctx.createLinearGradient(0,0,170,0);

	grd.addColorStop(0,color1);
	grd.addColorStop(1,color2);

	ctx.fillStyle = grd;
	ctx.fillRect(x1,y1,x2,y2);
}

function CanvasDrawLine(objcanvas, sx, sy, ex, ey){
	var ctx = objcanvas.getContext("2d");
	ctx.moveTo(sx,sy);
	ctx.lineTo(ex,ey);
	ctx.strokeStyle = '#ffaf00';
	ctx.stroke();
}


function CanvasDrawText(objcanvas, x, y, text, font){

	var ctx = objcanvas.getContext("2d");

	if(font != undefined)
		ctx.font = font;
	else
		ctx.font = "20px Georgia"

	ctx.fillStyle = '#000';
	ctx.fillText(text,x,y);

}

function drawCanvas(objcanvas){
	CanvasDrawRectangle(objcanvas, 5, 5, 50, 80, 0);
	CanvasDrawLine(objcanvas, 0, 60, 100, 60);
	CanvasDrawArc(objcanvas,100,75,50,2,3);
	CanvasDrawLinearGradient(objcanvas, 120, 20, 150, 50, '#ff00ff', '#5f5f5f');
	CanvasDrawRectangle(objcanvas, 100, 75, 50, 80, 1);
	CanvasDrawText(objcanvas, 10, 100, 'texto de prueba');
	//20,20,150,100
}