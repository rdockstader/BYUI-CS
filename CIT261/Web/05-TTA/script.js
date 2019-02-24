var gameEle = document.getElementById('game-section');
var amount = 0;
var luckyNumber = -1;
var clickCount = 0;
var scale = 1;

function getRandomInt(min, max) {
    min = Math.ceil(min);
    max = Math.floor(max);
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

var validateParent = function(parent) {
    if(typeof(parent) === 'object') {
        return true;
    }

    return false;
}

var ClearGameEle = function() {
    while(gameEle.firstChild) {
        gameEle.removeChild(gameEle.firstChild);
    }
}

var boxSelected = function(event) {
    clickCount = clickCount + 1;
    var boxEle = event.target;
    if(boxEle.id == luckyNumber) {
        alert("you won in " + clickCount + " Clicks!");
    } else {
        // Fade out wrong box
        boxEle.parentElement.style.opacity = '0';
        setTimeout(function(){
            gameEle.removeChild(boxEle.parentElement);
            amount = amount - 1;
            scale = scale + (1/amount);
            // enlarge remaining boxes
            gameEle.style.transform = 'scale(' + scale + ', ' + scale + ')';
            gameEle.style.transformOrigin = '0%';
        }, 1000);
    }
}

var startGame = function() {
    amount = document.getElementById('box-amount').value;
    console.log(amount);
    if(amount == null || amount == '') {
        // maybe create a nice div here...
        alert('You must select an amount of boxes!');
    } else if(amount > 10) {
        alert('Please choose a number 10 or under');
    } else {
        ClearGameEle();
        // set the lucky number
        luckyNumber = getRandomInt(0, amount-1);
        // create the box package divs
        for(var i = 0; i < amount; i++) {
            // create the wrapper div
            var wrapperDiv = document.createElement('div');
            wrapperDiv.classList.add('box-wrapper');
            wrapperDiv.style.width = ((1 / (amount + '.1')) * 100) + '%';
            wrapperDiv.style.cssFloat = "left";
            // create the box
            var boxDiv = document.createElement('img');
            boxDiv.src = '../img/box.png';
            boxDiv.alt = 'box ' + i;
            boxDiv.id = i;
            boxDiv.style.width = '80%';
            boxDiv.onclick = boxSelected;
            wrapperDiv.appendChild(boxDiv);
            gameEle.appendChild(wrapperDiv);
            wrapperDiv.style.opacity = '1';

        }
    }
    
    
}

var initGameSection = function(parent) {
    if(validateParent(parent)){
        // create input
        var inputEle = document.createElement('input');
        inputEle.type = "number";
        inputEle.value = 3;
        inputEle.id = "box-amount";
        inputEle.max = 10;
        // create input label
        var labelEle = document.createElement('label');
        labelEle.for = "box-amount";
        labelEle.innerHTML = 'Amount of Boxes (10 or under)';
        // create submit button
        var btnEle = document.createElement('button');
        btnEle.onclick = startGame;
        btnEle.classList.add('btn');
        btnEle.classList.add('btn-primary');
        btnEle.innerHTML = "Start Game!";

        parent.appendChild(labelEle);
        parent.appendChild(inputEle);
        parent.appendChild(btnEle);
    }
}

var createBoxes = function(amount, parent) {
    
}


initGameSection(gameEle);