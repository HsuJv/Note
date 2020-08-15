/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package DAO;

import Model.Message;
import java.util.List;

/**
 *
 * @author Hsu
 */
public interface MessageDao {
    public boolean addMessage(Message message);    //新增主题帖
    public boolean deleteMessage(Message message); //删除主题帖,根据主题帖的ID进行删除，即message_id
    public boolean deleteMessageByCata_id(int cata_id); // 根据版块编号，删除所有主题帖
    public List<Message> searchMessageByCata(int cata_id);   //显示版块主题帖信息，查询了日期，以及account表的发帖人名字
    public List<Message> searchMessageIpost(long account_account);    //根据用户Id显示该用户所有的发布主题帖
    public List<Message> searchMessageByKeyword(String[] keys);     //根据关键词查询帖子
    public Message returnMessageByMessage_id(Message message);//显示所有主题帖信息给用户，包括发帖人名字，回帖数
    public long returnMessageNumByCata_id(long cata_id); //根据cata_id获得其主题帖总数
}