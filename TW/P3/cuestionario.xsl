<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version = "1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="cuestionario">
		<html>
			<head>
				<link rel="stylesheet" type="text/css" href="css/main-xslt.css" />
				<meta http-equiv="Content-Type" content="text/html;charset=UTF-8" />
				<title>Cuestionario - <xsl:value-of select="@id"/></title>
			</head>
			<body>
				<div class="container">
					<div class="cuestionario">
						<div class="titulo">
							<h1>Cuestionario automatizado online</h1>
							<div class="info">
								<h3>Información del cuestionario</h3>
								<p><h4>Nombre: <xsl:value-of select="@tema"/></h4></p>
								<p><h4>Identificador: <xsl:value-of select="@id"/></h4></p>
							</div>
						</div>
						<!-- id="T1-1" correcta="T1-1-2" fecha-creacion="28/12/2014" autor="Diego"> -->
						<div class="cuerpo">
							<form action="#" name="cuestionario" method="GET">
							<xsl:apply-templates select="pregunta"/>
							<input type="reset" value="borrar"/>
							<input type="submit" value="Enviar"/>
							</form>
						</div>
					</div>
				</div>
				
			</body>
		</html>
	</xsl:template>
	


	<xsl:template match="pregunta">
		<div class="info-pregunta">
			ID:<xsl:value-of select="@id"/>
			Fecha:<xsl:value-of select="@fecha-creacion"/>
			Autor:<xsl:value-of select="@autor"/>
		</div>
		<div class="pregunta">
			<xsl:apply-templates/>
				<xsl:choose>
					<xsl:when test="enunciado/@tipo='codificada'">
						<xsl:for-each select="respuesta">
							<xsl:value-of select="."/>
						</xsl:for-each>
					</xsl:when>
					<xsl:otherwise>
						<h1>N</h1>
					</xsl:otherwise>
				</xsl:choose>
		</div>
		<div class="respuestas">
			<xsl:apply-templates select="respuesta"/>
		</div>
	</xsl:template>





	<xsl:template match="enunciado">
		<div class="enunciado"><xsl:value-of select="text()"/></div>
	</xsl:template>

	

	<xsl:template match="respuesta">

		<div class="respuesta">
			<!-- <xsl:value-of select="/pregunta/enunciado"/> -->
			

		</div>
	</xsl:template>
</xsl:stylesheet>