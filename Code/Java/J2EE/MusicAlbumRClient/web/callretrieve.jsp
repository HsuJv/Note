<%-- 
    Document   : callretrieve
    Created on : 2018-5-1, 14:46:52
    Author     : Hsu
--%>

<%@page import="java.io.InputStreamReader"%> 
<%@page import="java.io.BufferedReader"%> 
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
            java.lang.String parameter[] = {"", "Result:", "ID:", "Album Name:", "Artist:", "Year:", "Price:", "Description:", "", ""};     
            URL url = new URL("http://localhost:8084/MusicAlbumR/webresources/albums/" + request.getParameter("id"));    
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();        
            connection.setRequestMethod("GET");         
            connection.setRequestProperty("Accept", "application/xml");  
            if (connection.getResponseCode() != 200) {              
                out.println("Operation failed: " + connection.getResponseCode());   
            }          
            System.out.println("Content-Type: " + connection.getContentType());  
            BufferedReader reader = new BufferedReader(new InputStreamReader(connection.getInputStream()));     
            String line = reader.readLine();
            int i = 0;       
            out.println("<table>");  
            while (line != null) {     
                out.println("<tr><td>" + parameter[i] + "</td><td>" + line +"</td></tr>");         
                line = reader.readLine();        
                i++;        
            }         
            out.println("</table>");
            connection.disconnect();    
        %> 
    </centre>    
</body> 
</html>