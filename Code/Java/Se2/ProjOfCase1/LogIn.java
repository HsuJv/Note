import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;

public class LogIn extends JFrame implements ActionListener {
	JFrame MyFrame;
	JPanel MyPanel;
	JTextField txtField;
	JPasswordField pwdField;
	JButton button1,button2;
	JLabel label1,label2;
	public LogIn(){
		MyPanel=new JPanel();
		setTitle("Login");
		txtField=new JTextField(15);
		pwdField=new JPasswordField(15);
		button1=new JButton("Login");
		button1.addActionListener(this);
		label1=new JLabel("Username: ");
		label2=new JLabel("Password: ");
		button2=new JButton("Cancel");
		button2.addActionListener(this);
		MyPanel.add(label1);
		MyPanel.add(txtField);
		MyPanel.add(label2);
		MyPanel.add(pwdField);
		MyPanel.add(button1);
		MyPanel.add(button2);
		add(MyPanel);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		int width = Toolkit.getDefaultToolkit().getScreenSize().width;
		int height = Toolkit.getDefaultToolkit().getScreenSize().height;
		int windowsWedth = 300;
		int windowsHeight = 150;
		//设置窗体在显示器居中显示
		this.setBounds((width - windowsWedth) / 2,(height - windowsHeight) / 2, windowsWedth, windowsHeight);
		setVisible(true);
        setSize(300, 150);
        setResizable(false);
	}
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		if (e.getSource() == button1) {
            //Validation Code
            Pattern Mypattern = Pattern.compile("[A-Za-z0-9]+");
            Matcher Mymatcher = Mypattern.matcher(txtField.getText());
            Boolean Myboolean = Mymatcher.matches();
            Pattern Mypattern1 = Pattern.compile("[A-Za-z0-9]+");
            Matcher Mymatcher1 = Mypattern1.matcher(pwdField.getText());
            Boolean Myboolean1 = Mymatcher1.matches();
            if (Myboolean) 
            {
            	if (Myboolean) 
            	{
            		this.dispose();
            		new GUI();
            	} 
            	else 
            	{
            		JOptionPane.showMessageDialog(this, "Password is incorrect");
            	}
            } 
            else 
            {
            	JOptionPane.showMessageDialog(this, "Username is incorrect");
            }

        }
        if (e.getSource() == button2) {
            System.exit(0);
        }
	}
}
