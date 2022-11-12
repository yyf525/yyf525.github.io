function loadfile(filename,func){
	let url=filename;
	let httpRequest=new XMLHttpRequest();
	httpRequest.open('GET',url,true);
	httpRequest.send();
	httpRequest.onreadystatechange=function(){
		if (httpRequest.readyState==4 && httpRequest.status==200)
			func(httpRequest.responseText);
	};
}
function changeTheme(theme) {
    $('body').removeClass("mdui-theme-primary-" + localStorage.maincolor);
	localStorage.maincolor = theme;
    $('body').addClass("mdui-theme-primary-" + localStorage.maincolor);
}
$(document).ready(function(){
    if(localStorage.maincolor==undefined)
        localStorage.maincolor="indigo";
    var maincolor=localStorage.maincolor;
    $('body').addClass("mdui-theme-primary-"+maincolor);
});
