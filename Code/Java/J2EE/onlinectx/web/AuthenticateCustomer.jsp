<%-- 
    Document   : AuthenticateCustomer
    Created on : 2018-5-13, 17:30:52
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
        <%
            /* Retrieving the value of the uname text field */
            String user = request.getParameter("uname");
            /* Converting the string value into the Integer value */
            int customerID = Integer.parseInt(user);
            /* Retrieving the value of the pasword text filed */
            String pass = request.getParameter("password");
            /* Validate the customerID and password */
            if (customerID == 1010 && pass.equals("Jackson")){
                out.println("Welcome to Online Banking System");
        %>
        <br>
        <br>
        <%
                out.println("Login Successful");
            } else {
                out.println("Login Unsuccessful");
            }
        %>
    </body>
</html>
