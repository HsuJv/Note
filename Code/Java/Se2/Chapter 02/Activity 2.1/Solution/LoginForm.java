package loginformvalidate;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import javax.swing.*;

class LoginForm extends JFrame implements ActionListener {

    JPanel jp;
    JFrame f, f1;
    JButton b1;
    JButton b2, k;
    JTextField t1;
    JPasswordField t2;
    JLabel l1, l2;

    public LoginForm() {

        jp = new JPanel();
        setVisible(true);
        setSize(300, 300);


        t1 = new JTextField(20);
        t2 = new JPasswordField(20);
        b1 = new JButton("Validate");
        b1.addActionListener(this);
        l1 = new JLabel("Email-id    ");
        l2 = new JLabel("Password");
        b2 = new JButton("Exit");
        b2.addActionListener(this);
        jp.add(l1);
        jp.add(t1);
        jp.add(l2);
        jp.add(t2);
        jp.add(b1);
        jp.add(b2);
        add(jp);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
        setSize(300, 300);
        setResizable(false);

    }

    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == b1) {
            //Validation Code
            Pattern Mypattern = Pattern.compile("^[a-z]+[a-z.0-9-]+@[a-z]+(\\.[a-z]+[a-z]+)([/?].*)?$");
Matcher Mymatcher = Mypattern.matcher(t1.getText());
Boolean Myboolean = Mymatcher.matches();
Pattern Mypattern1 = Pattern.compile("^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=.*[@#$%^&+=]).{8,}$");
Matcher Mymatcher1 = Mypattern1.matcher(t2.getText());
Boolean Myboolean1 = Mymatcher1.matches();
if (Myboolean == true) 
{
if (Myboolean1 == true) 
{
JOptionPane.showMessageDialog(this, "Email-id and password are correct");
} 
else 
{
JOptionPane.showMessageDialog(this, "Password is incorrect");
}
} 
else 
{
JOptionPane.showMessageDialog(this, "Email-id is incorrect");
}

        }
        if (e.getSource() == b2) {

            System.exit(0);
        }
    }

    public static void main(String[] args) {
        LoginForm f1 = new LoginForm();


    }
}