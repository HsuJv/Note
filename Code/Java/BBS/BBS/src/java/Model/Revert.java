/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Model;

import java.sql.Timestamp;
import java.util.Date;

/**
 *
 * @author Hsu
 */

public class Revert {
    private long revert_account; //回复贴的发帖人数字账号设立对应account表的外键
    private long revert_messageid; //所回复的主题帖的id 设立对应message表的外键
    private long revert_id;         //回复贴的id主键
    private String revert_content; //回复贴的内容
    private Date revert_date;      //回复贴的发帖日期

    /**
     * @return the revert_account
     */
    public long getRevert_account() {
        return revert_account;
    }

    /**
     * @param revert_account the revert_account to set
     */
    public void setRevert_account(long revert_account) {
        this.revert_account = revert_account;
    }

    /**
     * @return the revert_messageid
     */
    public long getRevert_messageid() {
        return revert_messageid;
    }

    /**
     * @param revert_messageid the revert_messageid to set
     */
    public void setRevert_messageid(long revert_messageid) {
        this.revert_messageid = revert_messageid;
    }

    /**
     * @return the revert_id
     */
    public long getRevert_id() {
        return revert_id;
    }

    /**
     * @param revert_id the revert_id to set
     */
    public void setRevert_id(long revert_id) {
        this.revert_id = revert_id;
    }

    /**
     * @return the revert_content
     */
    public String getRevert_content() {
        return revert_content;
    }

    /**
     * @param revert_content the revert_content to set
     */
    public void setRevert_content(String revert_content) {
        this.revert_content = revert_content;
    }

    /**
     * @return the revert_date
     */
    public Date getRevert_date() {
        return revert_date;
    }

    /**
     * @param revert_date the revert_date to set
     */
    public void setRevert_date(Date revert_date) {
        this.revert_date = revert_date;
    }
    
   
}
