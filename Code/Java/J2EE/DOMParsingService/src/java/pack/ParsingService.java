/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pack;

import javax.xml.parsers.*;
import org.w3c.dom.*;
import java.io.*;
import javax.jws.WebMethod;
import javax.jws.WebParam;
import javax.jws.WebService;

/**
 *
 * @author Hsu
 */

@WebService()
public class ParsingService {
    /**
     * Web service operation
     */
    @WebMethod(operationName = "parseFile")
    public String parseFile(@WebParam(name = "bookName")
    String bookName) {
       String qty = "";
        String date="";
        String amt="";//="The information of all Books is as follows: <br>";
        try {
            File file = new File("Q:\\Users\\Hsu\\Documents\\NetBeansProjects\\DOMParsingService\\src\\java\\pack\\inventory.xml");
            DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
            DocumentBuilder db = dbf.newDocumentBuilder();
            Document doc = db.parse(file);
            doc.getDocumentElement().normalize();
            NodeList nodeLst = doc.getElementsByTagName(bookName);
            for (int s = 0; s < nodeLst.getLength(); s++) {
                Node fstNode = nodeLst.item(s);
                if (fstNode.getNodeType() == Node.ELEMENT_NODE) {
                    Element fstElmnt = (Element) fstNode;
                    NodeList fstNmElmntLst = fstElmnt.getElementsByTagName("Quantity");
                    Element fstNmElmnt = (Element) fstNmElmntLst.item(0);
                    NodeList fstNm = fstNmElmnt.getChildNodes();
                    qty = "" + ((Node) fstNm.item(0)).getNodeValue()+"\n";
                    System.out.println(qty);
                    NodeList secNmElmntLst = fstElmnt.getElementsByTagName("ExpectedDelivery");
                    Element secNmElmnt = (Element) secNmElmntLst.item(0);
                    NodeList secNm = secNmElmnt.getChildNodes();
                    date = "" + ((Node) secNm.item(0)).getNodeValue()+"\n";
                    System.out.println(date);
                    NodeList lstNmElmntLst = fstElmnt.getElementsByTagName("TotalCost");
                    Element lstNmElmnt = (Element) lstNmElmntLst.item(0);
                    NodeList lstNm = lstNmElmnt.getChildNodes();
                    amt = "" + ((Node) lstNm.item(0)).getNodeValue()+"\n";
                    System.out.println(amt);
                }
            }
        } catch (Exception e) {
          //  return e.toString();
        }
        return bookName + "," + qty + "," + date + "," + amt;
    }
}
