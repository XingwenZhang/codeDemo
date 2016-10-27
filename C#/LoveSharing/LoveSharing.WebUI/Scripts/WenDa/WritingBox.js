(function ($) {
    var bg = $('.Writing-wrap .wbg');
    var ImgAdder = function (parent) {

        var typing = 0;

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
                    $('.imageAdder .submit').removeClass('hide');
                }
            });

            uploader.on('uploadError', function (file) {
                alerter("好像出错了，请刷新页面试试");
            });

        };

        var close = function () {
            $('.imageAdder').hide(400);
            bg.hide();
        };

        var clear = function () {
            fileIds = [];
            $('.imageAdder .imgCollections .imgArticle').remove();
        };

        var init = function () {
            $('.imgInfo p').click(function () {
                $(this).addClass('hide');
                $(this).parent().find('input').removeClass('hide').focus();
                typing = 0;
            });
            $('.imgInfo input').blur(function () {
                var it = $(this);
                var txt = it.val();
                it.addClass('hide');

                it.parent().find('p').removeClass('hide').html(txt);
                typing = 1;
            });

            $('.imgInfo input').keydown(function (key) {
                if (key.keyCode == 13) {
                    var it = $(this);
                    var txt = it.val();
                    it.addClass('hide');

                    it.parent().find('p').removeClass('hide').html(txt);
                    typing = 1;
                }
            })

            $('.icon-remove').click(function () {
                var box = $(this).parent().parent().parent();
                uploader.removeFile(box.find('.fileId').val());
                box.remove();

            })

            uploaderInit();

            $('.imageAdder .submit').click(function () {
                var box = $('.imageAdder');
                var imgboxs = box.find('.imgCollections .imgArticle');
                if (imgboxs.length == 0) {
                    alerter('图片不能为空')
                    return;
                }
                var imgs = [];
                
                for (var i = 0; i < box.find('.imgCollections .imgArticle').length; i++) {
                    var b = imgboxs.eq(i);
                    var img = {
                        title: b.find('.imgInfo p').html(),
                        src: b.find('.imgView img').attr('src')
                    };
                    parent.pushImg(img);
                    imgs.push(img);
                }
                for (var i = 0; i < imgs.length; i++) {
                    var img = $('<img src="' + imgs[i].src + '"  title="' + imgs[i].title+'"/>');
                    img.appendTo(parent.area);
                }
                close();
                clear();
            });

            $('.imageAdder .cancel').click(close);

        }

        return {
            init: init,
            clear : clear
        }

    }

    var CodeAdder = function (parent) {

        var close = function () {
            $('.codeAdder').hide(400);
            bg.hide();
        };

        var clear = function () {
            $('.codeAdder textarea').val("");
        }

        var checker = function (c) {

            if (c == "" || c == "\n") {
                return false;
            }
            
            for (var i = 0; i < c.length; i++) {
                if (c[i] != " " && c[i] != "\n") {
                    return true;
                }
            }
            return false;

        };

        var cliper = function (c) {
            var ret = "";
            var i,j;
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


        var init = function () {
            $('.codeAdder .submit').click(function () {
                var box = $('.codeAdder');
                var la = box.find('select option:selected').html();
                var code = box.find('textarea').val();
                if (checker(code) == false) {
                    alerter("请输入代码");
                    return;
                }
                code = cliper(code);
                var push = {
                    la: la,
                    content: code
                };
                parent.pushCode(push);
                var insert = "[code=" + la + "]" + code + "[/code]";
                parent.area.html(parent.area.html() + insert);
                close();
                clear();
            });

            $('.codeAdder .cancel').click(close);
        };

        return {
            init: init,
            checker: checker,
            cliper: cliper,
            clear : clear
        };

    };

    var LinkAdder = function (parent) {

        var close = function () {
            $('.linkAdder').hide(400);
            bg.hide();
        };

        var clear = function () {
            $('.linkAdder input').val("");
        };

        var checker = function (c) {
            if (c === "" || typeof c === "undefinded" || c == "undefinded") {
                return false;
            }
            for (var i = 0; i < c.length; i++) {
                if (c[i] != " ") {
                    return true;
                }
            }
            return false;
        };

        var urlChecker = function (c) {
            var r = /^http:\/\/([\w-]+\.)+[\w-]+(\/[\w-./?%&=]*)?$/;
            return r.test(c);
        };

        var finish = function () {
            var box = $('.linkAdder');
            var title = box.find('input[type=text]').val();
            var url = box.find('input[type=url]').val();
            if (checker(title) == false) {
                alerter("请输标题");
                return;
            }
            if (urlChecker(url) == false) {
                alerter("请输入正确地址");
                return;
            }
            var push = {
                title: title,
                url: url
            };
            parent.pushLink(push);
            var insert = " <a href='" + url + "' >" + title + "</a> ";
            $(insert).appendTo(parent.area);
            close();
            clear();
        };

        var init = function () {
            $('.linkAdder .submit').click(finish);

            $('.linkAdder').keydown(function (e) {
                if (e.keyCode == 13) {
                    finish();
                }
            })

            $('.linkAdder .cancel').click(close);
        };

        return {
            init: init,
            clear: clear
        };

    };

    var AtAdder = function (parent) {
        var close = function () {
            $('.atAdder').hide(400);
            bg.hide();
        };

        var checkSubmit = function () {
            if ($('.atAdder .userArticle.active').length == 0) {
                $('.atAdder .submit').hide();
            }
            else {
                $('.atAdder .submit').show();
            }
        };

        var clear = function () {
            $('.atAdder .userArticle').removeClass('active');
            $('.atAdder .submit').hide();
        };

        var init = function () {
            $('.atAdder .userArticle').click(function () {
                var box = $(this);
                if (box.hasClass('active')) {
                    box.removeClass('active');
                }
                else {
                    box.addClass('active');
                }
                checkSubmit();
            });
            $('.atAdder .submit').click(function () {
                var box = $('.atAdder .userArticle.active');
                for (var i = 0; i < box.length; i++) {
                    var b = box.eq(i);
                    var id = b.attr('data-userid');
                    var title = b.find('span').html();
                    parent.pushAt(id);
                    var insert = '[at=' + id+']@'+title + '[/at]';
                    parent.area.html(parent.area.html() + insert);
                }
                close();
                clear();
            });


            $('.atAdder .cancel').click(close);
            checkSubmit();
            
        };
        return {
            init: init,
            clear : clear
        };

    };


    var WritingBox = function (options) {
        
        //default params
        var defaults = {
            id: ".WritingBox"
        };

        //declare varibles
        var o = $.extend({}, defaults, options),
            id = o.id,
            h = $(id),
            scrollTop = $(window).scrollTop(),
            windowHeight = $(window).height(),
            c = {
                area: h.find('.text'),
                imgs: [],
                code: [],
                at: [],
                link: [],
                pushImg: function (get) {
                    c.imgs.push(get);
                },
                pushAt: function (get) {
                    c.at.push(get);
                },
                pushLink: function (get) {
                    c.link.push(get);
                },
                pushCode: function (get) {
                    c.code.push(get);
                },
            };
        //r = /\[code=(.*)\](.*)\[\/code\]/g;
    
        //on Window Resize
        $(window).resize(function () {
            scrollTop = $(window).scrollTop();
            windowHeight = $(window).height();
        });

        // on window scroll
        $(window).scroll(function () {
            scrollTop = $(window).scrollTop();
        });

        

        var imgAdder,
            codeAdder,
            linkAdder,
            atAdder;

        var cliper = function (c) {
            var ret = "";
            var i, j;
            for (i = 0; i < c.length; i++) {
                if (c[i] != ' ' && c[i] != "\n") {
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
        
        //initiation
        var init = function () {
            
            //imgAdder.init();
            // code click
            $('.WritingBox .codeAdd').click(function () {
                bg.show();
                var cb = $('.codeAdder');
                if (typeof codeAdder === "undefined") {
                    codeAdder = CodeAdder(c);
                    codeAdder.init();
                    cb.removeClass('hide').hide();
                }
                cb.show(400);
            });

            $('.WritingBox .linkAdd').click(function () {
                bg.show();
                var lb = $('.linkAdder');
                if (typeof linkAdder === "undefined") {
                    linkAdder = LinkAdder(c);
                    linkAdder.init();
                    lb.removeClass('hide').hide();
                }
                lb.show(400);
            });

            $('.WritingBox .imgAdd').click(function () {
                bg.show();
                var ib = $('.imageAdder');
                if (typeof imgAdder === "undefined") {
                    ib.removeClass('hide');
                    imgAdder = ImgAdder(c);
                    imgAdder.init();   
                }
                ib.show(400);
            });

            $('.WritingBox .atAdd').click(function () {
                bg.show();
                var ab = $('.atAdder');
                if (typeof atAdder === "undefined") {
                    atAdder =  AtAdder(c);
                    atAdder.init();
                    ab.removeClass('hide').hide();
                }
                ab.show(400);
            });

        };

        var onView = function () {
            var content = $('.WritingBox .text').html();
            content = cliper(content);
            var cr = /\[code=(.*)\]([\s\S]*)\[\/code\]/;
            content = content.replace(cr, '<pre><code data-language="$1">$2</code></pre>');
            
            var ar = /\[at=(.*)\](.*)\[\/at\]/g;
            content = content.replace(ar, '<span class="at" data-userid="$1">$2</span>');
            var br = /<div>(\s*)<\/div>/;
            conten = content.replace(br, "");
            return content;
        };

        var clear = function () {
            var er = [];
            er.push(imgAdder); er.push(codeAdder); er.push(linkAdder); er.push(atAdder);
            for (var i = 0; i < er.length; i++) {
                if (typeof er[i] !== "undefined") {
                    er[i].clear();
                }
            }
        };


        return {
            init: init,
            h: h,
            onView: onView,
            cliper: cliper,
            clear : clear
        };

    };

    window.WritingBox = WritingBox;

    var wb = WritingBox();
    wb.init();
    window.wb = wb;

})(jQuery);