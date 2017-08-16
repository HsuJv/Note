import java.awt.GridLayout;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileWriter;
import java.io.IOException;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class AddBook extends JFrame implements ActionListener{
	JFrame MyFrame;
	JPanel MyPanel;
	JTextField txtField1,txtField2,txtField3,txtField4,txtField5,txtField6;
	JLabel label1,label2,label3,label4,label5,label6;
	JButton button1,button2;
	public AddBook(){
		MyPanel=new JPanel();	
		GridLayout gl=new GridLayout(7,2);	
		MyPanel.setLayout(gl);
		setTitle("AddBook");
		txtField1=new JTextField(30);
		txtField2=new JTextField(10);
		txtField3=new JTextField(20);
		txtField4=new JTextField(15);
		txtField5=new JTextField(10);
		txtField6=new JTextField(4);
		label1=new JLabel("   Book name:");
		label2=new JLabel("   Book code:");
		label3=new JLabel("   Author name:");
		label4=new JLabel("   Book category:");
		label5=new JLabel("   Number:");
		label6=new JLabel("   Price:");
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
		MyPanel.add(label5);	
		MyPanel.add(txtField5);	
		MyPanel.add(label6);
		MyPanel.add(txtField6);	
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
					txtField4.getText().trim().length()==0||
					txtField5.getText().trim().length()==0||
					txtField6.getText().trim().length()==0)
			{
				JOptionPane.showMessageDialog(this, "Input error!");
			}
			else
			{
				try {
					FileWriter f=new FileWriter("Book.txt",true);
					String str=txtField1.getText()+" "+txtField2.getText()+" "+txtField3.getText()+" "+txtField4.getText()+" "+txtField5.getText()+" "+txtField6.getText()+"\r\n";
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