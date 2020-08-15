/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package DAO;

import Model.Words;
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
public class WordsDaoConn implements WordsDao {

    Connection conn;
    Statement stmt;//评测字符串执行SQL
    PreparedStatement pstmt;//?编译对象占位符 可防止sql注入
    ResultSet rs;

    /**
     * 新增留言
     *
     * @param words
     * @return
     */
    @Override
    public boolean addWords(Words words) {
        boolean flag = false;
        int i = 0;
        // 1.定义sql
        String sql = "insert into words_table(words_object,words_subject,words_content) values(?,?,?)";
        // 2.获得连接
        conn = DBUtil.getConnection();
        try {
            // 3.编译sql
            pstmt = conn.prepareStatement(sql);
            // 4.执行sql
            pstmt.setLong(1, words.getWords_object());
            pstmt.setLong(2, words.getWords_subject());
            pstmt.setString(3, words.getWords_content());
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
     * 更改留言已读状态
     *
     * @param words
     * @return
     */
    @Override
    public boolean readWords(Words words) {
        boolean flag = false;
        int i = 0;
        String sql = "update words_table set words_new=0 where words_id=?";;
        conn = DBUtil.getConnection();
        try {
            pstmt = conn.prepareStatement(sql);
            pstmt.setLong(1, words.getWords_id());
            i = pstmt.executeUpdate();
            if (i > 0) {
                flag = true;
                words.setWords_new((short) 0);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return flag;
    }

    /**
     * 根据留言id删除留言
     *
     * @param words
     * @return
     */
    @Override
    public boolean deleteWords(Words words) {
        boolean flag = false;
        int i = 0;
        String sql = "delete from words_table where words_id=?";
        conn = DBUtil.getConnection();
        try {
            pstmt = conn.prepareStatement(sql);
            pstmt.setLong(1, words.getWords_id());
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
     * 根据用户数字账号，删除该用户留言
     *
     * @param account_account
     * @return
     */
    @Override
    public boolean deleteWordsByAccount_account(long account_account) {
        boolean flag = false;
        int i = 0;
        String sql = "delete from words_table where words_subject=?";
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
     * 根据用户id查询所有未读留言个数
     *
     * @param account_account
     * @return
     */
    @Override
    public long returnNewWordsNumByObjectId(long account_account) {
        long num = 0;
        // 1.定义sql
        String sql = "select count(words_id) total_count from words_table where words_object=?";
        // 2.获得连接
        conn = DBUtil.getConnection();
        try {
            // 3.编译sql
            pstmt = conn.prepareStatement(sql);
            pstmt.setLong(1, account_account);
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

    /**
     * 根据用户id查询该用户收到的所有留言
     *
     * @param account_account
     * @return
     */
    @Override
    public List<Words> searchWordsByObjectId(long account_account) {
        List<Words> list = new ArrayList<>();
        Words words = null;
        ResultSet rs = null;

        String sql = "select * from words_table where words_object=?";
        conn = DBUtil.getConnection();
        try {
            // 预编译
            pstmt = conn.prepareStatement(sql);

            // 执行
            pstmt.setLong(1, account_account);
            rs = pstmt.executeQuery();

            while (rs.next()) {
                words = new Words();

                words.setWords_object(account_account);
                words.setWords_subject(rs.getLong("words_subject"));
                words.setWords_content(rs.getString("words_content"));
                words.setWords_id(rs.getLong("words_id"));
                words.setWords_date(rs.getTimestamp("words_date"));
                words.setWords_new(rs.getShort("words_new"));
                list.add(words);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return list;
    }
}
