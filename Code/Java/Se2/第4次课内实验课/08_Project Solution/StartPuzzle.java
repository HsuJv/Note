//package gameconsole;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

class StartPuzzle extends JFrame implements ActionListener 
{
    JPanel jp;
    JFrame f, f1;
    JButton b1, b3, b4;
    JTextField t1 = new JTextField(20);
    JLabel l1, l2, l3, l4;
    static String s1;

    public StartPuzzle() 
    {
        jp = new JPanel();
        b1 = new JButton("Start Game");
        b3 = new JButton("Exit");

        b1.addActionListener(this);
        b3.addActionListener(this);

        l1 = new JLabel("Enter Your Name");

        jp.add(l1);
        jp.add(t1);
        jp.add(b1);
        jp.add(b3);

        add(jp);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
        setSize(400, 100);
        setResizable(false);
        setLocationRelativeTo(null);

    }
public synchronized void processSalary()
{
    
}
    public void actionPerformed(ActionEvent e) 
    {
        if (e.getSource() == b1) 
        {
            this.dispose();
            s1 = t1.getText().toUpperCase();

            JigsawPuzzle m = new JigsawPuzzle();
           
        }

        if (e.getSource() == b3) 
        {
            this.dispose();
            GameMenu obj = new GameMenu();
            obj.addComponent();
        }

    }

}