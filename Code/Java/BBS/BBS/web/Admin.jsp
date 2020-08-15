<%-- 
    Document   : Admin
    Created on : Jun 25, 2018, 1:36:16 AM
    Author     : hsu
--%>

<%@page import="Util.PrivilegeUtil"%>
<%@page import="DAO.AccountDaoConn"%>
<%@page import="Model.Account"%>
<%@page import="java.util.ArrayList"%>
<%@page import="Model.Cata"%>
<%@page import="java.util.List"%>
<%@page import="DAO.CataDaoConn"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Moderator Management</title>
    </head>
    <script>
        var flag = '<%=request.getParameter("flag")%>';
        if (1 == flag) {
            alert("用户不存在");
        } else if (2 == flag) {
            window.confirm("只有站长可访问", "提示");
            location.href = 'index.jsp';
        } else if (3 == flag) {
            alert("添加版主失败");
        } else if (4 == flag) {
            alert("删除版主失败");
        } else if (5 == flag) {
            alert("添加版块失败");
        } else if (6 == flag) {
            alert("删除版块失败");  
        }
    </script>
    <body>
        <jsp:include page="top.jsp"/>
        <%
            Account account = (Account) session.getAttribute("sessionAccount");
            String flag = request.getParameter("flag");
            if (null != flag && flag.equalsIgnoreCase("2")) {
                return;
            }
            if (null == account  || !PrivilegeUtil.checkAdmin(account.getAccount_limit())) {
                response.sendRedirect("Admin.jsp?flag=2");
            } else {
        %>
        <table>
            <tr>
                <th align="left">版块名</th>
                <th>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp版主&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp</th>
                <th>新增版主</th>
                <th>删除版主</th>
                <th></th>
            </tr>
            <%
                CataDaoConn cataDaoConn = new CataDaoConn();
                AccountDaoConn accountDaoConn = new AccountDaoConn();
                List<Cata> catas = new ArrayList<>();
                catas = cataDaoConn.searchAllCata();

                for (int i = 0; i < catas.size(); i++) {
                    Cata cata = catas.get(i);
                    int cata_id = cata.getId();
                    String cata_name = cata.getName();
                    List<Account> moderators = new ArrayList<>();
                    moderators = accountDaoConn.searchAdminAll(cata_id);

            %>
            <tr>
                <td> <%=cata_name%></td>
                <td align="middle">
                    <% for (int j = 0; j < moderators.size(); j++) {%>
                    <p><%=moderators.get(j).getAccount_name()%></p>
                    <% }%>
                </td>
                <td>
                    <form action="AddModeratorServlet" method="post">
                        <input name="moderator_name" type="text"/>
                        <input name="cata_id" type="hidden" value="<%=cata_id%>"/>
                        <button type="submit"> + </button>
                    </form>
                </td>
      
                <td>
                    <form action="DelModeratorServlet" method="post">
                        <input name="moderator_name" type="text"/>
                        <input name="cata_id" type="hidden" value="<%=cata_id%>"/>
                        <button type="submit"> - </button>
                    </form>
                </td>
                <td>
                    <form action="DelCataServlet" method="post">
                        <input name="cata_id" type="hidden" value="<%=cata_id%>"/>
                        <button type="submit">删除版块</button>
                    </form>
                </td>
            </tr>
            <% }%>
            <tr>
                <td><b>新建版块</b></td>
                <td>&nbsp&nbsp</td>
                <td colspan="3">
                    <form action="AddCataServlet" method="post">
                        <input name="cata_name" type="text"/>
                        <button type="submit"> + </button>
                    </form>
                </td>
            </tr>
        </table>
        <%  }%>
    </body>
</html>
