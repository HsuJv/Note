<%-- 
Document   : top
Created on : 2018-6-23, 21:58:04
Author     : xty
--%>

<%@page import="Model.Cata"%>
<%@page import="DAO.CataDaoConn"%>
<%@page import="Model.Message"%>
<%@page import="DAO.MessageDaoConn"%>
<%@page import="Model.Account"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <style type="text/css">
            body,html{
                width: 1004px;
                padding: 0px;
                margin: 0px auto;
                background-image: url(images/background.jpg);      
                background-repeat:no-repeat ;
                background-size:100% 100%; 
                background-attachment: fixed;
                border: none;
            }
            .pic{
                background-repeat:no-repeat ;
                background-size:100% 100%; 
                background-image:url(images/gd.png);
            }
            .top{
                width: 1004px;
                height: 150px;

            }
            a:link, a:visited {
                text-decoration: none;
                color:black;
            }
            .user-bar{
                height: 30px;
                width: 1004px;
                line-height: 30px;

            }
            .login_register{
                width: 300px;
                height: 30px;
                line-height: 30px;
                float: left;
                text-align: right;
                font-weight: bold;
                font-size: 16px;
                font-family: 微软雅黑;
                color:black;

            }
            .user_center{
                width: 120px;
                height: 30px;
                line-height: 30px;
                float: left;
                font-weight: bold;
                text-align: center;
                font-size: 16px;
                font-family: 微软雅黑;
                color:black;

            }
            a:link{
                color: black;
                text-decoration: none;
            }
            .nav{
                width: 720px;
                height: 40px;
                margin-top: 3px;
                float: left;
                background-color: #6699CC;
            }
            .menu_nav{
                margin: 0;
                padding: 0;
                list-style: none;
                list-style-type: none;
            }
            .menu_nav li{
                position: relative;
                width: 110px;
                background: #6699CC;
                float: left;
                text-align: center;
                font-weight: bold;
                font-size: 18px;
                font-weight: bold;
            }
            .menu_nav li a{
                border-right: 1px solid #e9e9e9;
                color: white;
                height: 40px;
                line-height: 40px;
                text-decoration: none;
                display: block;
                text-align: center;
                overflow: hidden;
                text-decoration: none;
            }
            .search{
                width: 284px;
                height: 40px;
                margin-top: 3px;
                line-height: 40px;
                float: left;
                background-color: #6699CC;
            }
            .search .search_content{
                width: 180px;
                height: 22px;
                font-size: 12px;
                background-color: white;
                border: 0;
                padding-left: 6px;
            }
            .search .search_submit{
                background-color: white;
                font-size: 12px;
                height: 22px;
                border: 0;
                color: #6699CC;
                font-weight: bolder;
            }
        </style>

        <script type="text/javascript">
            function checkLogin() {
                var flag = document.getElementById("flag");
                if (flag == null) {
                    var returnVal = window.confirm("未登录或登录已失效！请登录！", "提示");
                    if (returnVal) {
                        location.href = 'Login.jsp';
                    }
                    return false;
                }
                return true;
            }
        </script>
    </head>
    <body>
        <div class="top" >
            <div class="user-bar">
                <div style="width: 580px;height: 30px;float: left;text-align:left;font-size: 12px;font-family: 微软雅黑"></div>
                <div class="login_register">
                    <%
                        //存储URL路径,Servlet处理完后重定向至原URL
                        session.setAttribute("path", request.getRequestURI()
                                + "?" + request.getQueryString());
                        Account at = (Account) session.getAttribute(
                                "sessionAccount");
                        if (at == null) {
                    %>
                    <a href="Login.jsp" style="color:black">登录</a>  
                    <a href="Register.jsp" style="color:white">注册</a>
                    <%
                    } else {
                    %>
                    <span>欢迎您，用户 <%=at.getAccount_name()%></span>
                    <a href="./LogoutServlet" >退出</a>
                    <input id="flag" hidden="hidden" type="text" value="1">
                    <%
                        }
                    %>
                </div>
                <div class="user_center">
                    <% if (null != at && -1 != at.getAccount_limit()) {%>
                    <a href="user.jsp" onclick="return checkLogin();" style="color:black">个人中心</a>
                    <%} else {%>
                    <a href="Admin.jsp" onclick="return checkLogin();" style="color:black">个人中心</a>
                    <% } %>
                </div>
            </div>
            <div class="pic">
                <img src="images/1.png">
            </div>
        </div> 
        <div class="nav" align="center">
            <ul class="menu_nav">
                <li>
                    <a href="index.jsp">首页</a>
                </li>
                <li>
                    <%
                        if (request.getParameter("message") != null && request.
                                getParameter("id") != null) {
                            int message_id = Integer.parseInt(request.
                                    getParameter("id"));
                            MessageDaoConn messageDaoConn = new MessageDaoConn();
                            Message m = new Message();
                            m.setMessage_id(message_id);
                            m = messageDaoConn.returnMessageByMessage_id(m);
                            CataDaoConn cataDaoConn = new CataDaoConn();
                            Cata c = cataDaoConn.returnCataById(m.
                                    getMessage_cata());
                            String cata = c.getName();
                            int id = c.getId();
                    %>
                    <a href="message.jsp?cata=<%=cata%>&id=<%=id%>">帖子</a>
                    <%
                        }
                    %>
                </li>
                <li>
                    <a href="index.jsp">版块</a>
                </li>
                <li>
                    <a href="help.html">帮助</a>
                </li>
            </ul>
        </div>
        <div class="search" align="left">
            <form action="SearchResult.jsp">
                <input class="search_content" name="keys">
                <input class="search_submit" type="submit" value="搜索">
            </form>
        </div>
    </body>
</html>
