<?php 

	require_once 'db_abstract_adapter.php';
	require_once 'constants.php';

	class Embarcaciones extends DBAbstractModel{

		public function __construct(){
			
		}

		public function login($user, $pass){


			if((empty($user)) || (empty($pass)))
				return 0;


			$q = "SELECT Password, Id_Empleado, Tipo, Fotografia FROM empleados WHERE Usuario=".$this->intoQuote($user);
			$this->setQuery($q);
			$this->get_results_from_query();

			$aux = $this->getRows();
			
			if(count($aux) == 0)
				return 0;

			$dbPass = $aux[0]['Password'];
			$dbUserId = $aux[0]['Id_Empleado'];
			$dbPerm = $aux[0]['Tipo'];
			$dbPic = $aux[0]['Fotografia'];


			if(sha1($pass) == $dbPass){
				@session_start();
				$_SESSION['userId'] = $dbUserId;
				$_SESSION['userName'] = $user;
				$_SESSION['userPerm'] = $dbPerm;
				$_SESSION['userPhoto'] = $dbPic;

				return 1;
			}
			else{
				return 0;
			}
		}

		public function logout(){
			@session_start();
			session_unset();
			session_destroy();
		}

		public function listTableData($table){
			

			switch ($table) {
				case EMPLOYEES:
					$q = "SELECT idEmpleado, Tipo, DNI, Nombre, Apellido1, Apellido2, Direccion, CP, Poblacion, Provincia, Telefono E-mail, usuario FROM empleados";
				break;
				
				default:
					
				break;
			}

			$this->setQuery($q);
			$this->get_results_from_query();
			$aux = $this->getRows();

			var_dump($aux);

			echo 'Q-> '.$q;

		}
	}

 ?>