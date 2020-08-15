/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Servlet;

import DAO.MessageDaoConn;
import Model.Cata;
import Model.Message;
import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author aasus
 */
public class SaveMessageServlet extends HttpServlet {

    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        request.setCharacterEncoding("utf-8");
        response.setContentType("text/html;charset=utf-8");

        long message_account = Long.parseLong(request.getParameter("new_message_account"));
        int message_cataid = Integer.parseInt(request.getParameter("new_message_cata_id"));
        String message_cataname = request.getParameter("new_message_cata_ name");
        String message_title = request.getParameter("post_title");
        String message_content = request.getParameter("post_content");

        MessageDaoConn mdc = new MessageDaoConn();
        Message new_message = new Message();
        new_message.setMessage_account(message_account);
        new_message.setMessage_cata(message_cataid);
        new_message.setMessage_title(message_title);
        new_message.setMessage_content(message_content);

        if (mdc.addMessage(new_message)) {
            System.out.println("add success");
            response.sendRedirect("message.jsp?cata=" + message_cataname + "&id=" + message_cataid);
        }
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        doGet(request, response);
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>

}
