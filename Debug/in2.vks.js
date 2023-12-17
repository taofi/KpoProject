function console1s(str)
{
console.log(str);
}
function pow2ii(number, degree)
{
return Math.pow(number, degree);
}
function itos1i(number)
{
return ('' + number);
}
function CreateVideo1s(link) {
    var iframe = document.createElement("iframe");
    iframe.width = "560";
    iframe.height = "315";
    iframe.src = link;
    iframe.title = "YouTube video player";
    iframe.frameBorder = "0";
    iframe.allow = "accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share";
    iframe.allowFullscreen = true;
    return iframe;
}function tomas0()
{
document.body.innerHTML += '<iframe width="560" height="315" src="https://www.youtube.com/embed/X-ANZ8ba8jU?autoplay=1&loop=1" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>';
}
function GetBody0()
{
return document.body;
}
function Create1s(tag)
{
return document.createElement(tag);
}
function InsertToHtml2hh(parent, child)
{
parent.appendChild(child);
}
function TextAdd2hs(tag, text)
{
return tag.innerHTML += text;
}
function fi1i( y ){
let x = 0;
x = x > 0;
let intLv21i = function( asd ){
asd = asd + 564 * 10;
return asd;
}
let z = 0;
z = intLv21i( 123 ) + y;
let l = '';
l = itos1i( z );
console1s( l );
return '123';
}
function videoBody1s( link ){
let body = GetBody0(  );
let videoTag = CreateVideo1s( link );
InsertToHtml2hh( body , videoTag );
}
function fun4cr0(  ){
let body = GetBody0(  );
let tag = Create1s( 'div' );
let f = 100;
while( f > 0 ){
f = f - 1;
TextAdd2hs( tag , '4 ' );
}
InsertToHtml2hh( body , tag );
}
function main() {
let y = 0;
y = pow2ii( 2 , 3 );
let asd123 = 15;
y = y + asd123 + 3 + 290;
let l2 = fi1i( y );
console1s( l2 );
tomas0(  );
tomas0(  );
tomas0(  );
tomas0(  );
tomas0(  );
tomas0(  );
tomas0(  );
tomas0(  );
tomas0(  );
}

main();