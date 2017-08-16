package chapter05;
import java.awt.Color;
import java.util.Random;
import javax.swing.*;

public class ThreadMove extends Thread {

    String ThreadName;
    JLabel l1;
    JFrame fr;

    public ThreadMove() {
        buildGUI();
    }

    public ThreadMove(String s) {
        super(s);
    }

    public void run() {

       while(true)
       {
        if (Thread.currentThread().getName().equals("RunnerA")) 
        {
            runRunnerA();
            runRunnerB();
            }
       }
    }

    public void runRunnerA() {
        
        for (int i = 10; i < 260; i++) {

            l1.setBounds(i, 10, 120, 30);
            try {
                Thread.sleep(10);
                
            } catch (Exception e) {
                
                System.out.println(e);
            }
        }

    }

    public void runRunnerB() {
       
        for (int i = 260; i>10; i--) {
            l1.setBounds(i, 10, 120, 30);
           
            try {
                Thread.sleep(10);

            } catch (Exception e) {
                System.out.println(e);
            }
        }
    }
    public void buildGUI() {
        fr = new JFrame("Moving objects");
        fr.setVisible(true);
        fr.setSize(400, 200);
        fr.setLayout(null);
        l1 = new JLabel("!!..Congratulations..!!");
        l1.setSize(20, 20);
        l1.setBackground(Color.red);
        l1.setBounds(10, 10, 100, 100);
        fr.add(l1);
               
    }

    public static void main(String args[]) {
        ThreadMove obj = new ThreadMove();
        Thread Runner1 = new Thread(obj);
        Thread Runner2 = new Thread(obj);
        Runner1.setName("RunnerA");
        Runner2.setName("RunnerB");
      
        Runner1.start();
        try {
            Runner1.join();
        } catch (Exception e) {
        }
        Runner2.start();
        try {
            Runner2.join();
        } catch (Exception e) {
        }
    }
}
