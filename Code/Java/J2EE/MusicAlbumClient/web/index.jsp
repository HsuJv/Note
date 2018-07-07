<%-- 
    Document   : index
    Created on : 2018-4-6, 14:20:55
    Author     : Hsu
--%>

<%@page import="client.Serialize"%>
<%@page import="java.util.List"%>
<%@page import="java.util.Map"%>
<%@page import="java.util.HashMap" %>
<%@page import="java.util.Set"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Index</title>
    </head>
    <body>
    <center>
        <%-- start web service invocation --%>
        <%
            try {
                String Label[] = {"", "NAME", "ARTIST", "A_YEAR", "PRICE", "DESCRIPTION"};
                pack.MusicAlbumEdit_Service service = new pack.MusicAlbumEdit_Service();
                pack.MusicAlbumEdit port = service.getMusicAlbumEditPort();
                // TODO process result here
                if (request.getParameter("id") != null) {
                    port.delete(Integer.parseInt(request.getParameter("id")));
                    response.sendRedirect("index.jsp");
                }
                
                if (request.getParameter("NAME") != null) {
                    HashMap<String, String> details = new HashMap<>();
                    details.put(Label[1], request.getParameter(Label[1]));
                    details.put(Label[2], request.getParameter(Label[2]));
                    details.put(Label[3], request.getParameter(Label[3]));
                    details.put(Label[4], request.getParameter(Label[4]));
                    details.put(Label[5], request.getParameter(Label[5]));
                    port.add(Serialize.SerializeObjectToString(details));
                    response.sendRedirect("index.jsp");
                }

                java.lang.String result = port.display();
                List<Map<String, String>> list = (List<Map<String, String>>) Serialize.UnserializeStringToObject(result);

                if (0 == list.size()) {
                    out.print("There is no records. <br/> Please add one first.");
                } else {
                    out.println("<table align=center border = 1 cellpadding=2><caption><b>Album Details</b></caption>");
                    out.println("<tr>");
                    for (int i = 1; i <= 5; i++) {
                        out.println("<th>" + Label[i] + "</th>");
                    }
                    out.println("<th>" + Label[0] + "</th>");
                    out.println("</tr>");
                    for (int i = 0; i < list.size(); i++) {
                        out.print("<tr>");
                        out.println("<td>" + list.get(i).get(Label[1]) + "</td>");
                        out.println("<td>" + list.get(i).get(Label[2]) + "</td>");
                        out.println("<td>" + list.get(i).get(Label[3]) + "</td>");
                        out.println("<td>" + list.get(i).get(Label[4]) + "</td>");
                        out.println("<td>" + list.get(i).get(Label[5]) + "</td>");
                        out.print("<td><form action=\"index.jsp\"/><input type=\"hidden\" name=\"id\" value=" + list.get(i).get("ID") + "><input type=\"submit\" value=\"Delete\"/></form></td>");
                        out.println("</tr>");
                    }
                    out.println("<tr><td colspan=\"6\"><form action=\"detail.jsp\"><button type=\"submit\" style=\"width: 100%\">Add a new record</button></form></td></tr>");
                    out.println("</table>");
                }
            } catch (Exception ex) {
                out.println(ex.toString());
            }
        %>
        <%-- end web service invocation --%>
    </center>
    </body>
</html>
