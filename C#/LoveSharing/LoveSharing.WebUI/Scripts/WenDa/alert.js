(function ($) {

    var time = 3000;
    (function () {
        $('.alert i ').click(function () {
            $(this).parent().stop().hide();
        })
        $('.alert').mouseover(function () {
            $(this).stop();
            $(this).css('opacity', '1');
        })
        $('.alert').mouseout(function () {
            $(this).fadeOut(time);
        })
    })();

    var alerter = function (txt) {
        $('.alert p').html(txt);
        $('.alert').show().fadeOut(time);
    }
    window.alerter = alerter;

})(jQuery);