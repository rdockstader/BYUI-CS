
var increaseWidth = function() {
    //console.log('increate width');
    this.style.width = '60%';
}

var decreaseWidth = function() {
    //console.log('decrease width');
    this.style.width = '';
}

var setActiveButton = function(ele) {
    //console.log('setting active button');
    var btns = [];
    btns.push(document.getElementById('video-btn'));
    btns.push(document.getElementById('audio-btn'));
    btns.push(document.getElementById('canvas-btn'));
    btns.push(document.getElementById('clear-btn'));

    btns.forEach((e) => {
        if(e !== ele) {
            if(!e.classList.contains('btn-primary')) {
                e.classList.add('btn-primary');
            }
            e.classList.remove('btn-success');
        } else {
            e.classList.remove('btn-primary');
            if(!e.classList.add('btn-success')) {
                e.classList.add('btn-success');
            }
        }
    });
}

var getMainSection = function() {
    return document.getElementById('main-section');
}

var clearMainSection = function() {
    var mainSection = getMainSection();

    while(mainSection.firstChild) {
        mainSection.removeChild(mainSection.firstChild);
    }
    mainSection.style = null;
}

var videoBtnClick = function() {
    //console.log('video button clicked');
    var videoBtn = document.getElementById('video-btn');
    setActiveButton(videoBtn);
    clearMainSection();
    // build main section for video
    var mainSection = getMainSection();
    var vidWrapper = document.createElement('div');
    vidWrapper.classList.add('media-wrapper');
    var vid = document.createElement('video');
    vid.setAttribute('src', 'https://download.blender.org/peach/bigbuckbunny_movies/BigBuckBunny_320x180.mp4');
    vid.controls = true;
    vid.style.width = '100%';
    vidWrapper.appendChild(vid);
    mainSection.appendChild(vidWrapper);
}

var audioBtnClick = function() {
    console.log('audio button clicked');
    var audioBtn = document.getElementById('audio-btn');
    setActiveButton(audioBtn);
    clearMainSection();
    // Build main section for audio
    var mainSection = getMainSection();
    var audioWrapper = document.createElement('div');
    audioWrapper.classList.add('media-wrapper');
    var audio = document.createElement('audio');
    audio.controls = true;
    audio.src = '../mp3/sample.mp3';
    audioWrapper.appendChild(audio);
    mainSection.appendChild(audioWrapper);
}

var rotateCanvas = function() {
    console.log('rotate canvas called');
    var canvas = document.getElementById('main-canvas');
    var rotateBtn = document.getElementById('rotate-btn');
    if(canvas) {
        if(canvas.style.transform != '') {
            console.log('here');
            canvas.style.transform = '';
            rotateBtn.innerHTML = "Portrait";
            
        } else {
            canvas.style.transform = "rotate(90deg)";
            rotateBtn.innerHTML = "Landscape";
        }
    }
}

var canvasClick = function(event) {
    console.log(event);
    var canvas = document.getElementById('main-canvas');
    var ctx = canvas.getContext("2d");
    ctx.beginPath();
    ctx.arc(event.offsetX, event.offsetY, 10, 0, 2 * Math.PI);
    ctx.stroke();
    // Fill random color
    var color = 'black';
    switch(Math.floor(Math.random() * 4)) {
        case 0:
            color = 'red';
            break;
        case 1:
            color = 'blue';
            break;
        case 2:
            color = 'green';
            break;
        case 3:
            color = 'yellow';
            break;
        case 4:
            color = 'orange';
            break;
        default:
            break;
    }
    ctx.fillStyle = color;
    ctx.fill();
}

var canvasBtnClick = function() {
    var canvasBtn = document.getElementById('canvas-btn');
    setActiveButton(canvasBtn);
    clearMainSection();
    var mainSection = getMainSection();
    var canvasWrapper = document.createElement('div');
    //canvasWrapper.classList.add('media-wrapper');
    var btnDiv = document.createElement('div');
    canvasWrapper.appendChild(btnDiv);
    var rotateBtn = document.createElement('button');
    rotateBtn.classList.add('btn');
    rotateBtn.classList.add('btn-primary');
    rotateBtn.id = 'rotate-btn';
    rotateBtn.innerHTML = "Portrait";
    btnDiv.appendChild(rotateBtn);
    var canvasDiv = document.createElement('div');
    canvasDiv.style.margin = "100px 100px";
    var canvas = document.createElement('canvas');
    canvas.id = 'main-canvas';
    canvas.style.border = "1px solid black";
    canvas.style.borderRadius = '2px';
    canvas.onclick = canvasClick;
    rotateBtn.onclick = rotateCanvas;
    canvasDiv.appendChild(canvas);
    canvasWrapper.appendChild(canvasDiv);
    mainSection.appendChild(canvasWrapper);


}

var clearBtnClick = function() {
    var clearBtn = document.getElementById('clear-btn');
    setActiveButton(clearBtn);
    clearMainSection();
}

var onInit = function() {
    var videoBtn = document.getElementById('video-btn');
    var audioBtn = document.getElementById('audio-btn');
    var canvasBtn = document.getElementById('canvas-btn');
    var clearBtn = document.getElementById('clear-btn');
    // On Mouse Over
    videoBtn.onmouseover = increaseWidth;
    audioBtn.onmouseover = increaseWidth;
    canvasBtn.onmouseover = increaseWidth;
    clearBtn.onmouseover = increaseWidth;

    // On Mouse Out
    videoBtn.onmouseout = decreaseWidth;
    audioBtn.onmouseout = decreaseWidth;
    canvasBtn.onmouseout = decreaseWidth;
    clearBtn.onmouseout = decreaseWidth;

    // On click 
    videoBtn.onclick = videoBtnClick;
    audioBtn.onclick = audioBtnClick;
    canvasBtn.onclick = canvasBtnClick;
    clearBtn.onclick = clearBtnClick;

    setActiveButton(clearBtn);
}

onInit();