/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package DAO;

import Model.Words;
import java.util.List;

/**
 *
 * @author Hsu
 */

public interface WordsDao {
    public boolean addWords(Words words);//新增留言
    public boolean readWords(Words words); //更改留言已读状态
    public boolean deleteWords(Words words); //根据留言id删除留言
    public boolean deleteWordsByAccount_account(long account_account); //根据用户数字账号，删除该用户回帖
    public long    returnNewWordsNumByObjectId(long account_account); // 根据用户id查询所有未读留言个数
    public List<Words> searchWordsByObjectId(long account_account); //根据用户id查询该用户收到的所有留言
}