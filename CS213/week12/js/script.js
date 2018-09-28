// array to hold all state codes
var stateCodes = [
    'AL', 'AK', 'AZ', 'AR', 'AS',
    'CA', 'CO', 'CT',
    'DE', 'DC',
    'FL', 'FM',
    'GA', 'GU',
    'HI',
    'ID', 'IL', 'IN', 'IA',
    'KS', 'KY',
    'LA',
    'ME', 'MD', 'MA', 'MI', 'MN', 'MS', 'MO', 'MT', 'MH', 'MP',
    'NE', 'NV', 'NH', 'NY', 'NC', 'ND',
    'OH', 'OK', 'OR', 
    'PA', 'PW', 'PR',
    'RI',
    'SC', 'SD',
    'TN', 'TX',
    'UT', 
    'VT',
    'VA', 'VI',
    'WA', 'WV', 'WI', 'WY'
];

function canEnableButton() {
    var checkElements = [
        "card-number-valid-icon",
        "state-valid-icon",
        "zip-valid-icon",
        "phone-valid-icon"
    ];
    for(i in checkElements) {
        if(document.getElementById(checkElements[i]).classList.contains("ion-ios-close")) {
            return false;
        }
    }
    
    return true;
    
}

function tryEnableButton() {
    var btn = document.getElementById("contact-submit");
    if(canEnableButton()) {
        btn.disabled = false;
    } else {
        btn.disabled = true;
    }
}

//declare function for use in the HTML document. needed before document is ready
function updateTotal(ele) {
    var price = parseFloat(document.getElementById(ele.id + "-price").innerHTML.substr(1));
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
    //event.preventDefault(); //stop submit from happening
}

// setup functions when document is completely loaded
document.onreadystatechange = () => {
  if (document.readyState === 'complete') {
      // setup credit card validation
      document.getElementById("card-number").onkeyup = function() {
        var creditCard = this;
        var display = document.getElementById("card-number-valid-icon");
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
        tryEnableButton();
    }
    // setup state code validation
    document.forms["contact-form"]["address-state"].onkeyup = function() {
        var stateCode = this;
        var display = document.getElementById("state-valid-icon");
        stateCode = stateCode.value.trim();
        if(stateCodes.includes(stateCode)) {
            display.classList.add("ion-ios-checkmark");
            display.classList.remove("ion-ios-close");
            
        } else {
            display.classList.add("ion-ios-close");
            display.classList.remove("ion-ios-checkmark");
        }
        tryEnableButton();

    }
    // setup zip validation
    document.getElementById("address-zip").onkeyup = function() {
        var zip = this;
        var display = document.getElementById("zip-valid-icon");
        
        if(this.value.length == 5 && !isNaN(this.value)) {
            display.classList.add("ion-ios-checkmark");
            display.classList.remove("ion-ios-close");
        } else {
            display.classList.add("ion-ios-close");
            display.classList.remove("ion-ios-checkmark");
        }
        tryEnableButton();
    }
    // Setup phone number validation
    document.getElementById('phone-number').onkeyup = function() {
        var num = this; 
        var display = document.getElementById("phone-valid-icon");
        var reg = /^[\+]?[(]?[0-9]{3}[)]?[-\s\.]?[0-9]{3}[-\s\.]?[0-9]{4,6}$/im;
        if(this.value.match(reg)) {
          display.classList.add("ion-ios-checkmark");
            display.classList.remove("ion-ios-close");
        } else {
            display.classList.add("ion-ios-close");
            display.classList.remove("ion-ios-checkmark");
        }
        tryEnableButton();
    }
    
    
  }
};

