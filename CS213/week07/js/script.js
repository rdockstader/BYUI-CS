//declare function for use in the HTML document. needed before document is ready
function updateTotal(ele) {
    var price = parseFloat(document.getElementById(ele.value + "-price").innerHTML.substr(1));
    var totalElement = document.getElementById("total-output");
    var total = parseFloat(totalElement.innerHTML.substr(1));
    if(ele.checked) {
        total += price;
    } else {
        total -= price;
    }
    totalElement.innerHTML = "$" + total.toFixed(2);
        
}

document.onreset = function() {
    document.getElementById("total-output").innerHTML = "$0.00" //reset total
}

document.onsubmit = function() {
    event.preventDefault(); //stop submit from happening
}

// setup functions when document is completely loaded
document.onreadystatechange = () => {
  if (document.readyState === 'complete') {
      // setup credit card validation
      document.getElementById("card-number").onkeyup = function() {
        var creditCard = this;
        var display = creditCard.nextElementSibling;
        var parsedCCN = creditCard.value.trim().split(" ");
        if((parsedCCN.length == 4 && parsedCCN[0].length == 4  && parsedCCN[1].length == 4
           && parsedCCN[2].length == 4 && parsedCCN[3].length == 4) 
           || parsedCCN.length == 1 && parsedCCN[0].length == 16)  {
                var ccn = creditCard.value.trim();
                ccn = ccn.replace(/\s/g,'');
                if(ccn.length == 16) {
                    display.classList.add("ion-ios-checkmark");
                    display.classList.remove("ion-ios-close");
                } else {
                    display.classList.add("ion-ios-close");
                    display.classList.remove("ion-ios-checkmark");
                }
        } else {
            display.classList.add("ion-ios-close");
            display.classList.remove("ion-ios-checkmark");
        }

    }
    // setup state code validation
    document.forms["contact-form"]["address-state"].onkeyup = function() {
        var stateCode = this;
        var display = stateCode.nextElementSibling;
        stateCode = stateCode.value.trim();
        if(stateCode.length == 2 && stateCode == stateCode.toUpperCase()) {
            display.classList.add("ion-ios-checkmark");
            display.classList.remove("ion-ios-close");
        } else {
            display.classList.add("ion-ios-close");
            display.classList.remove("ion-ios-checkmark");
        }

    }
    
    
  }
};

