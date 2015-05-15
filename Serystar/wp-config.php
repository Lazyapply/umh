<?php
/** 
 * Configuración básica de WordPress.
 *
 * Este archivo contiene las siguientes configuraciones: ajustes de MySQL, prefijo de tablas,
 * claves secretas, idioma de WordPress y ABSPATH. Para obtener más información,
 * visita la página del Codex{@link http://codex.wordpress.org/Editing_wp-config.php Editing
 * wp-config.php} . Los ajustes de MySQL te los proporcionará tu proveedor de alojamiento web.
 *
 * This file is used by the wp-config.php creation script during the
 * installation. You don't have to use the web site, you can just copy this file
 * to "wp-config.php" and fill in the values.
 *
 * @package WordPress
 */

// ** Ajustes de MySQL. Solicita estos datos a tu proveedor de alojamiento web. ** //
/** El nombre de tu base de datos de WordPress */
define('DB_NAME', 'DB2135324');

/** Tu nombre de usuario de MySQL */
define('DB_USER', 'U2135324');

/** Tu contraseña de MySQL */
define('DB_PASSWORD', 'rita1234');

/** Host de MySQL (es muy probable que no necesites cambiarlo) */
define('DB_HOST', 'rdbms.strato.de');

/** Codificación de caracteres para la base de datos. */
define('DB_CHARSET', 'utf8');

/** Cotejamiento de la base de datos. No lo modifiques si tienes dudas. */
define('DB_COLLATE', '');

/**#@+
 * Claves únicas de autentificación.
 *
 * Define cada clave secreta con una frase aleatoria distinta.
 * Puedes generarlas usando el {@link https://api.wordpress.org/secret-key/1.1/salt/ servicio de claves secretas de WordPress}
 * Puedes cambiar las claves en cualquier momento para invalidar todas las cookies existentes. Esto forzará a todos los usuarios a volver a hacer login.
 *
 * @since 2.6.0
 */
define('AUTH_KEY', '/*DI/`CJ5Y1Z~uXv2IdJn[%^FZCrD!9]Ob&O=v}Z_!k$<gb?Wd!cK%ZAcE,y)U=m'); // Cambia esto por tu frase aleatoria.
define('SECURE_AUTH_KEY', '{NL2JM_ZX%|E=G2h+T}YCDz|e9Iq+EMf%/8Xo[N>3Bb-PN@>jz,tGM);|l[=gF-S'); // Cambia esto por tu frase aleatoria.
define('LOGGED_IN_KEY', 'zeVYGX,-?!9][L=%o?r;5%0D =S}z:.dE9fUaF o+@N-YLAu!Gz4H;}h[;Q/(c~%'); // Cambia esto por tu frase aleatoria.
define('NONCE_KEY', '=T2U-$;RJ7$xGk2Q}fg?u$8hh>3 N1OVjJ04]R-T}d@R-OdF93|%$xFk;jx+xwH~'); // Cambia esto por tu frase aleatoria.
define('AUTH_SALT', 'e&0K5%V&V?wTkO+H.27~hD}NM;HXKq-14*{+Cv5ADSz<SO-PW4P9_qZxVf4esiji'); // Cambia esto por tu frase aleatoria.
define('SECURE_AUTH_SALT', 'tDUQ#wAR}0m7j2=h(%Kq<AsdG*6mX_Um? hF= ycWQhjtJ/Q>~u|(-i:QxR,Drc+'); // Cambia esto por tu frase aleatoria.
define('LOGGED_IN_SALT', 'TQb}LU3X={xR`58CT2m{:4pTLtfp~NS9d6%yKFk8+x[4/*rGT9%d7b7liWv|8Q`m'); // Cambia esto por tu frase aleatoria.
define('NONCE_SALT', 'F-|YG!e/!^/w<m*]kKXFn# Ij}<_A{Q pKRdQ|ArS  QS[C[|#wA*A7_N_QFnvP%'); // Cambia esto por tu frase aleatoria.

/**#@-*/

/**
 * Prefijo de la base de datos de WordPress.
 *
 * Cambia el prefijo si deseas instalar multiples blogs en una sola base de datos.
 * Emplea solo números, letras y guión bajo.
 */
$table_prefix  = 'wp_';


/**
 * Para desarrolladores: modo debug de WordPress.
 *
 * Cambia esto a true para activar la muestra de avisos durante el desarrollo.
 * Se recomienda encarecidamente a los desarrolladores de temas y plugins que usen WP_DEBUG
 * en sus entornos de desarrollo.
 */
define('WP_DEBUG', false);

/* ¡Eso es todo, deja de editar! Feliz blogging */

/** WordPress absolute path to the Wordpress directory. */
if ( !defined('ABSPATH') )
	define('ABSPATH', dirname(__FILE__) . '/');

/** Sets up WordPress vars and included files. */
require_once(ABSPATH . 'wp-settings.php');

