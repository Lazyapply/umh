<?xml version="1.0"?>
<xsl:stylesheet version = "1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
xmlns:xlink="http://www.w3.org/1999/xlink">



<xsl:template match="/">
   <xsl:apply-templates/>
   
</xsl:template>
<xsl:template match="basedatos">
   <html>
   <head>
   <h1><strong> BASE DE DATOS EMPRESA</strong></h1>
   <p></p>
   </head>
   <body>
      <xsl:apply-templates/>
   </body>
   </html>
</xsl:template>


 <xsl:template match="empleado">
     <br/><br/> 
	  <h1> EMPLEADO </h1> 
     <xsl:apply-templates/>
    <br/><br/> 
</xsl:template>

<xsl:template match="num_emp">
	<h3> NUMERO: </h3>
	<strong><xsl:value-of select="."/></strong>
	<br/>
</xsl:template>

<xsl:template match="nom_emp">
	<h3> NOMBRE: </h3>
	<em><xsl:value-of select="."/></em>
	<br/>
</xsl:template>

<xsl:template match="sueldo">
	<h3> SUELDO: </h3>
	<em><xsl:value-of select="."/></em>
	<br/>
</xsl:template>

<xsl:template match="num_dep">
	<h3> NUMDEP: </h3>
	<em><xsl:value-of select="."/></em>
	<br/>
</xsl:template>


<xsl:template match="departamento">
	
	 <h1> DEPARTAMENTO </h1> 
			<xsl:apply-templates/>
		<br/>
   
	 
</xsl:template>

<xsl:template match="nom_dep">
	<h3> NOMBRE: </h3>
	<em><xsl:value-of select="."/></em>
	<br/>
</xsl:template>

<xsl:template match="presupuesto">
	<h3> PRESUPUESTO: </h3>
	<em><xsl:value-of select="."/></em>
	<br/>
</xsl:template>


</xsl:stylesheet>
