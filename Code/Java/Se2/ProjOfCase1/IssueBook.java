import java.awt.GridLayout;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Date;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class IssueBook extends JFrame implements ActionListener{
	JFrame jf;
	JPanel MyPanel;
	JTextField txtField1,txtField2,txtField3,txtField4;
	JLabel label1,label2,label3,label4;
	JButton button1,button2;
	public IssueBook(){
		MyPanel=new JPanel();	
		GridLayout grdLayout=new GridLayout(5,2);	
		MyPanel.setLayout(grdLayout);
		setTitle("IssueBook");
		txtField1=new JTextField(30);
		txtField2=new JTextField(20);
		txtField3=new JTextField(20);
		txtField4=new JTextField(20);
		label1=new JLabel("   Book name:");
		label2=new JLabel("   Name of the person:");
		label3=new JLabel("   Date of issue:");
		label4=new JLabel("   Return date:");
		button1=new JButton("Submit");
		button1.addActionListener(this);
		button2=new JButton("Back");
		button2.addActionListener(this);
		MyPanel.add(label1);	
		MyPanel.add(txtField1);	
		MyPanel.add(label2);
		MyPanel.add(txtField2);
		MyPanel.add(label3);	
		MyPanel.add(txtField3);	
		MyPanel.add(label4);
		MyPanel.add(txtField4);	
		MyPanel.add(button1);
		MyPanel.add(button2);
		add(MyPanel);
		int width = Toolkit.getDefaultToolkit().getScreenSize().width;
		int height = Toolkit.getDefaultToolkit().getScreenSize().height;
		int windowsWedth = 500;
		int windowsHeight = 500;
		//设置窗体在显示器居中显示
		this.setBounds((width - windowsWedth) / 2,(height - windowsHeight) / 2, windowsWedth, windowsHeight);
		setVisible(true);
		setSize(500,500);
		}
	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource()==button1)
		{
			if(txtField1.getText().trim().length()==0||
					txtField2.getText().trim().length()==0||
					txtField3.getText().trim().length()==0||
					txtField4.getText().trim().length()==0)
			{
				JOptionPane.showMessageDialog(this, "Input error!");
			}
			else
			{
				try {
					FileWriter f=new FileWriter("IssueBook.txt",true);
					String str=txtField1.getText()+" "+txtField2.getText()+" "+txtField3.getText()+" "+txtField4.getText()+"\r\n";
					f.write(str);
					JOptionPane.showMessageDialog(this, "Submit Success!");
					f.close();
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					System.out.println(e1);
				}
			}
		}
		if(e.getSource()==button2)
		{
			setVisible(false);
			new GUI();
		}
	}
}