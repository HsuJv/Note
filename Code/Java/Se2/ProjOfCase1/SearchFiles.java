import java.awt.GridLayout;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;

public class SearchFiles extends JFrame implements ActionListener{
	JFrame MyFrame=new JFrame();
	JPanel MyPanel;
	JTextArea txtArea1,txtArea2,txtArea3;
	JLabel label1,label2,label3;
	JButton button;
	public SearchFiles() {
		txtArea1=new JTextArea();
		txtArea2=new JTextArea();
		txtArea3=new JTextArea();
		MyPanel=new JPanel();
		GridLayout gl=new GridLayout(7,1);	
		MyPanel.setLayout(gl);
		setTitle("Search Files");
		button=new JButton("Back");
		button.addActionListener(this);
		label1=new JLabel("Users' Messages");
		label2=new JLabel("Books' Messages");
		label3=new JLabel("Issue Messages");
		File f1=new File("User.txt");
		setTextArea(f1,txtArea1);
		File f2=new File("Book.txt");
		setTextArea(f2,txtArea2);
		File f3=new File("IssueBook.txt");
		setTextArea(f3,txtArea3);
		MyPanel.add(label1);
		MyPanel.add(txtArea1);
		MyPanel.add(label2);
		MyPanel.add(txtArea2);
		MyPanel.add(label3);
		MyPanel.add(txtArea3);
		MyPanel.add(button);
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
		// TODO Auto-generated method stub
		if(e.getSource()==button)
		{
			setVisible(false);
			new GUI();
		}
	}
	private void setTextArea(File f,JTextArea ta) 
	{
		
		try(FileReader fr=new FileReader(f))
		{
			BufferedReader br=new BufferedReader(fr);
			String str=br.readLine();
			while(str != null)
			{
				str+="\n";
				ta.append(str);
				str=br.readLine();
			}
		}
		catch(IOException e)
		{
			System.out.println(e);
		}
	}
}
