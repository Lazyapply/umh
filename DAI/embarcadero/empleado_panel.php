<?php 
      @session_start();
      require_once 'includes/embarcaciones.php';
      $myEmbarcaciones = new Embarcaciones();
?>

<!DOCTYPE html>
  <html>
   <?php require_once 'components/header.html' ?>

    <body>
    
    <header>
      <?php require_once 'components/navBar.html'; ?>
    </header>
    

    <main>
    <div class="container">
      <div class="row">
        <div class="col s12">
      
          <?php if(!empty($_SESSION)): ?>
            <div class="col s12 warning">
              <div id="employeeContent">
              <?php 
                require_once 'components/list_employees.php';
              ?>
              </div>
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
  </main>
   <?php require_once 'components/footer.html'; ?>
   <script type="text/javascript" src="js/jquery-2.1.3.min.js"></script>
<script type="text/javascript" src="js/materialize.min.js"></script>
<script type="text/javascript" src="js/embarcadero.js"></script>
    </body>
  </html>