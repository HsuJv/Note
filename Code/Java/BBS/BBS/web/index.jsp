<%-- 
    Document   : index
    Created on : 2018-6-22, 11:25:35
    Author     : xty
--%>

<%@page import="DAO.CataDaoConn"%>
<%@page import="java.util.List"%>
<%@page import="java.io.PrintWriter"%>
<%@page import="Model.Cata"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>学习论坛首页</title>
        <script type="text/javascript">
        </script>
        <style type="text/css">
            .index_wrap{
                width: 960px;
                margin: 10px auto;
                font-size: large;
            }
            a:link, a:visited {
                text-decoration: none;
                color:black;


            }
            .page{
                font-size: medium;
                position:relative;
                bottom:50px;
            }
        </style>
    </head>
    <body>
        <div class="topNav">
            <jsp:include page="/top.jsp"></jsp:include>
            </div>
            <div class="index_wrap">

            <%
                int maxNum = 7;//每页容纳最大板块数
                int count = 0;//板块数
                int firstPage = 1; //首页
                int lastPage = 1; // 尾页
                int pageNo = 1; //当前页号

                CataDaoConn cataDaoConn = new CataDaoConn();

                List<Cata> cataList = cataDaoConn.searchAllCata();
                count = cataList.size();

                lastPage = (int) Math.ceil((double) count / maxNum);//向上取整获得尾页
                int firstCataId = 1 + (pageNo - 1) * maxNum; //本页首个板块id

                if (request.getParameter("pageNo") == null || request.getParameter("pageNo").equals("")) {
                    pageNo = 1;
                } else {
                    pageNo = Integer.parseInt(request.getParameter("pageNo"));
                    if (pageNo > lastPage) {
                        response.sendRedirect("index.jsp?pageNo=" + lastPage);
                    }
                    if (pageNo < 1) {
                        response.sendRedirect("index.jsp?pageNo=" + firstPage);
                    }
                }

                for (int i = 0; i < maxNum; i++) {
                    int cataIndex = firstCataId + i - 1;//板块索引
                    //板块索引大于等于count时说明已经没有板块了
                    if (count <= cataIndex) {
                        break;
                    }
                    Cata c = cataList.get(cataIndex);
                    String cata_name = c.getName();
                    int cata_id = c.getId();
                    long message_num = c.getMessage_num();
            %>
            <table>
                <tr>
                    <td width =500>
                        <a href="message.jsp?cata=<%=cata_name%>&id=<%=cata_id%>"><%=cata_name%></a>
                        <p>  &nbsp</p>
                    </td>
                    <td style="font-size: medium">
                        帖子数<%=message_num%>
                    </td>
                </tr>
            </table>
            <%
                }
            %>
            <div class="page">  
                <p>当前页:  <%=pageNo%> 总页数:  <%=lastPage%></p>
                <form action="./CataPageServlet">
                    <table>
                        <tr>
                            <td><a href="index.jsp?pageNo=<%=firstPage%>">【首页】</a></td>
                            <td><a href="index.jsp?pageNo=<%=pageNo - 1%>">【上一页】</a></td>
                            <td><a href="index.jsp?pageNo=<%=pageNo + 1%>">【下一页】</a></td>
                            <td><a href="index.jsp?pageNo=<%=lastPage%>">【尾页】</a></td>
                            <td>输入页号: <select name="selectPage" style="width:70px;height:24px;border-radius:0;border: 1px solid silver;">
                                    <option value="0">请选择</option>
                                    <%
                                        for (int i = 0; i < lastPage; i++) {
                                            out.println("<option value=\"" + (i + 1) + "\">" + (i + 1) + "</option>");
                                        }
                                    %>
                                </select>
                            </td>
                            <td>

                                <input type="submit" value="GO">
                            </td>

                        </tr>
                    </table>
                </form>
            </div>
        </div>
    </body>
</html>
