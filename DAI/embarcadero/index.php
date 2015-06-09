<!DOCTYPE html>
  <html>
    <head>
      <meta charset="UTF-8">

      <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no"/>
      <link type="text/css" rel="stylesheet" href="css/materialize.min.css"  media="screen,projection"/>
      <link type="text/css" href="css/embarcadero.css">
    </head>

    <body>
    
    <header>
      <?php require_once 'components/navBar.html'; ?>
    </header>
    
    
    <main>
    <div class="container">
      <div class="row">
        <div class="col s12">
          <?php require_once 'components/slider.html'; ?>
        </div>
      </div>
    </div>
    </main>
  
      <?php require_once 'components/footer.html' ?>
   



      <script type="text/javascript" src="https://code.jquery.com/jquery-2.1.1.min.js"></script>
      <script type="text/javascript" src="js/materialize.min.js"></script>
      <script type="text/javascript" src="js/embarcadero.js"></script>
    </body>
  </html>