<?php 

	require_once 'db_abstract_adapter.php';
	require_once 'constants.php';

	class Embarcaciones extends DBAbstractModel{

		public function __construct(){
			
		}

		public function uploadImgbyForm($folder = ' '){
		
			//tratamiento del upload de la imagen
					$validImgFormats = array('jpg', 'png');
					$target_dir = ROOT.'/img/profiles/';
					$target_file = $target_dir . basename($_FILES["image"]["name"]);
					$imgName = $_FILES["image"]["name"];
					$imgTmpPath = $_FILES["image"]["tmp_name"];
					$uploadStatus = 1; //1 ok, 0 wrong
					$mensajes = array();
					$imageFileType = strtolower(pathinfo($target_file, PATHINFO_EXTENSION));
					//comprobamos si el archivo existe
					if(file_exists($target_file)){
						array_push($mensajes, "El archivo ".$imgName." ya existe");
						$uploadStatus = 0;
					}
					//limitamos el tamaño max
					if($_FILES['image']['size'] > MAX_UPLOAD_FILE_SIZE){
						array_push($mensajes, "El archivo es mas grande del máximo permitido ( ".(MAX_UPLOAD_FILE_SIZE/1000000)."Mb)");
						$uploadStatus = 0;
					}
					//limitamos el tipo de datos (jpg, npg)
					if(!in_array($imageFileType, $validImgFormats)){
						$aux = "El archivo ".$imgName." no tiene un formato válido (";
						
						foreach ($validImgFormats as $key => $value) {
							$aux .= $value;
							if($key < (count($validImgFormats)-1))
								$aux .=', ';
						}
						$aux .=')';
						array_push($mensajes, $aux);
						$uploadStatus = 0;
					}
					//comprobamos si se puede subir el archivo ($uploadStatus)
					
					if($uploadStatus){
						//subimos el archivo
						if(move_uploaded_file($imgTmpPath, $target_file))
							array_push($mensajes, "El archivo $imgName se ha sido subido con éxito");
						else
							array_push($mensajes, "No se ha podido subir el archivo $imgName");
						
					}
					else{
						array_push($mensajes, "No se ha podido subir el archivo");
					}
					var_dump($mensajes);
					echo '<br>'.$target_file;
					return $imgName;
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

		public function asyncJsFromPHP($jsCode){
			echo '<script>'.$jsCode.'</script>';
		}

		public function o($string){
			$log = "console.log(\"".addslashes($string)."\");";
			$this->asyncJsFromPHP($log);
		}

		public function erase($target, $data = array()){

			foreach ($data as $key => $value) {
				$q = "DELETE FROM empleados WHERE id_Empleado =".$value.';';
				$this->setQuery($q);
				$this->execute_single_query();
			}

			
		}


		public function add($target, $data = array()){
			
			if(!empty($_FILES['image']['name']))
				$imgName = $this->uploadImgbyForm($folder = 'img/profiles/');

			switch ($target) {

				case EMPLOYEE:
					$q = "INSERT INTO empleados (Tipo, DNI, Nombre, Apellido1, Apellido2, Direccion, CP, Poblacion, Provincia, Telefono, Email, Usuario, Password, fotografia)
						VALUES(";
				break;
				
				default:
					# code...
					break;
			}

			
			var_dump($data);
			echo '<br>';

			//start construct query
				$c = 0;
				foreach ($data as $key => $value) {
					$q .= "'".$value."'";
					if($c < count($data) -1)
						$q .= ', ';

					$c++;
				}
				if(isset($imgName))
					$q .= ', \''.$imgName."'";
				else
					$q .= ", 'default-profile.png'";

				$q .= ')';
			//end construct query


			$this->setQuery($q);
			$this->execute_single_query();
			unset($_POST);

			echo $target.'<br>'.$q;
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
				if($newRow == 0) $newRow = 1;
				foreach ($aux[$key] as $clave => $valor) {

					if($newRow == 1){
						$tableData .= '<input type="checkbox" id="'.$aux[$key][$clave].'" />&nbsp;&nbsp;&nbsp;
      									<label for="'.$aux[$key][$clave].'"></label></td>';
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
							$tableData .= '<td class="tr-left center"><img class=" materialboxed responsive-img"  width="50" src="img/profiles/'.$valor.'"></td>';
					}
					
				}
				
				$tableData .= '</tr>';
			}

			return $tableData;

		}
	}

 ?>