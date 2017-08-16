
package chapter01;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;


public class MouseMoveDemo extends JFrame 
{
    int x, y;
    JLabel position;
    
    public MouseMoveDemo()
    {
        super("Mouse Motion Event Demo");
        position = new JLabel();
        
        setLayout(new FlowLayout());
        
        add(position);
              
        setSize(320,300);
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
       addMouseMotionListener(new MouseAdapter(){
          public void mouseMoved(MouseEvent me)
            {
                x = me.getX();
                y = me.getY();
                position.setText("Mouse cursor is at " + x + " " + y);
            } 
       }
       );
    }
        
 
    
    public static void main(String[] args)
    {
        MouseMoveDemo obj = new MouseMoveDemo();
    }
        
}
