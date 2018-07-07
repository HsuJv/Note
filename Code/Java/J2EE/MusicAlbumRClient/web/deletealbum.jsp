<%-- 
    Document   : deletealbum
    Created on : 2018-5-1, 15:02:59
    Author     : Hsu
--%>

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
        <h1>DeleteAlbum</h1>        
        <form name="addForm" action="calldelete.jsp" method="POST">   
            ID:<input type="text" name="id" value="" />    
            <input type="submit" value="Delete" name="delete" />      
        </form> 
    </centre>    
</body> 
</html>