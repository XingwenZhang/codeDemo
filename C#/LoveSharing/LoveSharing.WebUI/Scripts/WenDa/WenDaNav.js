(function ($) {

    var wd = window.wd || {};

    wd.loaidng = $('.loaidng');

    wd.nav = function(id,widgets){
        var $this = $(id);

        for(var i = 0; i < widgets.length; i ++){
            (function(){
                var th = i;
                $(widgets[th].triggerId).click(function(){
                    // console.log(th);
                    widgets[th].handler(this);
                });
            })();
        }

    };

    wd.enumStatus = {
        False : 0,  //错误
        Succeed : 1    //成功
    };

    wd.enumType = {
        question: 0,
        answer : 1,
        topic: 2,
        tag : 3,
        user : 4,
        adminer : 5
    };

    wd.Action = function(options){


        var _this = this;
        var $this ;
        this.triggerId = options.id;



        this.commit = function(infos){
            var url = options.inactiveUrl;
            if (infos.active ){
                url = options.activeUrl;
            }
            $.ajax({
                url: url,
                type: "POST",
                data: {
                    UserId: wd.ui,
                    RelativeId: infos.id,
                    type: infos.type,
                    anonymity : infos.anonymity
                },
                success: function (r) {
                    var ret = $.parseJSON(r);
                    if (ret.Status == wd.enumStatus.False) {
                        alerter(ret.Message);
                    } else if(ret.Status == wd.enumStatus.Succeed){
                        if (infos.active) {
                            alerter(options.word + " - 1");
                            $this.removeClass('active');
                            $this.find('.txt').html(options.word);
                            var c = $this.find('.count');
                            c.html(parseInt(c.html()) - 1);
                        } else {
                            alerter(options.word  + "+ 1");
                            $this.addClass('active');
                            $this.find('.txt').html("取消" + options.word);
                            var c = $this.find('.count');
                            c.html(parseInt(c.html()) + 1);
                        }
                    }
                },
                error: function (info) {
                    alerter(info.statusText);
                }
            });
        };

        var getInfos = function(){
            return {
                url : options.inactiveUrl,
                id : $this.attr('data-id'),
                anonymity : wd.getAnonymity(),
                type : $this.attr('data-type'),
                active : $this.hasClass('active')
            };

        };

        this.handler = function(target){
            $this = $(target);
            ui = wd.getUserId();
            if (typeof ui === "undefined"){
                alerter("请先登录");
                return ;
            }

            _this.commit(getInfos());
        }
    };

    wd.replier = function(options){

        var $this ;
        var _this = this;
        this.triggerId = options.id;

        var _infos;
        var _target ;

        var getInfos = function(){
            return {
                id : $this.attr('data-id'),
                questionId : $this.attr('data-questionid'),
                type : $this.attr('data-type'),
                title : $this.parent().parent().parent().find('.title .name').html(),
                no : $this.attr('data-no'),
                visible :  $this.attr('data-visible'),
                anonymity : wd.getAnonymity()
            };
        };

        
        var instance = undefined;

        

        var editor = function(){

            var $this = $('.wd-reply-wrap');

            var editor = wd.editor({
                handler: {
                    at: new wd.AtAdder('.atAdder', '.wd-editor .text'),
                    code: new wd.CodeAdder('.codeAdder', '.wd-editor .text'),
                    link: new wd.LinkAdder('.linkAdder', '.wd-editor .text'),
                    img: new wd.ImgAdder('.imageAdder', '.wd-editor .text')
                }
            });

            var close = function(){
                $this.hide();
                bg_1.hide();
            };

            var clear = function(){
                editor.clear();
            };
            

            

            var show = function(){
                bg_1.show();
                $this.removeClass('hide').show();

                var top = $(window).scrollTop();
                $this.css('max-height', $('body').height() - top  - 80 + 'px');
                $this.css('top', top + 'px').css('opacity', 0);
                $this.animate({ "opacity": "1", 'top': top + 30 + 'px' }, 400, "swing");
            };

            var init = function(){
                editor.init();

                $this.find('.replyBar .cancel').click(close);

                $this.find('.onView').click(function () {
                    
                    var infos = $.extend({
                        content : wd.strictCliper($this.find('.wd-editor .text').html())
                    }, _infos);


                    if (infos.content == ""){
                        alerter("请输入内容");
                        return false;
                    }

                    wd.preView(infos,'.View .wdArticle');
                    bg_2.show();

                    var $v = $('.View');
            
                    $v.removeClass('hide');
                    $v.css('top', $(window).scrollTop());
                    var bw = $('body').height();
                    $('.wd-wrap',$v).css('max-height', bw - $(window).scrollTop() - 140 + 'px');

                });

                $('.View .ok').click(function(){
                    bg_2.hide();
                    $('.View').addClass('hide');
                });

                $('.onSubmit').click(function(){

                    var infos = $.extend({
                        content : wd.strictCliper($this.find('.wd-editor .text').html())
                    }, _infos);

                    if (infos.content == ""){
                        alerter("请输入内容");
                        return false;
                    }

                    var content = wd.cliper(infos.content);


                    var c = content;
                    var ar = /\[at=(.*)\](.*)\[\/at\]/;
                    var ats = [];
                    var exec ;
                    while ( exec = ar.exec(c)) {
                        ats.push(exec[1]);
                        c = c.replace(ar, "");
                    }


                    $.ajax({
                        url: "/WenDa/Question/Reply",
                        type: "POST",
                        data: {
                            Content: infos.content,
                            UserId: wd.ui,
                            Anonymity: infos.anonymity,
                            Type: infos.type,
                            RelativeId: infos.id,
                            RelativeQuestionId: infos.questionId,
                            No: infos.no,
                            AnswerederVisible : infos.visible,
                            Ats : ats,
                        },
                        beforeSend: function () {
                            loading.fadeIn(400);
                        },
                        error: function (ret) {
                            alerter(ret.statusText);
                        },
                        success: function (r) {
                            var ret = $.parseJSON(r);
                            if (ret.Status == wd.enumStatus.False) {
                                alerter(ret.Message);
                            } else {
                                alerter("评论 + 1");
                                var $li = $(_target);
                                $li.addClass('active');
                                var $count = $li.find('span > span');
                                $count.html(Math.floor($count.html()) + 1);
                                clear();
                            }
                        },
                        complete: function () {
                            loading.fadeOut(400, "swing");
                            close();
                        }
                    })
                });


            };


            

            return {
                init : init,
                run : show
            };

        }();

        // editor.init();
        

        var init = function(){
            editor.init();
        };

        this.handler = function(target){
            _target = target;
            $this = $(target);
            _infos = getInfos();
            ui = wd.getUserId();
            if (typeof ui === "undefined"){
                alerter("请先登录");
                return ;
            }
            if (typeof instance === "undefined"){
                init();
            }
            editor.run();
        };

    };

    window.wd = wd;

    
        
})(jQuery);