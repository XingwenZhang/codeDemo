(function ($,B) {
    var Login = function (preurl) {
        


        var PasswordChecker = /^\w+$/;

        var passwordCheck = function (c) {
            return PasswordChecker.test(c);
        };

        var enumStatus = {
            login: 0,
            register: 1
        },
            status = enumStatus.login,
            enumReturnStatus = {
                Success: 1,
                False: 0
            };

        var warningClear = function () {
            $('.warning').parent().hide();
        };

        var showClear = function () {
            warningClear();
            
        };

        var nameCheck = function (c) {

            if (c == "" || c.length > 20) return false;
            for (var i = 0; i < c.length; i++) {
                if (i != " ") return true;
            }
            return false;

        };

        var finish = function () {
            warningClear();
            var url = preurl + "/Login";
            var flag = 0;
            var email = $('.EmaiInput input').val();
            var password = $('.password input').val();
            if (B.emailCheck(email) == false) {
                $('.EmailWarning').slideDown();
                flag = 1;
            }
            if (passwordCheck(password) == false) {
                $('.PasswordWarning').slideDown();
                flag = 1;
            }
            var name, repassword, tel;
            if (status == enumStatus.register) {
                name = $('.NameInput input').val();
                repassword = $('.passwordConfirm input').val();
                tel = $('.TelInput input').val();
                if (nameCheck(name) == false) {
                    $('.NameWarning').slideDown();
                    flag = 1;
                }
                if (repassword != password) {
                    $('.RepasswordWarning').slideDown();
                    flag = 1;
                }
                url = preurl + "/Register";
            }
            if (flag == 0) {

                var loading = $('.loading');
                
                if (status == enumStatus.register) {
                    $.ajax({
                        url: url,
                        type: "POST",
                        data: {
                            Name: name,
                            Email: email,
                            Password: password,
                        },
                        success: function (r) {
                            var ret = $.parseJSON(r);
                            if (ret.Status == enumReturnStatus.False) {
                                loading.hide();
                                alerter(ret.Message);
                            }
                            else {
                                window.location = ret.Message;
                            }
                        },
                        error: function (info) {
                            alerter(info.statusText);
                            loading.hide();
                        },
                        beforeSend: function () {
                            loading.show();
                        },
                    })
                }
                if (status == enumStatus.login) {
                    $.ajax({
                        url: url,
                        type: "POST",
                        data: {
                            Email: email,
                            Password: password
                        },
                        success: function (r) {
                            var ret = $.parseJSON(r);
                            if (ret.Status == enumReturnStatus.False) {
                                loading.hide();
                                alerter(ret.Message);
                            }
                            else {
                                window.location = ret.Message;
                            }

                        },

                        error: function (info) {
                            alerter(info.statusText);
                            loading.hide();
                        },
                        beforeSend: function () {
                            loading.show();
                        }
                    })
                }
            }
        };

        $('.loginOption').click(function () {
            if ($(this).hasClass('active')) {
                return;
            }
            $(this).addClass('active');
            $('.registerOption').removeClass('active');
            warningClear();
            $('.passwordConfirm').hide();
            $('.NameInput').hide();
            $('.TelInput').hide();
            $('.submit button').html("登录");
            status = enumStatus.login;
        });

        $('.registerOption').click(function () {
            if ($(this).hasClass('active')) {
                return;
            }
            $(this).addClass('active');
            $('.loginOption').removeClass('active');
            warningClear();
            $('.passwordConfirm').show();
            $('.NameInput').show();
            $('.TelInput').show();
            $('.submit button').html("注册");
            status = enumStatus.register;
        });

        $('.submit button').click(finish);
        $('.LR').keydown(function (e) {
            if (e.keyCode == 13) {
                finish();
            }
        });



    };

    window.Login = Login;
})(jQuery,Base);