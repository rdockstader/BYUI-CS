var token = "";

function search() {
    var input = $("#search-box").val();
    var output = document.getElementById("output");
    var apiUrl = "http://www.omdbapi.com/?apikey=f8240d6f&s=" + input;
    $.ajax({
        type: "GET",
        url: apiUrl,
        success: function (result) {
            var html = "";
            for(var movie in result.Search) {
                movie = result.Search[movie];
                html += "<div><p>";
                html += movie.Title
                html += "</p><button onclick='viewDetails(\"" + movie.imdbID + "\")'>View Details</button><p id=\"" + movie.imdbID + "\"></p></div";
            }
            output.innerHTML = html;
        },
        error: function (result) {
        console.log(result);
        alert("Sorry, addition failed.  Please refresh the page before continuing");
        }
    });
}

function viewDetails(id) {
    var output = document.getElementById(id);
    var apiUrl = "http://www.omdbapi.com/?apikey=f8240d6f&i=" + id;
    console.log(id);
    $.ajax({
        type: "GET",
        url: apiUrl,
        success: function (result) {
            var html = "<img src='" + result.Poster + "'>";
            html += "<p>" + JSON.stringify(result) + "</p>";
            console.log(result)
            output.innerHTML = html;
        },
        error: function (result) {
        console.log(result);
        alert("Sorry, addition failed.  Please refresh the page before continuing");
        }
    });
}


function login() {
	var username = $("#username").val();
	var password = $("#password").val();

	var params = {
		username: username,
		password: password
	};

	$.post("/login", params, function(result) {
		if (result && result.success) {
            token = result.token;
			$("#status").text("Successfully logged in.");
		} else {
            $("#status").text("Error logging in.");
            console.log(result);
		}
	});
}

function logout() {
    token = null;
	$.post("/logout", function(result) {
		if (result && result.success) {
			$("#status").text("Successfully logged out.");
		} else {
			$("#status").text("Error logging out.");
		}
	});
}

function getServerTime() {
    $.ajax({
            type: 'GET',
            url: '/getServerTime',
            dataType: 'json',
            beforeSend: function(xhr) {
                xhr.setRequestHeader ("Authorization", "Bearer " + token);
            },
            success: function(result) {
                $("#status").text("Server time: " + result.time);  
            },
            error: function(result) {
                $("#status").text("Got a result back, but it wasn't a success. Your reponse should have had a 401 status code.");
                console.log(result);
            }
        });
}