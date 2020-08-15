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

public class Words {
    private long words_object; //留言对象的数字账号设立对应account表的外键
    private long words_subject; //留言的发布者的数字账号 设立对应account表的外键
    private long words_id;         //留言的id主键
    private String words_content; //留言的内容
    private boolean words_new;    //留言是否已读
    private Date words_date;      //留言的日期

    /**
     * @return the words_object
     */
    public long getWords_object() {
        return words_object;
    }

    /**
     * @param words_object the words_object to set
     */
    public void setWords_object(long words_object) {
        this.words_object = words_object;
    }

    /**
     * @return the words_subject
     */
    public long getWords_subject() {
        return words_subject;
    }

    /**
     * @param words_subject the words_subject to set
     */
    public void setWords_subject(long words_subject) {
        this.words_subject = words_subject;
    }

    /**
     * @return the words_id
     */
    public long getWords_id() {
        return this.words_id;
    }

    /**
     * @param words_id the words_id to set
     */
    public void setWords_id(long words_id) {
        this.words_id = words_id;
    }

    /**
     * @return the words_content
     */
    public String getWords_content() {
        return this.words_content;
    }

    /**
     * @param words_content the words_content to set
     */
    public void setWords_content(String words_content) {
        this.words_content = words_content;
    }

    /**
     * @return the words_new
     */
    public boolean getWords_new() {
        return this.words_new;
    }

    /**
     * @param words_new the words_new to set
     */
    public void setWords_new(short words_new) {
        if (0 == words_new) this.words_new = false;
        else this.words_new = true;
    }

    /**
     * @return the words_date
     */
    public Date getWords_date() {
        return this.words_date;
    }

    /**
     * @param words_date the words_date to set
     */
    public void setWords_date(Date words_date) {
        this.words_date = words_date;
    }
    
   
}
