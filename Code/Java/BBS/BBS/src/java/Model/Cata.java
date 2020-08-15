/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Model;

/**
 *
 * @author Hsu
 */
public class Cata {
    private int id; // 版块id
    private String name; // 版块名
    private long message_num; // 版块帖子数

    /**
     * @return the id
     */
    public int getId() {
        return id;
    }

    /**
     * @param id the id to set
     */
    public void setId(int id) {
        this.id = id;
    }

    /**
     * @return the name
     */
    public String getName() {
        return name;
    }

    /**
     * @param name the name to set
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * @return the message_num
     */
    public long getMessage_num() {
        return message_num;
    }

    /**
     * @param message_num the message_num to set
     */
    public void setMessage_num(long message_num) {
        this.message_num = message_num;
    }
    
    
}
