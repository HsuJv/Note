<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" charset=UTF-8">
        <title>注册页面</title>
        <meta charset="utf-8">
        <link href="css/loginstyle.css" rel='stylesheet' type='text/css' />
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <script type="application/x-javascript"> addEventListener("load", function() { setTimeout(hideURLbar, 0); }, false); function hideURLbar(){ window.scrollTo(0,1); } </script>
        <!--webfonts-->
        <!--//webfonts-->
    </head>
    <script type="text/javascript">
        function check() {
            var flag = true;
            var name = document.getElementById("name").value;
            var password = document.getElementById("password").value;
            var relpassword = document.getElementById("relpassword").value;

            if (name == "") {
                alert("请输入用户名！");
                flag = false;
                return false;
            } else if (password == "") {
                alert("请输入密码！");
                flag = false;
                return false;
            } else if (relpassword != password) {
                alert("密码不一致！");
                flag = false;
                return false;
            }
            if (flag == true) {
                return true;
            }
        }
    var validate = '<%=request.getParameter("validate")%>';
        if (validate == 1) {
            alert("用户名已被注册！");
        }
    </script>
    <body>
        <!-----start-main---->
        <div class="main">
            <div class="login-form">
                <h1>Member Register</h1>
                <div class="head">
                    <img src="images/user.png" alt=""/>
                </div>
                <form action="RegisterServlet" method="post">
                    <input type="text" name="account_name" class="text" placeholder="请输入您的用户名" onfocus="this.value = '';" onblur="if (this.value == '') {
                                                            this.value = 'USERNAME';}" >
                    <input type="password"  name="account_pass"  placeholder="请输入您的密码"  onfocus="this.value = '';" onblur="if (this.value == '') {
                                                            this.value = 'Password';}">
                    <input type="password" name="relpassword" placeholder="再次输入密码" id="relpassword" size="20">
                    <div class="submit">
                        <input type="submit" value="注册" onclick="return check();" >
                        <input type="button" value="返回" onclick="window.location.href = 'Login.jsp'" />
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