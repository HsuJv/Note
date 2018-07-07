<%-- 
    Document   : LoginErrorPage
    Created on : 2018-5-13, 17:43:00
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
        <h3> An exception has occurred </h3>
        <br>
        <table>
            <tr>
                <td> Exception Class: </td>
                <%-- Obtain the name of exception class where 'exception' 
is the implicit object provided by JSP --%>
                <td><%=pageContext.getException()%></td>
            </tr>
        </table>
        To go back to the login page click Login Page button
        <form name="f2" action="Login.html">
            <input type="submit" name="button1" value="Login Page">
        </form>
    </body>
</html>
