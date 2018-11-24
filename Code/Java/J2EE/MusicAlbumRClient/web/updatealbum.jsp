<%-- 
    Document   : updatealbum
    Created on : 2018-5-1, 14:54:05
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
        <h1>UpdateAlbum</h1>     
        <table>     
            <form name="addForm" action="callupdate.jsp" method="POST">    
                <tr>
                    <td>ID:</td>
                    <td><input type="text" name="id" value="" /></td>
                </tr>                 
                <tr>
                    <td>Name:</td>
                    <td><input type="text" name="name" value="" /></td>
                </tr>                 
                <tr>
                    <td>Artist:</td>
                    <td><input type="text" name="artist" value="" /></td>
                </tr>                 
                <tr>
                    <td>Issue Year:</td>
                    <td><input type="text" name="year" value="" /></td>
                </tr>                 
                <tr>
                    <td>Price:</td>
                    <td><input type="text" name="price" value="" /></td>
                </tr>                 
                <tr>
                    <td>Description:</td>
                    <td><input type="text" name="description" value="" /></td>
                </tr>                           
                <tr>
                    <td><input type="submit" value="Update" name="update" /></td>
                </tr>    
            </form>      
        </table>
    </centre>    
</body> 
</html> 
