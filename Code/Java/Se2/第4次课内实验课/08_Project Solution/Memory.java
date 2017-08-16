//package gameconsole;

import java.awt.*;
import java.awt.event.*;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;
import javax.swing.*;

public class Memory extends JFrame {

    static JLabel guessLabel = new JLabel(); 	//so the value does not change.
    static JLabel label0 = new JLabel();
    static JLabel label1 = new JLabel();
    static JLabel label2 = new JLabel();
    static JLabel label3 = new JLabel();
    static JLabel label4 = new JLabel();
    static JLabel label5 = new JLabel();
    static JLabel label6 = new JLabel();
    static JLabel label7 = new JLabel();
    static JLabel label8 = new JLabel();
    static JLabel label9 = new JLabel();
    static JLabel label10 = new JLabel();
    static JLabel label11 = new JLabel();
    static JLabel label12 = new JLabel();
    static JLabel label13 = new JLabel();
    static JLabel label14 = new JLabel();
    static JLabel label15 = new JLabel();
    static JLabel[] boxLabel = new JLabel[16];
    static ImageIcon apple = new ImageIcon("apple.gif");
    static ImageIcon banana = new ImageIcon("banana.gif");
    static ImageIcon cherry = new ImageIcon("cherry.gif");
    static ImageIcon grape = new ImageIcon("grape.gif");
    static ImageIcon lemon = new ImageIcon("lemon.gif");
    static ImageIcon orange = new ImageIcon("orange.gif");
    static ImageIcon pear = new ImageIcon("pear.gif");
    static ImageIcon plum = new ImageIcon("plum.gif");
    static ImageIcon backing = new ImageIcon("backing.gif");
    static ImageIcon[] choiceIcon = new ImageIcon[8];
    static JButton newButton = new JButton();
    static JButton exitButton = new JButton();
    
    
    static Random myRandom = new Random();
    static int choice;
    static int index;
    static int[] picked = new int[2];
    static int[] behind = new int[16];
    static int guesses;
    static int remaining;
    static Timer delayTimer;



