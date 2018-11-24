/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pack;


import java.util.Date;
import javax.servlet.ServletContext;
import javax.servlet.ServletContextAttributeEvent;
import javax.servlet.ServletContextAttributeListener;
import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;
import javax.servlet.ServletRequestEvent;
import javax.servlet.ServletRequestListener;


/**
 *
 * @author Hsu
 */

public class ServletEventsListener
        implements ServletContextListener, ServletContextAttributeListener, ServletRequestListener{
    ServletContext contx;
    String name;
    String value;
    
    @Override
    public void contextInitialized(ServletContextEvent sce) {
        contx  = sce.getServletContext();
        contx.log("Context has been initialized at" + new Date());
    }

    @Override
    public void contextDestroyed(ServletContextEvent sce) {
        contx.log("Context has veen destroyed at " + new Date());
    }

    @Override
    public void attributeAdded(ServletContextAttributeEvent event) {
        name = event.getName();
        value = (String) event.getValue();
        contx.log("Attribute with name: " + name + " and value: " + value + " has been added to the context at: " + new Date());
    }

    @Override
    public void attributeRemoved(ServletContextAttributeEvent event) {
        contx.log("Attribute with name: " + name + " and value: " + value + " has been removed from the context at: " + new Date());
    }

    @Override
    public void attributeReplaced(ServletContextAttributeEvent arg0) {
        contx.log("Attribute with name: " + name + " and value: " + value + " has been replaced context at: " + new Date());
    }

    @Override
    public void requestDestroyed(ServletRequestEvent sre) {
        contx.log("A reuqest has been destroyed at: " + new Date());
    }

    @Override
    public void requestInitialized(ServletRequestEvent sre) {
        contx.log("A reuqest has been initialized at: " + new Date());
    }   
}