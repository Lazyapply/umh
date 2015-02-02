<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<!-- Estructura del documento -->
	<xsl:template match="examen">
		<html>
			<head>
				<link rel="stylesheet" type="text/css" href="css/main-xslt.css" />
				<meta http-equiv="Content-Type" content="text/html;charset=ISO-8859-1" />
				<title>Examen ATW</title>
			</head>
			<body>
				<div class="container">
					<xsl:apply-templates/>
				</div>
			</body>
		</html>
	</xsl:template>

	<!-- nodos -->

	<!-- nodo cuestion -->
	<xsl:template match="cuestion">
		<xsl:choose>
			<xsl:when test="@autor = 'Antonio'">
				<div id="cuestion">
					<xsl:apply-templates/>
				</div>
			</xsl:when>
		</xsl:choose>
	</xsl:template>


	<!-- nodo materia -->
	<xsl:template match="materia">
		<h3><xsl:value-of select="."/></h3>
	</xsl:template>

	<!-- nodo enunciado -->
	<xsl:template match="enunciado">
		<h3><xsl:value-of select="."/></h3>
	</xsl:template>

	<!-- nodo respuesta -->
	<xsl:template match="respuesta">
		<xsl:choose>
			<xsl:when test="@correcta='si'">
				<strong><xsl:value-of select="."/></strong><br/>
			</xsl:when>
			<xsl:when test="@correcta='no'">
				<xsl:value-of select="."/><br/>
			</xsl:when>
		</xsl:choose>
	</xsl:template>

</xsl:stylesheet>