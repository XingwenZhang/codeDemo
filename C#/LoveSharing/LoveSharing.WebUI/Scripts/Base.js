/*
 *  Basic Object is a set of many uesd frequently methods
 */
(function ($) {
    var Base = {
        /**
		 * 实现类与类之间的继承。
		 * @method inherits
		 * @grammar Base.inherits( super ) => child
		 * @grammar Base.inherits( super, protos ) => child
		 * @grammar Base.inherits( super, protos, statics ) => child
		 * @param  {Class} super 父类
		 * @param  {Object | Function} [protos] 子类或者对象。如果对象中包含constructor，子类将是用此属性值。
		 * @param  {Function} [protos.constructor] 子类构造器，不指定的话将创建个临时的直接执行父类构造器的方法。
		 * @param  {Object} [statics] 静态属性或方法。
		 * @return {Class} 返回子类。
		*/
        inherits: function (Super, protos, staticProtos) {
            var child;
            if (typeof protos === 'function') {
                child = protos;
                protos = null;
            } else if (protos && protos.hasOwnProperty('constructor')) {
                child = protos.constructor;
            } else {
                child = function () {
                    return Super.apply(this, arguments);
                };
            }

            // 复制静态方法
            $.extend(true, child, Super, staticProtos || {});

            /* jshint camelcase: false */

            // 让子类的__super__属性指向父类。
            child.__super__ = Super.prototype;

            // 构建原型，添加原型方法或属性。
            // 暂时用Object.create实现。
            child.prototype = Base.createObject(Super.prototype);
            protos && $.extend(true, child.prototype, protos);

            return child;
        },

        createObject: function (proto) {
            var f;

            if (Object.create) {
                return Object.create(proto);
            } else {
                f = function () { };
                f.prototype = proto;
                return new f();
            }
        },

        fixObjectToWindowHeight: function (id) {
            var wh = $(window).height();
            $(id).height(wh);
            $(window).resize(function () {
                wh = $(window).height();
                $(id).height(wh);
            });
        },

        EmailRegExp: /^(\w-*\.*)+@(\w-?)+(\.\w{2,})+$/,
        emailCheck: function (c) {
            var r = /^(\w-*\.*)+@(\w-?)+(\.\w{2,})+$/;
            return r.test(c);
        },
        phoneRegExp: /^([0-9]){11}$/,
        phoneCheck: function (c) {
            var r = /^([0-9]){11}$/;
            return r.test(c);
        }

    }

    window.Base = Base;


})(jQuery);

