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

					<xsl:when test="enunciado/@tipo='codificadam'">
						<xsl:for-each select="respuesta">
							<p><input type="checkbox" name="respuesta" /><xsl:value-of select="."/></p>
						</xsl:for-each>
					</xsl:when>

					<xsl:when test="enunciado/@tipo='codificadas'">
						<xsl:for-each select="respuesta">
							<p><input type="radio" name="respuesta" /><xsl:value-of select="normalize-space(.)"/></p>
						</xsl:for-each>
					</xsl:when>
					
					<xsl:when test="enunciado/@tipo='textolibre'">
						<xsl:variable name="cols" select="enunciado/@cols"/>
						<xsl:variable name="rows" select="enunciado/@rows"/>
						<textarea name="text" cols="{$cols}" rows="{$rows}" scroll="no"></textarea>
					</xsl:when>

					<xsl:when test="enunciado/@tipo='numerica'">
						<xsl:variable name="min" select="enunciado/@min"/>
						<xsl:variable name="max" select="enunciado/@max"/>
						<p><input type="number" min="{$min}" max="{$max}"/></p>
					</xsl:when>

					<xsl:when test="enunciado/@tipo='logica'">
						<xsl:for-each select="respuesta">
						<p><input type="radio" name="logica"/><xsl:value-of select="normalize-space(.)"/></p>
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