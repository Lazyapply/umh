
function ini(){
	var player = document.getElementById('player');
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
}

function pause(){
	player.pause();
}

function stop(){
	player.pause();
	player.currentTime = 0;

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