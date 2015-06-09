<?php 
      @session_start();
      require_once 'includes/embarcaciones.php';
      $myEmbarcaciones = new Embarcaciones();
?>

<!DOCTYPE html>
  <html>
    <head>
      <meta charset="UTF-8">
      <link type="text/css" rel="stylesheet" href="css/materialize.min.css"  media="screen,projection"/>
      <link type="text/css" href="css/embarcadero.css">
      <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no"/>
    </head>

    <body>
    
    <header>
      <?php require_once 'components/navBar.html'; ?>
    </header>
    


    <div class="container">
      <div class="row">
        <div class="col s12">
        <div class="row"></div>
          <?php if(!empty($_SESSION)): ?>
            <div class="col s12 warning">

              <?php 
                require_once 'components/empleado_options.html';
              ?>

            </div>
          <?php else: ?>
            <div class="col s12 red-text">
              <?php 
                $_POST['msg'] = "Usuario y/o Contraseña incorrectos";
                require_once 'components/error.html';
                ?>
            </div>
          <?php endif ?>
        </div>
      </div>
    </div>
  
    <?php require_once 'components/footer.html'; ?>


      <script type="text/javascript" src="https://code.jquery.com/jquery-2.1.1.min.js"></script>
      <script type="text/javascript" src="js/materialize.min.js"></script>
      <script type="text/javascript" src="js/embarcadero.js"></script>
    </body>
  </html>