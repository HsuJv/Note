
package phonebook;

import java.awt.FlowLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.TreeSet;
import javax.swing.JButton;
import javax.swing.JFrame;

public class Menu extends JFrame implements ActionListener
{
    JButton btn_add, btn_view;
    
    //AddContact Object
    AddContact addContObj;
    
    public Menu()
    {
        setSize(280,220);
        setVisible(true);
        setTitle("Phone Book Menu");
        setLocationRelativeTo(null);
        btn_add = new JButton("Add Contact");
        btn_add.addActionListener(this);
        btn_add.setSize(100, 25);
        btn_view = new JButton("View Contact");
        btn_view.addActionListener(this);
        addContObj = new AddContact();
                  
    }
    
    public void addComponent()
    {
        setLayout(null);
        
        btn_add.setBounds(30, 40, 200, 40);
        add(btn_add);
        
        btn_view.setBounds(30,100,200,40);
        add(btn_view);
        
        setResizable(false);
        
    }
    
    public void actionPerformed(ActionEvent e)
    {
        //Action Performed Event
	if(e.getSource() == btn_add)
        {            
            addContObj.addComponentToAdd();
        }
        else if(e.getSource() == btn_view)
        {
            addContObj.addComponentToView();
        }
    }           
    
    public static void main(String[] args)
    {
        Menu mobj = new Menu();
        mobj.addComponent();
    }
    
    
    
}
