
function alog(page)
{
	var alogurl = "/ct/alog.php";
	alogurl += "?page=" + page;
	alogurl += "&url=" + encodeURIComponent(document.location);
	alogurl += "&ref=" + encodeURIComponent(document.referrer);
	
	document.writeln('<script type="text/javascript" id="alogjsframe"></script>');
	document.getElementById('alogjsframe').setAttribute('src', alogurl);
	document.writeln('<a href="mailto:daytime' + String.fromCharCode(8 * 8) + 'officedaytime.com">Daytime &lt;daytime' + String.fromCharCode(8 * 8) + 'officedaytime.com&gt;</a>');	
}


