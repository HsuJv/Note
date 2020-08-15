/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package DAO;

import Model.Account;
import Model.Message;
import Util.DBUtil;
import Util.SQLUtil;
import java.sql.Connection;
import java.sql.Date;
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
public class MessageDaoConn implements MessageDao {

    Connection conn;
    Statement stmt;//评测字符串执行SQL
    PreparedStatement pstmt;//?编译对象占位符 可防止sql注入
    ResultSet rs;

    /**
     * 新增主题帖
     *
     * @param message
     * @return
     */
    @Override
    public boolean addMessage(Message message) {
        boolean flag = false;
        int i = 0;
        // 1.定义sql
        String sql = "insert into message_table(message_cata,message_title,message_content,message_account) values(?,?,?,?)";
        // 2.获得连接
        conn = DBUtil.getConnection();
        try {
            // 3.编译sql
            pstmt = conn.prepareStatement(sql);
            // 4.执行sql
            pstmt.setInt(1, message.getMessage_cata());
            pstmt.setString(2, message.getMessage_title());
            pstmt.setString(3, message.getMessage_content());
            pstmt.setLong(4, message.getMessage_account());
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
     * 删除主题帖
     *
     * @param message
     * @return
     */
    @Override
    public boolean deleteMessage(Message message) {
        boolean flag = false;
        int i = 0;
        String sql = "delete from message_table where message_id=?";
        conn = DBUtil.getConnection();
        try {
            pstmt = conn.prepareStatement(sql);
            pstmt.setLong(1, message.getMessage_id());
            
            // 删除回复
            RevertDaoConn revertDaoConn = new RevertDaoConn();
            revertDaoConn.deleteRevertbyMessage_id(message.getMessage_id());
            
            // 删除帖子
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
     * 根据版块编号，删除所有主题帖
     *
     * @param cata_id
     * @return
     */
    @Override
    public boolean deleteMessageByCata_id(int cata_id) {
        boolean flag = false;
        int i = 0;
        String sql = "select * from message_table where message_cata=?";
        Message message = null;
        
        conn = DBUtil.getConnection();
        try {
            pstmt = conn.prepareStatement(sql);
            pstmt.setLong(1, cata_id);       
            rs = pstmt.executeQuery();
            while (rs.next()) {
                message = new Message();
                
                message.setMessage_id(rs.getLong("message_id"));
                flag = deleteMessage(message);
                if (!flag) break;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return flag;
    }

    /**
     * 显示所有主题帖信息，查询了日期，以及account表的发帖人名字
     *
     * @param cata_id
     * @return
     */
    @Override
    public List<Message> searchMessageByCata(int cata_id) {
        // TODO Auto-generated method stub
        List<Message> list = new ArrayList<>();
        Message message = null;
        Account account = null;
        AccountDaoConn accounDaoConn = null;
        RevertDaoConn revertDaoConn = null;
        String sql = null;

        sql = "select * from message_table where message_cata=?";
        // get connection
        conn = DBUtil.getConnection();
        try {
            // 编译sql
            pstmt = conn.prepareStatement(sql);
            // 执行sql
            pstmt.setInt(1, cata_id);
            rs = pstmt.executeQuery();

            accounDaoConn = new AccountDaoConn();
            revertDaoConn = new RevertDaoConn();

            while (rs.next()) {
                message = new Message();
                account = new Account();

                account.setAccount_account(rs.getLong("message_account"));
                account = accounDaoConn.returnAccountByAccount_account(account);

                message.setMessage_account(account.getAccount_account());
                message.setMessage_account_name(account.getAccount_name());
                message.setMessage_cata(cata_id);
                message.setMessage_content(rs.getString("message_content"));
                message.setMessage_date(rs.getTimestamp("message_date"));
                message.setMessage_id(rs.getLong("message_id"));
                message.setMessage_title(rs.getString("message_title"));
                message.setRevert_num(revertDaoConn.returnRevertNumByMessage_id(
                        rs.getLong("message_id")));

                list.add(message);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return list;
    }

    /**
     * 根据用户Id显示该用户所有的发布主题帖
     *
     * @param account_account
     * @return
     */
    @Override
    public List<Message> searchMessageIpost(long account_account) {
        List<Message> list = new ArrayList<>();
        Message message = null;
        Account account = null;
        AccountDaoConn accounDaoConn = null;
        RevertDaoConn revertDaoConn = null;
        String sql = null;

        sql = "select * from message_table where message_account=?";
        // get connection
        conn = DBUtil.getConnection();
        try {
            // 编译sql
            pstmt = conn.prepareStatement(sql);
            // 执行sql
            pstmt.setLong(1, account_account);
            rs = pstmt.executeQuery();

            accounDaoConn = new AccountDaoConn();
            revertDaoConn = new RevertDaoConn();

            while (rs.next()) {
                message = new Message();
                account = new Account();

                account.setAccount_account(account_account);
                account = accounDaoConn.returnAccountByAccount_account(account);

                message.setMessage_account(account_account);
                message.setMessage_account_name(account.getAccount_name());
                message.setMessage_cata(rs.getInt("message_cata"));
                message.setMessage_content(rs.getString("message_content"));
                message.setMessage_date(rs.getTimestamp("message_date"));
                message.setMessage_id(rs.getLong("message_id"));
                message.setMessage_title(rs.getString("message_title"));
                message.setRevert_num(revertDaoConn.returnRevertNumByMessage_id(
                        rs.getLong("message_id")));

                list.add(message);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return list;
    }

    /**
     * 显示所有主题帖信息给用户，包括发帖人名字，回帖数
     *
     * @param message
     * @return
     */
    @Override
    public Message returnMessageByMessage_id(Message message) {
        Account account = null;
        AccountDaoConn accounDaoConn = null;
        RevertDaoConn revertDaoConn = null;
        String sql = null;

        sql = "select * from message_table where message_id=?";
        // get connection
        conn = DBUtil.getConnection();
        try {
            // 编译sql
            pstmt = conn.prepareStatement(sql);
            // 执行sql
            pstmt.setLong(1, message.getMessage_id());
            rs = pstmt.executeQuery();

            accounDaoConn = new AccountDaoConn();
            revertDaoConn = new RevertDaoConn();

            if (rs.next()) {
                message = new Message();
                account = new Account();

                account.setAccount_account(rs.getLong("message_account"));
                account = accounDaoConn.returnAccountByAccount_account(account);

                message.setMessage_account(rs.getLong("message_account"));
                message.setMessage_account_name(account.getAccount_name());
                message.setMessage_cata(rs.getInt("message_cata"));
                message.setMessage_content(rs.getString("message_content"));
                message.setMessage_date(rs.getTimestamp("message_date"));
                message.setMessage_id(rs.getLong("message_id"));
                message.setMessage_title(rs.getString("message_title"));
                message.setRevert_num(revertDaoConn.returnRevertNumByMessage_id(
                        rs.getLong("message_id")));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return message;
    }

    /**
     * 根据关键词查询帖子
     *
     * @param message
     * @return
     */
    @Override
    public List<Message> searchMessageByKeyword(String[] keys) {
        List<Message> list = new ArrayList<>();
        Message message = null;
        Account account = null;
        AccountDaoConn accounDaoConn = null;
        RevertDaoConn revertDaoConn = null;
        String sql = null;

        sql = "select * from message_table where message_title like ?";
        // get connection
        conn = DBUtil.getConnection();
        try {
            // 修改sql
            for (int i = 1; i < keys.length; i++) {
                sql += " and message_title like ?";
            }

            // 编译sql
            pstmt = conn.prepareStatement(sql);

            // 执行sql
            for (int i = 1; i <= keys.length; i++) {
                pstmt.setString(i, SQLUtil.percentAdded(keys[i-1]));
            }
            rs = pstmt.executeQuery();

            accounDaoConn = new AccountDaoConn();
            revertDaoConn = new RevertDaoConn();

            while (rs.next()) {
                message = new Message();
                account = new Account();

                account.setAccount_account(rs.getLong("message_account"));
                account = accounDaoConn.returnAccountByAccount_account(account);

                message.setMessage_account(rs.getLong("message_account"));
                message.setMessage_account_name(account.getAccount_name());
                message.setMessage_cata(rs.getInt("message_cata"));
                message.setMessage_content(rs.getString("message_content"));
                message.setMessage_date(rs.getTimestamp("message_date"));
                message.setMessage_id(rs.getLong("message_id"));
                message.setMessage_title(rs.getString("message_title"));
                message.setRevert_num(revertDaoConn.returnRevertNumByMessage_id(
                        rs.getLong("message_id")));

                list.add(message);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return list;

    }

    /**
     *
     * @param cata_id
     * @return
     */
    @Override
    public long returnMessageNumByCata_id(long cata_id) {
        long num = 0;
        // 1.定义sql
        String sql = "select count(message_id) total_count from message_table where message_cata=?";
        // 2.获得连接
        conn = DBUtil.getConnection();
        try {
            // 3.编译sql
            pstmt = conn.prepareStatement(sql);
            pstmt.setLong(1, cata_id);
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
