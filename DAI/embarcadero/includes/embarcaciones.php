<?php 

	require_once 'db_abstract_adapter.php';


	class Embarcaciones extends DBAbstractModel{

		public function __construct(){
			
		}

		public function login($user, $pass){


			if((empty($user)) || (empty($pass)))
				return 0;


			$q = "SELECT Password, Id_Empleado, Tipo FROM empleados WHERE Usuario=".$this->intoQuote($user);
			$this->setQuery($q);
			$this->get_results_from_query();

			$aux = $this->getRows();
			
			if(count($aux) == 0)
				return 0;

			$dbPass = $aux[0]['Password'];
			$dbUserId = $aux[0]['Id_Empleado'];
			$dbPerm = $aux[0]['Tipo'];



			if(sha1($pass) == $dbPass){
				@session_start();
				$_SESSION['userId'] = $dbUserId;
				$_SESSION['userName'] = $user;
				$_SESSION['userPerm'] = $dbPerm;

				return 1;
			}
			else{
				return 0;
			}

		}


	}

 ?>