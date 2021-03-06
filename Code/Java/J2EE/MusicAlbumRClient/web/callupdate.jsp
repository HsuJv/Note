<%-- 
    Document   : callupdate
    Created on : 2018-5-1, 14:58:03
    Author     : Hsu
--%>

<%@page import="java.io.OutputStream"%> 
<%@page import="java.net.HttpURLConnection"%>
<%@page import="java.net.URL"%> 
<%@page contentType="text/html" pageEncoding="UTF-8"%> 
<!DOCTYPE html> 
<html>     
<head>         
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">         
    <title>JSP Page</title>     
</head>     
<body>    
    <centre>
        <ul>             
            <li><a href="addalbum.jsp">Add Album</a></li>             
            <li><a href="retrievealbum.jsp">Retrieve Album</a></li>             
            <li><a href="updatealbum.jsp">Update Album</a></li>             
            <li><a href="deletealbum.jsp">Delete Album</a></li>         
        </ul>       
        <h1>OperationStatus</h1>     
        <%
            String addCustomerXML = "<album>";
            addCustomerXML += "<id>" + request.getParameter("id") + "</id>";
            addCustomerXML += "<albumname>" + request.getParameter("name") + "</albumname> ";
            addCustomerXML += "<artistname>" + request.getParameter("artist") + "</artistname> ";
            addCustomerXML += "<issueyear>" + request.getParameter("year") + "</issueyear> ";
            addCustomerXML += "<price>" + request.getParameter("price") + "</price> ";
            addCustomerXML += "<description>" + request.getParameter("description") + "</description> ";
            addCustomerXML += "</album>";
            URL url = new URL("http://localhost:8084/MusicAlbumR/webresources/albums/" + request.getParameter("id"));
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.setDoOutput(true);
            connection.setInstanceFollowRedirects(false);
            connection.setRequestMethod("PUT");
            connection.setRequestProperty("Content-Type", "application/xml");
            OutputStream os = connection.getOutputStream();
            os.write(addCustomerXML.getBytes());
            os.flush();
            connection.connect();
            if (connection.getResponseCode() == 204) {      
                out.println("<h1>Album Updated</h1>");     
            } else {          
                out.println("<h1>Unable to Update the Album</h1>");      
            }
            connection.disconnect();
        %>   
    </centre>
</body> 
</html> 