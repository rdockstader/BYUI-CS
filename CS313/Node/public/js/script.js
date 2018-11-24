function doMathsAJAX() {
    console.log("Doing some AJAX maths!");
    var lhs = document.getElementById('numberOne');
    var operator = document.getElementById('operator');
    var rhs = document.getElementById('numberTwo');
    var output = document.getElementById('output');
    $.ajax({
        url: "/09/team/math_service",
        type: "POST",
        data: {
            numberOne: lhs.value,
            numberTwo: rhs.value,
            operator: operator.value
        },
        success: function(result) {
            output.innerHTML = "Result of equation: " + result.total;
        }
    })   
}

function getRateAJAX() {
    console.log("getting some rates AJAX!");
    var weightEle = document.getElementById('weight');
    var typeEle = document.getElementById('type');
    var output = document.getElementById('output');
    $.ajax({
        url: "/09/prove/rate",
        type: "POST",
        data: {
            weight: weightEle.value,
            type: typeEle.value
        },
        success: function(result) {
            output.innerHTML = "<h3> Rate: $" + result.rate + "</h3>";
        }
    }) 
}


function getPersons() {
    var nameEle = document.getElementById('firstName');
    var outputEle = document.getElementById('output-id');

    if(nameEle.value == null || nameEle.value == '') {
        outputEle.innerHTML = '<div class="alert alert-danger" role="alert">First Name must be filled out</div>'
    } else {
        $.ajax({
            url: "/api/person/firstName/" + nameEle.value,
            type: "GET",
            success: function(result) {
                // build html table
                var html = '<table class="table">';
                html += '<thead><tr>';
                html += '<th>ID</th>';
                html += '<th>First</th>';
                html += '<th>Last</th>';
                html += '<th>DoB</th>';
                html += '</tr></thead><tbody>';
                for(var pers in result) {
                    pers = result[pers];
                    html += '<tr>';
                    html += '<td>' + pers['_id'] + '</td>';
                    html += '<td>' + pers['firstName'] + '</td>';
                    html += '<td>' + pers['lastName'] + '</td>';
                    var dob = new Date(pers['dateOfBirth']);
                    html += '<td>' + dob.toLocaleDateString("en-US") + '</td>';
                    html += '</tr>';
                }
                html += '</tbody></table>';
                outputEle.innerHTML = html;
            },
            error: function(err) {
                outputEle.innerHTML = err;
            }
        })
    }
}
function getParents() {
    var idEle = document.getElementById('id');
    var outputEle = document.getElementById('output-realation');

    if(idEle.value == null || idEle.value == '') {
        outputEle.innerHTML = '<div class="alert alert-danger" role="alert">ID must be filled out</div>'
    } else {
        $.ajax({
            url: "/api/person/" + idEle.value + '/parents',
            type: "GET",
            success: function(result) {
                var html = '<h2>Parents</h2>';
                // build html table
                html += '<table class="table">';
                html += '<thead><tr>';
                html += '<th>ID</th>';
                html += '<th>First</th>';
                html += '<th>Last</th>';
                html += '<th>DoB</th>';
                html += '</tr></thead><tbody>';
                for(var pers in result) {
                    pers = result[pers]['parent'];
                    html += '<tr>';
                    html += '<td>' + pers['_id'] + '</td>';
                    html += '<td>' + pers['firstName'] + '</td>';
                    html += '<td>' + pers['lastName'] + '</td>';
                    var dob = new Date(pers['dateOfBirth']);
                    html += '<td>' + dob.toLocaleDateString("en-US") + '</td>';
                    html += '</tr>';
                }
                html += '</tbody></table>';
                outputEle.innerHTML = html;
            },
            error: function(err) {
                outputEle.innerHTML = err;
            }
        })
    }
    
}
function getChildren() {
    var idEle = document.getElementById('id');
    var outputEle = document.getElementById('output-realation');

    if(idEle.value == null || idEle.value == '') {
        outputEle.innerHTML = '<div class="alert alert-danger" role="alert">ID must be filled out</div>'
    } else {
        $.ajax({
            url: "/api/person/" + idEle.value + '/children',
            type: "GET",
            success: function(result) {
                var html = '<h2>Children</h2>';
                // build html table
                html += '<table class="table">';
                html += '<thead><tr>';
                html += '<th>ID</th>';
                html += '<th>First</th>';
                html += '<th>Last</th>';
                html += '<th>DoB</th>';
                html += '</tr></thead><tbody>';
                for(var pers in result) {
                    pers = result[pers]['child'];
                    html += '<tr>';
                    html += '<td>' + pers['_id'] + '</td>';
                    html += '<td>' + pers['firstName'] + '</td>';
                    html += '<td>' + pers['lastName'] + '</td>';
                    var dob = new Date(pers['dateOfBirth']);
                    html += '<td>' + dob.toLocaleDateString("en-US") + '</td>';
                    html += '</tr>';
                }
                html += '</tbody></table>';
                outputEle.innerHTML = html;
            },
            error: function(err) {
                outputEle.innerHTML = err;
            }
        })
    }
}