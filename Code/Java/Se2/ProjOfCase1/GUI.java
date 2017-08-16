import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class GUI extends JFrame implements ActionListener{

	JFrame MyFrame;
	JPanel MyPanel;
	JButton button1,button2,button3,button4,button5;
	public GUI(){
		MyPanel=new JPanel();
		setTitle("Menu");
		button1=new JButton("Add a user membership");
		button1.addActionListener(this);
		button2=new JButton("     Add a book      ");
		button2.addActionListener(this);
		button3=new JButton("    Issue a book     ");
		button3.addActionListener(this);
		button4=new JButton("    Search Files     ");
		button4.addActionListener(this);
		button5=new JButton("        Exit         ");
		button5.addActionListener(this);
		button1.setLocation(50, 33);
		button2.setLocation(50, 66);
		button3.setLocation(50, 99);
		button4.setLocation(50, 132);
		button5.setLocation(50, 165);
		MyPanel.add(button1);
		MyPanel.add(button2);
		MyPanel.add(button3);
		MyPanel.add(button4);
		MyPanel.add(button5);
		add(MyPanel);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		int width = Toolkit.getDefaultToolkit().getScreenSize().width;
		int height = Toolkit.getDefaultToolkit().getScreenSize().height;
		int windowsWedth = 200;
		int windowsHeight = 150;
		//设置窗体在显示器居中显示
		this.setBounds((width - windowsWedth) / 2,(height - windowsHeight) / 2, windowsWedth, windowsHeight);
		setVisible(true);
        setSize(200, 200);
        setResizable(false);
	}
	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		if(e.getSource()==button1)
		{
			setVisible(false);
			new AddUser();
		}
		if(e.getSource()==button2)
		{
			setVisible(false);
			new AddBook();
		}
		if(e.getSource()==button3)
		{
			setVisible(false);
			new IssueBook();
		}
		if(e.getSource()==button4)
		{
			setVisible(false);
			new SearchFiles();
		}
		if(e.getSource()==button5)
		{
			System.exit(0);
		}
	}
}
