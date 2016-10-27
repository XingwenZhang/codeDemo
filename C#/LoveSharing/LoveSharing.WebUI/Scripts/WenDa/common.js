(function ($) {

    $('.anonymitySwitch button').click(function () {
        var $it = $(this);
        if ($it.hasClass('active')) {
            $it.removeClass('active');
        } else {
            $it.addClass('active');
        }
    }); 


})(jQuery);