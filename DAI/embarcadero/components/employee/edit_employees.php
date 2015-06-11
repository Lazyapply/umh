
<!--  \" \", ),
 , , , , , Email, , fotografia -->
<div class="row"></div>
<div class="row">
<h5 class="center-align">Editar empleado</h5>
<!-- 
  














  -->
  <?php 
    // echo __DIR__;
    require_once '../../includes/embarcaciones.php';

  
  $myEmbarcaciones = new Embarcaciones();

    $myEmbarcaciones->edit($_GET['from'], $_GET['id']);
    // var_dump($_GET);
  ?>
<form action ="components/processDB.php" method="post" class="col s6 offset-s3" enctype="multipart/form-data">
 
  <input type="hidden" name="action" value="update">
	<input type="hidden" name="from" value="employee">
  <input type="hidden" name="id" value="<?php echo $_GET['id']; ?>">
 

      <div class="row">
        <div class="input-field col s6">
          <input  name="nombre" id="nombre" type="text" value="<?php echo $_POST['Nombre'];?>" class="validate">
          <label for="nombre">Nombre</label>
        </div>
        <div class="input-field col s3">
          <input  name="tipo" id="tipo" value="<?php echo $_POST['Tipo'];?>" type="text" class="validate">
          <label for="tipo">Tipo</label>
        </div>
        <div class="input-field col s3">
          <input  name="dni" id="dni" value="<?php echo $_POST['DNI'];?>" type="text" class="validate">
          <label for="dni">DNI</label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s6">
          <input  name="apellido1" id="apellido1" value="<?php echo $_POST['Apellido1'];?>" type="text" class="validate">
          <label for="apellido1">Primer apellido</label>
        </div>
        <div class="input-field col s3">
          <input  name="poblacion" id="poblacion" value="<?php echo $_POST['Poblacion'];?>" type="text" class="validate">
          <label for="poblacion">Poblacion</label>
        </div>
        <div class="input-field col s3">
          <input  name="provincia" id="provincia" value="<?php echo $_POST['Provincia'];?>" type="text" class="validate">
          <label for="provincia">Provincia</label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s6">
          <input  name="apellido2" id="apellido2" value="<?php echo $_POST['Apellido2'];?>" type="text" class="validate">
          <label for="apellido2">Segundo apellido</label>
        </div>
        <div class="input-field col s3">
          <input  name="cp" id="cp" value="<?php echo $_POST['CP'];?>" type="text" class="validate">
          <label for="cp">CP</label>
        </div>
        <div class="input-field col s3">
          <input  name="telefono" id="telefono" value="<?php echo $_POST['Telefono'];?>" type="text" class="validate">
          <label for="telefono">Telefono</label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s6">
          <input  name="direccion" id="direccion" value="<?php echo $_POST['Direccion'];?>" type="text" class="validate">
          <label for="direccion">Dirección</label>
        </div>
        <div class="input-field col s6">
         	<input  name="email" id="email" value="<?php echo $_POST['Email'];?>" type="email" class="validate">
          <label for="email">E-mail</label>
        </div>
        <div class="input-field col s3">
          <input  name="usuario" id="usuario" value="<?php echo $_POST['Usuario'];?>" type="text" class="validate">
          <label for="usuario">Usuario</label>
        </div>
        <div class="input-field col s3">
          <input  name="Password" id="Password"  type="password" class="validate">
          <label for="Password">Contraseña</label>
        </div>
			<div class="input-field col s6">
				<div class="file-field input-field">
					<input class="file-path validate"  type="text"/>
				<div class="">
					<span><img src="img/profiles/<?php echo $_POST['fotografia'];?>"></span>
					<input  name="image" id="image" value="" type="file" />
				</div>
				</div>
    		</div>
      </div>
      
	<div class="row">
	<br>
		<div class="col s12 right">
			<input type="submit" value="Guardar" class="btn right" />
		</div>
	</div>
    </form>
</div>


<!-- <div class="fixed-action-btn" style="bottom: 45px; right: 24px;">
    <a class="btn-floating btn-large red">
      <i class="large mdi-editor-mode-edit"></i>
    </a>
    <ul>
		<li class="tooltipped" data-position="left" data-delay="5" data-tooltip="Añadir"><a  id="btnAdd" onclick="dumpSelectedItems()" class="btn-floating green"><i class="large mdi-social-group-add"></i></a></li>
		<li class="tooltipped" data-position="left" data-delay="5" data-tooltip="Editar"><a id="btnEdit"  class="btn-floating yellow darken-1"><i class="large mdi-image-edit"></i></a></li> 
		<li class="tooltipped" data-position="left" data-delay="5" data-tooltip="Eliminar"><a id="btnErase" class="btn-floating red"><i class="large mdi-action-delete"></i></a></li> 
    </ul>
  </div> -->