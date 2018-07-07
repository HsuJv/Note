/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pack;


import java.io.IOException;
import java.io.InputStream;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;
/**
 *
 * @author Hsu
 */
public class BuildAlbums {
    
     Albums  parseAlbum(Albums album, InputStream customerData) throws ParserConfigurationException, SAXException, IOException {
        if (album == null) {
            album = new Albums();
        }
        DocumentBuilder documentBuilder = DocumentBuilderFactory.newInstance().newDocumentBuilder();
        Document document = documentBuilder.parse(customerData);
        document.getDocumentElement().normalize();

        NodeList nodeList = document.getElementsByTagName("album");

        for (int temp = 0; temp < nodeList.getLength(); temp++) {

            Node nNode = nodeList.item(temp);
            if (nNode.getNodeType() == Node.ELEMENT_NODE) {
                Element eElement = (Element) nNode;
                album.setId(getTagValue("id", eElement));
                album.setName(getTagValue("albumname", eElement));
                album.setArtist(getTagValue("artistname", eElement));
                album.setA_year(getTagValue("issueyear", eElement));
                album.setPrice(getTagValue("price", eElement));
                album.setDescription(getTagValue("description", eElement));
            }
        }
        return album;
    }

    private static String getTagValue(String sTag, Element eElement) {
        NodeList nlList = eElement.getElementsByTagName(sTag).item(0).getChildNodes();
        Node nValue = (Node) nlList.item(0);
        return nValue.getNodeValue();
    }
}
