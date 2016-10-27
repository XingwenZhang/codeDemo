(function ($, B) {

    var Ask = function () {


        var AnonymityUserImg = $('.View .title img').attr('src');

        var check = function () {
            var title = $('.askBox > .title input').val();
            if (wb.cliper(title) == "") {
                return false;
            }
        };

        var init = function () {

            $('.title input').on('input', function () {
                $('.title .warning span').first().addClass('hide');
                var it = $(this);
                
                var txt = it.val();
                var txted = wb.cliper(txt);
                if (txt.length != txted.length) {
                    txt = txted;
                    it.va(txt);
                }

                if (txt.length > 50) {
                    txt = txt.substring(0, 50);
                    it.val(txt);
                    $('.title .warning span').first().removeClass('hide');
                }
                $('.title .count').html(txt.length);
            });

            $('.categories').perfectScrollbar();
            $('.categories ul li').first().addClass('active');
            $('.tags').first().removeClass('hide');

            var clearActive = function () {
                $('.categories ul li').removeClass('active');
                $('.section .tags').addClass('hide');
            };

            $('.categories ul li').click(function () {
                var index = $('.categories ul li').index(this);
                clearActive();
                $(this).addClass('active');
                $('.tags').eq(index).removeClass('hide');
            });

            $('.tagArticle').click(function () {
                var it = $(this);
                var id = it.attr('data-tagid');
                if (it.hasClass('active')) {
                    it.removeClass('active');
                    $('.tagedArticle[data-tagid=' + id + ']').remove();
                }
                else {
                    it.addClass('active');
                    var n = $('.template .tagedArticle.hide').clone(true);
                    n.attr('data-tagid', id);
                    n.find('span').html(it.find('span.block').html());
                    n.removeClass('hide');
                    n.insertBefore('.tagInputed >  div.clear-float');
                }
            });

            $('.tagedArticle .icon-cancel').click(function () {
                console.log('fds');
                var it = $(this).parent();
                var id = it.attr('data-tagid');
                $('.tagArticle[data-tagid=' + id + ']').removeClass('active');
                it.remove();
            });

            var activeToggle = function (i) {
                var it = $(i);
                if (it.hasClass('active')) {
                    it.removeClass('active');
                }
                else {
                    it.addClass('active');
                }
            };

            $('.onAnonymity').click(function () {
                activeToggle(this);
            });

            $('.onTag').click(function () {
                activeToggle(this);
                var it = $(this);
                $('.tagsInput').slideToggle(400);
            });

            $('.onView').click(function () {
                if (check() == false) {
                    alerter("请务必填写标题");
                    return;
                }
                var title = $('.askBox > .title input').val();
                var content = $('.WritingBox .text').html();
                content = wb.onView(content);

                var target = $('.View .wdArticle');
                if ($('.onAnonymity').hasClass('active')) {
                    target.find('.title img').attr('src', AnonymityUserImg);
                    target.find(' .title .name').html("问答用户");
                } else {
                    target.find('.title img').attr('src', $('.header .nav .user > a img').attr('src'));
                    target.find('.title .name').html($('.header .nav .user > a span').html());
                }
                target.find('.title .content').html(title);
                target.find('> .content').html(content);

                var tags = [];
                var ts = $('.tagInputed .tagedArticle');
                for (var i = 0; i < ts.length; i++) {
                    var b = ts.eq(i);
                    var t = {
                        id: b.attr('data-tagid'),
                        title: b.find('span').first().html()
                    };
                    
                    $('<a href="#" data-tagid="' + t.id + '">' + t.title + '</a>').insertBefore(target.find('.tags .clear-float'));
                }
                $('.secondBg').show();
                $('.View').removeClass('hide');
                $('.View').css('top', $(window).scrollTop());
                var bw = $('body').height();
                $('.View .WenDaList').css('max-height', bw * 0.9 - $(window).scrollTop() + 'px');
            });

            $('.View .ok').click(function () {
                $('.secondBg').hide();
                $('.View').addClass('hide');
            });

            $('.onSubmit').click(function () {
                if (check() == false) {
                    alerter("请务必填写标题");
                    return;
                }
                var ui = $('._UI').val();
                var _info = $('._info');

                var content = wb.cliper($('.WritingBox .text').html());
                _info.find('input[name=Content]').val(content);
                var c = content;
                var ar = /\[at=(.*)\](.*)\[\/at\]/;
                var ats = [];
                var exec ;
                while ( exec = ar.exec(c)) {
                    ats.push(exec[1]);
                    c = c.replace(ar, "");
                }
                var tbox = $('.tagInputed .tagedArticle');
                var tags = [];
                for (var i = 0; i < tbox.length; i++) {
                    tags.push(tbox.eq(i).attr('data-tagid'));
                }


                var Anonymity = $('.onAnonymity').hasClass('active') == true ? 1 : 0;
                for (var i = 0; i < ats.length; i++) {
                    $('<input type="hidden" value="' + ats[i] + '" name="ats"/>').appendTo('._info');
                }
                for (var i = 0; i < tags.length; i++) {
                    $('<input type="hidden" value="' + tags[i] + '" name="tags"/>').appendTo('._info');
                }
                _info.find('input[name=UserId]').val(ui);
                _info.find('input[name=Content]').val(content);
                _info.find('input[name=Anonymity]').val(Anonymity);

                $('#askform')[0].submit();
            });
            
            
        }();

    };
    var ask = Ask();

})(jQuery, Base);