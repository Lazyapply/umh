


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