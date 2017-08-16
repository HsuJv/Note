
package chapter01;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
public class WindowCloseDemo extends JFrame {

public WindowCloseDemo() {
super("Window Closing Demo");
this.addWindowListener(new WindowCloser());
setSize(300,300);
setVisible(true);
}

private class WindowCloser extends WindowAdapter {
public void windowClosing(WindowEvent windowEvent) {
System.exit(0);
}
}
public static void main(String args[]){
    WindowCloseDemo wcd=new WindowCloseDemo();
}
}

