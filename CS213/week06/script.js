//First problem: Age
function validateAge(age) {
    var display = age.nextElementSibling;
    if(age.value <= 118 && age.value >= 0) {
        display.style.color = "green";
        display.innerHTML = "Valid Age";
    } else {
        display.style.color = "red";
        display.innerHTML = "Invalid Age";
    }
    
    
}

//Second problem: SSN
function validateSSN(ssn) {
    var display = ssn.nextElementSibling;
    var parsedSSN = ssn.value.trim().split("-");
    if(parsedSSN.length == 3 && parsedSSN[0].length == 3 && parsedSSN[1].length == 2 
           && parsedSSN[2].length == 4 ){
        display.style.color = "green";
        display.innerHTML = "Valid SSN";
    } else {
        display.style.color = "red";
        display.innerHTML = "Invalid SSN";
    }
}

//Third problem: Credit Card Number
function validateCreditCard(creditCard) {
    var display = creditCard.nextElementSibling;
    var parsedCCN = creditCard.value.trim().split(" ");
    if((parsedCCN.length == 4 && parsedCCN[0].length == 4  && parsedCCN[1].length == 4
       && parsedCCN[2].length == 4 && parsedCCN[3].length == 4) 
       || parsedCCN.length == 1 && parsedCCN[0].length == 16)  {
            var ccn = creditCard.value.trim();
            ccn = ccn.replace(/\s/g,'');
            if(ccn.length == 16) {
                display.style.color = "green";
                display.innerHTML = "Valid credit card number";
            } else {
                display.style.color = "red";
                display.innerHTML = "Invalid credit card number";
            }
    } else {
        display.style.color = "red";
        display.innerHTML = "Invalid credit card number";
    }

}

//Fourth problem: Date
function validateDate(date) {
    var display = date.nextElementSibling;
    var parsedDate = date.value.trim().split("/");
    if(parsedDate.length == 3 
       && parsedDate[0] >= 1 && parsedDate[0] <= 12
      && parsedDate[1] >= 1 && parsedDate[1] <= 31
      && parsedDate[2] >= 1753 && parsedDate[2] <= 2100) {
        display.style.color = "green";
        display.innerHTML = "Valid Date";
    } else {
        display.style.color = "red";
        display.innerHTML = "Invalid Date";
    }
}

//Fifth problem: Abbreviation
function validateState(stateCode) {
    var display = stateCode.nextElementSibling;
    stateCode = stateCode.value.trim();
    if(stateCode.length == 2 && stateCode == stateCode.toUpperCase()) {
        display.style.color = "green";
        display.innerHTML = "Valid state abbreviation";
    } else {
        display.style.color = "red";
        display.innerHTML = "Invalid state abbreviation";
    }
    
}

//Sixth problem: Money
function validateMoney(money) {
    var display = money.nextElementSibling;
    var reg = /^\d+$/;
    money = money.value.trim();
    if(money.charAt(0) == "$")
        money = money.substr(1);
    money = money.replace(/,/g , "");
    var parsedMoney = money.split(".");
    if(reg.test(parsedMoney[0]) && (parsedMoney.length < 2 || 
       parsedMoney.length == 2 && parsedMoney[1].length == 2)) {
        display.style.color = "green";
        display.innerHTML = "Valid money amount";
    } else {
        display.style.color = "red";
        display.innerHTML = "Invalid money amount";
    }
}














