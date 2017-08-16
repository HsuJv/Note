//package gameconsole;


import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JOptionPane;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;

public class GameMenu extends JFrame implements ActionListener
{
    JButton option1;
    JButton option2;
    JButton option3;
    JLabel name;
      
    public GameMenu()
    {
        option1 = new JButton("Memory");
        option2 = new JButton("Jigsaw Puzzle");
        option3 = new JButton("Exit");
        name = new JLabel("GAME CONSOLE");
        name.setFont(new Font("Serif", Font.PLAIN, 24));
        
        setTitle("Game Menu");
        setSize(300,200);
        setResizable(false);
        setVisible(true);
        setLocationRelativeTo(null);

	option1.addActionListener(this);
        option2.addActionListener(this);
        option3.addActionListener(this);

    }

	
    public void actionPerformed(ActionEvent e)
    {
        if(e.getSource() == option1)
        {
             StartMemory mobj = new StartMemory();
             this.dispose();
        }
        else if(e.getSource() == option2)
        {
             StartPuzzle pobj = new StartPuzzle();
             this.dispose();
        }
        else if(e.getSource() == option3)
        {
             System.exit(0);
        }
    }

    
    public void addComponent()
    {
        setLayout(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();

        c.gridx = 0;
        c.gridy = 0;
        c.weighty = 0.1;
        c.anchor = c.CENTER;
        add(name,c);

        c.gridx = 0;
        c.gridy = 1;
        c.fill = c.HORIZONTAL;
        add(option1, c);

        c.gridx = 0;    
        c.gridy = 2;
        c.fill = c.HORIZONTAL;
        add(option2, c);
        
        c.gridx = 0;    
        c.gridy = 3;
        c.fill = c.HORIZONTAL;
        add(option3, c);
    }
    
    public static void main(String[] args)
    {
        GameMenu obj = new GameMenu();
        obj.addComponent();
    }
}

