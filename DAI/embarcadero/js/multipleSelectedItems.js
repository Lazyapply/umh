/**********************************************************

Módulo:				----
Archivo:			multipleSelectedItems.js
Alias:				----
Fecha creacion:		10/06/2015
Ultima modif:		11/06/2015
Versión: 			0.1
Autor: 				@dvel_


Descripción:
fuctions to allow multiple selection
**********************************************************/


var DEBUG_MODE_ON = 0;
//----------------------
//items
var selectedItems = [];
var id;
var totalElements = 0;

//buttons
var btnAdd = document.getElementById("btnAdd");
var btnEdit = document.getElementById("btnEdit");
var btnErase = document.getElementById("btnErase");



$(document).ready(function(){
	
	//buttons
	checkButtons();


	//start footer
	var bodyHeight = $("body").height();
	var vwptHeight = $(window).height();
	if (vwptHeight > bodyHeight) {
		$("footer#colophon").css("position","absolute").css("bottom",0).css("width","100%");
	}
	//end footer

	// start multiple selected items
	$( "input[type=checkbox]" ).on( "click", function(event){
		//el vector es para transformar el objeto jquery a objeto js
		elemento = $(event.target)[0];
		id = elemento.getAttribute("id");
		var checked = elemento.checked;
		// o(checked);
		if(checked){
			if(selectedItems.indexOf(id) == -1){
				o('in ' + id);
				selectedItems.push(id);
				totalElements = selectedItems.length;
				
			}

		}
		else{
				o('out ' + id);
				selectedItems.pop(id);
				totalElements = selectedItems.length;
				
			
		}

		checkButtons();

	});

	//end multiple selected items

});

function checkButtons(){
	//if there are multiselection, edit and erase disable,
	//only will be available erase button
	if(totalElements == 0){
		btnEdit.classList.add("hide");
		btnErase.classList.add("hide");
		btnAdd.classList.remove("hide");
	}
	else{
		if(totalElements == 1)
			btnEdit.classList.remove("hide");
		else
			btnEdit.classList.add("hide");

		btnErase.classList.remove("hide");
		btnAdd.classList.add("hide");
	}
}


function o(valor){ (DEBUG_MODE_ON) ? console.log(valor) : false; }

function dumpSelectedItems(){ 
	// totalElements = selectedItems.length;
	o("dump SelectedItems: " + totalElements);
	o("------------------------------");
	for(i=0;i<totalElements;i++){
		o('[' + i + ']-> ' + selectedItems[i]);
	}
}

