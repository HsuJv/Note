/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Servlet;

import java.io.IOException;
import java.io.PrintWriter;
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
@WebServlet(name = "RegisterServlet", urlPatterns = {"/RegisterServlet"})
public class RegisterServlet extends HttpServlet {

    private static final long serialVersionUID = 1L;

    public RegisterServlet() {
        super();
    }


    protected void doGet(HttpServletRequest request,
            HttpServletResponse response) throws ServletException, IOException {
        request.setCharacterEncoding("utf-8");
        response.setContentType("text/html;charset=utf-8");
        String account_name = request.getParameter("account_name");
        String account_pass = request.getParameter("account_pass");
        Account account = new Account();
        AccountDaoConn accountDaoConn = new AccountDaoConn();
        account.setAccount_name(account_name);
        account.setAccount_pass(account_pass);
        
        if (!accountDaoConn.addAccount(account)) {
            response.sendRedirect("Register.jsp?validate=1");
        } else {
            PrintWriter out = response.getWriter();
            out.print(
                    "<script>alert('注册成功!');window.location.href='Login.jsp'</script>");
        }
    }

    protected void doPost(HttpServletRequest request,
            HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}
