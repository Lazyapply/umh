var carritoArray = array();
var carritoPrecio = array();

function addProduct(product){

	var carrito = document.getElementById("carrito");



	switch (product){

		case 1:
			carrito.innerHTML += "<div class=\"col s8 left-align\">Nikon D5300 24MP</div><div class=\"col s4 left-align\">639.00€</div>";
			carritoArray.push("Nikon D5300 24MP");
			carritoPrecio.push("639.00");
		break;

		case 2:
			carrito.innerHTML += "<div class=\"col s8 left-align\">Verbatin Portable HHD</div><div class=\"col s4 left-align\">79.95€</div>";
		break;

		case 3:
			carrito.innerHTML += "<div class=\"col s8 left-align\">Sony Xperia M4</div><div class=\"col s4 left-align\">228.00€</div>";
		break;
	
		case 4:
			carrito.innerHTML += "<div class=\"col s8 left-align\">MSI GeForce Gtx 960</div><div class=\"col s4 left-align\">270.00€</div>";	
		break;

	}
	alert(carritoArray);
	addTotal();
}

function addTotal(){
	alert("entro");
	 arrayAux = carritoArray.slice();
	 arrayPrecio = carritoPrecio.slice();
	 total = arrayAux.lenght;

	alert(carritoArray);
	var totalField = document.getElementById("total");




}