/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package DAO;

import Model.Revert;
import java.util.List;

/**
 *
 * @author Hsu
 */

public interface RevertDao {
    public boolean addRevert(Revert revert);//新增回帖
    public boolean deleteRevert(Revert revert); //根据帖子id删除回帖
    public boolean deleteRevertByAccount_account(long account_account); //根据用户数字账号，删除该用户回帖
    public boolean deleteRevertbyMessage_id(long message_id); //根据主题帖id删除所有回帖
    public List<Revert> searchRevertByMessage_id(long message_id); //显示所有回帖
    public Revert searchNewRevertByMessage_id(long message_id); //显示最新回帖
    public List<Revert> searchRevertById(long account_account); //根据用户id查询该用户的所有回复
    public long returnRevertNumByMessage_id(long message_id); //根据message_id获得其回帖总数
}