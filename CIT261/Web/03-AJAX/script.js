var kanto;

function getJSON(url, method, isAsync, callback)
{
	// Verify there is a URL, if not exit function
    if(url == null) {
        console.error('URL CANNOT BE NULL');
        return;
    }
    // Verify ther eis a callback, if not exit the function
    if(callback == null) {
        console.error('CALLBACK CANNOT BE NULL');
        return;
    }
    // default to GET
    if(method == null) {
        method = 'GET';
    }
    // default to true (false is depreciated)
    if(isAsync == null) {
        isAsync = true;
    }
    // setup and send request
	var xmlhttp = new XMLHttpRequest();
	xmlhttp.onreadystatechange=function()	
			{
				if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                    callback(xmlhttp.responseText);
                    
                } 
					
			}
	xmlhttp.open(method, url, isAsync);
	xmlhttp.send();
}

var getRandomPokemon = function() {
    var index = Math.floor(Math.random() * 152)-1;
    var display = document.getElementById('poke-display');
    var html = '';
    if(kanto != null) {
        var pokemon = kanto.pokemon[index];
        html = '<h1>' + pokemon.name + '</h1>';
        html += '<h2>' + pokemon.number + '</h2>';
        html += '<img src="' + pokemon.imgPath + '" alt="' + pokemon.name + '">' 
        
    } else {
        html = '<p class="error">ERROR GETTING JSON FILE</p>';
    }
    
    display.innerHTML = html;

}

getJSON('./pokemon.json', null, null, function(resp) {
    kanto = JSON.parse(resp)['regions'][0];
});