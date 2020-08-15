/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package DAO;

import Model.Revert;
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
public class RevertDaoConn implements RevertDao {

    Connection conn;
    Statement stmt;//评测字符串执行SQL
    PreparedStatement pstmt;//?编译对象占位符 可防止sql注入
    ResultSet rs;

    /**
     * 新增回帖
     *
     * @param revert
     * @return
     */
    @Override
    public boolean addRevert(Revert revert) {
        boolean flag = false;
        int i = 0;
        // 1.定义sql
        String sql = "insert into revert_table(revert_account,revert_messageid,revert_content) values(?,?,?)";
        // 2.获得连接
        conn = DBUtil.getConnection();
        try {
            // 3.编译sql
            pstmt = conn.prepareStatement(sql);
            // 4.执行sql
            pstmt.setLong(1, revert.getRevert_account());
            pstmt.setLong(2, revert.getRevert_messageid());
            pstmt.setString(3, revert.getRevert_content());
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
     * 根据帖子id删除回帖
     *
     * @param revert
     * @return
     */
    @Override
    public boolean deleteRevert(Revert revert) {
        boolean flag = false;
        int i = 0;
        String sql = "delete from revert_table where revert_id=?";
        conn = DBUtil.getConnection();
        try {
            pstmt = conn.prepareStatement(sql);
            pstmt.setLong(1, revert.getRevert_id());
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
     * 根据用户数字账号，删除该用户回帖
     *
     * @param account_account
     * @return
     */
    @Override
    public boolean deleteRevertByAccount_account(long account_account) {
        boolean flag = false;
        int i = 0;
        String sql = "delete from revert_table where revert_account=?";
        conn = DBUtil.getConnection();
        try {
            pstmt = conn.prepareStatement(sql);
            pstmt.setLong(1, account_account);
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
     * 根据主题帖id删除所有回帖
     *
     * @param message_id
     * @return
     */
    @Override
    public boolean deleteRevertbyMessage_id(long message_id) {
        boolean flag = false;
        int i = 0;
        String sql = "delete from revert_table where revert_messageid=?";
        conn = DBUtil.getConnection();
        try {
            pstmt = conn.prepareStatement(sql);
            pstmt.setLong(1, message_id);
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
     * 根据帖子id显示所有回帖
     *
     * @param message_id
     * @return
     */
    @Override
    public List<Revert> searchRevertByMessage_id(long message_id) {
        List<Revert> list = new ArrayList<>();
        Revert revert = null;
        ResultSet rs = null;

        String sql = "select * from revert_table where revert_messageid=?";
        conn = DBUtil.getConnection();
        try {
            // 预编译
            pstmt = conn.prepareStatement(sql);

            // 执行
            pstmt.setLong(1, message_id);
            rs = pstmt.executeQuery();

            while (rs.next()) {
                revert = new Revert();
                    
                revert.setRevert_account(rs.getLong("revert_account"));
                revert.setRevert_content(rs.getString("revert_content"));
                revert.setRevert_date(rs.getTimestamp("revert_date"));
                revert.setRevert_id(rs.getLong("revert_id"));
                revert.setRevert_messageid(message_id);

                list.add(revert);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return list;
    }

    /**
     * 显示最新回帖
     *
     * @param message_id
     * @return
     */
    @Override
    public Revert searchNewRevertByMessage_id(long message_id) {
        Revert revert = null;
        ResultSet rs = null;

        String sql = "select * from revert_table where revert_messageid=?";
        conn = DBUtil.getConnection();
        try {
            // 预编译
            pstmt = conn.prepareStatement(sql);

            // 执行
            pstmt.setLong(1, message_id);
            rs = pstmt.executeQuery(sql);

            if (rs.last()) {
                revert = new Revert();
                
                revert.setRevert_account(rs.getLong("revert_accout"));
                revert.setRevert_content(rs.getString("revert_content"));
                revert.setRevert_date(rs.getTimestamp("revert_date"));
                revert.setRevert_id(rs.getLong("revert_id"));
                revert.setRevert_messageid(message_id);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return revert;
    }

    /**
     * 根据用户id查询该用户的所有回复
     *
     * @param account_account
     * @return
     */
    @Override
    public List<Revert> searchRevertById(long account_account) {
        List<Revert> list = new ArrayList<>();
        Revert revert = null;
        ResultSet rs = null;

        String sql = "select * from revert_table where revert_account=?";
        conn = DBUtil.getConnection();
        try {
            // 预编译
            pstmt = conn.prepareStatement(sql);

            // 执行
            pstmt.setLong(1, account_account);
            rs = pstmt.executeQuery();

            while (rs.next()) {
                revert = new Revert();
                
                revert.setRevert_account(account_account);
                revert.setRevert_content(rs.getString("revert_content"));
                revert.setRevert_date(rs.getTimestamp("revert_date"));
                revert.setRevert_id(rs.getLong("revert_id"));
                revert.setRevert_messageid(rs.getLong("revert_messageid"));

                list.add(revert);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return list;
    }

    /**
     * 根据message_id获得其回帖总数
     *
     * @param message_id
     * @return
     */
    @Override
    public long returnRevertNumByMessage_id(long message_id) {
        long num = 0;
        // 1.定义sql
        String sql = "select count(revert_id) total_count from revert_table where revert_messageid=?";
        // 2.获得连接
        conn = DBUtil.getConnection();
        try {
            // 3.编译sql
            pstmt = conn.prepareStatement(sql);
            pstmt.setLong(1, message_id);
            //4.执行sql
            rs = pstmt.executeQuery();
            if (rs.next()) {
                num = rs.getLong("total_count");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return num;
    }

}
