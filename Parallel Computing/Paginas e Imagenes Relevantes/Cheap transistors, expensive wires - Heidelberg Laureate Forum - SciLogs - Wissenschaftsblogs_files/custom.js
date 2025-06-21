/*
 * ATTENTION: The "eval" devtool has been used (maybe by default in mode: "development").
 * This devtool is neither made for production nor for readable output files.
 * It uses "eval()" calls to create a separate source file in the browser devtools.
 * If you are trying to read the output file, select a different devtool (https://webpack.js.org/configuration/devtool/)
 * or disable the default devtool with "devtool: false".
 * If you are looking for production-ready output files, see mode: "production" (https://webpack.js.org/configuration/mode/).
 */
/******/ (() => { // webpackBootstrap
/******/ 	var __webpack_modules__ = ({

/***/ "./resources/js/custom.js":
/*!********************************!*\
  !*** ./resources/js/custom.js ***!
  \********************************/
/***/ (() => {

eval("/*\n *-----------------------------------------------------------------------------------\n *Smooth Scrolling\n *-----------------------------------------------------------------------------------\n */\n/*\n *!\n * Smooth Scroll - v1.4.5 - 2012-07-21\n *\n * Copyright (c) 2012 Karl Swedberg; Licensed MIT, GPL\n * https://github.com/kswedberg/jquery-smooth-scroll\n *\n *\n */\n(function (a) {\n  function f(a) {\n    return a.replace(/(:|\\.)/g, '\\\\$1');\n  }\n  const b = '1.4.5';\n  const c = {\n    exclude: [],\n    excludeWithin: [],\n    offset: 0,\n    direction: 'top',\n    scrollElement: null,\n    scrollTarget: null,\n    beforeScroll() {},\n    afterScroll() {},\n    easing: 'swing',\n    speed: 400,\n    autoCoefficent: 2\n  };\n  const d = function (b) {\n    let c = [];\n    let d = !1;\n    const e = b.dir && 'left' == b.dir ? 'scrollLeft' : 'scrollTop';\n    return this.each(function () {\n      if (this == document || this == window) {\n        return;\n      }\n      const b = a(this);\n      0 < b[e]() ? c.push(this) : (b[e](1), d = 0 < b[e](), b[e](0), d && c.push(this));\n    }), 'first' === b.el && c.length && (c = [c[0]]), c;\n  };\n  const e = ('ontouchend' in document);\n  a.fn.extend({\n    scrollable(a) {\n      const b = d.call(this, {\n        dir: a\n      });\n      return this.pushStack(b);\n    },\n    firstScrollable(a) {\n      const b = d.call(this, {\n        el: 'first',\n        dir: a\n      });\n      return this.pushStack(b);\n    },\n    smoothScroll(b) {\n      b = b || {};\n      const c = a.extend({}, a.fn.smoothScroll.defaults, b);\n      const d = a.smoothScroll.filterPath(location.pathname);\n      return this.unbind('click.smoothscroll').bind('click.smoothscroll', function (b) {\n        const e = this;\n        const g = a(this);\n        const h = c.exclude;\n        const i = c.excludeWithin;\n        let j = 0;\n        let k = 0;\n        let l = !0;\n        const m = {};\n        const n = location.hostname === e.hostname || !e.hostname;\n        const o = c.scrollTarget || (a.smoothScroll.filterPath(e.pathname) || d) === d;\n        const p = f(e.hash);\n        if (!c.scrollTarget && (!n || !o || !p)) {\n          l = !1;\n        } else {\n          while (l && j < h.length) {\n            g.is(f(h[j++])) && (l = !1);\n          }\n          while (l && k < i.length) {\n            g.closest(i[k++]).length && (l = !1);\n          }\n        }\n        l && (b.preventDefault(), a.extend(m, c, {\n          scrollTarget: c.scrollTarget || p,\n          link: e\n        }), a.smoothScroll(m));\n      }), this;\n    }\n  }), a.smoothScroll = function (b, c) {\n    let d;\n    let f;\n    let g;\n    let h;\n    let i = 0;\n    let j = 'offset';\n    let k = 'scrollTop';\n    const l = {};\n    let m = !1;\n    let n = [];\n    'number' === typeof b ? (d = a.fn.smoothScroll.defaults, g = b) : (d = a.extend({}, a.fn.smoothScroll.defaults, b || {}), d.scrollElement && (j = 'position', 'static' == d.scrollElement.css('position') && d.scrollElement.css('position', 'relative')), g = c || a(d.scrollTarget)[j]() && a(d.scrollTarget)[j]()[d.direction] || 0), d = a.extend({\n      link: null\n    }, d), k = 'left' == d.direction ? 'scrollLeft' : k, d.scrollElement ? (f = d.scrollElement, i = f[k]()) : (f = a('html, body').firstScrollable(), m = e && 'scrollTo' in window), l[k] = g + i + d.offset, d.beforeScroll.call(f, d), m ? (n = 'left' == d.direction ? [l[k], 0] : [0, l[k]], window.scrollTo.apply(window, n), d.afterScroll.call(d.link, d)) : (h = d.speed, 'auto' === h && (h = l[k] || f.scrollTop(), h /= d.autoCoefficent), f.stop().animate(l, {\n      duration: h,\n      easing: d.easing,\n      complete() {\n        d.afterScroll.call(d.link, d);\n      }\n    }));\n  }, a.smoothScroll.version = b, a.smoothScroll.filterPath = function (a) {\n    return a.replace(/^\\//, '').replace(/(index|default).[a-zA-Z]{3,4}$/, '').replace(/\\/$/, '');\n  }, a.fn.smoothScroll.defaults = c;\n})(jQuery);\njQuery(document).ready(() => {\n  jQuery('a.top').smoothScroll();\n  jQuery('a.share-btn').click(() => {\n    jQuery.smoothScroll({\n      scrollElement: jQuery('.share'),\n      scrollTarget: '#'\n    });\n    return false;\n  });\n});\nif (1025 < document.documentElement.clientWidth) {\n  jQuery(document).ready(() => {\n    jQuery('a.site-nav-btn').smoothScroll();\n  });\n}\n\n/*\n *---------------------------------------------------------------------------------------------\n *Flexible width for embedded videos (see https://github.com/davatron5000/FitVids.js/)\n *----------------------------------------------------------------------------------------------\n */\njQuery(document).ready(() => {\n  jQuery('#content').fitVids();\n  jQuery('.widget').fitVids();\n});\n\n//# sourceURL=webpack://scilogs-theme/./resources/js/custom.js?");

/***/ })

/******/ 	});
/************************************************************************/
/******/ 	
/******/ 	// startup
/******/ 	// Load entry module and return exports
/******/ 	// This entry module can't be inlined because the eval devtool is used.
/******/ 	var __webpack_exports__ = {};
/******/ 	__webpack_modules__["./resources/js/custom.js"]();
/******/ 	
/******/ })()
;