<%-- 
    Document   : detail
    Created on : 2018-4-6, 16:25:11
    Author     : Hsu
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>JSP Page</title>
        <script>
            function CheckInputIntFloat(oInput) {
                if ('' !== oInput.value.replace(/\d{1,}\.{0,1}\d{0,}/, '')) {
                    oInput.value = oInput.value.match(/\d{1,}\.{0,1}\d{0,}/) === null ? '' : oInput.value.match(/\d{1,}\.{0,1}\d{0,}/);
                }
            }
        </script>
    </head>
    <body>
    <center>
        <form action="index.jsp">
            <table>
                <caption>New Record</caption>
                <tr>
                    <td>Name :</td>
                    <td><input type="text" name="NAME" style="width: 100%" required="required"/></td>
                </tr>
                <tr>
                    <td>Artist :</td>
                    <td><input type="text" name="ARTIST" style="width: 100%" required="required"/></td>
                </tr>
                <tr>
                    <td>Issue Year :</td>
                    <td><input type="text" name="A_YEAR" style="width: 100%" required="required"/></td>
                </tr>
                <tr>
                    <td>Price :</td>
                    <td><input type="text" name="PRICE" onclick="CheckInputIntFloat(this)" style="width: 100%" required="required"/></td>
                </tr>
                <tr>
                    <td>Description :</td>
                    <td><textarea type="text" name="DESCRIPTION" style="width: 100%"></textarea></td>
                </tr>
                <tr>
                    <td colspan="2" ><button type="submit" value = "Add" style="width: 100%; height: 100%">Add a new record</button></td>
                </tr>
            </table>
        </form>
    </center>
    </body>
</html>
