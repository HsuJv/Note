/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Util;

import java.sql.Connection;
import java.sql.DriverManager;

/**
 *
 * @author Hsu
 */
public class DBUtil {

    private static final String DBURL = "jdbc:derby://localhost:1527/BBS";
    private static final String DBUSER = "root";
    private static final String DBPWD = "root";

    public static Connection getConnection() {
        Connection conn = null;

        try {
            Class.forName("org.apache.derby.jdbc.ClientDriver").newInstance();
            conn = DriverManager.getConnection(DBURL, DBUSER, DBPWD);

        } catch (Exception e) {
            e.printStackTrace();
        }

        return conn;
    }
}
