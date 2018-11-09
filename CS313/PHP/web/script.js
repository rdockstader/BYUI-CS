function hasNumber(myString) {
  return /\d/.test(myString);
} 

function comparePasswords() {
    var password = document.getElementById('login-password');
    var passwordConfirm = document.getElementById('login-password-confirm');
    var prompt = document.getElementById('confirm-pw-prompt');
    if(password.value !== passwordConfirm.value) {
         prompt.removeAttribute('hidden');
    } else if(!prompt.getAttribute('hidden')) {
        prompt.setAttribute('hidden', 'true');
    }
}

function validatePassword() {
    var password = document.getElementById('login-password');
    var length = document.getElementById('greater-then-7');
    var hasNumbers = document.getElementById('contains-number');
    // numbers
    var hasNum = hasNumber(password.value)
    if(!hasNum && !hasNumbers.classList.contains('required')) {
        hasNumbers.classList.add('required');
    } else if (hasNum && hasNumbers.classList.contains('required')) {
        hasNumbers.classList.remove('required');
    }
    // length
    if(password.value.length < 8 && !length.classList.contains('required')) {
        length.classList.add('required');
    } else if (password.value.length >= 8 && length.classList.contains('required')) {
        length.classList.remove('required');
    } 
}

