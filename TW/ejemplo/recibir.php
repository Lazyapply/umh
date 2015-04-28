<?php 

$query = "SELECT * FROM tabla WHERE nombre=";


foreach ($_POST['checkboxvar'] as $value) {

	if (isset($_POST['checkboxvar'])) 
    	$query .= "'".array_shift($_POST['checkboxvar'])."'";

    if (count($_POST['checkboxvar']) != 0) 
    	$query .= " OR nombre="; 
}

	echo '<br>'.$query;
	


 ?>