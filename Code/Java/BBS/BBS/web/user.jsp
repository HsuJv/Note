<%-- 
    Document   : information
    Created on : 2018-6-24, 22:39:45
    Author     : Administrator
--%>

<%@page import="Model.Words"%>
<%@page import="java.util.List"%>
<%@page import="DAO.WordsDaoConn"%>
<%@page import="Model.Account"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>个人中心</title>
    </head>
    <style type="text/css">
        body{
            margin: 0;
            padding: 0;
        }
        #left{
            width: 30%;
            height: 200px;
            float: left;
        }
        #right{
            width: 70%;
            height: 200px;
            float: right;
        }
    </style>
    <script type="text/javascript">
        var flag = '<%=request.getParameter("flag")%>';
        if (1 == flag) {
            alert("User not exists");
        } else if (2 == flag) {
            window.confirm("请先登录", "提示");
            location.href = 'index.jsp';
        }
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
            alert("修改信息失败！");
        }
    </script>
    <body>
        <div class="topNav">
            <jsp:include page="/top.jsp"></jsp:include>
            </div>
            <div id="left">
                <ul class="sidebar">
                    <li><a href="user.jsp" style="text-decoration:none"> 修改个人信息</a></li><br>
                    <li><a href="personpost.jsp" style="text-decoration:none"> 我的帖子</a></li><br>
                    <li><a href="personmessage.jsp" style="text-decoration:none"> 我的留言</a></li><br>
                    <%
                        Account account = (Account) session.getAttribute(
                                "sessionAccount");
                        String flag = request.getParameter("flag");
                        if (null != flag && flag.equalsIgnoreCase("2")) {
                            return;
                        }
                        if (null == account) {
                            response.sendRedirect("user.jsp?flag=2");
                        } else {
                            long account_account = account.getAccount_account();
                            WordsDaoConn wdc = new WordsDaoConn();
                            List<Words> list = wdc.searchWordsByObjectId(account_account);
                            boolean isNew = false;
                            for (int i = 0; i < list.size(); i++) {
                                if (list.get(i).getWords_new()) {
                                    isNew = true;
                                    break;
                                }
                            }
                            if (isNew) {
                    %>
                <li><a href="personword.jsp" style="text-decoration: none"> 我的讯息(您有新的信息)</a></li>
                    <%
                    } else {
                    %>
                <li><a href="personword.jsp" style="text-decoration: none"> 我的讯息</a></li>
                    <%}%>
            </ul>
        </div>
        <div>
            <form action="UserServlet" method="post">
                <table style="margin-left:35%">          
                    <tr>    
                        <td>用户名:</td>    
                        <td>
                            <input name="account_name" type="text" id="name" size="20" value="<%=account.getAccount_name()%>">
                        </td>
                    </tr>    
                    <tr>    
                        <td>密码:</td>    
                        <td>
                            <input name="account_pass" type="password" id="password" size="20">
                        </td>
                    </tr>
                    <tr>
                        <td>确认密码:</td>
                        <td>
                            <input type="password" name="relpassword" id="relpassword" size="20">
                        </td>
                    </tr>
                </table>
                <br>
                <input type="submit" value="确定"  onclick="return check();" style="margin-left:15%">        
            </form> 
            <%
                }
            %>    
        </div>

    </body>
</html>
