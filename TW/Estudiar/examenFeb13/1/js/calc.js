function isNumeric(val){
	//comprobamos que sea numerico
	if(!/^[0-9]{1,}$/.test(val))
		return false;

	return true;
}

function formatDistancia(val){
	if(!isNumeric(val))
		return false;

	return true
}

function formatRitmo(val){
	if(!/^[0-9]{2}:[0-9]{2}$/.test(val))
		return false;

	return true;
}

function formatTiempo(val){
	if(!/^[0-9]{2}:[0-9]{2}:[0-9]{2}$/.test(val))
		return false;

	return true;
}


function calculaTiempoTotalDesdeRitmo(distancia, ritmo){
	var ritmoN = (ritmo.substring(0,2) * 60) + ritmo.substring(3,5);
	// (distancia * ritmoN)
	var c = distancia * ritmoN;
	var tt, h=0, m=0, s=0;

	h = parseInt(c/3600);
	c -= h*3600;
	m = parseInt(c/60);
	c -= m*60;
	s = c;
	tt = h+":"+m+":"+s;
	alert("Su Tiempo total es: " + tt);
}

function calculaRitmoDesdeTiempoTotal(tiempoTotal, distancia){
	alert("Su ritmo es: "+ (tiempoTotal/distancia));
}


function calcular(){
	frm 		= document.getElementById("formulario");
	distancia 	= frm.elements[0];
	ritmo 		= frm.elements[1];
	ttotal 		= frm.elements[2];

	if(formatDistancia(distancia.value) && isNumeric(distancia.value)){
		// alert("Formato distancia ok");
		distancia.className -= "incorrect";
	}
	else{
		alert("Formato distancia mal");
		distancia.className = "incorrect";
		distancia.focus();
		return false;
	}

	//ritmo no y ttotal se
	if(ritmo.value =='' && ttotal.value !=''){

		if(formatTiempo(ttotal.value)){
			calculaRitmoDesdeTiempoTotal(ttotal.value, distancia.value);
			ttotal.className -= "incorrect";

		}
		else{
			alert("Formato tiempo total mal");
			ttotal.className = "incorrect";
			ttotal.focus();
			return false;
		}
	}
	//ritmo si y ttotal no
	else if(ritmo.value !='' && ttotal.value ==''){
		if(formatRitmo(ritmo.value)){
			calculaTiempoTotalDesdeRitmo(distancia.value, ritmo.value);
			ritmo.className -= "incorrect";
		}
		else{
			alert("Formato ritmo mal");
			ritmo.className = "incorrect";
			ritmo.focus();
			return false;
		}
	}
	else{
		alert("No pueden estar los campos Ritmo y Tiempo vacios o rellenos simultaneamente.\n Borre/Escriba uno de los dos campos");
		ritmo.className = "incorrect";
		ttotal.className = "incorrect";
		ritmo.focus();
		return false;
	}



		

}