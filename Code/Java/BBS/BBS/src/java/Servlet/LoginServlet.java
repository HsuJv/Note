/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Servlet;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import DAO.AccountDaoConn;
import Model.Account;

/**
 *
 * @author Administrator
 */
@WebServlet(name = "LoginServlet", urlPatterns = {"/LoginServlet"})
public class LoginServlet extends HttpServlet {

    public LoginServlet() {
        super();
    }

    protected void doGet(HttpServletRequest request,
            HttpServletResponse response) throws ServletException, IOException {
        request.setCharacterEncoding("utf-8");
        response.setContentType("text/html;charset=utf-8");
        String account_name = request.getParameter("account_name");
        String account_pass = request.getParameter("account_pass");
        AccountDaoConn adc = new AccountDaoConn();
        Account account = new Account();
        account.setAccount_name(account_name);
        account.setAccount_pass(account_pass);
        Account at = adc.loginAccount(account);

        String path = (String) request.getSession().getAttribute("path");
        if (at != null) {
            request.getSession().setAttribute("sessionAccount", at);
            if (-1 == at.getAccount_limit()) {
                response.sendRedirect("Admin.jsp");
            } else {
                response.sendRedirect(path);
            }
        } else {
            response.sendRedirect("Login.jsp?flag=1");
        }
    }

    protected void doPost(HttpServletRequest request,
            HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}
