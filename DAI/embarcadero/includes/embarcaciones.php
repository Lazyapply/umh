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
			
			$tableData = '';

			switch ($table) {
				case EMPLOYEES:
					$q = "SELECT id_Empleado, Tipo, DNI, CONCAT(Nombre, \" \", Apellido1, \" \", Apellido2), Direccion, CP, Poblacion, Provincia, Telefono, Email, usuario, fotografia FROM empleados";
				break;
				
				default:
					
				break;
			}


			$this->clearRows();
			$this->setQuery($q);
			$this->get_results_from_query();
			$aux = $this->getRows();
			$newRow = 1;

			//var_dump($aux);
			foreach ($aux as $key => $value) {
				$tableData .= '<tr><td>';

				foreach ($aux[$key] as $clave => $valor) {

					if($newRow){
						$tableData .= '<input type="checkbox" id="id_'.$aux[$key][$clave].'" />
      									<label for="id_'.$aux[$key][$clave].'"></label></td>';
      					$newRow = 0;
					}

					if($clave == 'Tipo'){
						if($valor == 1){
							$tableData .= '<td class="tr-left">Admin</td>';
						}
						else{
							$tableData .= '<td class="tr-left">Empleado</td>';
						}
						
					}
					else{
						if($clave != 'fotografia')
							$tableData .= '<td class="tr-left">'.$valor.'</td>';
						else
							$tableData .= '<td class="tr-left"><img class="responsive-img" src="img/profiles/'.$valor.'"></td>';
					}
					
				}
				$newRow = 0;
				$tableData .= '</tr>';
			}

			return $tableData;

		}
	}

 ?>