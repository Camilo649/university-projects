function init_menu()
{
    //Logger.open();
    //log("init_menu() is called");

    // register click events for <a>
    let menu = document.getElementById("menu");
    if(!menu)
        return;

    // focus the current html
    let as = menu.querySelectorAll("a");
    as.forEach(e => e.classList.remove("focuseditem")); // unfocus all
    as.forEach(a =>
    {
        let aid = a.id.slice(5);    // trim prefix
        //log(aid == document.body.id);
        if(aid == document.body.id)
            a.classList.add("focuseditem");

        a.addEventListener("click", () =>
        {
            //console.log("aaaaaaaaaaaaaat");
            console.log(menu.scrollHeight);
        });
    });

    // get prev collapsed <ul>s
    let collapsedUls = JSON.parse(sessionStorage.getItem("collapsedUls"));
    if(!collapsedUls)
    {
        collapsedUls = []; // create new array
    }

    // register click events for <span>
    let plusminus = document.getElementsByClassName("plusminus");
    for(let e of plusminus)
    {
        // get <ul> for curr <span>
        let childUl = e.parentElement.parentElement.querySelector("ul");

        // set and remember height of <ul> for animation
        let height = childUl.scrollHeight;
        //log("UL height: " + height + ", " + childUl.clientHeight + ", " + childUl.offsetHeight);
        if(collapsedUls.includes(childUl.id))
        {
            childUl.style.height = "0px";
            let pm = childUl.parentElement.querySelector("span");
            if(pm)
                pm.classList.add("collapseditem");
        }
        else
        {
            childUl.style.height = height + "px";
        }

        // click event to toggle collapse
        e.addEventListener("click", ev =>
        {
            ev.preventDefault();
            ev.stopPropagation();

            if(e.classList.contains("collapseditem"))
            {
                e.classList.remove("collapseditem");
                childUl.style.height = height + "px";

                let index = collapsedUls.indexOf(childUl.id);
                if(index > -1)
                    collapsedUls.splice(index, 1);
            }
            else
            {
                e.classList.add("collapseditem");
                childUl.style.height = "0px";

                if(!collapsedUls.includes(childUl.id))
                    collapsedUls.push(childUl.id);
            }
            sessionStorage.setItem("collapsedUls", JSON.stringify(collapsedUls));
        });
    }
}
