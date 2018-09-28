// Hello World (1)
function problem1() {
    console.log("Hello, World!");
}
// Form Letter (2)
function problem2(newName, text) {
    var formNames = document.getElementsByClassName("form-name");
    for(var i = 0, max = formNames.length; i < max; i++) {
        formNames[i].innerHTML = newName;
    }
    console.log(document.getElementById("text2").textContent);
}

// Temperature Conversion (3)
function problem3(temp) {
    if(isNaN(temp)) {
        document.getElementById("temp-output").innerHTML = "INVALID INPUT";
        console.log("INVALID INPUT");
    } else {
        var tempC = (temp - 32) * (5/9);
        tempC = tempC.toFixed(1);
        //document.getElementById("temp-output").innerHTML = "Temp in Celsius: " + tempC +"&deg;";
        console.log(tempC);
    }
}

// Postage (4)
var postageCosts = new Object();
postageCosts[1] = "$0.98";
postageCosts[2] = "$1.19";
postageCosts[3] = "$1.40";
postageCosts[4] = "$1.61";
postageCosts[5] = "$1.82";
function problem4(ounceInput) {
    var priceOutput = "";
    if(ounceInput > 0 && ounceInput <= 5) {
        priceOutput = postageCosts[ounceInput];
    } else {
        priceOutput = "Invalid weight";
    }
    //document.getElementById("postage-output").innerHTML = priceOutput;
    console.log(priceOutput);
}

// Compound interest (5)
function problem5(apr, term, amount) {
    apr = Number(apr)/100;
    term = Number(term);
    amount = Number(amount);
    var output = 1 + apr;
    for(var i = 1; i < term; i++) {
        output *= 1+apr;
    }
    output *= amount;
    output = output.toFixed(2);

    //document.getElementById("comp-int-output").innerHTML = "total amount to be paid: $" + output;
    console.log(output);

}