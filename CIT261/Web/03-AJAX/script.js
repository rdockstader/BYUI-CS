var kanto;

function getJSON(url, method, isAsync, callback)
{
	// Verify there is a URL, if not exit function
    if(url == null) {
        console.error('URL CANNOT BE NULL');
        return;
    }
    // Verify there is a callback, if not exit the function
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


var searchMovie = function() {
    var title = document.getElementById('movie-title').value;
    var year = document.getElementById('movie-year').value;
    var type = document.getElementById('movie-type').value;
    
    var url = 'http://www.omdbapi.com/?apikey=980b75d0';
    if(title != null && title != '') {
        url += '&s=' + title;
    } else {
        // throw error here
        return;
    }
    if(year != null && year != '' && !isNaN(year)) {
        url += '&y=' + year;
    }
    if(type != null && type != '') {
        url += '&type=' + type;
    }
    
    getJSON(url, null, null, function(resp) {
        var result = JSON.parse(resp);
        var html = '';
        if(result.Response != 'False') {
            result.Search.forEach(function(ele) {
            html += '<h3>' + ele.Title + '</h3>';
            html += '<h4>' + ele.Year + ' ~ ' + ele.Type + '</h4>';
            if(ele.Poster != 'N/A') {
                html += '<img src="' + ele.Poster + '" alt="' + ele.Title + '">';
            } else {
                html += '<p><em> No poster available </em></p>';
            }
            
        })
        
        html += '<p><em> Total Results: ' + result.totalResults + '</em></p>';
        } else {
            html += '<p> No Results Found </p>';
        }
        
        document.getElementById('movie-display').innerHTML = html;
    })
    
    
}

getJSON('./pokemon.json', null, null, function(resp) {
    kanto = JSON.parse(resp)['regions'][0];
});