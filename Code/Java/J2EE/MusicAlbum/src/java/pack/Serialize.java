/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pack;

import java.io.*;
import java.net.*;

/**
 *
 * @author Hsu
 */

public class Serialize {
    public static String SerializeObjectToString(Object object) throws Exception{
         
        ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
        ObjectOutputStream objectOutputStream = new ObjectOutputStream(byteArrayOutputStream);
        objectOutputStream.writeObject(object);  
        String serStr = byteArrayOutputStream.toString("ISO-8859-1");
        serStr = URLEncoder.encode(serStr, "UTF-8");
         
        objectOutputStream.close();
        byteArrayOutputStream.close();
        return serStr;
         
    };
     
    public static Object UnserializeStringToObject(String encoded) throws Exception{
         
        String redStr = URLDecoder.decode(encoded, "UTF-8");
        ByteArrayInputStream byteArrayInputStream = new ByteArrayInputStream(redStr.getBytes("ISO-8859-1"));
        ObjectInputStream objectInputStream = new ObjectInputStream(byteArrayInputStream); 
        Object obj = objectInputStream.readObject();        
        objectInputStream.close();
        byteArrayInputStream.close();
        return obj;
    };
}
