/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package DAO;

import Model.Cata;
import Util.DBUtil;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author Hsu
 */
public class CataDaoConn implements CataDao{

    Connection conn;
    Statement stmt;//评测字符串执行SQL
    PreparedStatement pstmt;//?编译对象占位符 可防止sql注入
    ResultSet rs;
    
    /**
     * 新增版块
     *
     * @param cata
     * @return
     */
    @Override
    public boolean addCata(Cata cata) {
        boolean flag = false;
        int i = 0;
        // 1.定义sql
        String sql = "insert into cata_table(cata_name) values(?)";
        // 2.获得连接
        conn = DBUtil.getConnection();
        try {
            // 3.编译sql
            pstmt = conn.prepareStatement(sql);
            // 4.执行sql
            pstmt.setString(1, cata.getName());
            //5.返回数据操作结行数1
            i = pstmt.executeUpdate();//对结果进行判断，返回操作成功的行数，该例成功为1，失败为0
            if (i > 0) {
                flag = true;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return flag;
    }

    /**
     * 删除版块
     *
     * @param cata
     * @return
     */
    @Override
    public boolean deleteCata(Cata cata) {
        boolean flag = false;
        MessageDaoConn messageDaoConn = null;
        
        int i = 0;
        String sql = "delete from cata_table where cata_id=?";
        conn = DBUtil.getConnection();
        try {
            // 删除版块下所有帖子
            messageDaoConn = new MessageDaoConn();
            messageDaoConn.deleteMessageByCata_id(cata.getId());
            
            // 预编译
            pstmt = conn.prepareStatement(sql);
            
            // 
            pstmt.setLong(1, cata.getId());
            i = pstmt.executeUpdate();
            if (i > 0) {
                flag = true;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return flag;
    }

    /**
     * 返回所有版块信息
     *
     * @return
     */
    @Override
    public List<Cata> searchAllCata() {
        List<Cata> list = new ArrayList<>();
        Cata cata = null;
        MessageDaoConn messageDaoConn;

        // 1.定义sql
        String sql = "select * from cata_table";
        // 2.获得连接
        conn = DBUtil.getConnection();
        try {
            // 3.编译sql
            pstmt = conn.prepareStatement(sql);
            // 4.执行sql
            rs = pstmt.executeQuery();

            messageDaoConn = new MessageDaoConn();
                    
            while (rs.next()) {
                cata = new Cata();
                cata.setId(rs.getInt("cata_id"));
                cata.setMessage_num(messageDaoConn.returnMessageNumByCata_id(
                        rs.getInt("cata_id")));
                cata.setName(rs.getString("cata_name"));
                
                list.add(cata);
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return list;
    }

    @Override
    public Cata returnCataById(long id) {
        Cata cata = null;
        MessageDaoConn messageDaoConn;

        // 1.定义sql
        String sql = "select * from cata_table where cata_id=?";
        // 2.获得连接
        conn = DBUtil.getConnection();
        try {
            // 3.编译sql
            pstmt = conn.prepareStatement(sql);
            pstmt.setLong(1, id);
            // 4.执行sql
            rs = pstmt.executeQuery();

            messageDaoConn = new MessageDaoConn();
                    
            if (rs.next()) {
                cata = new Cata();
                cata.setId(rs.getInt("cata_id"));
                cata.setMessage_num(messageDaoConn.returnMessageNumByCata_id(
                        rs.getInt("cata_id")));
                cata.setName(rs.getString("cata_name"));
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return cata;
    }
    
}
