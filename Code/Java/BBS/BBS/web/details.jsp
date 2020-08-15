<%-- 
    Document   : details
    Created on : 2018-6-23, 15:20:43
    Author     : xty
--%>

<%@page import="Model.Account"%>
<%@page import="DAO.AccountDaoConn"%>
<%@page import="java.util.Date"%>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@page import="Model.Revert"%>
<%@page import="java.util.List"%>
<%@page import="DAO.RevertDaoConn"%>
<%@page import="DAO.MessageDaoConn"%>
<%@page import="Model.Message"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>帖子——<%=request.getParameter("message")%></title>
        <style type="text/css">
            .detail_wrap{
                width: 1004px;
                margin: 10px auto;
            }
            .topic_wrap {
                background: #fff;
                box-shadow: 0 1px 2px 0 rgba(0,0,0,.06);
                display: table;
                table-layout: fixed;
                width: 100%;
            }
            .user {
                background: #fafbfc;
                box-shadow: inset -1px 0 0 0 #ebedf0;
                display: table-cell;
                position: relative;
                text-align: center;
                width:200px;  /*设置div的大小*/
                border:1px 	Azure;    /*边框*/
                text-align: center;        /*文字水平居中对齐*/
                line-height: 200px;        /*设置文字行距等于div的高度*/
                overflow:hidden;
            }
            .content{    margin-left: 152px;
                         padding: 0 24px;
                         display: table-cell;
                         max-width: 804px;
                         vertical-align: top;
                         overflow: hidden;
            }
            .message_info{
                height: 32px;
                line-height: 32px;
                font-size: 12px;
                color: #999;
            }
            .reply{
                float: left;
            }
            .date{
                float: right;
            }
            .floor{
                margin-left: 16px;
                color: #4f4f4f;
                font-weight: 700;
            }
            .message_body{
                clear: both;
                word-wrap: break-word;
                overflow: hidden;
                padding: 16px 0;
                font-size: 14px;
                color: #4f4f4f;
                font-weight: 700;
                line-height: 24px;
                position: relative;
                min-height: 116px;
            }
            .review_wrap{
                padding: 10px;
                background-color: #fff;
                margin-top: 8px;
                box-sizing: border-box;
            }
            .menu_a {
                display: inline-block;
                vertical-align: middle;
                height: 28px;
                line-height: 26px;
                padding: 0 8px;
                background-color: #4788c7;
                border: 1px solid #00669f;
                border-radius: 2px;
                font-size: 13px;
                color: #fff;
            }
            .bbs_editor{
                width: 100%;
                background-color: #fff;
                box-shadow: 0 2px 4px 0 rgba(0,0,0,.05);
                margin: 8px 0;
                display: none;
            }
            form{
                list-style: none;
                margin: 0;
                padding: 0;
                outline: 0;
            }
            .post_body{
                padding: 5px;
                width: 99%;
                height: 320px;
                clear: both;
                line-height: 18px;
                overflow: auto;
                border-color: #ccc;
                resize: none;
                vertical-align: top;
            }
            .btn_b{
                cursor: pointer;
                border-radius: 2px;
                -webkit-border-radius: 2px;
                -moz-border-radius: 2px;
                -khtml-border-radius: 2px;
                padding: 0 15px;
                height: 32px;
                line-height: 30px;
                background-color: #CA0C16;
                border: 1px solid #B50A13;
                color: #fff !important;
                font-size: 14px;
            }
        </style>
        <script>
            function checkNewPost() {
                var editor = document.getElementById("editor");
                var flag = document.getElementById("flag");
                if (flag == null) {
                    var returnVal = window.confirm("未登录或登录已失效！请登录！", "提示");
                    if (returnVal) {
                        location.href = 'Login.jsp';
                    }
                    return false;
                }
                editor.style.display = "block";
                return true;
            }
            function checkNewWord() {
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
        <div class="topNav">
            <jsp:include page="/top.jsp"></jsp:include>
            </div>
            <div class="detail_wrap">
            <%
                MessageDaoConn messageDaoConn = new MessageDaoConn();
                RevertDaoConn revertDaoConn = new RevertDaoConn();

                long message_id = Long.parseLong(request.getParameter("id"));
                Message message = new Message();
                message.setMessage_id(message_id);
                message = messageDaoConn.returnMessageByMessage_id(message);
                List<Revert> reverts = revertDaoConn.searchRevertByMessage_id(
                        message_id);
            %>
            <div class="topic_wrap">
                <div class="user">
                    <a href="newword.jsp?object=<%=message.getMessage_account()%>"
                       onclick="return checkNewWord();"><%=message.getMessage_account_name()%></a>
                </div>
                <div class="content">
                    <div class="message_info">
                        <div class="reply">
                            <span>回复次数</span>
                            <em><%=message.getRevert_num()%></em>
                        </div>
                        <div class="date">
                            <label>发表于 <%=message.getMessage_date()%></label>
                            <span class="floor">楼主</span>
                        </div>
                    </div>
                    <div class="message_body">
                        <p><%=message.getMessage_content()%></p>
                    </div>
                </div>
            </div>
            <%

                int revert_count = reverts.size();
                for (int i = 0; i < revert_count; i++) {
                    Revert revert = reverts.get(i);
                    Account account = new Account();
                    AccountDaoConn accountDaoConn = new AccountDaoConn();
                    account.setAccount_account(revert.getRevert_account());
                    account = accountDaoConn.returnAccountByAccount_account(account);
                    String account_name = account.getAccount_name();
                    Date revert_date = revert.getRevert_date();
                    String revert_content = revert.getRevert_content();
                    System.out.println(revert_date.getTime());
            %>
            <div class="topic_wrap">
                <div class="user">
                    <a href="newword.jsp?object=<%=account.getAccount_account()%>" 
                       onclick="return checkNewWord();"><%=account_name%></a>
                </div>
                <div class="content">
                    <div class="message_info">
                        <div class="date">
                            <label>发表于 <%=revert_date.toString()%></label>
                            <span class="floor"><%=(i + 1)%>#</span>
                        </div>
                    </div>
                    <div class="message_body">
                        <p><%=revert_content%></p>
                    </div>
                </div>
            </div>
            <%
                }
            %>

            <div class="review_wrap">
                <a class="menu_a" href="#new_post" onclick="return checkNewPost();">回复</a>
            </div>

            <div class="topic_wrap">
                <div id="editor" class="bbs_editor">
                    <form id="new_post" class="new_post" action="./SaveRevertServlet">
                        <%
                            Account at = (Account) session.getAttribute("sessionAccount");
                            if (at != null) {
                                long revert_account = at.getAccount_account();
                                long revert_messageid = message_id;
                        %>
                        <input name="revert_account" type="text" hidden="hidden" value="<%=revert_account%>">
                        <input name="revert_messageid" type="text" hidden="hidden" value="<%=revert_messageid%>">
                        <%
                            }
                        %>
                        <textarea name="revert_content" class="post_body" cols="20" rows="10" maxlength="300"> 
                        </textarea>
                        <div class="pub">
                            <input  value="提交回复" class="btn_b" type="submit">
                        </div>
                    </form>
                </div>

            </div>
        </div>
    </body>
</html>
