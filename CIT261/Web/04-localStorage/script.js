/*
font-family: 'Major Mono Display', monospace;
font-family: 'ZCOOL KuaiLe', cursive;
font-family: 'Staatliches', cursive;
font-family: 'Ubuntu', sans-serif;
font-family: 'Indie Flower', cursive;
font-family: 'Anton', sans-serif;
font-family: 'Lato', sans-serif;
*/

updateFontStyle = function() {
    var fontStyle = document.getElementById('font-style');
    var fontFamily;
    switch(fontStyle.value) {
        case 'major-mono':
            fontFamily = 'Major Mono Display';
            break;
        case 'zcool':
            fontFamily = 'ZCOOL KuaiLe';
            break;
        case 'staatliches':
            fontFamily = 'Staatliches';
            break;
        case 'ubuntu':
            fontFamily = 'Ubuntu';
            break;
        case 'flower':
            fontFamily = 'Indie Flower';
            break;
        case 'anton':
            fontFamily = 'Anton';
            break;
        default:
            fontFamily = 'lato';
            break;
    }
    document.body.style.fontFamily = fontFamily;
}

updateFontSize = function() {
    var fontSize = document.getElementById('font-size');
    var fontSizeValue = fontSize.value;
    if(fontSizeValue < 5) {
        fontSizeValue = 5
    } else if(fontSizeValue > 30) {
        fontSizeValue = 30;
    }
    fontSize.value = fontSizeValue
    
    document.body.style.fontSize = fontSizeValue + 'px';
}

updateFontColor = function() {
    var fontColor = document.getElementById('font-color');
    var backgroundColor = document.getElementById('background-color');
    if(fontColor.value === backgroundColor.value) {
        // notify the user that's bad.
        fontColor.value = (backgroundColor.value === 'black')? 'white': 'black';
    }
    document.body.style.color = fontColor.value;
}

updateBackgroundColor = function() {
    var fontColor = document.getElementById('font-color');
    var backgroundColor = document.getElementById('background-color');
    if(fontColor.value === backgroundColor.value) {
        // notify the user that's bad.
        backgroundColor.value = (fontColor.value === 'black')? 'white': 'black';
    }
    document.body.style.backgroundColor = backgroundColor.value;
}

onSave = function() {
    var snideComment = document.getElementById('snide-comment');
    if(snideComment) {
        snideComment.parentNode.removeChild(snideComment);
    }

    // Style preferences
    var fontStyle = document.getElementById('font-style').value;
    var fontSize = document.getElementById('font-size').value;
    var fontColor = document.getElementById('font-color').value;
    var backgroundColor = document.getElementById('background-color').value;
    var style = new Object();
    style.fontStyle = fontStyle;
    style.fontSize = fontSize;
    style.fontColor = fontColor;
    style.backgroundColor = backgroundColor;
    localStorage.setItem('style', JSON.stringify(style));
    // User info
    var name = document.getElementById('name').value;
    var favoriteColor = document.getElementById('favorite-color').value;
    var userInfo = {
        name: name,
        favoriteColor: favoriteColor,
        colorChoice: {}
    }
    if(!localStorage.userInfo) {
        userInfo.colorChoice.white = 0;
        userInfo.colorChoice.black = 0;
        userInfo.colorChoice.blue = 0;
        userInfo.colorChoice.azure = 0;
        userInfo.colorChoice.goldenrod = 0;
        userInfo.colorChoice.honeydew = 0;
        userInfo.colorChoice.blueviolet = 0;
    } else {
        var userInfoLS = JSON.parse(localStorage.userInfo)
        userInfo.colorChoice = userInfoLS.colorChoice;
    }
    userInfo.colorChoice[fontColor] = userInfo.colorChoice[fontColor] + 1;
    userInfo.colorChoice[backgroundColor] = userInfo.colorChoice[backgroundColor] + 1;
    localStorage.setItem('userInfo', JSON.stringify(userInfo));
}

onClear = function() {
    if(localStorage.style) {
        localStorage.removeItem('style');
    }
    setDefaults();
}

onLoad = function() {
    // load style
    if(localStorage.style) {
        var style = JSON.parse(localStorage.style);
        document.getElementById('font-style').value = style.fontStyle;
        updateFontStyle();
        document.getElementById('font-size').value = style.fontSize;
        updateFontSize();
        document.getElementById('font-color').value = style.fontColor;
        updateFontColor();
        document.getElementById('background-color').value = style.backgroundColor;
        updateBackgroundColor();




    } else {
        setDefaults();
    }
    // load user info
    if(localStorage.userInfo) {
        var userInfo = JSON.parse(localStorage.userInfo);
        document.getElementById('name').value = userInfo.name;
        var favoriteColor = document.getElementById('favorite-color');
        favoriteColor.value = userInfo.favoriteColor;

        var mostUsedColor = 'None';
        var mostUsedAmount = 0;
        for(var i in userInfo.colorChoice) {
            if(userInfo.colorChoice[i] > mostUsedAmount) {
                mostUsedColor = i;
                mostUsedAmount = userInfo.colorChoice[i];
            }
        }
        if(mostUsedAmount > 0 && favoriteColor.value != mostUsedColor) {
            var snideComment = document.createElement('p');
            snideComment.innerHTML = userInfo.name + ', are you sure that ' 
                                  + favoriteColor.value 
                                  + ' is your favorite color? You used '
                                  + mostUsedColor
                                  + ' '
                                  + mostUsedAmount
                                  + ' time(s), but you only used your "favorite color", '
                                  + favoriteColor.value
                                  + ', '
                                  + userInfo.colorChoice[favoriteColor.value]
                                  + ' time(s)...';
            snideComment.classList.add('clear');
            snideComment.id = 'snide-comment';
            console.log(snideComment);
            favoriteColor.parentNode.insertBefore(snideComment, favoriteColor.nextSibling);
            
        }
    }
}

setDefaults = function() {
    document.getElementById('font-style').value = 'lato';
    document.getElementById('font-size').value = '12';
    document.getElementById('font-color').value = 'black';
    document.getElementById('background-color').value = 'white';

    document.body.style = null;
}

addCar = function() {
    // setup variables
    var carTable = document.getElementById('cars');
    var car = document.getElementById('car');
    var carVal = car.value;
    // null car ele value
    car.value = null;
    // setup row number ele
    var carRowNumEle = document.createElement('td');
    carRowNumEle.innerHTML = carTable.children.length+1;
    // setup data ele
    var carDataEle = document.createElement('td');
    carDataEle.innerHTML = carVal;
    // Setup delete Button
    var deleteButtonEle = document.createElement('button');
    deleteButtonEle.id = carRowNumEle.innerHTML;
    deleteButtonEle.onclick = deleteRow;
    deleteButtonEle.classList.add('btn');
    deleteButtonEle.classList.add('btn-danger');
    deleteButtonEle.innerHTML = 'Delete Car';
    var carDeleteEle = document.createElement('td');
    carDeleteEle.appendChild(deleteButtonEle);
    // create table row, add table data to row, add row to table
    var carEle = document.createElement('tr');
    carEle.appendChild(carRowNumEle);
    carEle.appendChild(carDataEle);
    carEle.appendChild(carDeleteEle);
    carTable.appendChild(carEle);
}

deleteRow = function(event) {
    var carRow = event.toElement.parentNode.parentNode;
    var carTable = document.getElementById('cars');
    carTable.removeChild(carRow);
}


onLoad();