var carritoArray = [];
var carritoPrecio = [];
var carrito = document.getElementById("carrito");
var carrito_out = document.getElementById("carrito_form");
var total_price = document.getElementById("totalPrice");


function addProduct(product){




	switch (product){

		case 1:

			if(carritoArray.indexOf("Nikon D5300 24MP") == -1){

				carritoArray.push("Nikon D5300 24MP");
				carritoPrecio.push(639.00);

				carrito.innerHTML += "<div class=\"col s8 left-align\">Nikon D5300 24MP</div><div class=\"col s4 left-align\">639.00€</div>";
			}
		break;

		case 2:
			if(carritoArray.indexOf("Verbatin Portable HHD") == -1){
				carritoArray.push("Verbatin Portable HHD");
				carritoPrecio.push(79.95);
				carrito.innerHTML += "<div class=\"col s8 left-align\">Verbatin Portable HHD</div><div class=\"col s4 left-align\">79.95€</div>";
				
			}
		break;

		case 3:
			if(carritoArray.indexOf("Sony Xperia M4") == -1){
				carritoArray.push("Sony Xperia M4");
				carritoPrecio.push(228.00);
				carrito.innerHTML += "<div class=\"col s8 left-align\">Sony Xperia M4</div><div class=\"col s4 left-align\">228.00€</div>";
				
			}
		break;
	
		case 4:
			if(carritoArray.indexOf("MSI GeForce Gtx 960") == -1){
				carritoArray.push("MSI GeForce Gtx 960");
				carritoPrecio.push(270.00);
				carrito.innerHTML += "<div class=\"col s8 left-align\">MSI GeForce Gtx 960</div><div class=\"col s4 left-align\">270.00€</div>";	
				
			}
		break;

	}

	addTotal();
}

function addTotal(){
	
	

	 arrayAux = carritoArray.slice();
	 arrayPrecio = carritoPrecio.slice();
	 var precioTotal = 0.0;
	 var totalField = document.getElementById("total");
	 var i = 0;
	 total = carritoArray.length;

	 //alert(carritoArray.length);
	 console.log("------------------------");
	 for(i=0;i<total;i++){
	 	console.log(carritoArray[i] + " ->" + carritoPrecio[i]);
	 	precioTotal += carritoPrecio[i];
	 }

	 total_price.innerHTML = precioTotal + " €";
	 document.getElementById("inputTotal").setAttribute("value", precioTotal);
	 //carrito_out.innerHTML += "<input type=\"hidden\" name=\"item_name_1" value="Compra de Producto X">";
			

			/*
							<input type="hidden" name="item_name_1" value="Compra de Producto X">
				<input type="hidden" name="amount_1" value="50.00">

			 */



	//alert(carritoArray.length);
	




}