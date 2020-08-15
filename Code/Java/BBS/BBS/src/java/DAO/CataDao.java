/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package DAO;

import Model.Cata;
import java.util.List;

/**
 *
 * @author Hsu
 */
public interface CataDao {
    public boolean addCata(Cata cata); // 新增版块
    public boolean deleteCata(Cata cata); // 删除版块
    public Cata returnCataById(long id);
    public List<Cata> searchAllCata(); // 返回所有版块信息
}
