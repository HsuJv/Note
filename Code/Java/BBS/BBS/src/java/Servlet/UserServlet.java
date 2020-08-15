/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Servlet;

import DAO.AccountDaoConn;
import Model.Account;
import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author Administrator
 */
@WebServlet(name = "UserServlet", urlPatterns = {"/UserServlet"})
public class UserServlet extends HttpServlet {

    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request,
            HttpServletResponse response) throws ServletException, IOException {
        request.setCharacterEncoding("utf-8");
        response.setContentType("text/html;charset=utf-8");
        String account_name = request.getParameter("account_name");
        String account_pass = request.getParameter("account_pass");
        Account at = (Account) request.getSession().getAttribute(
                "sessionAccount");
        AccountDaoConn adc = new AccountDaoConn();

        at.setAccount_name(account_name);
        at.setAccount_pass(account_pass);
        if (!adc.updateAccount(at)) {
            response.sendRedirect("user.jsp?validate=1");
        } else {
            request.getSession().setAttribute("sessionAccount", at);
            PrintWriter out = response.getWriter();
            out.print(
                    "<script>alert('修改成功!');window.location.href='Login.jsp'</script>");
        }
    }

    protected void doPost(HttpServletRequest request,
            HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}
