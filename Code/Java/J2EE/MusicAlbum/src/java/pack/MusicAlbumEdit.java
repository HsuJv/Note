/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pack;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import javax.jws.WebService;
import javax.jws.WebMethod;
import javax.jws.WebParam;

/**
 *
 * @author Hsu
 */
@WebService(serviceName = "MusicAlbumEdit")
public class MusicAlbumEdit {

    private static String dbURL = "jdbc:derby://localhost:1527/JerryMusicStore;create=true;user=Jerry;password=J123";
    Connection con;
   
    /**
     * Web 服务操作
     */
    @WebMethod(operationName = "add")
    public String add(@WebParam(name = "details") String details) {
        int id = 1;
        String showAll = "select * from albums";
        String insert = "insert into albums values(?, ?, ?, ?, ?, ?)";
                
        try{
            Class.forName("org.apache.derby.jdbc.ClientDriver").newInstance();
            con = DriverManager.getConnection(dbURL);
            
            
            ResultSet rs = con.prepareStatement(showAll).executeQuery();
            PreparedStatement psInsert = con.prepareStatement(insert);

            while(rs.next()){
                id = rs.getInt("id") + 1;
            }
            HashMap<String, String> list = (HashMap<String, String>)Serialize.UnserializeStringToObject(details);
            psInsert.setInt(1, id);
            psInsert.setString(2, list.get("NAME"));
            psInsert.setString(3, list.get("ARTIST"));
            psInsert.setString(4, list.get("A_YEAR"));
            psInsert.setDouble(5, Double.parseDouble(list.get("PRICE")));
            psInsert.setString(6, list.get("DESCRIPTION"));
            psInsert.execute();
            return "Success";
        }
        catch (Exception e){
            return e.toString();
        }
    }

    /**
     * Web 服务操作
     */
    @WebMethod(operationName = "delete")
    public String delete(@WebParam(name = "id") int id) {
        String del = "delete from albums where id = " + id;
        try{
            Class.forName("org.apache.derby.jdbc.ClientDriver").newInstance();
            con = DriverManager.getConnection(dbURL);
            
            
            con.prepareStatement(del).execute();
            return "Success";
        }
        catch (Exception e){
            return e.toString();
        }
    }

    /**
     * Web 服务操作
     */
    @WebMethod(operationName = "display")
    public String display(){
        String showAll = "select * from albums";
        List<Map<String, String>> res = new ArrayList<>();
        String r = new String();
        
        try{      
            Class.forName("org.apache.derby.jdbc.ClientDriver").newInstance();
            con = DriverManager.getConnection(dbURL);
            
            
            ResultSet rs = con.prepareStatement(showAll).executeQuery();
            ResultSetMetaData rsmd = rs.getMetaData();
            int colCnt = rsmd.getColumnCount();
            
            while(rs.next()){
                Map<String, String> item = new HashMap<>();
                for (int i = 1; i <= colCnt; i++){ 
                    item.put(rsmd.getColumnLabel(i), rs.getString(i));
                }
                res.add(item);
            }
            r = Serialize.SerializeObjectToString(res);
        }
        catch (Exception e){
            return e.toString();
        }
        return r;
    }
}
