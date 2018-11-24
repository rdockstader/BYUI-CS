/*****************************************/
/* NAME: onGetPaymentScheduleClick       */
/* DESC: Function called by the Get      */
/******* Payment Schedule button click.  */
/*****************************************/
var onGetPaymentScheduleClick = function() {
    var loanVars = getLoanVariables();
    var paymentAmount = Number(calculatePaymentAmount(loanVars['principal'], loanVars['interestRate'], loanVars['years']));
    var amountRemaing = Number(loanVars['principal']);
    var payments = [];
    while(amountRemaing > paymentAmount) {
        var payedTowardsInterest = Number(calculateInterest(amountRemaing, loanVars['interestRate']));
        var payedTowardsPrincipal = (paymentAmount - payedTowardsInterest).toFixed(2);
        payments.push({"paymentAmount":paymentAmount.toFixed(2), "towardsPrincipal":payedTowardsPrincipal, "towardsInterest":payedTowardsInterest.toFixed(2), "amountRemaing": Number(amountRemaing).toFixed(2)});
        
        amountRemaing -= payedTowardsPrincipal;
    }
    var payedTowardsInterest = Number(calculateInterest(amountRemaing, loanVars['interestRate']));
    payments.push({"paymentAmount":paymentAmount.toFixed(2), "towardsPrincipal":Number(amountRemaing).toFixed(2), "towardsInterest":payedTowardsInterest.toFixed(2), "amountRemaing": Number(amountRemaing).toFixed(2)});
    
    populateTable(payments);
}

/******************************************/
/* NAME: onCalculateClick                 */
/* DESC: Function called by the           */
/******* Calculate Payment button click.  */
/******************************************/
var onCalculateClick = function() {
    var loanVars = getLoanVariables();

    var paymentAmount = calculatePaymentAmount(loanVars['principal'], loanVars['interestRate'], loanVars['years']);
    console.log(paymentAmount);
    var paymentAmountHtml = 'Payment Amount: $';
    paymentAmountHtml += paymentAmount;
    document.getElementById('payment-amount').innerHTML = paymentAmountHtml;
    
}


/**************************************/
/* NAME: populateTable                */
/* DESC: populates the payment table  */
/**************************************/
var populateTable = function(payments) {
    var tableHtml = '<thead><tr>'
    tableHtml += '<th>Payments Remaining</th>'
    tableHtml += '<th>Payment Amount</th>'
    tableHtml += '<th>Paid Towards Principal</th>'
    tableHtml += '<th>Paid Towards Interest</th>'
    tableHtml += '<th>Amount Remaining</th>'
    tableHtml += '</tr></thead><tbody>';
    var totalPayments = payments.length;
    var rowNum = 0;
    payments.forEach(element => {
        tableHtml += '<tr>';
        tableHtml += '<td>' + (totalPayments - rowNum) + '</td>';
        tableHtml += '<td>' + element['paymentAmount'] + '</td>';
        tableHtml += '<td>' + element['towardsPrincipal'] + '</td>';
        tableHtml += '<td>' + element['towardsInterest'] + '</td>';
        tableHtml += '<td>' + element['amountRemaing'] + '</td>';
        tableHtml += '</tr>';
        rowNum++;
    })
    tableHtml += '</tbody>'
    
    document.getElementById('payment-schedule-table').innerHTML = tableHtml;
}


/***********************************/
/* NAME: getLoanVariables          */
/* DESC: Gets the current value of */
/******  the three loan inputs     */
/***********************************/
var getLoanVariables = function() {
    var years = document.getElementById('years').value;
    var principal = document.getElementById('principal').value;
    var interestRate = document.getElementById('interest-rate').value / 100;
    
    return {"years": years, "principal": principal, "interestRate": interestRate};
}

/********************************/
/* NAME: calculatePaymentAmount */
/* DESC: Calculates the loan    */
/******  payment amount         */
/********************************/
var calculatePaymentAmount = function(principal, annualInterest, loanYears) {
    var numberOfPayments = loanYears * 12;
    var effectiveInterest = annualInterest/12; 
    var multiplier = Math.pow((1+effectiveInterest),numberOfPayments);
    return (principal * ((effectiveInterest * multiplier) / (multiplier - 1))).toFixed(2);
}

/****************************/
/* NAME: calculateInterest  */
/* DESC: Calculates monthly */
/******  interest paid      */
/****************************/
var calculateInterest = function(amountRemaining, annualInterest) {
    var effectiveInterest = annualInterest/12;
    return (amountRemaining * effectiveInterest).toFixed(2);
}

