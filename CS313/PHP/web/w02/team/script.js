function btnClick() {
    alert('Clicked!');
}

function changeColor() {
     $("#box-1").css('background-color', $("#color").val());
}

function toggleDiv3() {
    console.log($("#box-3"));
    $("#box-3").fadeToggle();
}



/*
function changeColor() {
    var textbox_id = "color";
    var textbox = document.getElementById(textbox_id);
    
    var div_id = "box-1";
    var div = document.getElementById(div_id)
    
    
    var color = textbox.value;
    div.style.backgroundColor = color;
}

*/
