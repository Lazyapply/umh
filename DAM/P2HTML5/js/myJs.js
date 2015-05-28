
function ini(){

	//cerramos la lista de reproducción
	document.getElementById("playList").style.display = "none";
	var player = document.getElementById('player');

	player.ontimeupdate = function(){
		console.log("vamos")
	}

	//colores toogle
	var btn = document.getElementById("showList");
	var btn2 = document.getElementById("showControls");
	btn.style.color = 'black';
	btn2.style.color = 'black';

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

	
}


	
function showList(){

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
	var controls = document.getElementById("navigationControls");


	if(btn.style.color == 'black'){
		btn.style.color = 'white';
		controls.style.display = "block";
	}
	else{
		btn.style.color = 'black';
		controls.style.display = "none";
		
	}
}



function testFiles(){
	// Check for the various File API support.
	if (window.File && window.FileReader && window.FileList && window.Blob){
	  // Great success! All the File APIs are supported.
	} 
	else {
	  alert('The File APIs are not fully supported in this browser.');
	}
}


function handleFileSelect(evt) {
	//var files = evt.target.files; // FileList object
var files = 'css'; 
	// files is a FileList of File objects. List some properties.
	var output = [];
	for (var i = 0, f; f = files[i]; i++) {
	output.push('<li><strong>', escape(f.name), '</strong> (', f.type || 'n/a', ') - ',
	f.size, ' bytes, last modified: ',
	f.lastModifiedDate ? f.lastModifiedDate.toLocaleDateString() : 'n/a',
	'</li>');
	}
	document.getElementById('list').innerHTML = '<ul>' + output.join('') + '</ul>';
}

document.getElementById('files').addEventListener('change', handleFileSelect, false);


function previous(){
	alert("previous");
}

function next(){
	alert("next");
}

function play(){
	player.play();
	//showTime()
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
	aux = valor;
	min = valor / 60;
	min = Math.round(min);
	seg = valor % 60;
	seg = Math.round(seg);

	return min + ":" + seg;
}



function showTime(){
	var labelTime = document.getElementById('playerTime');
	var total = player.duration;
	var currTime = player.currentTime;
	labelTime.innerHTML = secondToMinutes(currTime) + "/" +  secondToMinutes(total);
}


function volumen(){
	
	var valor = document.getElementById('barVolumen').value;
	var btn = document.getElementById("btnMute");

	if(valor == 99)
		valor = valor + 1;

	if(valor == 0)
		btn.className = "mdi-av-volume-off small valign";
	else
		btn.className = "mdi-av-volume-up small valign";

	player.volume = valor/100;

	
	
}

function mute(){
	
	var btn = document.getElementById("btnMute");

	if(btn.className == 'mdi-av-volume-up small valign'){
		btn.className = "mdi-av-volume-off small valign";
		player.muted = true;
	}
	else{
		btn.className = "mdi-av-volume-up small valign";
		player.muted = false;
	}
	
}


function changeStart(){
	//alert("cambiando posición");
	var ancho = document.getElementById("progressField").offsetWidth;
	var paso = ancho/100;
	var aumento = paso;
	//alert(aumento);
	while(aumento < ancho){
		document.getElementById("progressBar").style.width = aumento + "%";
		aumento += aumento;
	}
	//alert(aumento)
}