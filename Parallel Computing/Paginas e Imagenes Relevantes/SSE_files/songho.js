///////////////////////////////////////////////////////////////////////////////
// songho.js
// =========
// Javascript module for www.songho.ca
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2012-11-09
// UPDATED: 2023-12-29
///////////////////////////////////////////////////////////////////////////////

// constants
const MARGIN_TOP_COMMENT = 15;
const SCROLL_DURATION = 600;    // ms

// register event handlers
document.addEventListener("DOMContentLoaded", main);
//window.addEventListener("resize", handleResize);
//window.addEventListener("scroll", handleScroll);



///////////////////////////////////////////////////////////////////////////////
// entry point when a page is loaded
///////////////////////////////////////////////////////////////////////////////
function main()
{
    includeHtmls();
    initToc();

    // add click event to toggle comment block on/off
    let buttonComment = document.getElementById("buttonDisqus");
    if(buttonComment)
    {
        buttonComment.addEventListener("click", toggleCommentBlock);
        let disqusBlock = document.getElementById("disqus_thread");
        if(disqusBlock)
        {
            if(disqusBlock.style.display == "none")
                buttonComment.textContent = "Show Comments";
            else
                buttonComment.textContent = "Hide Comments";
        }
    }
}



///////////////////////////////////////////////////////////////////////////////
// init IntersectionObserver for table of contents
///////////////////////////////////////////////////////////////////////////////
function initToc()
{
    // create IntersectionObserver object
    let options =
    {
        root: null,
        rootMargin: "0px",
        //rootMargin: "0px 0px -50% 0px",
        threshold: 0
    };
    let observer = new IntersectionObserver(handleIntersection, options);

    // attach targets to observer
    let h2s = document.querySelectorAll("h2");
    h2s.forEach(h2 => observer.observe(h2));
}



///////////////////////////////////////////////////////////////////////////////
// callback for  IntersectionObserver
///////////////////////////////////////////////////////////////////////////////
function handleIntersection(entries, observer)
{
    entries.forEach(e =>
    {
        if(e.isIntersecting)
        {
            let as = document.querySelectorAll("#toc li > a");
            as.forEach(a => a.classList.remove("active"));

            let a = document.querySelector("#toc li > a[href='#" + e.target.id + "']");
            a?.classList.add("active");
        }
    });
}



///////////////////////////////////////////////////////////////////////////////
// handle window resize event
///////////////////////////////////////////////////////////////////////////////
function handleResize(e)
{
    /*
    let commentBlock = document.getElementById("commentblock");
    if(commentBlock)
    {
        let windowHeight = getWindowHeight();
        let commentHeight = commentBlock.offsetHeight;
        if(windowHeight > commentHeight)
        {
            // reset the top position
            let offset = getScrollOffset();
            commentBlock.style.top = (offset.y + MARGIN_TOP_COMMENT) + "px";
        }
    }
    */
}



///////////////////////////////////////////////////////////////////////////////
// handle window scroll event
///////////////////////////////////////////////////////////////////////////////
function handleScroll(e)
{
    /*
    let commentBlock = document.getElementById("commentblock");
    if(commentBlock)
    {
        if(!commentBlock.scrollTo)
            addScrollTo(commentBlock);

       let left = parseInt(commentBlock.style.left);

        //let contentHeight = document.getElementById("leftblock").offsetHeight;
        let windowHeight = getWindowHeight();
        let commentHeight = commentBlock.offsetHeight;
        if(windowHeight < commentHeight)
        {
            commentBlock.scrollTo(left, MARGIN_TOP_COMMENT, SCROLL_DURATION, AnimationMode.EASE_OUT);
        }
        else
        {
            let offset = getScrollOffset();
            //commentBlock.style.position = "absolute";
            commentBlock.scrollTo(left, MARGIN_TOP_COMMENT + offset.y, SCROLL_DURATION, AnimationMode.EASE_OUT);
        }
    }
    */
}



