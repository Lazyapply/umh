<?xml version="1.0"?>
<xsl:stylesheet version = "1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
   <xsl:apply-templates/>
   
</xsl:template>

<xsl:template match="novedades">
   <html>
   <head>
   <h1> IBERIAN RECORDS</h1>
 <!--   <link rel="stylesheet" href="cssxsl.css" media="screen" />  -->
   </head>
   <body>
	<a href="wwww.iberian-records.com"> INFORMACION</a>
	
      <!-- Con esto se consigue que solo se aplique a libro
			<xsl:apply-templates select="libro"/>  
	  -->
	  
	 	  <xsl:apply-templates/>
   </body>
   </html>
</xsl:template>



<xsl:template match="fecha">
   <h1> Lista de novedades a fecha: 
	<xsl:value-of select="."/>
   </h1>
</xsl:template>

 <xsl:template match="disco">
     <h2><u>
	 
       <font color="#AFFB02"><xsl:value-of select="@genero"/></font>
	   <xsl:choose>
			<xsl:when test='@genero="pop"'>
				<h3> EL POP DE SIEMPRE </h3>
			</xsl:when>
			<xsl:when test='@genero="rock"'>
				<h3> LARGA VIDA AL ROCKANROL </h3>
			</xsl:when>
		</xsl:choose>
		 
	 </u></h2>
	 <br/><br/> 
	<br/><br/>  
     <xsl:apply-templates/>   
    <br/><br/> 
		 
</xsl:template>


<xsl:template match="interprete">
	<h2>INTERPRETE: </h2> 
     <xsl:apply-templates/>
    <br/><br/> 
</xsl:template>

<xsl:template match="libro">
	<h2>LIBRO </h2> 
     <xsl:apply-templates/>
    <br/><br/> 
</xsl:template>

<xsl:template match="titulo">
	<em><xsl:value-of select="."/></em>
	<br/>
</xsl:template>

<xsl:template match="direccion">
	<font color="#FF0000"><em><xsl:value-of select="."/></em></font>
	<br/>
</xsl:template>
<xsl:template match="autor">
	<em><xsl:value-of select="."/></em>
	<br/>
</xsl:template>


</xsl:stylesheet>
