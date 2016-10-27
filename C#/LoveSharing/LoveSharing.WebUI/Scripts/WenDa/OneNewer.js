(function ($, B) {

    var One = function (on_id, box_id) {

        var ui = 123;//$('._UI').val();
        var on = $(on_id);
        var box = $(box_id);
        

        if (typeof alerter == "undefinded"){
            alerter = alert;
        }

        var Box = function () {

            var b = box;
            var bg = $('.blackBg');
            

            var show = function () {
                bg.show();
                b.show();
            };

            var close = function () {
                bg.hide();
                b.hide();
            };

            var clear = function () {
                b.find('textarea').val("");
            };

            b.find('.cancel').click(function () {
                close();
            });

            b.find('.submit').click(function () {
                var txt = b.find('textarea').val();
                
                var loading = $('.loading');
                $.ajax({
                    url: "/WenDa/WenDa/GetOne",
                    type: "POST",
                    data: {
                        UserId : ui,
                        Content : txt
                    },
                    beforeSend: function () {
                        
                        loading.show();
                    },
                    success: function (r) {
                        console.log(r);
                        var ret = $.parseJSON(r);
                        if (ret.Status == 0) {
                            alerter(ret.Message);
                        } else {
                            close();
                            clear();
                            alterer("感谢您的推荐");
                        }
                        
                    },
                    complete: function () {
                        loading.hide();
                    },
                    error: function (ret) {
                        alerter(ret.statusText);
                    }
                });
            });

            return {
                show : show
            }
        }();


        on.click(function () {
            if (typeof ui === "undefined") {
                alerter("请先登录");
                return;
            }
            Box.show();
        });

        

    };

    window.One = One;

})(jQuery, Base);