///////////////////////////////////////////////////////////////////////////////
// toggle on/off comment bolck
///////////////////////////////////////////////////////////////////////////////
function toggleCommentBlock()
{
    let disqus = document.getElementById("disqus_thread");
    if(disqus)
    {
        // if visible, hide it
        if(disqus.style.display != "none")
        {
            disqus.style.display = "none";
            this.textContent = "Show Comments";
        }
        else
        {
            disqus.style.display = "block";
            this.textContent = "Hide Comments";
        }
    }
}



///////////////////////////////////////////////////////////////////////////////
// compute the client area of window (width and height)
///////////////////////////////////////////////////////////////////////////////
function getWindowWidth()
{
    return window.innerWidth || document.documentElement.clientWidth || document.body.clientWidth || 0;
}
function getWindowHeight()
{
    return window.innerHeight || document.documentElement.clientHeight || document.body.clientHeight || 0;
}



///////////////////////////////////////////////////////////////////////////////
// compute the offset position(left, top) of the element
///////////////////////////////////////////////////////////////////////////////
function getElementOffset(element)
{
    let x = 0;
    let y = 0;
    while(element)
    {
        x += element.offsetLeft || 0;
        y += element.offsetTop || 0;
        element = element.offsetParent; // next
    }
    return {x:x, y:y};
}



///////////////////////////////////////////////////////////////////////////////
// compute the scroll offset of the page
///////////////////////////////////////////////////////////////////////////////
function getScrollOffset()
{
    let x = window.pageXOffset || document.documentElement.scrollLeft;
    let y = window.pageYOffset || document.documentElement.scrollTop;
    return {x:x, y:y};
}



///////////////////////////////////////////////////////////////////////////////
// insert html pages from custom attribs, data-html, data-js
///////////////////////////////////////////////////////////////////////////////
function includeHtmls()
{
    let tags = document.getElementsByClassName("include-html");
    for(let tag of tags)
    {
        let js = tag.dataset.js || "";
        fetch(tag.dataset.html).then(resp => resp.text()).then(text =>
        {
            tag.innerHTML = text;
            //log("tag: " + tag.clientHeight);
            loadJavaScript(tag.dataset.js); // load js if exists
            tag.removeAttribute("data-html"); // hide src names
            tag.removeAttribute("data-js");
        })
        .catch(e => console.log("[ERROR] Failed to load HTML: " + tag.dataset.html));
    }
}



///////////////////////////////////////////////////////////////////////////////
// load JS file if it is not loaded
function loadJavaScript(file)
{
    if(!file)
        return;

    let jsId = btoa(file);  // byte string to ascii
    if(document.getElementById(jsId))
        return;

    let script = document.createElement("script");
    script.src = file;
    script.id = jsId;
    document.head.appendChild(script);
    script.onload = () =>
    {
        // trim only filename
        let func = "init_" + file.substring(file.lastIndexOf("/")+1, file.lastIndexOf(".js"));
        //log(func);
        window[func](); // invoke function
    };
    script.onerror = () => console.log("[ERROR] Failed to load JS: " + file);
}



///////////////////////////////////////////////////////////////////////////////
// get requestAnimationFrame method for client browser
// If requestAnimationFrame() is implemented by the browser, use it to
// refresh the animations. Otherwise, use setTimeOut() with 16 ms interval.
///////////////////////////////////////////////////////////////////////////////
function getRequestAnimationFrameFunction(element)
{
    let names = ["requestAnimationFrame",
                 "mozRequestAnimationFrame",
                 "msRequestAnimationFrame",
                 "oRequestAnimationFrame",
                 "webkitRequestAnimationFrame"];
    let functionName = getAvailableFunctionFromList(element, names);
    if(functionName)
        return function(callback) { return element[functionName](callback); };
    else
        return function(callback) { return setTimeout(callback, 16); }; // 60 fps
}



