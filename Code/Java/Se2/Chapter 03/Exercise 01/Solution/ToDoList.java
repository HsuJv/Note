package chapter03;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTextField;

public class ToDoList extends JFrame implements ActionListener 
{
    JLabel lbl_catg, lbl_task, lbl_time, lbl_list;
    JTextField txt_task;
    JComboBox jcb_task, jcb_hours, jcb_min;
    JList jl_task;
    DefaultListModel dlm_task;
    JScrollPane jsp_task;
    JButton btn_add, btn_view;
    JFrame list;
    TaskProcessor<? extends Task> tp;
    String hour, min;
    int i_hour, i_min;
    public ToDoList() 
    {
        setLocationRelativeTo(null);
        setLayout(null);
        setResizable(false);
        setTitle("To Do List");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        lbl_catg = new JLabel("Select the Category:");
        lbl_catg.setBounds(10, 10, 200, 15);
        add(lbl_catg);

        lbl_task = new JLabel("Enter the Task:");
        lbl_task.setBounds(10, 40, 100, 15);
        add(lbl_task);

        lbl_time = new JLabel("Enter the Time (HH:MM):");
        lbl_time.setBounds(10, 70, 150, 15);
        add(lbl_time);

        jcb_task = new JComboBox();
        jcb_task.addItem("Select One");
        jcb_task.addItem("Event");
        jcb_task.addItem("Meeting");
        jcb_task.setBounds(170, 10, 200, 20);
        add(jcb_task);

        txt_task = new JTextField();
        txt_task.setBounds(170, 40, 200, 20);
        add(txt_task);

        hour = new SimpleDateFormat("HH").format(Calendar.getInstance().getTime());
        min =  new SimpleDateFormat("MM").format(Calendar.getInstance().getTime());
        
        i_hour = Integer.parseInt(hour);
        i_min = Integer.parseInt(min);
        
        jcb_hours = new JComboBox();
        for (int i = 0; i < 24; i++) 
        {
            if (i < 10) 
            {
                jcb_hours.addItem("0" + i);
            } 
            else 
            {
                jcb_hours.addItem(i);
            }
        }
        
        jcb_hours.setBounds(170, 70, 50, 20);
        add(jcb_hours);

        jcb_min = new JComboBox();
        for (int i = 0; i < 60; i++) 
        {
            if (i < 10) 
            {
                jcb_min.addItem("0" + i);
            } 
            else 
            {
                jcb_min.addItem(i);
            }
        }
        
        jcb_min.setBounds(230, 70, 50, 20);
        add(jcb_min);

        btn_add = new JButton("Add");
        btn_add.addActionListener(this);
        btn_add.setBounds(100, 120, 100, 25);
        add(btn_add);

        btn_view = new JButton("View");
        btn_view.addActionListener(this);
        btn_view.setBounds(210, 120, 100, 25);
        add(btn_view);

        setSize(400, 180);
        setVisible(true);

        list = new JFrame("Task List");
        list.setLayout(null);
        list.setLocationRelativeTo(null);
        setResizable(false);

        lbl_list = new JLabel("To do list:");
        lbl_list.setBounds(150, 10, 100, 15);
        list.add(lbl_list);

        jl_task = new JList();
        dlm_task = new DefaultListModel();
        jl_task.setModel(dlm_task);
        jsp_task = new JScrollPane(jl_task);
        jsp_task.setBounds(10, 40, 335, 90);
        list.add(jsp_task);
        list.setSize(350, 180);
    }

    public void actionPerformed(ActionEvent e) 
    {
        if (e.getSource() == btn_add) 
        {
            int t_hour = Integer.parseInt(jcb_hours.getSelectedItem().toString());
            int t_min = Integer.parseInt(jcb_min.getSelectedItem().toString());
            if(jcb_task.getSelectedItem().equals("Select One"))
            {
                JOptionPane.showMessageDialog(this, "Please select the category of task.", "Warning", JOptionPane.WARNING_MESSAGE);
            }
            else if(txt_task.getText().equals(""))
            {
                JOptionPane.showMessageDialog(this, "Please provide the proper task.", "Warning", JOptionPane.WARNING_MESSAGE);
            }
            else if((t_hour < i_hour))
            {
                JOptionPane.showMessageDialog(this, "The time of the task must be greater than the current time.", "Warning", JOptionPane.WARNING_MESSAGE);
            }
            
            if (jcb_task.getSelectedItem().equals("Event")&&!(txt_task.getText().equals(""))&&!(t_hour < i_hour)) 
            {
                String item = jcb_hours.getSelectedItem().toString() + ":" + jcb_min.getSelectedItem().toString() + " - " + txt_task.getText() + " ( " + jcb_task.getSelectedItem() + " )";
                Event obj = new Event(item);
                tp = new TaskProcessor<>(obj);
                dlm_task.addElement(tp.getTaskP());
                jcb_task.setSelectedIndex(0);
                txt_task.setText(" ");
                jcb_hours.setSelectedIndex(0);
                jcb_min.setSelectedIndex(0);
            } 
            else if (jcb_task.getSelectedItem().equals("Meeting")&&!(txt_task.getText().equals(""))&&!(t_hour <= i_hour)) 
            {
                String item = jcb_hours.getSelectedItem().toString() + ":" + jcb_min.getSelectedItem().toString() + " - " + txt_task.getText() + " ( " + jcb_task.getSelectedItem() + " )";
                Meeting obj2 = new Meeting(item);
                tp = new TaskProcessor<>(obj2);
                dlm_task.addElement(tp.getTaskP());
                jcb_task.setSelectedIndex(0);
                txt_task.setText(" ");
                jcb_hours.setSelectedIndex(0);
                jcb_min.setSelectedIndex(0);
            }
        } 
        else if (e.getSource() == btn_view) 
        {
            list.setVisible(true);
        }

    }

    public static void main(String[] args) 
    {
        ToDoList tdl = new ToDoList();

    }
}
