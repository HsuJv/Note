<%-- 
    Document   : index
    Created on : 2018-5-6, 22:33:43
    Author     : Hsu
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
    "http://www.w3.org/TR/html4/loose.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
    <head>
        <meta http-equiv="Content-Type"
              content="text/html; charset=iso-8859-1">
        <title>Online Book Store</title>
        <link href="css/style.css" rel="stylesheet" type="text/css">
    </head>
    <body>
        <div id="main-wraper">
            <div id="top-wraper">
                <div id="banner">Online Book Store</div>
                <div id="nav">
                    <ul>
                        <li><a href="#">Home</a></li>
                        <li><a href="#">About us</a></li>
                        <li><a href="#">Recent articles</a></li>
                        <li><a href="#">Email</a></li>
                        <li><a href="#">Resources</a></li>
                        <li
                            style="padding: 0px 2px 0px 3px; background: transparent none repeat scroll 0% 50%; -moz-background-clip: initial; -moz-background-origin: initial; -moz-background-inline-policy: initial;"><a
                                href="#">Links</a></li>
                    </ul>
                </div>
            </div>
            <div id="mid-wraper">
                <div id="mid-wraper-inner">
                    <div id="left-wraper">
                        <div id="left-wraper-top">
                            <div
                                style="margin: 0px; padding: 20px; width: 256px; float: left; display: block;">
                                <h1>Operations</h1>
                            </div>
                            <ul>
                                <li><a href="addbook.jsp">Add Book</a></li>
                                <li><a href="retrievebook.jsp">Retrieve Book</a></li>
                                <li><a href="updatebook.jsp">Update Book</a></li>
                                <li><a href="deletebook.jsp">Delete Book</a></li>
                            </ul>
                        </div>
                        <div id="news">
                            <h3>News</h3>
                            <img src="images/news.jpg" alt="">
                            <div style="width: 270px; float: left; padding-top: 10px;"> <strong>10.042010</strong>
                                Online Book Store is a global book store, which offer you a wide range of books.
                                This CMS for Online book store allows you to add new books, search for books stored in the databases on the basis of ID.
                                You can also update book information along with deleting books from the database.<br>

                                <a href="#" class="link" style="float: right;">read more</a> </div>
                        </div>
                    </div>
                    <div id="right-wraper">
                        <div class="right-part">
                            <!-- <h1>Operation<span class="blue-text">Status</span></h1>-->
                            <img src="images/welcome-brd.jpg" alt="">
                            <div style="padding: 10px 0px; width: 596px; float: left;">
                                <h1>Welcome to HEB Inventory Managment System</h1>
                                <br> <br>
                                <form method="post" action="/DOMParsingClient/index.jsp">
                                    Enter Book Name: <input type=text name="txt"><br>
                                    <br><br> <input type=submit value="Submit Book">
                                </form>
                                <%
                                    java.lang.String parameter[] = {"Book Name:", "Quantity:", "Excepected Delivery:", "Total Cost:", ""};
                                    try {
                                        pack.ParsingServiceService service = new pack.ParsingServiceService();
                                        pack.ParsingService port = service.getParsingServicePort();
                                        // TODO initialize WS operation arguments here
                                        java.lang.String query = request.getParameter("txt");
                                        // TODO process result here
                                        java.lang.String result = port.parseFile(query);
                                        //out.println("Result = " + result);
                                        if (!request.getParameter("txt").equals("")) {
                                            out.println("<br>");
                                            out.println("<br>");
                                            out.println("Result<br>");
                                            result = result.substring(0, result.length());
                                            final String[] details = result.split(",");
                                            out.println("<table border=1>");
                                            for (int i = 0; i < details.length; i++) {
                                                out.println("<tr><td>" + parameter[i] + "</td><td>" + details[i] + "</td></tr>");
                                                //out.println("<br>");
                                            }
                                            out.println("</table>");
                                        }
                                    } catch (Exception ex) {
                                        // TODO handle custom exceptions here
                                    }
                                %>
                            </div></div>
                        <div id="foter">
                            <div id="foter-inner">
                                <p
                                    style="margin: 0px; padding: 0px; width: 550px; float: left; display: block;"><a
                                        href="#" class="footer-link">Home</a> <a href="#" class="footer-link">About
                                        us</a> <a href="#" class="footer-link">Recent articles</a> <a href="#"
                                                                                                  class="footer-link">Email</a> <a href="#" class="footer-link">Resources</a>
                                    <a href="#" class="footer-link">Links</a></p>
                                <p
                                    style="margin: 0px; padding: 0px; width: 200px; float: right; text-align: right; display: block;">&copy;
                                    Designed by <a class="footer-link" target="_blank"
                                                   href="http://www.htmltemplates.net/">HTML
                                        Templates</a></p>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </body>
</html>