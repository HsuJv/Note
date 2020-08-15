/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Servlet;

import DAO.RevertDaoConn;
import Model.Revert;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author aasus
 */
public class SaveRevertServlet extends HttpServlet {

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

        long revert_account = Long.parseLong(request.getParameter("revert_account"));
        long revert_messageid = Long.parseLong(request.getParameter("revert_messageid"));
        String revert_content = request.getParameter("revert_content");

        RevertDaoConn rdc = new RevertDaoConn();
        Revert new_revert = new Revert();
        new_revert.setRevert_account(revert_account);
        new_revert.setRevert_messageid(revert_messageid);
        new_revert.setRevert_content(revert_content);

        if (rdc.addRevert(new_revert)) {
            System.out.println("add success");
        }

        String path = (String) request.getSession().getAttribute("path");
        response.sendRedirect(path);
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
