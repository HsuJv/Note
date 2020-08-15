/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package DAO;

import Model.Account;
import java.util.List;

/**
 *
 * @author Hsu
 */
public interface AccountDao {

    public boolean addAccount(Account account);//新增账号信息

    public boolean deleteAccount(Account account);//删除账号信息

    public boolean updateAccount(Account account);//更新账号信息

    public List<Account> searchAccountAll();//只查询普通用户

    public List<Account> searchAdminAll(int limit);//只查询管理员

    public Account returnAccountByAccount_account(Account account);  //根据用户数字账号返回用户

    public Account returnAccountByAccount_name(Account account);//通过用户名返回用户

    public Account loginAccount(Account account); //查询登录信息以及返回用户

    public boolean setAccountAdmin(Account account, int limit);//将用户权限变为对应版块id，即使管理员
}
