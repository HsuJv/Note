/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pack;

import java.util.ArrayList;
import java.util.Iterator;

/**
 *
 * @author Hsu
 */
class PersistData {

    static private ArrayList<Albums> albums = new ArrayList<Albums>();

    PersistData() {
    }

    static String persist(Albums album) {
        albums.add(album);
        return album.getId();
    }

    static String loadAlbums(String albumId) {
        String result = albumId + "is not available. SORRY!!!";
        Iterator<Albums> it = albums.iterator();
        while (it.hasNext()) {
            Albums album = it.next();
            String id = album.getId();
            if (id.equals(albumId)) {
                result = "<?xml version=\"1.0\"?> \n";
                result += "<album>\n";
                result += "<id>" + album.getId() + "</id>\n";
                result += "<albumname>" + album.getName()+ "</albumname>\n";
                result += "<artistname>" + album.getArtist()+ "</artistname>\n";
                result += "<issueyear>" + album.getA_year()+ "</issueyear>\n";
                result += "<price>" + album.getPrice()+ "</price>\n";
                result += "<description>" + album.getDescription()+ "</description>\n";
                result += "</album>\n";
                break;
            }
        }
        return result;
    }

    static void persistupdate(Albums album) {
        Iterator<Albums> it = albums.iterator();
        while (it.hasNext()) {
            Albums al = it.next();
            String id = al.getId();
            if (id.equals(album.getId())) {
                it.remove();
                albums.add(album);
                break;
            }
        }
    }

    static void deleteData(String albumId) {
        Iterator<Albums> it = albums.iterator();
        while (it.hasNext()) {
            Albums album = it.next();
            String id = album.getId();
            if (id.equals(albumId)) {
                it.remove();
                break;
            }
        }
    }
}

