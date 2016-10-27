(function () {

    var View = function (id) {

        var _this = $(id);

        _this.each(function () {
            
            var $this = $(this);
            var txt = $this.html();

            var reg = /\[code=(.*)\]([\s\S]*)\[\/code\]/;
            txt = txt.replace(reg, '<pre><code data-language="$1">$2</code></pre>');
            $this.html(txt);

            //code处理


        });

    };

    window.View = View;

})(jQuery);