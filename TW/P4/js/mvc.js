$(function() {
 
    var enlace_movil = $('#nav-responsive'),
        menu = $('#responsive-menu').find('ul');

    enlace_movil.on('click', function (e) {
        e.preventDefault();

        var esto = $(this);

        esto.toggleClass('nav-active');
        menu.toggleClass('open-responsive-menu');
    })
 
});