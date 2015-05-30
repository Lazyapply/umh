var DEBUG_MODE_ON = 1;
//----------------------
var text;
var curSong;
var curSongText;
var listSongs;
var lastValue;
var valor;
var total;
var currTime;
var jsListSong = {};
//**************************************************
var playerSrc = document.getElementById("mySource");
var volumeV = document.getElementById("volumeValue");

//-------- START JQUERY --------------------------------------------------------------------
var barVolumen = $("#slider").data("rangeinput");


$(document).ready(function(){

	//capturar canción pulsada
	$('.collection').dblclick(function(event) {
		var elemento = $(event.target);
    	var songName = elemento.text();
    	curSong = $('.currentSong');
    	curSongText = $('.currentSong').text();

    	curSong.removeClass('currentSong');
    	elemento.addClass('currentSong');
    	// o(listSongs);
    	setSong(jsListSong[listSongs.index(elemento)]);
    	
	});

	//captura de lista de canciones
	listSongs = $( ".collection" ).find( "li" );
	//pasamos de objetos Jquery a array javascript
	jsListSong = $.makeArray( listSongs );
	//cambio dinamico de valor
	$("#barVolumen").mousemove( function(e){	volumen();	});
	

	o("Documento cargado");
	// o(listSongs.index(curSong));
});

//-------- END JQUERY --------------------------------------------------------------------

function dump_listSong(){
	var total = jsListSong.length;

	for(c=0;c<total;c++)
		o("["+ c +"] -> " + getSongNamebyObject(jsListSong[c]));

	o("_______________________");
	o("Canciones cargadas: " + total);
	

	//setSong(jsListSong[1]);
	//test
	//var songPath = getSongPathbyObject(jsListSong[0]);
	//o(songPath);
	// document.getElementById("#test").innerHTML();
}

function o(valor){ (DEBUG_MODE_ON) ? console.log(valor) : false; }
function getSongPathbyObject(obj){ return obj.getAttribute("path"); }
function getSongNamebyObject(obj){ return obj.textContent; }

function setSong(songObj){
	var songName = getSongNamebyObject(songObj);
	var songPath = getSongPathbyObject(songObj);
	// var playerSrc = '<source id="mySource" src="'+ songPath +'" type="audio/mpeg" />';
	
	playerSrc.setAttribute("src", songPath);
	player.load();
	play();
	o(songName + ' - path - ' + songPath + '?? ' + playerSrc);
	// <source id="mySource" src="music/01 - Super Colossal.mp3" type="audio/mpeg" />


}

function ini(){

	dump_listSong();

	//cerramos la lista de reproducción
	document.getElementById("playList").style.display = "none";

	var player = document.getElementById('player');
	volumen();
	//cambio de tiempo en el player
	player.ontimeupdate = function(){ showTime(); }

	//colores toogle
	var btn = document.getElementById("showList");
	var btn2 = document.getElementById("showControls");
	btn.style.color = 'black';
	btn2.style.color = 'white';

	//punteros
	document.getElementById("showList").style.cursor = 'pointer';
	document.getElementById("showControls").style.cursor = 'pointer';
	document.getElementById("btnPrevious").style.cursor = 'pointer';
	document.getElementById("btnPlay").style.cursor = 'pointer';
	document.getElementById("btnPause").style.cursor = 'pointer';
	document.getElementById("btnStop").style.cursor = 'pointer';
	document.getElementById("btnNext").style.cursor = 'pointer';
	document.getElementById("btnMute").style.cursor = 'pointer';
	document.getElementById("barVolumen").style.cursor = 'pointer';
	document.getElementById("progressField").style.cursor = 'pointer';

	var aaa = secondToMinutes(10);
	o(aaa);
}


	
function showList(){
	//currSong = document.getElementByClassName('currentSong');
	

	var btn = document.getElementById("showList");
	var list = document.getElementById("playList");


	if(btn.style.color == 'black'){
		btn.style.color = 'white';
		list.style.display = "block";
	}
	else{
		btn.style.color = 'black';
		list.style.display = "none";
		
	}
}

function showControls(){

	var btn = document.getElementById("showControls");
	var controls = document.getElementById("navigation");


	if(btn.style.color == 'black'){
		btn.style.color = 'white';
		controls.style.display = "block";
	}
	else{
		btn.style.color = 'black';
		controls.style.display = "none";
		
	}
}

function previous(){
	alert("previous");
}

function next(){
	alert("next");
}

function play(){
	
	player.play();
	showTime();
}

function pause(){
	player.pause();
}

function stop(){
	player.pause();
	player.currentTime = 0;

}

function secondToMinutes(valor){
	var min, seg, aux;
	var strTime;

	aux = valor;
	min = valor / 60;
	min = Math.round(min);
	seg = valor % 60;
	seg = Math.round(seg);
// (DEBUG_MODE_ON) ? console.log(valor) : false;

	if(min <= 9)
		strTime = "0" + min;
	else
		strTime = min;

	if(seg <= 9)
		strTime = strTime + ":" + "0" + seg;
	else
		strTime = strTime + ":" + seg;
	
	//strTime = (min <= 9) "0" + min : min;
	//strTime = strTime + ":" (seg < 9) "0" + seg : seg;
	return  strTime;
}



function showTime(){
	var labelTime = document.getElementById('playerTime');
	total = player.duration;
	currTime = player.currentTime;
	// o(currTime+"/"+total);
	labelTime.innerHTML = secondToMinutes(currTime) + "/" +  secondToMinutes(total);

	changeStart();
}


function volumen(){
	
	valor = document.getElementById('barVolumen').value;
	var btn = document.getElementById("btnMute");

	if(valor == 99)
		valor = valor + 1;

	if(valor == 0)
		btn.className = "mdi-av-volume-off small valign";
	else
		btn.className = "mdi-av-volume-up small valign";

	volumeV.innerHTML = valor;
	o(valor);
	player.volume = valor/100;

	
	
}

function mute(){
	
	var btn = document.getElementById("btnMute");
	var bVolum = document.getElementById("barVolumen");
	var curValue = bVolum.getAttribute("value");


	if(curValue != 0)
			lastValue =  valor;

	if(btn.className == 'mdi-av-volume-up small valign'){
		btn.className = "mdi-av-volume-off small valign";
		o("no");
		o(0);
		

		bVolum.setAttribute("value", 0);
		volumeV.innerHTML = 0;
		player.muted = true;
	}
	else{
		btn.className = "mdi-av-volume-up small valign";
		bVolum.setAttribute("value", lastValue);
		volumeV.innerHTML = lastValue;
		o("Si");
		o(lastValue);
		player.muted = false;
	}

	bVolum.setAttribute("value", parseInt(valor));
}


function changeStart(){

	total = player.duration;
	currTime = player.currentTime;

	var ancho = document.getElementById("progressField").offsetWidth;
	var valorRange = document.getElementById("progressBar");
	var aumento;
	var paso = ancho/100;
	aumento =  (currTime / total) * 100 ;
	//alert(aumento);
	// while(aumento < ancho){
	// 	document.getElementById("progressBar").style.width = aumento + "%";
	// 	aumento += aumento;
	// }
	valorRange.style.width = aumento  + "%";
	o("progressBar valorRange = " + aumento);
	//alert(aumento)
}