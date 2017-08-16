//package gameconsole;

import java.awt.Color;
import java.awt.Cursor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.Random;
import java.util.TimerTask;
import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import java.util.Timer;
import javax.swing.TransferHandler;

public class JigsawPuzzle extends JFrame implements ActionListener 
{

    JLabel lbl1, lbl2, lbl3, lbl4, lbl5, lbl6, lbl7, lbl8, timer;
    JButton btn_start, btn_submit;
    String path1, path2, path3, path4, p1, p2, p3, p4;
    Random rnd;
    Timer countdown;
    MyTask t;
    int remaining = 10;
    ArrayList status;
    int img;
    int flag = 0;
    public int times;
    int score, temp1, temp2, temp3, temp4;

    public JigsawPuzzle() 
    {
        String prevScore = null;

        File f = new File("PuzzleScore.txt");
        if (f.exists()) 
        {
            try (BufferedReader bf = new BufferedReader(new FileReader("PuzzleScore.txt"))) 
            {
                String stringSearch = StartPuzzle.s1;
                flag = 0;
                String line;
                while ((line = bf.readLine()) != null) 
                {
                    String txt[] = line.split(" ");

                    if (flag == 1) 
                    {
                        prevScore = txt[1];
                        flag = 0;
                        continue;
                    }

                    for (int i = 0; i < txt.length; i++) 
                    {

                        if (txt[i].equals(stringSearch)) 
                        {

                            flag = 1;

                        }
                    }

                }
                
                
            } 
            catch (Exception e) 
            {
                
            }
        }

        rnd = new Random();
        score = 0;

        lbl1 = new JLabel();
        lbl2 = new JLabel();
        lbl3 = new JLabel();
        lbl4 = new JLabel();
        lbl5 = new JLabel();
        lbl6 = new JLabel();
        lbl7 = new JLabel();
        lbl8 = new JLabel();

        timer = new JLabel("Time Left: ");
        t = new MyTask();
        countdown = new Timer();

        btn_start = new JButton("Start");
        btn_start.addActionListener(this);
        btn_submit = new JButton("Submit");
        btn_submit.addActionListener(this);

        setLayout(null);
        setTitle("Jigsaw Puzzle");
        setLocationRelativeTo(null);

        timer.setBounds(420, 3, 100, 10);
        add(timer);

        lbl1.setBounds(10, 20, 120, 120);
        lbl1.setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));
        add(lbl1);
        lbl2.setBounds(129, 20, 120, 120);
        lbl2.setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));
        add(lbl2);
        lbl3.setBounds(10, 139, 120, 120);
        lbl3.setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));
        add(lbl3);
        lbl4.setBounds(129, 139, 120, 120);
        lbl4.setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));
        add(lbl4);

        lbl5.setBounds(300, 20, 120, 120);
        lbl5.setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));
        add(lbl5);
        lbl6.setBounds(419, 20, 120, 120);
        lbl6.setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));
        add(lbl6);
        lbl7.setBounds(300, 139, 120, 120);
        lbl7.setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));
        add(lbl7);
        lbl8.setBounds(419, 139, 120, 120);
        lbl8.setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));
        add(lbl8);

        btn_start.setBounds(80, 270, 100, 25);
        add(btn_start);

        btn_submit.setBounds(370, 270, 100, 25);
        add(btn_submit);

        status = new ArrayList();
        status.clear();
        
        WindowListener wl = new WindowAdapter()
        {
            public void windowClosing(WindowEvent e)
            {
                try (BufferedWriter bw = new BufferedWriter(new FileWriter("PuzzleScore.txt", true))) 
                {
                    bw.append("Player Name: " + StartPuzzle.s1);
                    bw.newLine();
                    bw.append("Score: " + score);
                    bw.newLine();
                    DateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy HH:mm");
                    Date date = new Date();
                    bw.append("Played at: " + dateFormat.format(date));
                    bw.newLine();
                    bw.append("------------------------------------------------------");
                    bw.newLine();
                } 
                catch (Exception ex) 
                {
                    
                }
                countdown.cancel();
                GameMenu obj = new GameMenu();
                obj.addComponent();
            }
        };

        MouseListener ml = new MouseAdapter() 
        {
            public void mousePressed(MouseEvent e) 
            {

                lbl1.setTransferHandler(new TransferHandler("icon"));
                lbl2.setTransferHandler(new TransferHandler("icon"));
                lbl3.setTransferHandler(new TransferHandler("icon"));
                lbl4.setTransferHandler(new TransferHandler("icon"));

                if ((e.getSource() == lbl1) || (e.getSource() == lbl2) || (e.getSource() == lbl3) || (e.getSource() == lbl4)) 
                {
                    JComponent jc = (JComponent) e.getSource();
                    TransferHandler handler = jc.getTransferHandler();
                    handler.exportAsDrag(jc, e, TransferHandler.COPY);
                }
                if (e.getSource() == lbl1) 
                {
                    lbl2.setTransferHandler(new TransferHandler(""));
                    lbl3.setTransferHandler(new TransferHandler(""));
                    lbl4.setTransferHandler(new TransferHandler(""));
                } 
                else if (e.getSource() == lbl2) 
                {
                    lbl1.setTransferHandler(new TransferHandler(""));
                    lbl3.setTransferHandler(new TransferHandler(""));
                    lbl4.setTransferHandler(new TransferHandler(""));
                } 
                else if (e.getSource() == lbl3) 
                {
                    lbl1.setTransferHandler(new TransferHandler(""));
                    lbl2.setTransferHandler(new TransferHandler(""));
                    lbl4.setTransferHandler(new TransferHandler(""));
                } 
                else if (e.getSource() == lbl4) 
                {
                    lbl1.setTransferHandler(new TransferHandler(""));
                    lbl2.setTransferHandler(new TransferHandler(""));
                    lbl3.setTransferHandler(new TransferHandler(""));
                } 
                else 
                {
                    e.consume();
                }
            }
        };

        lbl1.addMouseListener(ml);
        lbl2.addMouseListener(ml);
        lbl3.addMouseListener(ml);
        lbl4.addMouseListener(ml);

        lbl1.setTransferHandler(new TransferHandler("icon"));
        lbl2.setTransferHandler(new TransferHandler("icon"));
        lbl3.setTransferHandler(new TransferHandler("icon"));
        lbl4.setTransferHandler(new TransferHandler("icon"));
        lbl5.setTransferHandler(new TransferHandler("icon"));
        lbl6.setTransferHandler(new TransferHandler("icon"));
        lbl7.setTransferHandler(new TransferHandler("icon"));
        lbl8.setTransferHandler(new TransferHandler("icon"));
        
        this.addWindowListener(wl);
        setSize(565, 350);
        setVisible(true);
        setResizable(false);
        
        getContentPane().setBackground(Color.white);
        setLocationRelativeTo(null);
        
        if (prevScore != null) 
                {
                    JOptionPane.showMessageDialog(this, "Your previous score was " + prevScore, "Previous Score", JOptionPane.INFORMATION_MESSAGE);
                }


    }

    class MyTask extends TimerTask 
    {
        public int times = 61;

        public void run() 
        {
            times--;
            timer.setText("Time Left: " + times);

            if (times == 0) 
            {
                this.cancel();

                try (BufferedWriter bw = new BufferedWriter(new FileWriter("PuzzleScore.txt", true))) 
                {
                    bw.append("Player Name: " + StartPuzzle.s1);
                    bw.newLine();
                    bw.append("Score: " + score);
                    bw.newLine();
                    DateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy HH:mm");
                    Date date = new Date();
                    bw.append("Played at: " + dateFormat.format(date));
                    bw.newLine();
                    bw.append("------------------------------------------------------");
                    bw.newLine();
                } 
                catch (Exception ex) 
                {
                    
                }

                int n = JOptionPane.showConfirmDialog(JigsawPuzzle.this, "Time Over!\nYour final score is " + score + "\nDo you want to play again?", "Confirmation", JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE);

                if (n == 0) 
                {
                    JigsawPuzzle.this.dispose();
                    status.clear();
                    JigsawPuzzle obj = new JigsawPuzzle();
                } 
                else 
                {
                    JigsawPuzzle.this.dispose();
                    status.clear();
                    GameMenu obj = new GameMenu();
                    obj.addComponent();
                }
            }
        }
    }

    public void generatePath() 
    {
        img = rnd.nextInt(6);
        Iterator it = status.iterator();

        if (img == 0) 
        {
            while (img == 0) 
            {
                img = rnd.nextInt(6);
                while (it.hasNext()) 
                {
                    if (img == (Integer) it.next()) 
                    {
                        generatePath();

                    }
                }
              }
        } 
        else 
        {
            while (it.hasNext()) 
            {
                if (img == (Integer) it.next()) 
                {
                    generatePath();
                }
            }
        }
  }

    public void generateImage() 
    {
        flag = 0;

        p1 = "src/Image_" + img + "/1.gif";
        p2 = "src/Image_" + img + "/2.gif";
        p3 = "src/Image_" + img + "/3.gif";
        p4 = "src/Image_" + img + "/4.gif";

        temp1 = rnd.nextInt(5);

        while (temp1 == 0) 
        {
            temp1 = rnd.nextInt(5);
        }
        path1 = "src/Image_" + img + "/" + temp1 + ".gif";

        temp2 = rnd.nextInt(5);

        while ((temp2 == temp1) || (temp2 == 0)) 
        {
            temp2 = rnd.nextInt(5);
        }
        path2 = "src/Image_" + img + "/" + temp2 + ".gif";

        temp3 = rnd.nextInt(5);

        while ((temp3 == temp1) || (temp3 == temp2) || (temp3 == 0)) 
        {
            temp3 = rnd.nextInt(5);
        }
        path3 = "src/Image_" + img + "/" + temp3 + ".gif";

        temp4 = rnd.nextInt(5);

        while ((temp4 == temp1) || (temp4 == temp2) || (temp4 == temp3) || (temp4 == 0)) 
        {
            temp4 = rnd.nextInt(5);

        }
        path4 = "src/Image_" + img + "/" + temp4 + ".gif";


        if ((temp1 == 1) && (temp2 == 2) && (temp3 == 3) && (temp4 == 4)) 
        {
            generateImage();
        }
        if ((temp1 == 1) && (temp2 == 2)) 
        {
            generateImage();
        }
        if ((temp3 == 3) && (temp4 == 4)) 
        {
            generateImage();
        }
        if ((temp1 == 1) && (temp3 == 3)) 
        {
            generateImage();
        }
        if ((temp2 == 2) && (temp4 == 4)) 
        {
            generateImage();
        }
        if ((temp1 == 3) && (temp2 == 4)) 
        {
            generateImage();
        }
        if ((temp3 == 1) && (temp4 == 2)) 
        {
            generateImage();
        }
        if ((temp1 == 2) && (temp3 == 4)) 
        {
            generateImage();
        }
        if ((temp2 == 1) && (temp4 == 3)) 
        {
            generateImage();
        }

    }

    public void actionPerformed(ActionEvent e) 
    {

        if (e.getSource() == btn_start) 
        {
            countdown.schedule(t, 0, 1000);

            generatePath();
            status.add(img);
            generateImage();

            lbl1.setIcon(new ImageIcon(path1));
            lbl2.setIcon(new ImageIcon(path2));
            lbl3.setIcon(new ImageIcon(path3));
            lbl4.setIcon(new ImageIcon(path4));
            lbl5.setIcon(null);
            lbl6.setIcon(null);
            lbl7.setIcon(null);
            lbl8.setIcon(null);

            lbl1.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
            lbl2.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
            lbl3.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
            lbl4.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));

            btn_start.setEnabled(false);

        } 
        else if (e.getSource() == btn_submit) 
        {
            try 
            {
                if ((lbl5.getIcon() == null) || (lbl6.getIcon() == null) || (lbl7.getIcon() == null) || (lbl8.getIcon() == null)) 
                {
                    JOptionPane.showMessageDialog(this, "Please fill all the images", "Warning Message", JOptionPane.WARNING_MESSAGE);

                } 
                else if ((lbl5.getIcon().toString().equals(p1)) && (lbl6.getIcon().toString().equals(p2)) && (lbl7.getIcon().toString().equals(p3)) && (lbl8.getIcon().toString().equals(p4))) 
                {

                    flag = 0;
                    score += 10;

                    JOptionPane.showMessageDialog(this, "Correct Match", "Information Message", JOptionPane.INFORMATION_MESSAGE);
                    
                    if (score == 50) 
                    {
                        countdown.cancel();
                        try (BufferedWriter bw = new BufferedWriter(new FileWriter("PuzzleScore.txt", true))) 
                        {
                            bw.append("Player Name: " + StartPuzzle.s1);
                            bw.newLine();
                            bw.append("Score: " + score);
                            bw.newLine();
                            DateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy HH:mm");
                            Date date = new Date();
                            bw.append("Played at: " + dateFormat.format(date));
                            bw.newLine();
                            bw.append("------------------------------------------------------");
                            bw.newLine();
                        } 
                        catch (Exception ex) 
                        {
                            
                        }
                        
                        int n = JOptionPane.showConfirmDialog(this, "You won the game!\nYour final score is " + score + "\nDo you want to play again?", "Confirmation", JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE);
                        
                        if (n == 0) 
                        {
                            this.dispose();
                            countdown.cancel();
                            status.clear();
                            JigsawPuzzle obj = new JigsawPuzzle();

                        } 
                        else 
                        {
                            this.dispose();
                            GameMenu obj = new GameMenu();
                            obj.addComponent();
                        }
                    } 
                    else 
                    {
                        generatePath();
                        status.add(img);
                        generateImage();
                        
                        lbl1.setIcon(new ImageIcon(path1));
                        lbl2.setIcon(new ImageIcon(path2));
                        lbl3.setIcon(new ImageIcon(path3));
                        lbl4.setIcon(new ImageIcon(path4));
                        lbl5.setIcon(null);
                        lbl6.setIcon(null);
                        lbl7.setIcon(null);
                        lbl8.setIcon(null);

                        lbl1.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
                        lbl2.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
                        lbl3.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
                        lbl4.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
                    }
                } 
                else 
                {
                    JOptionPane.showMessageDialog(this, "Incorrect Match");
                }
            } 
            catch (Exception ex) 
            {
                
            }
        }
    }
}
