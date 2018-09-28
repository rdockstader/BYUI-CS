function submitRequest(reqPath) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
        document.getElementById("city-display").innerHTML = this.responseText.replace(/(?:\r\n|\r|\n)/g, '<br>');
    }
  };
  xhttp.open("GET", reqPath, true);
  xhttp.send();
}

function submitJSONRequest() {
    
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
        var parsedJSON = JSON.parse(this.response);
        var html = "<table><tr><th>First Name</th>";
        html += "<th>Last Name</th>";
        html += "<th>Major</th>";
        html += "<th>GPA</th>";
        html += "<th>Address</th></tr>";
        for(var i in parsedJSON.students) {
            html+= "<tr>";
            html += "<td>" + parsedJSON.students[i].first + "</td>";
            html += "<td>" + parsedJSON.students[i].last + "</td>";
            html += "<td>" + parsedJSON.students[i].major + "</td>";
            html += "<td>" + parsedJSON.students[i].gpa + "</td>";
            html += "<td>" + parsedJSON.students[i].address.city + " " 
                           + parsedJSON.students[i].address.state + ", "
                           + parsedJSON.students[i].address.zip + "</td>";
            html += "</tr>";
            
        }
        html += "</table>";
        
        
        document.getElementById("json-display").innerHTML = html;
    }
  };
  xhttp.open("GET", document.getElementById("json-file-input").value, true);
  xhttp.send();
}