    public Memory() {
        // frame constructor
        setVisible(true);
        setTitle("Memory Game");
        // setResizable(false);
        getContentPane().setBackground(Color.BLUE);		//for background color.
        addWindowListener(new WindowAdapter() //for closing window. 
        {
            public void windowClosing(WindowEvent evt) {
                exitForm(evt);
            }
        });
        getContentPane().setLayout(new GridBagLayout());		//Layout : Gridbag layout,to add boxes. 

        // position controls
        GridBagConstraints gridConstraints = new GridBagConstraints();
        guessLabel.setText("Guesses: 0");					//will be displayed on frame
        guessLabel.setForeground(Color.WHITE);			//Guessses will be displayed in white.by default it is black		
        guessLabel.setFont(new Font("Arial", Font.BOLD, 18));	//Font of guesses.
        gridConstraints.gridx = 1;
        gridConstraints.gridy = 0;
        gridConstraints.gridwidth = 2;
       
        getContentPane().add(guessLabel, gridConstraints);		//Adding.
        boxLabel[0] = label0;
        boxLabel[1] = label1;
        boxLabel[2] = label2;
        boxLabel[3] = label3;
        boxLabel[4] = label4;
        boxLabel[5] = label5;
        boxLabel[6] = label6;
        boxLabel[7] = label7;
        boxLabel[8] = label8;
        boxLabel[9] = label9;
        boxLabel[10] = label10;
        boxLabel[11] = label11;
        boxLabel[12] = label12;
        boxLabel[13] = label13;
        boxLabel[14] = label14;
        boxLabel[15] = label15;
        int x = 0;
        int y = 1;						//set to one to avoid overlap.
        for (int i = 0; i < 16; i++) //To set the positon of sixteen buttons.
        {
            gridConstraints = new GridBagConstraints();
            boxLabel[i].setPreferredSize(new Dimension(100, 100));		//size of each button.
            boxLabel[i].setIcon(backing);					//image has been added at each box.
            gridConstraints.gridx = x;
            gridConstraints.gridy = y;
            gridConstraints.insets = new Insets(5, 5, 5, 5);		//space between each button.
            getContentPane().add(boxLabel[i], gridConstraints);
            boxLabel[i].addMouseListener(new MouseAdapter() //Mouse listner has been applied at each box.
            {
                public void mouseClicked(MouseEvent e) {
                    labelMouseClicked(e);
                }
            });
            x++;
            if (x > 3) {
                x = 0;
                y += 1;
            }
        }
    
        newButton.setText("New Game");
        
        gridConstraints = new GridBagConstraints();
        gridConstraints.gridx = 1;
        gridConstraints.gridy = 6;
        gridConstraints.gridwidth = 2;
        gridConstraints.insets = new Insets(10, 10, 10, 10);
        getContentPane().add(newButton, gridConstraints);
        
        
        newButton.addActionListener(new ActionListener() //action listner on buttons. 
        {
            public void actionPerformed(ActionEvent e) {
                newButtonActionPerformed(e);
            }
        });
        exitButton.setText("Exit");
        
        
        gridConstraints = new GridBagConstraints();
        gridConstraints.gridx = 1;
        gridConstraints.gridy = 7;
        gridConstraints.gridwidth = 2;
        gridConstraints.insets = new Insets(0, 10, 10, 10);
        getContentPane().add(exitButton, gridConstraints);
        exitButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                exitButtonActionPerformed(e);
            }
        });

        delayTimer = new Timer(1, new ActionListener() //if we choose wrong image then image will again get hidden again.
        {
            public void actionPerformed(ActionEvent e) {
                delayTimerActionPerformed(e);
            }
        });

        pack();								//full visibility of Jframe.
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();	//setting of screen co-ordinate.
        setBounds((int) (0.5 * (screenSize.width - getWidth())), (int) (0.5 * (screenSize.height - getHeight())), getWidth(), getHeight());

        choiceIcon[0] = apple;
        choiceIcon[1] = banana;
        choiceIcon[2] = cherry;
        choiceIcon[3] = grape;
        choiceIcon[4] = lemon;
        choiceIcon[5] = orange;
        choiceIcon[6] = pear;
        choiceIcon[7] = plum;

    }

    private void labelMouseClicked(MouseEvent e) {
        Component clickedComponent = e.getComponent();
        for (index = 0; index < 16; index++) {
            if (clickedComponent == boxLabel[index]) {
                break;
            }
        }
        // If trying to pick same box, picking already selected box
        // or trying pick when not playing, exit
        if ((choice == 1 && index == picked[0]) || behind[index] == -1 || newButton.isEnabled()) //untill we choose anything new button stays enabled. 
        {
            return;
        }
        // Display selected picture
        boxLabel[index].setIcon(choiceIcon[behind[index]]);
        if (choice == 0) {
            picked[0] = index;
            choice = 1;
            return;
        }
        // use timer to process remaining code to allow
        // label control to refresh
        delayTimer.start();
    }

    private void newButtonActionPerformed(ActionEvent e) {
        guesses = 0;
        remaining = 8;
        guessLabel.setText("Guesses: 0");
        // Randomly sort 16 integers using Shuffle routine
        // Behind contains indexes (0 to 7) for hidden pictures
        behind = sortIntegers(16);
        for (int i = 0; i < 16; i++) {
            // reset image
            boxLabel[i].setIcon(backing);
            if (behind[i] > 7) {
                behind[i] = behind[i] - 8;
            }
        }
        choice = 0;
        newButton.setEnabled(false);		//new game button is disabled when the game is started.
        exitButton.setText("Stop");
    }

    private void exitButtonActionPerformed(ActionEvent e) {
        if (exitButton.getText().equals("Exit")) {
            exitForm(null);
            
        } else {
            exitButton.setText("Exit");
            newButton.setEnabled(true);			//new game button is enabled.
        }
    }

    private void exitForm(WindowEvent evt) {
        this.dispose();
            GameMenu obj = new GameMenu();
            obj.addComponent();
    }

    private void delayTimerActionPerformed(ActionEvent e) {
        // finish processing of display
        delayTimer.stop();
        guesses++;
        guessLabel.setText("Guesses: " + String.valueOf(guesses));

        picked[1] = index;
        if (behind[picked[0]] == behind[picked[1]]) {
                       
            behind[picked[0]] = -1;
            behind[picked[1]] = -1;
            remaining--;
        } else {
            // If no match, blank picture, restore backs
            
            // delay 1 second
            long t = System.currentTimeMillis();
            do {
            } while (System.currentTimeMillis() - t < 1000);
            boxLabel[picked[0]].setIcon(backing);
            boxLabel[picked[1]].setIcon(backing);
        }
        choice = 0;
        if (remaining == 0) {
            exitButton.doClick();
            newButton.requestFocus();
            try (BufferedWriter bw = new BufferedWriter(new FileWriter("MemoryScore.txt", true))) {


                bw.append("\n" + StartMemory.s1 + " " + guesses);

                bw.append("\n--------------------------");
                try (BufferedReader bf = new BufferedReader(new FileReader("MemoryScore.txt"))) {
                    String stringSearch = StartMemory.s1;
                    
                    String line;
                    String line1;
                    int flag = 2;
                    int flag1 =0;
                    int linecount = 0;
                    double temp = 0.0;
                    double sum = 0.0;
                    while ((line = bf.readLine()) != null) {
                        String txt[] = line.split(" ");
                        for (int i = 0; i < txt.length; i++) {
                            if(txt[i].equals(stringSearch)) {
                                   flag1 = 1;
                                temp = Double.parseDouble(txt[i + 1]);
                                linecount++;

                            } 
                            
                            
                        }
                                            
                        
                        if (guesses < temp) {
                            flag = 0;
                        }
                        if (guesses > temp) {
                            flag = 1;
                        }
                        if (flag == 2) {
                            
                        }
                    }
                    if (flag == 1) {
                        if (flag1==0){
                            
                        JOptionPane.showMessageDialog(null,"This is your first game"+"\n"+"Your Score is:"+guesses);
                        
                    }else{
                            JOptionPane.showMessageDialog(null, "You need to work hard."+"\n"+"Your Score is:"+guesses);
                        }
                    }
                    if (flag == 0) {
                        JOptionPane.showMessageDialog(null, "You have scored better."+"\n"+"Your Score is:"+guesses);
                    }
                    



                } catch (IOException e2) {
                }

            } catch (Exception e1) {
            }
        }
    }

    private static int[] sortIntegers(int n) {
        /*
         *  Returns n randomly sorted integers 0 -> n - 1
         */
        int nArray[] = new int[n];
        int temp, s;
        Random myRandom = new Random();
        //  initialize array from 0 to n - 1
        for (int i = 0; i < n; i++) {
            nArray[i] = i;
        }
        //  i is number of items remaining in list
        for (int i = n; i >= 1; i--) {
            s = myRandom.nextInt(i);
            temp = nArray[s];
            nArray[s] = nArray[i - 1];
            nArray[i - 1] = temp;
        }
        return (nArray);
    }
}
