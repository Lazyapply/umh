<?php
	require_once 'embarcaciones.php';
	$aux = new Embarcaciones();

	$aux->logout();
	header("Location: ../index.php");
	die();
?>