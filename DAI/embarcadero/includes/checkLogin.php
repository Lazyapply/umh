<?php
	require_once 'embarcaciones.php';
	$aux = new Embarcaciones();

	$aux->login($_POST['userName'], $_POST['userPass']);

?>