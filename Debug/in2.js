function concat2ss(str1, str2){return str1 + str2;}
function itos1i(number){return String(number);}
function CreateVideo1s(link) {
    let iframe = document.createElement("iframe");
    iframe.width = "560";
    iframe.height = "315";
    iframe.src = link;
    iframe.allow = "accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share";
    iframe.allowFullscreen = true;
    return iframe;
}function GetBody0(){return document.body;}
function Create1s(tag){return document.createElement(tag);}
function InsertToHtml2hh(parent, child){parent.appendChild(child);}
function TextSet2hs(tag, text){tag.innerHTML = text;}
function write2hs(tag, text){tag.innerHTML += text;}
function writeln2hs(tag, text){tag.innerHTML += `<br>${text}`;}
function SetCSS2hs(tag, css){tag.style.cssText = css;}
function SetAttribute3hss(tag, atr, value){tag.setAttribute(atr, value);}
function Create2ss( name , css ){
let tag = Create1s( name );
SetCSS2hs( tag , css );
return tag;
}
function CreateButton1s( value ){
let button = Create2ss( 'input' , 'width: 100px; height: 50px; margin: 4px; background-color: gray; border-radius: 10px; ' );
SetAttribute3hss( button , 'type' , 'button' );
SetAttribute3hss( button , 'value' , value );
return button;
}
function main() {
let body = GetBody0(  );
let window = Create2ss( 'div' , 'width: 560px; height: 315px; background-color: white; box-sizing: content-box; padding: 5px; border: solid 3px black;' );
InsertToHtml2hh( body , window );
let YoutubeVidoMaker1s = function( shortLink ){
let link = concat2ss( shortLink , '?autoplay=1&loop=1' );
let videoTag = CreateVideo1s( link );
InsertToHtml2hh( body , videoTag );
}
TextSet2hs( window , 'window of number' );
let i = -9;
while( i > 0 ){
let s = itos1i( i );
let button = CreateButton1s( s );
InsertToHtml2hh( body , button );
if( i <= 4 ){
button.addEventListener('click' , () => writeln2hs( window , '' ));
}
button.addEventListener('click' , () => write2hs( window , s ));
i = i - 1;
}
YoutubeVidoMaker1s( 'https://www.youtube.com/embed/X-ANZ8ba8jU' );
}

main();