$(document).ready(function(){
    $('#signup-submit').click(function(){
        var user = document.getElementById("signup-user").value;
        var email = document.getElementById("signup-email").value;
    	var pwd = document.getElementById("signup-pwd").value;
        var pwdConf = document.getElementById("signup-pwd-conf").value;
        if (pwd.localeCompare(pwdConf))
            {
                console.log("NOT MATCHING PWDS!!");
            }
        var endpoint = '?username=' + user + '&email=' + email + '&pwd=' + pwd;
        var url = 'https://felipearce.pw:3000/signup' + endpoint;
        console.log(url)
        let request = new XMLHttpRequest();
        request.open('POST', url, true);
        request.withCredentials = false;
        request.responseType = 'json';
        request.onload = function() {
            console.log(request.response);
            
            if (request.status == 200)
                {
                    window.location.replace("https://felipearce.pw/dashboard.html");
                }
            else
                {
                    console.log("Error: " + request.status);
                }
        };
        request.send();
        return true;
    });
   
    
});