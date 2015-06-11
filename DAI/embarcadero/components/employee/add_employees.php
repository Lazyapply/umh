
<!--  \" \", ),
 , , , , , Email, , fotografia -->
<div class="row"></div>
<div class="row">
<h5 class="center-align">Añadir nuevo empleado</h5>
<form action ="components/processDB.php" method="post" class="col s6 offset-s3" enctype="multipart/form-data">
 
  <input type="hidden" name="action" value="add">
	<input type="hidden" name="from" value="employee">

      <div class="row">
        <div class="input-field col s6">
          <input  name="nombre" id="nombre" type="text" class="validate">
          <label for="nombre">Nombre</label>
        </div>
        <div class="input-field col s3">
          <input  name="tipo" id="tipo" type="text" class="validate">
          <label for="tipo">Tipo</label>
        </div>
        <div class="input-field col s3">
          <input  name="dni" id="dni" type="text" class="validate">
          <label for="dni">DNI</label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s6">
          <input  name="apellido1" id="apellido1" type="text" class="validate">
          <label for="apellido1">Primer apellido</label>
        </div>
        <div class="input-field col s3">
          <input  name="poblacion" id="poblacion" type="text" class="validate">
          <label for="poblacion">Poblacion</label>
        </div>
        <div class="input-field col s3">
          <input  name="provincia" id="provincia" type="text" class="validate">
          <label for="provincia">Provincia</label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s6">
          <input  name="apellido2" id="apellido2" type="text" class="validate">
          <label for="apellido2">Segundo apellido</label>
        </div>
        <div class="input-field col s3">
          <input  name="cp" id="cp" type="text" class="validate">
          <label for="cp">CP</label>
        </div>
        <div class="input-field col s3">
          <input  name="telefono" id="telefono" type="text" class="validate">
          <label for="telefono">Telefono</label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s6">
          <input  name="direccion" id="direccion" type="text" class="validate">
          <label for="direccion">Dirección</label>
        </div>
        <div class="input-field col s6">
         	<input  name="email" id="email" type="email" class="validate">
          <label for="email">E-mail</label>
        </div>
        <div class="input-field col s3">
          <input  name="usuario" id="usuario" type="text" class="validate">
          <label for="usuario">Usuario</label>
        </div>
        <div class="input-field col s3">
          <input  name="pass" id="pass" type="password" class="validate">
          <label for="pass">Contraseña</label>
        </div>
			<div class="input-field col s6">
				<div class="file-field input-field">
					<input class="file-path validate" type="text"/>
				<div class="btn">
					<span>Foto</span>
					<input name="image" id="image" type="file" />
				</div>
				</div>
    		</div>
      </div>
      
	<div class="row">
	<br>
		<div class="col s12 right">
			<input type="submit" value="Añadir" class="btn right" />
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