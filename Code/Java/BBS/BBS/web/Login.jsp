<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" charset=UTF-8">
        <title>登录页面</title>
        <meta charset="utf-8">
        <link href="css/loginstyle.css" rel='stylesheet' type='text/css' />
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <script type="application/x-javascript"> addEventListener("load", function() { setTimeout(hideURLbar, 0); }, false); function hideURLbar(){ window.scrollTo(0,1); } </script>
        <!--webfonts-->
        <!--//webfonts-->
    </head>
    <script>
        function check() {
            var flag = true;
            var name = document.getElementById("name").value;
            var password = document.getElementById("password").value;

            if (name == "") {
                alert("请输入用户名！");
                flag = false;
                return false;
            } else if (password == "") {
                alert("请输入密码！");
                flag = false;
                return false;
            }

            if (flag == true) {
                return true;
            }
        }
        var flag = '<%=request.getParameter("flag")%>';
        if (flag == 1) {
            alert("登录失败！");
        }
    </script>
    <body>
        <!-----start-main---->
        <div class="main">
            <div class="login-form">
                <h1>Member Login</h1>
                <div class="head">
                    <img src="images/user.png" alt=""/>
                </div>
                <form action="LoginServlet" method="post">
                    <input type="text" name="account_name" class="text" value="USERNAME" onfocus="this.value = '';" onblur="if (this.value == '') {
                                                            this.value = 'USERNAME';
                                                        }" >
                    <input type="password"  name="account_pass"   value="Password" onfocus="this.value = '';" onblur="if (this.value == '') {
                                                            this.value = 'Password';}">
                    <div class="submit">
                        <input type="submit" onclick="return check()" value="登录" >
                        <input type="button" value="注册" onclick="window.location.href = 'Register.jsp'" />
                    </div>
                </form>
            </div>
            <!--//End-login-form-->
            <!-----start-copyright---->
            <div class="copy-right">
                <p>Designed by 408-1</a>
            </div>
            <!-----//end-copyright---->
        </div>
        <!-----//end-main---->

    </body>
</html>