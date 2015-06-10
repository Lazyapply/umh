<?php 

	require_once 'includes/embarcaciones.php';

	
	$myEmbarcaciones = new Embarcaciones();
	$myEmbarcaciones->listTableData(EMPLOYEES);


?>

<table class="hoverable">
	<caption class="right-align"><h5>Empleados</h5></caption>
	<thead>
		<tr>
			<th>&nbsp;</th>
			<th>Id</th>
			<th>Tipo</th>
			<th>DNI</th>
			<th>Nombre</th>
			<th>Dirección</th>
			<th>CP</th>
			<th>Población</th>
			<th>Ciudad</th>
			<th>Teléfono</th>
			<th>E-mail</th>
			<th>Nick</th>
			<th>Fotografía</th>
			
		</tr>
	</thead>
	<tbody>
		<?php echo $myEmbarcaciones->listTableData(EMPLOYEES); ?>
	</tbody>
</table>



<div class="fixed-action-btn" style="bottom: 45px; right: 24px;">
    <a class="btn-floating btn-large red">
      <i class="large mdi-editor-mode-edit"></i>
    </a>
    <ul>
		<li class="tooltipped" data-position="left" data-delay="5" data-tooltip="Añadir"><a  id="btnAdd" onclick="dumpSelectedItems()" class="btn-floating green"><i class="large mdi-social-group-add"></i></a></li>
		<li class="tooltipped" data-position="left" data-delay="5" data-tooltip="Editar"><a id="btnEdit"  class="btn-floating yellow darken-1"><i class="large mdi-image-edit"></i></a></li> 
		<li class="tooltipped" data-position="left" data-delay="5" data-tooltip="Eliminar"><a id="btnErase" class="btn-floating red"><i class="large mdi-action-delete"></i></a></li> 
    </ul>
  </div>