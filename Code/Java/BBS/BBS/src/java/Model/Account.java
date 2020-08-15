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
public class Account {

    private long account_account;  //用户数字账号 主键
    private String account_name;  //用户账号个性名字
    private String account_pass;  //用户账号密码
    private int account_limit;    //用户账号权限识别码
    private Date account_date;    //用户账号创建日期

    /**
     * @return the account_account
     */
    public long getAccount_account() {
        return account_account;
    }

    /**
     * @param account_account the account_account to set
     */
    public void setAccount_account(long account_account) {
        this.account_account = account_account;
    }

    /**
     * @return the account_name
     */
    public String getAccount_name() {
        return account_name;
    }

    /**
     * @param account_name the account_name to set
     */
    public void setAccount_name(String account_name) {
        this.account_name = account_name;
    }

    /**
     * @return the account_pass
     */
    public String getAccount_pass() {
        return account_pass;
    }

    /**
     * @param account_pass the account_pass to set
     */
    public void setAccount_pass(String account_pass) {
        this.account_pass = account_pass;
    }

    /**
     * @return the account_limit
     */
    public int getAccount_limit() {
        return account_limit;
    }

    /**
     * @param account_limit the account_limit to set
     * @return the new limit
     */
    public int setAccount_limit(int account_limit) {
        return this.account_limit = account_limit;
    }
    
    /**
     * @param account_limit the account_limit to update
     * @return the new limit
     */
    public int updateAccount_limit(int account_limit) {
        if (-1 == this.account_limit) {
            return -1;
        }
        if (this.account_limit % account_limit != 0) {
            this.account_limit *= account_limit;
        } else {
            this.account_limit /= account_limit;
        }
        return this.account_limit;
    }


    /**
     * @return the account_date
     */
    public Date getAccount_date() {
        return account_date;
    }

    /**
     * @param account_date the account_date to set
     */
    public void setAccount_date(Date account_date) {
        this.account_date = account_date;
    }

}
