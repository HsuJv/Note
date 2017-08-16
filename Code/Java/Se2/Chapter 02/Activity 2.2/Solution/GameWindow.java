
package localize;

import java.awt.Font;
import java.util.Locale;
import java.util.ResourceBundle;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;


public class GameWindow {
    JFrame f;
    JPanel p;
    JLabel l;
    JButton b1,b2,b3;
    
    Locale currentLocale;
    ResourceBundle messages ;
    
    GameWindow(){
        this("English");
    }
    GameWindow(String language){
        
        if(language.equals("English")){
            setEnglish();
            createFrame();
        }
        else if(language.equals("French")){
            setFrench();
            createFrame();
        }
        
       
    }
    
    public void setEnglish(){
        
        currentLocale= new Locale("en", "US");
            messages = ResourceBundle.getBundle("MessagesBundle", currentLocale);
        
    }
    public void setFrench(){
         currentLocale= new Locale("fr", "FR");
            messages = ResourceBundle.getBundle("MessagesBundle", currentLocale);
    }
    public void createFrame(){
         f = new JFrame();
        p = new JPanel();
        l = new JLabel("Puzzle");
        l.setFont(new Font("Serif", Font.PLAIN, 24));
        b1 = new JButton(messages.getString("PlayGame"));
        b2 = new JButton(messages.getString("ViewInstructions"));
        b3 = new JButton(messages.getString("Exit"));
        f.setTitle(messages.getString("Puzzle"));
        JLabel l = new JLabel(messages.getString("Puzzle"));
        l.setFont(new Font("Serif", Font.PLAIN, 36));
        f.add(p);
            f.setVisible(true);
            f.setSize(200, 200);
            p.add(l);
            p.add(b1);
            p.add(b2);
            p.add(b3);
    }
}
