


// function inicio(){
// 	var elements = ["inicio", "dominio", "hosting", "servidores"];
// 	var elementsTT = ["ttInicio", "ttDominio", "ttHosting", "ttServidores"];

// 	for(i=0;i<4;i++){
// 		// alert(elements[i] + ' ' + elementsTT[i]);
// 		document.getElementById(elements[i]).addEventListener("mouseover", function(){miFuncion(elementsTT[i]);}, true);
// 		document.getElementById(elements[i]).addEventListener("mouseout", function(){miFuncion(elementsTT[i]);}, true);
// 	}
// }




document.getElementById("inicio").addEventListener("mouseover", function(){miFuncion("ttInicio")});
document.getElementById("inicio").addEventListener("mouseout", function(){miFuncion("ttInicio")});

document.getElementById("dominio").addEventListener("mouseover", function(){miFuncion("ttDominio")});
document.getElementById("dominio").addEventListener("mouseout", function(){miFuncion("ttDominio")});

document.getElementById("hosting").addEventListener("mouseover", function(){miFuncion("ttHosting")});
document.getElementById("hosting").addEventListener("mouseout", function(){miFuncion("ttHosting")});

document.getElementById("servidores").addEventListener("mouseover", function(){miFuncion("ttServidores")});
document.getElementById("servidores").addEventListener("mouseout", function(){miFuncion("ttServidores")});


function miFuncion(obj){

	document.getElementById(obj).classList.toggle('hidden');
}

function getDate(){
	var d = new Date();
	var dd = d.getDate();
	var mm = d.getMonth()+1;
	var yy = d.getFullYear();

	var t = yy+'-'+mm+'-'+dd;
	document.getElementById("fechaD").value = t;

}


function validaCCC(val){
    var banco = val.substring(0,4);
    var sucursal = val.substring(4,8);
    var dc = val.substring(8,10);
    var cuenta=val.substring(10,20);
    var CCC = banco+sucursal+dc+cuenta;
    if (!/^[0-9]{20}$/.test(banco+sucursal+dc+cuenta)){
        return false;
    }
    else
    {
        valores = new Array(1, 2, 4, 8, 5, 10, 9, 7, 3, 6);
        control = 0;
        for (i=0; i<=9; i++)
        control += parseInt(cuenta.charAt(i)) * valores[i];
        control = 11 - (control % 11);
        if (control == 11) control = 0;
        else if (control == 10) control = 1;
        if(control!=parseInt(dc.charAt(1))) {
            return false;
        }
        control=0;
        var zbs="00"+banco+sucursal;
        for (i=0; i<=9; i++)
            control += parseInt(zbs.charAt(i)) * valores[i];
        control = 11 - (control % 11);
        if (control == 11) control = 0;
            else if (control == 10) control = 1;
        if(control!=parseInt(dc.charAt(0))) {
            return false;
        }
        return true;
    }
}

function checkCCC(val){
	if(!validaCCC(val)){
		alert("cuenta No valida");
	}
}


function checkDNI(dni) {
  numero = dni.substr(0,dni.length-1);
  let = dni.substr(dni.length-1,1);
  numero = numero % 23;
  letra='TRWAGMYFPDXBNJZSQVHLCKET';
  letra=letra.substring(numero,numero+1);
  if (letra!=let) 
    alert('Dni erroneo');
}