///////////////////////////////////////////////////////////////////////////////
// get animationStartTime method for client browser
// Use "animationStartTime" property, if possible, to sync other animations.
///////////////////////////////////////////////////////////////////////////////
function getAnimationStartTimeFunction(element)
{
    let names = ["animationStartTime",
                 "mozAnimationStartTime",
                 "msAnimationStartTime",
                 "oAnimationStartTime",
                 "webkitAnimationStartTime"];
    let functionName = getAvailableFunctionFromList(element, names);
    if(functionName)
        return function(){ return element[functionName]; };
    else
        return function() { return Date.now(); };
}



///////////////////////////////////////////////////////////////////////////////
// find available function from given list
// if not, return null
///////////////////////////////////////////////////////////////////////////////
function getAvailableFunctionFromList(element, names)
{
    if(!element) return null;

    for(let i = 0, count = names.length; i < count; ++i)
    {
        let name = names[i];
        if(element[name])   // if function exists, return the function name as string
            return name;
    }
    return null;            // if not found, return null
}



///////////////////////////////////////////////////////////////////////////////
// animation mode and interpolation
///////////////////////////////////////////////////////////////////////////////
let AnimationMode = {
    LINEAR: 0,
    EASE_IN: 1,
    EASE_IN2: 2, // using circle
    EASE_OUT: 3,
    EASE_OUT2: 4, // using circle
    EASE_IN_OUT: 5,
    EASE_IN_OUT2: 6, // using circle
    BOUNCE: 7,
    ELASTIC: 8
};
function getInterpolateAlpha(alpha, mode)
{
    let HALF_PI = Math.PI * 0.5;
    let t = alpha;

    // recompute alpha based on animation mode
    if(mode == AnimationMode.EASE_IN)
    {
        t = 1 - Math.cos(HALF_PI * alpha);
    }
    else if(mode == AnimationMode.EASE_IN2)
    {
        t = 1 - Math.sqrt(1 - alpha * alpha);
    }
    else if(mode == AnimationMode.EASE_OUT)
    {
        t = Math.sin(HALF_PI * alpha);
    }
    else if(mode == AnimationMode.EASE_OUT2)
    {
        t = Math.sqrt(1 - (1 - alpha) * (1 - alpha));
    }
    else if(mode == AnimationMode.EASE_IN_OUT)
    {
        t = 0.5 * (1 - Math.cos(Math.PI * alpha));
    }
    else if(mode == AnimationMode.EASE_IN_OUT2)
    {
        if(alpha < 0.5)
            t = 0.5 * (1 - Math.sqrt(1 - alpha * alpha));
        else
            t = 0.5 * Math.sqrt(1 - (1 - alpha) * (1 - alpha)) + 0.5;
    }
    else if(mode == AnimationMode.BOUNCE)
    {
    }
    else if(mode == AnimationMode.ELASTIC)
    {
    }

    return t;
}



///////////////////////////////////////////////////////////////////////////////
// add scroll animation method to an element
///////////////////////////////////////////////////////////////////////////////
function addScrollTo(element)
{
    if(!element)
        return;

    element.scrollTo = function(left, top, duration, mode, callback)
    {
        callback = callback || function(){};
        let self = this;

        let from = {};
        from.left = parseInt(this.style.left);
        from.top = parseInt(this.style.top);
        from.time = Date.now();

        let to = {}
        to.left = left;
        to.top = top;
        to.time = from.time + duration;

        let requestAnimationFrame = getRequestAnimationFrameFunction(window);
        requestAnimationFrame(scrollToFrame);
        function scrollToFrame()
        {
            let time = Date.now();
            if(time >= to.time)
            {
                self.style.left = to.left + "px";
                self.style.top = to.top + "px";
                callback();
                return;
            }
            let alpha = (time - from.time) / duration;
            alpha = getInterpolateAlpha(alpha, mode); // adjust alpha based on anim mode

            let left = Math.round(from.left + (to.left - from.left) * alpha);
            let top = Math.round(from.top + (to.top - from.top) * alpha);
            self.style.left = left + "px";
            self.style.top = top + "px";
            requestAnimationFrame(scrollToFrame);
        }
    };
}
