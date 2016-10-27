(function ($,B) {
    var wd = window.wd || {};

    wd.login = function (options){

        var getInfos = function (){
            return {
                Email : $(options.emailId).val(),
                Password : $(options.passwordId).val()
            };
        };

        var EmailRegExp =  /^(\w-*\.*)+@(\w-?)+(\.\w{2,})+$/;
        var emailCheck = function (c) {
            var r = /^(\w-*\.*)+@(\w-?)+(\.\w{2,})+$/;
            return r.test(c);
        };

        var check = function(infos){
            var success = 1;
            if (!emailCheck(infos.Email)){
                options.emailError();
                success = 0;
            } else{
                options.emailSuccess();
            }
            if (infos.Password == "" ){
                options.passwordError();
                success = 0;
            } else{
                options.passwordSuccess();
            }
            
            if (success == 0){
                return false;
            }
            
            return true;
            
        };

        var submit = function (infos){
            $.ajax({
                url : options.url,
                type : "POST",
                data : infos,
                beforeSend : options.beforeSend,
                success : options.success,
                error : options.error
            });

        };

        var run = function(){
            var infos = getInfos();
            if (check(infos)){
                submit(infos);
            };
            
        };

        return {
            run:run,
            emailCheck : emailCheck
        };


    };

    wd.register = function(options){
        var getInfos = function(){
            return {
                Email : $(options.emailId).val(),
                Password : $(options.passwordId).val(),
                Repassword : $(options.repasswordId).val(),
                Motto : $(options.mottoId).val(),
                Name : $(options.nameId).val(),
                Phone : $(options.phoneId).val(),
                Motto : $(options.mottoId).val(),
                ImageUrl : $(options.imageUrlId).val()
            };
        };

        var basicCheck = function(infos){
            var success = 1;
            for(var i = 0; i < options.basicInfo.length; i ++){
                var it = options.basicInfo[i];
                if (it.attr === "Repassword"){
                    if(it.check(infos[it.attr],infos["Password"])){
                        it.error();
                        success = 0;
                    }else{
                        it.success();
                    }
                }
                else if(!it.check(infos[it.attr])){
                    it.error();
                    success = 0;
                }else{
                    it.success();
                }
            }
            if (success === 1){
                return true;
            } else{
                return false;
            }
        };

        var avatorCheck = function (infos){
            if (infos.ImageUrl == ""){
                options.avatorError ();
                return false;
            } else{
                options.avatorSuccess ();
            }
            return true;
        };

        var submit = function (infos){
            $.ajax({
                url : options.url,
                data : infos,
                type:"POST",
                beforeSend : options.beforeSend,
                success : options.success,
                error : options.error
            })
        };

        var run = function(){
            var infos = getInfos();
            if (basicCheck(infos) && avatorCheck(infos)){
                submit(infos);
            };  
        };

        return {
            basicCheck : basicCheck,
            avatorCheck : avatorCheck,
            submit : submit,
            run:run
        };
    };

    window.wd = wd;


})(jQuery,Base);