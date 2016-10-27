(function ($) {
	//extra settings
	window.bg_1 = $('.bg-1');
	window.bg_3 = $('.bg-3');
    window.bg_2 = $('.bg-2');
    window.loading = $('.loading');
    if (typeof alerter === "undefined"){
    	alerter = alert;
    }

    var wd = window.wd || {};

    wd.editor = function (options) {
        var params = $.extend({}, this.editorDefault, options);    //parameters

        var $this = $(params.Id), //the instance of the box
            handler = params.handler,
            moduleName = params.moduleName,
            triggerdId = params.triggersId;

        var loadedModule = [];


        var init = function () {
            for (var i = 0; i < moduleName.length; i++) {
            	(function(){
	                var thisName = moduleName[i];
	                $(triggerdId[thisName]).click(function () {
	                    bg_2.show();
	                    handler[thisName].run();
	                })
            	}) ();
            }
        };

        var clear = function(){
        	$this.find('.text').val("");
        	for (var i = 0; i < moduleName.length; i++) {
            	(function(){
	                var thisName = moduleName[i];
	                $(triggerdId[thisName]).click(function () {
	                	if (typeof handler[thisName] !== "undefined"){
	                		handler[thisName].clear();
	                	}
	                })
            	}) ();
            }
        };

        return {
        	init : init,
        	clear : clear
        };
    };

    wd.editorDefault = {
        Id : ".wd-eidtor",
        triggersId : {
            code: ".codeTrigger",
            at: ".atTrigger",
            link: ".linkTrigger",
            img: ".imgTrigger"
        },
        handler : {
            code: undefined,
            at: undefined,
            link: undefined,
            img: undefined
        },
        moduleName : ["code", "at", "link", "img"]     
    };

    //construtor
    wd.Adder = function (id) {
    	var _this = this;
    	var $this = $(id);
        this.cancel = function(){
        	_this.close();
        };

        

	    this.close = function () {
	        $this.fadeOut();
	        bg_2.fadeOut();
	    };

		this.open = function () {
	        bg_2.show();
	        $this.show().css('opacity',0);
	        var bodyheight = $('body').height();
	        var scrollTop = $(window).scrollTop();
	        $this.css('top', scrollTop + 40 +'px')
	        	.css('max-height',bodyheight - scrollTop - 100 +'px');
	        $this.animate({'opacity':'1', 'top': scrollTop + 80 + 'px'},600);
	    };
	}


    //
    wd.CodeAdder = function (id, maintextarea) {
        var	$this = this.$this = $(id),
        	$text = $('textarea',$this),
        	_this = this;
       	
       	wd.Adder.call(this,id);
        
        this.clear = function () {
        	$text.val("");
        };

        this.submit = function(){
        	var txt = $text.val();
            var la = $this.find('select option:selected').html();
            txt = wd.cliper(txt);
            if (txt == "") {
                alerter("请输入代码");
                return;
            }
            var insert = "[code=" + la + "]" + txt + "[/code]";
            $(maintextarea).html($(maintextarea).html() + insert);
            _this.close();
            _this.clear();
        };

        this.init = function(){
        	$this.find('.submit').click(_this.submit);
        	$this.find('.cancel').click(_this.close);
        	return true;
        };

        this.instance =  undefined;

        this.run = function(){
        	if (typeof _this.instance === "undefined"){
        		_this.instance = _this.init();
        		$this.removeClass('hide');
        	}
        	_this.open();
        };

        // return this;

    };

    wd.LinkAdder = function(id,maintextarea){
    	var $this = this.$this = $(id);
    	var _this = this;
       	wd.Adder.call(this,id);

    	this.clear = function () {
            $('input',$this).val("");
        };

        this.submit = function(){
        	var title = wd.cliper($this.find('input[type=text]').val());
            var url = $this.find('input[type=url]').val();
            if (title == ""){
            	alerter("请输入标题");
            	return;
            }
            if (wd.urlChecker(url) === false){
            	alerter("请输入正确的url");
            	return;
            }
            var insert = " <a href='" + url + "' >" + title + "</a> ";
            $(insert).appendTo($(maintextarea));
            _this.close();
            _this.clear();
        };

        this.init = function(){
        	$this.find('.submit').click(_this.submit);
        	$this.find('.cancel').click(_this.close);
        	$('.linkAdder').keydown(function (e) {
                if (e.keyCode == 13) {
                    _this.submit();
                }
            });
            return true;
        };

        this.instance = undefined;

        this.run = function(){
        	if (typeof _this.instance === "undefined"){
        		_this.instance = _this.init();
        		$this.removeClass('hide');
        	}
        	_this.open();
        };

    }

    wd.ImgAdder = function(id, maintextarea){
    	var $this = this.$this = $(id);
    	var _this = this;
    	var typing = 0;
       	wd.Adder.call(this,id);

        var fileIds = [];
        var uploader;

        var ArticleAdd = function (id, name, src) {
            var box = $('.imgArticle.template.hide').clone(true);

            box.find('.imgView img').attr('src', src);
            box.find('input').val(name);
            box.find('.imgInfo p').html(name);
            box.find('.fileId').val(id);
            box.removeClass('hide').removeClass('template')
                .insertBefore('.imgCollections .uploader');
        };

        var uploaderInit = function () {
            
            uploader = new WebUploader.Uploader({
                swf: '../webuploader/Uploader.swf',
                server: '/WenDa/Else/Upload',
                pick: {
                    id: '.uploader',
                },
                auto: true,
                resize: false,
                threads: 1,
                accept: {
                    title: 'Images',
                    extensions: 'gif,jpg,jpeg,bmp,png',
                    mimeTypes: 'image/*'
                }


            });

            uploader.on('uploadAccept', function (object, ret) {
                if (ret._raw == "error")
                    alerter("好像出错了，请刷新页面试试");
                else {

                    var files = uploader.getFiles();
                    var file = files[files.length - 1];
                    ArticleAdd(file.id, file.name, ret._raw);
                    $('.submit',$this).removeClass('hide');
                }
            });

            uploader.on('uploadError', function (file) {
                alerter("好像出错了，请刷新页面试试");
            });

        };


        this.clear = function () {
        	for(var i = 0; i < fileIds.length; i ++){
        		uploader.removeFile(fileIds[i]);
        	}
            fileIds = [];
            $('.imgCollections .imgArticle',$this).remove();

        };

        this.submit = function(){
            var imgboxs = $this.find('.imgCollections .imgArticle');
            if (imgboxs.length == 0) {
                alerter('图片不能为空')
                return;
            }
            var imgs = [];
            
            for (var i = 0; i < $this.find('.imgCollections .imgArticle').length; i++) {
                var b = imgboxs.eq(i);
                var img = {
                    title: b.find('.imgInfo p').html(),
                    src: b.find('.imgView img').attr('src')
                };
                imgs.push(img);
            }
            for (var i = 0; i < imgs.length; i++) {
                var img = $('<img src="' + imgs[i].src + '"  title="' + imgs[i].title+'"/>');
                img.appendTo($(maintextarea));
            }
            _this.close();
            _this.clear();
        };

        var init = function () {
            $('.imgInfo p',$this).click(function () {
                $(this).addClass('hide');
                $(this).parent().find('input').removeClass('hide').focus();
                typing = 0;
            });
            $('.imgInfo input',$this).blur(function () {
                var it = $(this);
                var txt = it.val();
                it.addClass('hide');

                it.parent().find('p').removeClass('hide').html(txt);
                typing = 1;
            });

            $('.imgInfo input',$this).keydown(function (key) {
                if (key.keyCode == 13) {
                    var it = $(this);
                    var txt = it.val();
                    it.addClass('hide');

                    it.parent().find('p').removeClass('hide').html(txt);
                    typing = 1;
                }
            })

            $('.icon-remove',$this).click(function () {
                var box = $(this).parent().parent().parent();
                uploader.removeFile(box.find('.fileId').val());
                box.remove();

            })

            uploaderInit();

            $('.imageAdder .submit').click(_this.submit);

            $('.imageAdder .cancel').click(_this.close);

            return true;
        };

        this.instance = undefined;

        this.run = function(){
        	if (typeof _this.instance === "undefined"){
        		$this.removeClass('hide');
        		_this.instance = init();		
        	}
        	_this.open();
        };
    };

    wd.AtAdder = function(id,maintextarea){
    	var $this = this.$this = $(id);
    	var _this = this;
       	wd.Adder.call(this,id);



        var checkSubmit = function () {
            if ($('.userArticle.active',$this).length == 0) {
                $('.submit',$this).hide();
            }
            else {
                $('.submit',$this).show();
            }
        };

        this.clear = function () {
            $('.userArticle',$this).removeClass('active');
            $('.submit',$this).hide();
        };

        this.submit = function () {
            var $users = $this.find('.userArticle.active');
            for (var i = 0; i < $users.length; i++) {
                var b = $users.eq(i);
                var id = b.attr('data-userid');
                var title = b.find('span').html();
                var insert = '[at=' + id+']@'+title + '[/at]';
                $(maintextarea).html($(maintextarea).html() + insert);
            }
            _this.close();
            _this.clear();
        }

        var init = function () {
            $('.userArticle',$this).click(function () {
                if ($(this).hasClass('active')) {
                    $(this).removeClass('active');
                }
                else {
                    $(this).addClass('active');
                }
                checkSubmit();
            });
            $('.submit',$this).click(_this.submit);


            $('.atAdder .cancel').click(_this.close);
            checkSubmit();
            
        };
        this.run = function(){
        	if (typeof _this.instance === "undefined"){
        		_this.instance = init();
        		$this.removeClass('hide');
        	}
        	_this.open();
        };
    }



    wd.cliper = function(c){
            var ret = "";
            var i,j;
            if (typeof c === "undefined"){
            	return "";
            }
            for (i = 0; i < c.length; i++) {
                if (c[i] != ' ' && c[i] != "\n") {
                    break;
                }
            }
            for (j= c.length; j >= 0; j--) {
                if (c[j] != ' ' && c[j] != "\n") {
                    break;
                }
            }
            ret = c.substring(i,j);

            return ret;
    };

    wd.strictCliper = function(c){
        var ret = "";
        var i, j;
        for (i = 0; i < c.length; i++) {
            if (c[i] != ' ' && c[i] != "\n" && c[i] != '\r') {
                break;
            }
        }
        for (j = c.length; j >= 0; j--) {
            if (c[j] != ' ' && c[j] != "\n") {
                break;
            }
        }
        ret = c.substring(i, j);
        var br = /^<div>([(&nbsp;) (<br>)]*)<\/div>/;
        while (br.test(ret) == true) {
            ret = ret.replace(br, "");
        }
        var br = /<div>([(&nbsp; (<br>))]*)<\/div>$/
        while (br.test(ret) == true) {
            ret = ret.replace(br, "");
        }
        return ret;
    };

    wd.urlChecker = function (c) {
        var r = /^http:\/\/([\w-]+\.)+[\w-]+(\/[\w-./?%&=]*)?$/;
        return r.test(c);
    };

    wd.codeReg = /\[code=(.*)\]([\s\S]*)\[\/code\]/;

    wd.contentConvert_code = function(c){
        var reg = wd.codeReg;
        c = c.replace(reg, '<pre><code data-language="$1">$2</code></pre>');
        return c;
    };

    wd.contentConvert = function (c){
    	c = wd.strictCliper(c);        
    	c = wd.contentConvert_code(c);
		var ar = /\[at=(.*)\](.*)\[\/at\]/g;
        c = c.replace(ar, '<span class="at" data-userid="$1">$2</span>');

        return c;
    };



    wd.preView = function (infos, id, On){
    	var $this = $(id);

    	var content = wd.contentConvert(infos.content);

    	if (infos.Anonymity === 1){
			$this.find('.title img').attr('src', wd.AnonymityUserImg);
            $this.find(' .title .name').html("问答用户");
    	}else {
            $this.find('.title img').attr('src', wd.getUserImg());
            $this.find('.title .name').html(wd.getUserName());
        }
        if (typeof On !== "undefined"){
        	var tags = [];
	        var ts = $(infos.tagsId);
	        for (var i = 0; i < ts.length; i ++) {
	            var b = ts.eq(i);
	            $('<a href="#" data-tagid="' + b.attr('data-tagid') + '">' + b.find('span').first().html() + '</a>')
	            	.insertBefore($this.find('.tags .clear-float'));
	        }
        }
        
        var time = new Date(Date.now());

        $this.find('.title .content').html(infos.title);
        $this.find('> .content').html(content);
        $this.find(' ._time').html(
        	time.getFullYear() + '-' + Math.floor(time.getMonth() + 1) + '-' + time.getDate() 
        	+ ' '  + time.getHours() + ':' + time.getMinutes());
    };

    wd.getAnonymity = function(){
    	return $('.onAnonymity').hasClass('active') === true ? 1 : 0;
    };

    wd.getUserId = function(){
    	return $('._UI').val();
    }

    wd.getUserImg = function(){
    	return $('.header .nav .user > a img').attr('src');
    };

    wd.getUserName = function(){
    	return $('.header .nav .user > a span').html();
    };

    wd.isEmpty = function(c){
    	return wd.cliper(c) == ""  ? true : false;
    }

    wd.publish = function(infos, form){

    	infos.title = wd.strictCliper(infos.title);
    	if ( infos.title== "") {
            alerter("请务必填写标题");
            return;
        
        }
        var $this = $(form);
        var ui = wd.getUserId();

        var content = wd.cliper(infos.content);


        var c = content;
        var ar = /\[at=(.*)\](.*)\[\/at\]/;
        var ats = [];
        var exec ;
        while ( exec = ar.exec(c)) {
            ats.push(exec[1]);
            c = c.replace(ar, "");
        }

        var tbox = $('.tagInputed .tagedArticle',$this);
        var tags = [];
        for (var i = 0; i < tbox.length; i++) {
            tags.push(tbox.eq(i).attr('data-tagid'));
        }


        var Anonymity = wd.getAnonymity();
        for (var i = 0; i < ats.length; i++) {
            $('<input type="hidden" value="' + ats[i] + '" name="ats"/>').appendTo('._info');
        }
        for (var i = 0; i < tags.length; i++) {
            $('<input type="hidden" value="' + tags[i] + '" name="tags"/>').appendTo('._info');
        }
        $this.find('input[name=UserId]').val(ui);
        $this.find('input[name=Content]').val(content);
        $this.find('input[name=Anonymity]').val(Anonymity);

        $this.submit();
    };


    wd.timeConvert = function(time){
    	var t = new Date(time);
    	var now = new Date(Date.now());

    	var t_year = t.getFullYear(),
    		t_month = t.getMonth(),
    		t_day = t.getDate(),
    		t_hour = t.getHours(),
    		t_minute = t.getMinutes(),

    		n_year = now.getFullYear(),
    		n_month = now.getMonth();
    		n_day = now.getDate(),
    		n_hour = now.getHours(),
    		n_minute = now.getMinutes();


    	if (t_year === n_year && t_month === n_month && t_day === n_day 
    		&& n_hour === t_hour && n_minute - t_minute < 3){
    		return "刚刚";
    	}

    	if (t_year === n_year && t_month === n_month && t_day === n_day 
    		&& n_hour === t_hour && n_minute - t_minute > 3 ){
    		return n_minute - t_minute + "分钟前";
    	}

    	if (t_year === n_year && t_month === n_month && t_day === n_day ){
    		return n_hour - t_hour + "小时前";
    	}

    	if ( (t_year === n_year && t_month === n_month && t_day - n_day === 1)
    		|| (t_year - n_year == 1 && t_month === 0 && t_day === 1) ){
    		return "昨天";
    	}

    	return t_year + "-" + t_month + ' ' + t_hour + ":" + t_minute;
    }


    wd.ui = wd.getUserId();

   	wd.AnonymityUserImg = "../../../Images/WenDaStyle/userhide.png";

    wd.anonymityHandler = function(){
        $('.onAnonymity > div[class^=float]').click(function(){
             var $this = $(this);
            var $anonymity = $this.parent();
            if ($anonymity.hasClass('active')){
                $anonymity.removeClass('active');
            }
            else{
                $anonymity.addClass('active');
            }
        })
    };

    wd.AnswersViewHelper = function(){

        var $this = $('.AnswersViewHelper');
        var $answers = $('.wd-answer');

        $answers.eq(0).find('.AnswersViewHelper .prev').hide();
        $answers.last().find('.AnswersViewHelper .next').hide();

        $('.prev', $this).click(function(){
            var index = $('.prev', $this).index(this);
            $('html,body').animate({"scrollTop": 
                $answers.eq(--index).offset().top - 40+ 'px'},600);
        });

        $('.next', $this).click(function(){
            var index = $('.next', $this).index(this);
            $('html,body').animate({"scrollTop": 
                $answers.eq( ++index ).offset().top - 40+ 'px'},600);
        });

        $('.wd-answer').mousemove(function(e){
            var $this = $(this);
            $this.find('.AnswersViewHelper').css('top', e.pageY  -  $this.offset().top - 30  +'px');

        })
    };

    wd.oneRecommender =function (on_id, box_id) {
        var ui = wd.getUserId();
        var on = $(on_id);
        var $this = $(box_id);

        var open = function(){
            bg_1.show();
            $this.show();
        };
        

        var close = function(){
            $this.hide();
            bg_1.hide();
        };

        var clear = function(){
            $this.find('textarea').val("");
        };

        var submit = function(){
            var txt = wd.cliper($this.find('textarea').val());

            
            if (ui == null || ui == ""){
                alerter("请先登录");
                return;
            }

            if (txt == ""){
                alterer("请输入内容");
                return;
            }

            $.ajax({
                url: "/WenDa/WenDa/GetOne",
                data :{
                    UserId : ui,
                    Content : txt,
                },
                success: function (r) {
                    var ret = $.parseJSON(r);
                    if (ret.Status == 0) {
                        alerter(ret.Message);
                    } else {
                        close();
                        clear();
                        alerter("感谢您的推荐");
                    }
                    
                },
                complete: function () {
                },
                error: function (ret) {
                    alerter(ret.statusText);
                }
            })
        };

        

        $this.find('.cancel').click(close);

        $this.find('.submit').click(submit);


        $(on_id).click(function () {
            if (typeof ui === "undefined") {
                alerter("请先登录");
                return;
            }
            open();
        });

        

    };



    window.wd = wd;
})(jQuery);