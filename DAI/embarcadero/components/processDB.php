<?php 

	require_once '../includes/embarcaciones.php';
	$myEmbarcaciones = new Embarcaciones();

	if(!empty($_POST)){//POST
		$from = $_POST['from'];
		$action = $_POST['action'];
		unset($_POST['from']);
		unset($_POST['action']);
		// var_dump($_POST);
	}
	else{//GET
		$from = $_GET['from'];
		$action = $_GET['action'];
		unset($_GET['from']);
		unset($_GET['action']);

		if(!empty($_GET['id'])){
			$id = $_GET['id'];
			unset($_GET['id']);
		}


		// var_dump($_GET);
	}
	// echo $from.'<br>';

	switch ($from) {
		case EMPLOYEE:
		echo $action;
			switch ($action) {
				case ADD:
					$myEmbarcaciones->add($from, $_POST);
					break;

				case ERASE:
					$myEmbarcaciones->erase($from, $_GET);
					break;

				case EDIT:
					$myEmbarcaciones->edit($from, $id);
					break;

				case UPDATE:
					 $myEmbarcaciones->update($from, $_POST);
					 
					break;
				
				default:
					# code...
					break;
			}
			



			header("Location: ../empleado_panel.php");
			die();

			break;
		
		default:
			# code...
			break;
	}

	// var_dump($_POST);
?>