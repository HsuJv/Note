/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Model;

import java.util.Date;

/**
 *
 * @author Hsu
 */

public class Message {
    private long message_account;//主题帖发帖人数字账号,设立对应account表的外键
    private long message_id;  //主题帖的id 主键
    private int message_cata; // 主题帖版块号   
    private String message_title;   //主题帖名称
    private String message_content; //主题的内容
    private Date message_date;      //主题帖的发帖日期
    private String message_account_name;   //主题帖的发帖人账号名字
    private long revert_num;                   //主题帖的回帖数

    /**
     * @return the message_account
     */
    public long getMessage_account() {
        return message_account;
    }

    /**
     * @param message_account the message_account to set
     */
    public void setMessage_account(long message_account) {
        this.message_account = message_account;
    }

    /**
     * @return the message_id
     */
    public long getMessage_id() {
        return message_id;
    }

    /**
     * @param message_id the message_id to set
     */
    public void setMessage_id(long message_id) {
        this.message_id = message_id;
    }

    /**
     * @return the message_title
     */
    public String getMessage_title() {
        return message_title;
    }

    /**
     * @param message_title the message_title to set
     */
    public void setMessage_title(String message_title) {
        this.message_title = message_title;
    }

    /**
     * @return the message_content
     */
    public String getMessage_content() {
        return message_content;
    }

    /**
     * @param message_content the message_content to set
     */
    public void setMessage_content(String message_content) {
        this.message_content = message_content;
    }

    /**
     * @return the message_date
     */
    public Date getMessage_date() {
        return message_date;
    }

    /**
     * @param message_date the message_date to set
     */
    public void setMessage_date(Date message_date) {
        this.message_date = message_date;
    }

    /**
     * @return the message_account_name
     */
    public String getMessage_account_name() {
        return message_account_name;
    }

    /**
     * @param message_account_name the message_account_name to set
     */
    public void setMessage_account_name(String message_account_name) {
        this.message_account_name = message_account_name;
    }

    /**
     * @return the revert_num
     */
    public long getRevert_num() {
        return revert_num;
    }

    /**
     * @param revert_num the revert_num to set
     */
    public void setRevert_num(long revert_num) {
        this.revert_num = revert_num;
    }

    /**
     * @return the message_cata
     */
    public int getMessage_cata() {
        return message_cata;
    }

    /**
     * @param message_cata the message_cata to set
     */
    public void setMessage_cata(int message_cata) {
        this.message_cata = message_cata;
    }
    
    
}
