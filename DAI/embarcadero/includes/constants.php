<?php 

	define('DS', 			'/');

	define('APP_NAME', 		'umh/DAI/embarcadero');
	define('ROOT', 			$_SERVER['DOCUMENT_ROOT'].APP_NAME);
	define('COMPONENTS', 	DS.'components');
	define('INCLUDES', 		DS.'includes');

	define('EMPLOYEES', 	COMPONENTS.DS.'employee');
	define('EMPLOYEE', 		'employee');
	define('IMG',  			ROOT.DS.'img');



	define('MAX_UPLOAD_FILE_SIZE', 1000000);//1MB
	
	define('ADD',  			'add');
	define('EDIT',  		'edit');
	define('ERASE',  		'erase');
	define('UPDATE',  		'update');
	
 ?>