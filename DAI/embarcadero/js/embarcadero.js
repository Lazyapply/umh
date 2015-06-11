DEBUG_MODE_ON = 1;

var btnAdd = document.getElementById("btnAdd");
var btnEdit = document.getElementById("btnEdit");
var btnErase = document.getElementById("btnErase");


$(document).ready(function(){
	//modallogin
	$('.modal-trigger').leanModal();
	//slide
	$('.slider').slider({full_width: true});

	


});

function o(valor){ (DEBUG_MODE_ON) ? console.log(valor) : false; }
// sp?name1=value1&name2=value2
function loadErase(target){
	var location;

	switch (target){

		case 'employee':
			location = 'components/processDB.php' + constructGET(target, 'erase');;
		break;



	}
	// o(location);
	window.location.assign(location);
}


function loadEdit(target){
	var location;

	switch (target){

		case 'employee':
			location = 'components/employee/edit_employees.php' + constructGET(target, 'edit');
			// location = 'components/processDB.php' + constructGET(target, 'edit');
		break;



	}
	o(location);
	// window.location.assign(location);
	oXML.open('GET', location);
	
	oXML.onreadystatechange = function(){
		getAjaxHandler('employeeContent');
	};

	oXML.send();
}

function constructGET(target, action){
	var q = '?from='+target+'&action='+action ;

	switch(action){
		case 'erase':
			for(i=0;i<totalElements;i++){
				q = q + '&id'+ i + "=" + selectedItems[i];
			}

		break;

		case 'edit':
			q = q + '&id=' + selectedItems.pop();
				
		break;
	}
	

	return q;
}
//start dynamic

//add
function loadAdd(target){
	var location;

	switch (target){

		case 'employee':
			location = 'components/employee/add_employees.php';
		break;



	}

	oXML.open('GET', location);
	
	oXML.onreadystatechange = function(){
		getAjaxHandler('employeeContent');
	};

	oXML.send();
}

//list
function loadList(target){
	var location;

	switch (target){

		case 'employee':
			location = 'components/employee/list_employees.php';
		break;

		

	}

	oXML.open('GET', location);
	
	oXML.onreadystatechange = function(){
		getAjaxHandler('employeeContent');
	};

	oXML.send();
}


//end dynamic

//----- START AJAX ------------------------------------------------


function getAjax(){

	var obj;

	if(window.XMLHttpRequest){
		obj = new XMLHttpRequest();
	}
	else{
		try{
			obj = new ActiveXObject("Microsoft.XMLHTTP");
		}
		catch (e){
			alert("Este navegador no es compatible con AJAX");
		}
	}

	return obj;
}

var oXML = getAjax();

function addAjaxData(target, data){
	document.getElementById(target).innerHTML = data;
}

function getAjaxHandler(target){
	switch(oXML.readyState){

		case 2:
		case 3:
			addAjaxData(target, '<img id="preloader" class="loader-little centered" src="img/preloader.gif" alt="loader"/>');
		break;

		case 4:
			addAjaxData(target, oXML.responseText);
			
		break;
	}

}

//----- END AJAX ------------------------------------------------