<%-- 
    Document   : personmessage
    Created on : 2018-6-25, 2:32:37
    Author     : Administrator
--%>

<%@page import="DAO.AccountDaoConn"%>
<%@page import="Model.Words"%>
<%@page import="DAO.WordsDaoConn"%>
<%@page import="DAO.WordsDao"%>
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
                            long account_account = at.getAccount_account();
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
        <div id="right">
            <%if (list.isEmpty()) {
            %>
            <br><br>
            <a href="index.jsp" style="text-decoration:none">你的活跃度太低啦！还没有给你讯息哦。快去发一个帖子吧！</a>
            <%
            } else {
                for (int i = 0; i < list.size(); i++) {
                    Words w = list.get(i);
                    long word_subject = w.getWords_subject();
                    String words_content = w.getWords_content();
                    boolean word_new = w.getWords_new();
                    Date word_date = w.getWords_date();

                    AccountDaoConn adc = new AccountDaoConn();
                    Account subject = new Account();
                    subject.setAccount_account(word_subject);
                    subject = adc.returnAccountByAccount_account(subject);
                    String sub = subject.getAccount_name();
            %>
            <table>
                <tr>
                    <td width="500" rowspan="2">
                        <%=words_content%>
                    </td>
                    <td>
                        时间:<%=word_date%>
                    </td>
                    <td width="40" rowspan="2">
                        <%if (word_new) {
                        %>
                        <b style="font-size: 10px">*未读*</b>
                        <%
                            }
                        %>
                    </td>
                </tr>
                <tr>
                    <td>
                        来自:<a href="newword.jsp?object=<%=subject.getAccount_account()%>"><%=sub%></a>
                    </td>
                </tr>
            </table>
            <%
                            wdc.readWords(w);
                        }
                    }
                }
            %>
        </div>
    </body>
</html>
