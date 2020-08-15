/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package DAO;

import Model.Account;
import Util.DBUtil;
import Util.PrivilegeUtil;
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
public class AccountDaoConn implements AccountDao {

    Connection conn;
    Statement stmt;//评测字符串执行SQL
    PreparedStatement pstmt;//?编译对象占位符 可防止sql注入
    ResultSet rs;

    /**
     * 此方法是用户注册的相关方法
     *
     * @param account
     * @return
     */
    @Override
    public boolean addAccount(Account account) {
        boolean flag = false;
        int i = 0;
        // 1.定义sql
        String sql = "insert into account_table(account_name,account_pass) values(?,?)";
        // 2.获得连接
        conn = DBUtil.getConnection();
        try {
            // 3.编译sql
            pstmt = conn.prepareStatement(sql);
            // 4.执行sql
            pstmt.setString(1, account.getAccount_name());//1,2分别对应SQL中的问号顺序
            pstmt.setString(2, account.getAccount_pass());
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
     * 这是删除用户的方法 根据用户数字账号进行删除，即acount_acount（用户数字账号识别列）的值
     *
     * @param account
     * @return
     */
    @Override
    public boolean deleteAccount(Account account) {
        boolean flag = false;
        int i = 0;
        String sql = "delete from account_table where account_account=?";
        conn = DBUtil.getConnection();
        try {
            pstmt = conn.prepareStatement(sql);
            pstmt.setLong(1, account.getAccount_account());
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
     * 保存用户修改的方法
     *
     * @param account
     * @return
     */
    @Override
    public boolean updateAccount(Account account) {
        // TODO Auto-generated method stub
        boolean flag = false;
        int i = 0;
        String sql = "update account_table set account_name=?,account_pass=? where account_account=?";
        conn = DBUtil.getConnection();
        try {
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, account.getAccount_name());
            pstmt.setString(2, account.getAccount_pass());
            pstmt.setLong(3, account.getAccount_account());
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
     * 查询所有用户的方法，只查询普通用户，不查询管理员
     *
     * @return
     */
    @Override
    public List<Account> searchAccountAll() {
        // TODO Auto-generated method stub
        List<Account> list = new ArrayList<>();
        Account account = null;
        String sql = null;

        sql = "select * from account_table where account_limit=1"; //只查询普通用户
        // get connection
        conn = DBUtil.getConnection();
        try {
            // 编译sql
            pstmt = conn.prepareStatement(sql);
            // 执行sql
            rs = pstmt.executeQuery();
            while (rs.next()) {
                account = new Account();
                account.setAccount_account(rs.getInt("account_account"));
                account.setAccount_name(rs.getString("account_name"));
                account.setAccount_pass(rs.getString("account_pass"));
                account.setAccount_limit(rs.getInt("account_limit"));
                account.setAccount_date(rs.getDate("account_date"));
                list.add(account);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return list;
    }

    /**
     * 根据用户的账号查找其他的信息，即申明一个对象，仅赋予该对象数字账号，调用该方法会把名称，密码再赋值到该对象中，更加安全
     *
     * @param account
     * @return
     */
    @Override
    public Account returnAccountByAccount_account(Account account) {
        String sql = "select * from account_table where account_account=?";
        conn = DBUtil.getConnection();
        try {
            pstmt = conn.prepareStatement(sql);
            pstmt.setLong(1, account.getAccount_account());
            rs = pstmt.executeQuery();
            if (rs.next()) {
                account = new Account();
                account.setAccount_account(rs.getInt("account_account"));
                account.setAccount_name(rs.getString("account_name"));
                account.setAccount_pass(rs.getString("account_pass"));
                account.setAccount_limit(rs.getInt("account_limit"));
                account.setAccount_date(rs.getDate("account_date"));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return account;
    }

    /**
     * 用户登录
     *
     * @param account
     * @return
     */
    @Override
    public Account loginAccount(Account account) {
        // TODO Auto-generated method stub
        Account newaccount = null;
        String sql = "select * from account_table where account_name=? and account_pass=?";
        conn = DBUtil.getConnection();
        try {
            // 编译sql
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, account.getAccount_name());
            pstmt.setString(2, account.getAccount_pass());
            // 执行sql
            rs = pstmt.executeQuery();
            if (rs.next()) {
                newaccount = new Account();
                newaccount.setAccount_account(rs.getInt("account_account"));
                newaccount.setAccount_name(rs.getString("account_name"));
                newaccount.setAccount_pass(rs.getString("account_pass"));
                newaccount.setAccount_date(rs.getDate("account_date"));
                newaccount.setAccount_limit(rs.getInt("account_limit"));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return newaccount;
    }

    /**
     * 查询所有管理员
     *
     * @param id
     * @return
     */
    @Override
    public List<Account> searchAdminAll(int limit) {
        // TODO Auto-generated method stub
        List<Account> list = new ArrayList<>();
        Account account = null;
        String sql = null;

        sql = "select * from account_table where account_limit != 1 and MOD(account_limit, ?)=0"; //只查询管理员用户
        // get connection
        conn = DBUtil.getConnection();
        try {
            // 编译sql
            pstmt = conn.prepareStatement(sql);
            pstmt.setLong(1, PrivilegeUtil.getPrimes(limit));
            // 执行sql
            rs = pstmt.executeQuery();
            while (rs.next()) {
                account = new Account();
                account.setAccount_account(rs.getInt("account_account"));
                account.setAccount_name(rs.getString("account_name"));
                account.setAccount_pass(rs.getString("account_pass"));
                account.setAccount_limit(rs.getInt("account_limit"));
                account.setAccount_date(rs.getDate("account_date"));
                list.add(account);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return list;
    }

    /**
     * 设置管理员
     *
     * @param account
     * @param id
     * @return
     */
    @Override
    public boolean setAccountAdmin(Account account, int limit) {
        if (PrivilegeUtil.checkAdmin(account.getAccount_limit())) {
            return false;
        }
        boolean flag = false;
        int i = 0;
        String sql = "update account_table set account_limit=?  where account_account=?";
        conn = DBUtil.getConnection();
        try {
            pstmt = conn.prepareStatement(sql);
            int newLimit = account.updateAccount_limit(PrivilegeUtil.getPrimes(limit));
            pstmt.setInt(1, newLimit);
            pstmt.setLong(2, account.getAccount_account());
            i = pstmt.executeUpdate();
            if (i > 0) {
                flag = true;
            } else {
                account.updateAccount_limit(PrivilegeUtil.getPrimes(limit));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return flag;
    }

    /**
     *
     * @param accout
     * @return
     */
    @Override
    public Account returnAccountByAccount_name(Account account) {
        String sql = "select * from account_table where account_name=?";
        conn = DBUtil.getConnection();
        try {
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, account.getAccount_name());
            rs = pstmt.executeQuery();
            if (rs.next()) {
                account = new Account();
                account.setAccount_account(rs.getInt("account_account"));
                account.setAccount_name(rs.getString("account_name"));
                account.setAccount_pass(rs.getString("account_pass"));
                account.setAccount_limit(rs.getInt("account_limit"));
                account.setAccount_date(rs.getDate("account_date"));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return account;
    }
}
