<%-- 
    Document   : personmessage
    Created on : 2018-6-25, 2:32:37
    Author     : Administrator
--%>

<%@page import="Model.Words"%>
<%@page import="DAO.WordsDaoConn"%>
<%@page import="java.util.Date"%>
<%@page import="DAO.RevertDaoConn"%>
<%@page import="Model.Revert"%>
<%@page import="java.util.List"%>
<%@page import="Model.Account"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>我的留言</title>
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
                        Account at = (Account) session.getAttribute("sessionAccount");
                        String flag = request.getParameter("flag");
                        if (null != flag && flag.equalsIgnoreCase("2")) {
                            return;
                        }
                        if (null == at) {
                            response.sendRedirect("personmessage.jsp?flag=2");
                        } else {
                            long account_account_1 = at.getAccount_account();
                            WordsDaoConn wdc = new WordsDaoConn();
                            List<Words> l = wdc.searchWordsByObjectId(account_account_1);
                            boolean isNew = false;
                            for (int i = 0; i < l.size(); i++) {
                                if (l.get(i).getWords_new()) {
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
        <div id="right">
            <%
                long account_account = at.getAccount_account();
                RevertDaoConn rdc = new RevertDaoConn();
                List<Revert> list = rdc.searchRevertById(account_account);
                if (list.isEmpty()) {
            %>
            <br><br>
            <a href="index.jsp" style="text-decoration:none">你还没留过言，赶快去留下你的第一个评论吧！</a>
            <%
            } else {
                for (int i = 0; i < list.size(); i++) {
                    Revert r = list.get(i);
                    String revert_content = r.getRevert_content();
                    Date revert_date = r.getRevert_date();
                    long message_id = r.getRevert_messageid();
                    long revert_id = r.getRevert_id();
            %>
            <table>
                <tr>
                    <td width="500" rowspan="2">
                        <%=revert_content%>
                    </td>
                    <td>
                        发帖时间:<%=revert_date%>
                    </td>
                    <td rowspan="2">
                        <form action="DelRevertServlet" method="post">
                            <input name="revert_id" type="hidden" value="<%=revert_id%>"/>
                            <button type="submit">删除</button>
                        </form>
                    </td>
                </tr>
                <tr>
                    <td>
                        贴子ID:<%=message_id%>
                    </td>
                </tr>
            </table>
            <%
                        }
                    }
                }
            %>
        </div>
    </body>
</html>
