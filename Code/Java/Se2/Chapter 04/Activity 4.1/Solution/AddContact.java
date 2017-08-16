package phonebook;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.Collections;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTextField;

//Import Packages
import java.util.Comparator;
import java.util.TreeSet;

public class AddContact extends MouseAdapter implements ActionListener
{
    JFrame jf_AddContact, jf_ViewContact;
    JTextField txt_name, txt_cno;
    JLabel lbl_name, lbl_cno, name, no, lbl_ct;
    JButton btn_add;
    JList jl_contact;
    JScrollPane scroll;
    DefaultListModel dlm_contact;
    
    //Collection Variable
    TreeSet<Contact> contactList;

    public AddContact() 
    {
        txt_name = new JTextField();
        txt_cno = new JTextField();
        lbl_name = new JLabel("Enter Name:");
        lbl_cno = new JLabel("Enter Contact No:");
        lbl_ct = new JLabel("Contacts:");
        btn_add = new JButton("Add");
        jl_contact = new JList();
        jl_contact.addMouseListener(this);
        dlm_contact = new DefaultListModel();

	//Collection Initialization
        contactList = new TreeSet<Contact>(new ContactSort());

        btn_add.addActionListener(this);
        txt_cno.addKeyListener(new KeyAdapter()
        {
            public void keyTyped(KeyEvent e)
            {
                Character c = e.getKeyChar();
                if(!(Character.isDigit(c)|| c==KeyEvent.VK_BACK_SPACE || c==KeyEvent.VK_DELETE))
                {
                    e.consume();
                 }
             }
          });
    }
	
    //Sorting Classes
    
    class ContactSort implements Comparator<Contact> 
    {

        public int compare(Contact c1, Contact c2) 
        {
            return c1.getNo().compareTo(c2.getNo());
        }
        
     }
    class NameSort implements Comparator<Contact>
    {
        public int compare(Contact c1, Contact c2)
        {
            return c1.getName().compareTo(c2.getName());
        }
    }


    public void addComponentToAdd() 
    {
        jf_AddContact = new JFrame("Add Contact");
        jf_AddContact.setLayout(null);
        jf_AddContact.setSize(300, 220);
        jf_AddContact.setVisible(true);
        jf_AddContact.setLocationRelativeTo(null);

        lbl_name.setBounds(10, 20, 100, 20);
        jf_AddContact.add(lbl_name);

        txt_name.setBounds(120, 20, 150, 20);
        jf_AddContact.add(txt_name);

        lbl_cno.setBounds(10, 70, 100, 20);
        jf_AddContact.add(lbl_cno);

        txt_cno.setBounds(120, 70, 150, 20);
        jf_AddContact.add(txt_cno);

        btn_add.setBounds(120, 140, 100, 25);
        jf_AddContact.add(btn_add);

        jf_AddContact.setResizable(false);
    }

    public void addComponentToView() 
    {
        jf_ViewContact = new JFrame("View Contact");
        jf_ViewContact.setLayout(null);
        jf_ViewContact.setSize(300, 220);
        jf_ViewContact.setVisible(true);
        jf_ViewContact.setLocationRelativeTo(null);

        jl_contact.setModel(dlm_contact);
        scroll = new JScrollPane(jl_contact);

        lbl_ct.setBounds(10, 20, 100, 20);
        jf_ViewContact.add(lbl_ct);

        scroll.setBounds(10, 50, 265, 100);
        jf_ViewContact.add(scroll);

    }

    public void actionPerformed(ActionEvent ae) 
    {
	//Action Performed Event
       	String name = txt_name.getText();
        String cno = txt_cno.getText();

        if (name.equals("") || (cno.equals(""))) 
        {
            JOptionPane.showMessageDialog(jf_AddContact, "Please fill the details properly", "Warning Message", JOptionPane.WARNING_MESSAGE);
        } 
        else 
        {
            Contact obj = new Contact();
            obj.setName(name);
            obj.setNo(cno);

            contactList.add(obj);
            
            ArrayList<Contact> tempList = new ArrayList<Contact>(contactList);
            Collections.sort(tempList, new NameSort());
            
            dlm_contact.removeAllElements();

            for (Contact c : tempList) 
            {
                dlm_contact.addElement(c);
            }

            txt_name.setText("");
            txt_cno.setText("");

            JOptionPane.showMessageDialog(jf_AddContact, "Contact has been added", "Success Message", JOptionPane.INFORMATION_MESSAGE);
            int status = JOptionPane.showConfirmDialog(jf_AddContact, "Do you want to add more contacts?", "Confirmation", JOptionPane.YES_NO_OPTION, JOptionPane.WARNING_MESSAGE);

            if (status == 0) 
            {
                jf_AddContact.setVisible(true);
            } 
            else 
            {
                jf_AddContact.dispose();
            }
        }

    }

    public void mouseClicked(MouseEvent e) 
    {
        //Mouse Clicked Event
	if (e.getSource() == jl_contact) 
        {
            JList l = (JList) e.getSource();
            if (e.getClickCount() == 2) 
            {
                Contact o = (Contact) l.getSelectedValue();
                if (o != null) 
                {
                    String name = o.getName();
                    String no = o.getNo();
                    String info = "Name is: " + name + "\nContact No is: " + no;

                    JOptionPane.showMessageDialog(jf_AddContact, info, "Contact Details", JOptionPane.INFORMATION_MESSAGE);
                }
            }
        }
    }
    
    
}

    