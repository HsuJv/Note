<%-- 
    Document   : personpost
    Created on : 2018-6-25, 0:30:07
    Author     : Administrator
--%>


<%@page import="Model.Cata"%>
<%@page import="DAO.CataDaoConn"%>
<%@page import="Model.Words"%>
<%@page import="DAO.WordsDaoConn"%>
<%@page import="java.util.Date"%>
<%@page import="DAO.MessageDaoConn"%>
<%@page import="Model.Message"%>
<%@page import="java.util.List"%>
<%@page import="Model.Account"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>我的帖子</title>
    </head>
    <script type="text/javascript">
        var flag = '<%=request.getParameter("flag")%>';
        if (1 == flag) {
            alert("User not exists");
        } else if (2 == flag) {
            window.confirm("请先登录", "提示");
            location.href = 'index.jsp';
        } else if (3 == flag) {
            alert("删除失败");
        }
    </script>
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
                            response.sendRedirect("personpost.jsp?flag=2");
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
                    <%
                        }
                    %>
            </ul>
        </div>

        <div id="right">
            <%
                long account_account = at.getAccount_account();
                MessageDaoConn mdc = new MessageDaoConn();
                List<Message> list = mdc.searchMessageIpost(account_account);
                if (list.isEmpty()) {
            %>
            <br><br>
            <a href="index.jsp" style="text-decoration:none">你还没发过帖子，赶快去发布你的第一个帖子吧！</a>
            <%
            } else {
                for (int i = 0; i < list.size(); i++) {
                    Message m = list.get(i);
                    String message_title = m.getMessage_title();
                    long message_id = m.getMessage_id();
                    Date message_date = m.getMessage_date();
                    long revert_num = m.getRevert_num();
                    int message_cata = m.getMessage_cata();
                    CataDaoConn cd = new CataDaoConn();
                    Cata c = new Cata();
                    c = cd.returnCataById(message_cata);
                    String cata_name = c.getName();
            %>
            <table>
                <tr>
                    <td width="500" rowspan="3">
                        <a href="details.jsp?message=<%=message_title%>&id=<%=message_id%>" style="text-decoration:none"><%=message_title%></a>
                    </td>

                    <td>
                        所属板块:<%=cata_name%>
                    </td>
                    <td rowspan="3">
                        <form action="DelMessageServlet" method="post">
                            <input name="message_id" type="hidden" value="<%=message_id%>"/>
                            <button type="submit">删除</button>
                        </form>
                    </td>
                </tr>
                <tr>
                    <td>
                        发帖时间:<%=message_date%>
                    </td>
                </tr>
                <tr>
                    <td>
                        回复数:<%=revert_num%>
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
