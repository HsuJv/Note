import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
 
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
 
 
public class Calculator extends JFrame implements ActionListener{
 
        
        
         JMenuBar cMenuBar = new JMenuBar();
         JMenu cEdit = new JMenu("编辑(E)");
         JMenu cView = new JMenu("查看(V)");
         JMenu cHelp = new JMenu("帮助(H)");
         JMenuItem cCopy = new JMenuItem("复制(C)");
         JMenuItem cPaste = new JMenuItem("粘贴(P)");
         JMenuItem cStandard = new JMenuItem("标准型");
         JMenuItem cScience = new JMenuItem("科学型");
         JMenuItem cGroup = new JMenuItem("查看分组");
         JMenuItem cHelpItem = new JMenuItem("帮助主题");
         JTextField text = new JTextField("0.",20);
        
         StringBuffer copyBoard = new StringBuffer(20);       //剪贴板
         StringBuffer buff = new StringBuffer();
         StringBuffer memory=new StringBuffer(20);//M系列
        
         boolean isDouble=false;
        
         int preOp,currentOp=0;//标准位
         double op1=0,op2=0;//操作数
        
         JButton bM = new JButton("   ");
         JButton bOther;
         JButton bNumber;
         JButton bOperator;
        
         public Calculator(){
                  
                   super("计 算 器");
                   cMenuBar.setOpaque(true);    // setOpaque(true);设置控件不透明   setOpaque(false);设置控件透明
                  
                   cEdit.setMnemonic(KeyEvent.VK_E);
                   cCopy.setMnemonic(KeyEvent.VK_C);
                   cPaste.setMnemonic(KeyEvent.VK_P);
                   cCopy.addActionListener(this);
                   cPaste.addActionListener(this);
                   cEdit.add(cCopy);
                   cEdit.add(cPaste);
                  
                   cView.setMnemonic(KeyEvent.VK_V);
                   cView.add(cStandard);
                   cView.add(cScience);
                   cView.addSeparator();
                   cView.add(cGroup);
                  
                   cHelp.setMnemonic(KeyEvent.VK_H);
                   cHelpItem.addActionListener(this);
                   cHelp.add(cHelpItem);
                   cMenuBar.add(cEdit);
                   cMenuBar.add(cView);
                   //cMenuBar.addSeparator();  如何添加分隔符
                  
                   cMenuBar.add(cHelp);
                  
                  
                  
                   JPanel cTop = new JPanel();
                   text.setHorizontalAlignment(JTextField.RIGHT);    //text水平对齐方式
                   text.setEditable(false);   //使调用这个函数的控件不能被编辑，如果设为true或者不调用这个函数，则控件可以编辑
                   cTop.add(text);
                  
                   JPanel jp = new JPanel();
                   jp.setLayout(new BorderLayout());
                   JPanel jpLeft = new JPanel();
                   jpLeft.setLayout(new GridLayout(5,1,3,3));
                   bM.setEnabled(false);
                   jpLeft.add(bM);
                  
                   bOther = new JButton("MC");
                   bOther.addActionListener(this);
                   bOther.setForeground(Color.red);
                   bOther.setMargin(new Insets(3,2,3,2));   //setMargin(new Insets(3,2,3,2))  设置按钮边框和标签之间  相当于起点坐标是3,2,然后后面的3,2表示长为3,高为2的一个矩形
                   jpLeft.add(bOther);
                  
                   bOther = new JButton("MR");
                   bOther.addActionListener(this);
                   bOther.setForeground(Color.red);
                   bOther.setMargin(new Insets(3,2,3,2));  
                   jpLeft.add(bOther);
                  
                   bOther = new JButton("MS");
                   bOther.addActionListener(this);
                   bOther.setForeground(Color.red);
                   bOther.setMargin(new Insets(3,2,3,2));  
                   jpLeft.add(bOther);
                  
                   bOther = new JButton("M+");
                   bOther.addActionListener(this);
                   bOther.setForeground(Color.red);
                   bOther.setMargin(new Insets(3,2,3,2));  
                   jpLeft.add(bOther);
                  
                  
                  
                   JPanel jpRight = new JPanel();
                   jpRight.setLayout(new BorderLayout());
                   JPanel jpRUp = new JPanel();
                   jpRUp.setLayout(new GridLayout(1,3,3,3));
                   bOther = new JButton("BackSpace");
                   bOther.addActionListener(this);
                   bOther.setForeground(Color.red);
                   bOther.setMargin(new Insets(3,2,3,2));
                   jpRUp.add(bOther);
                  
                   bOther = new JButton("CE");
                   bOther.addActionListener(this);
                   bOther.setForeground(Color.red);
                   bOther.setMargin(new Insets(3,2,3,2));
                   jpRUp.add(bOther);
                  
                   bOther = new JButton("C");
                   bOther.addActionListener(this);
                   bOther.setForeground(Color.red);
                   bOther.setMargin(new Insets(3,2,3,2));
                   jpRUp.add(bOther);
                  
                   JPanel jpRDown = new JPanel();
                   JPanel jpRDowns1 = new JPanel();
                   jpRDowns1.setLayout(new GridLayout(4,3,3,2));
                   JPanel jpRDowns2 = new JPanel();
                   jpRDowns2.setLayout(new GridLayout(4,2,3,2));
                   for(int i=9;i>=0;i--){
                            bNumber = new JButton(""+i);
                            bNumber.addActionListener(this);
                            bNumber.setBackground(Color.blue);
                            bNumber.setMargin(new Insets(3,3,3,3));
                            jpRDowns1.add(bNumber);
                   }
                   bOperator = new JButton(".");
                   bOperator.addActionListener(this);
                   bOperator.setBackground(Color.red);
                  bOperator.setMargin(new Insets(3,3,3,3));
                   jpRDowns1.add(bOperator);
                  
                   bOperator = new JButton("+/-");
                   bOperator.addActionListener(this);
                   bOperator.setBackground(Color.red);
                   bOperator.setMargin(new Insets(3,3,3,3));
                   jpRDowns1.add(bOperator);
                 
                   bOperator = new JButton("/");
                   bOperator.addActionListener(this);
                   bOperator.setBackground(Color.red);
                   bOperator.setMargin(new Insets(3,3,3,3));
                   jpRDowns2.add(bOperator);
                  
                   bOperator = new JButton("sqrt");
                   bOperator.addActionListener(this);
                   bOperator.setBackground(Color.red);
                   bOperator.setMargin(new Insets(3,3,3,3));
                   jpRDowns2.add(bOperator);
                  
                   bOperator = new JButton("*");
                   bOperator.addActionListener(this);
                   bOperator.setBackground(Color.red);
                   bOperator.setMargin(new Insets(3,3,3,3));
                   jpRDowns2.add(bOperator);
                  
                   bOperator = new JButton("%");
                   bOperator.addActionListener(this);
                   bOperator.setBackground(Color.red);
                   bOperator.setMargin(new Insets(3,3,3,3));
                   jpRDowns2.add(bOperator);
                  
                   bOperator = new JButton("-");
                   bOperator.addActionListener(this);
                   bOperator.setBackground(Color.red);
                   bOperator.setMargin(new Insets(3,3,3,3));
                   jpRDowns2.add(bOperator);
                  
                   bOperator = new JButton("1/X");
                   bOperator.addActionListener(this);
                   bOperator.setBackground(Color.red);
                   bOperator.setMargin(new Insets(3,3,3,3));
                   jpRDowns2.add(bOperator);
                  
                   bOperator = new JButton("+");
                   bOperator.addActionListener(this);
                   bOperator.setBackground(Color.red);
                   bOperator.setMargin(new Insets(3,3,3,3));
                   jpRDowns2.add(bOperator);
                  
                   bOperator = new JButton("=");
                   bOperator.addActionListener(this);
                   bOperator.setBackground(Color.red);
                   bOperator.setMargin(new Insets(3,3,3,3));
                   jpRDowns2.add(bOperator);
                   jpRDown.setLayout(new BorderLayout());
                  
                   jpRDown.add(BorderLayout.CENTER,jpRDowns1);
                   jpRDown.add(BorderLayout.EAST,jpRDowns2);
                   jpRight.add(BorderLayout.NORTH,jpRUp);
                   jpRight.add(BorderLayout.SOUTH,jpRDown);
                  
                   setJMenuBar(cMenuBar);
                   jp.add(BorderLayout.WEST,jpLeft);
                   jp.add(BorderLayout.EAST,jpRight);
                  
                                    
                   add(BorderLayout.NORTH,cTop);
                   add(BorderLayout.SOUTH,jp);
         }
        
        
        
    public void actionPerformed(ActionEvent e){
            
                   String str = e.getActionCommand();    // getActionCommand()返回与此动作相关的命令字符串
                  
                  
                   if(str.equals("复制(C)")){
                            String temp = text.getText().trim();    //trim() 返回字符串的副本，忽略前导空白和尾部空白
                           
                           
                           
                            copyBoard.replace(0,copyBoard.length(),temp);
                            cPaste.setEnabled(true);
                   }
                   else  if(str.equals("粘贴(P)")){
                           
                           
                            text.setText(copyBoard.toString());
                   }
                   else if(str.equals("帮助主题")){
                           
                            JOptionPane.showMessageDialog(this, " 1.CE :清除文本框                                                                   2.BackSpace :回删刚输入数字\n " +
                                               "3.C :删除当前计算                                                                  4.MC :清除缓冲区\n " +
                                               "5.MR :恢复缓冲区的数到文本框                                         6.MS :将文本框的数存入缓冲区\n" +
                                               "7.M+ :将文本框值与缓冲区的数相加但不显示结果        8. 1/x :将文本框中的数据为它的倒数\n" +
                                               "9.sqrt:将文本框中的内容求平方根                                     10.+/- :负数符号");
                   }
                   else if(str.equals("CE")){
                            text.setText("0.");
                   }
                   else if(str.equals("BackSpace")){
                            if(!text.getText().trim().equals("0.")){
                                     if(buff.length()!=1&&buff.length()!=0){
                                               text.setText(buff.delete(buff.length()-1, buff.length()).toString());
                                     }
                                     else
                                     {
                                               text.setText("0.");
                                               buff.setLength(0);
                                     }
                            }
                            op2 = Double.parseDouble(text.getText().trim());
                   }
                   else if(str.equals("C")){
                            text.setText("0.");                 //?????
                            op1 = op2 = 0;
                            buff.replace(0, buff.length(), " ");
                            preOp = currentOp = 0;
                   }
                   else if(str.equals("MC")){
                            String temp = " ";
                            memory.replace(0, memory.length(), temp);
                            bM.setText("   ");
                   }
                   else if(str.equals("MR")){
                            text.setText(memory.toString());
                   }
                   else if(str.equals("MS")){
                            String temp = text.getText().trim();
                            memory.replace(0, memory.length(), temp);
                            bM.setText("M");
                   }
                   else if(str.equals("M+")){
                            String temp1 = text.getText().trim();
                            Double num = Double.parseDouble(temp1);
                            String temp2 = memory.toString();
                            num += Double.parseDouble(temp2);
                             temp1 = String.valueOf(num);
                            memory.replace(0, memory.length(), temp1);
                   }
                   else if(str.equals("1/X")){
                            String temp = text.getText().trim();
                            Double ctemp = Double.parseDouble(temp);
                            text.setText(""+1/ctemp);
                   }
                   else if(str.equals("+/-")){
                            if((text.getText().trim().indexOf("+")!=-1)||(text.getText().trim().indexOf("-")!=-1)){}
                            else{
                                     String s="-";
                                     text.setText((buff.append(""+s)).toString());
                            }
                   }
                   else if(str.equals("%")){
                            buff.setLength(0);
                            if(currentOp==0){
                                     preOp = currentOp = 5;
                                     op2 = 0;
                                     text.setText(""+op1);
                            }
                            else
            {
                currentOp = preOp;
                preOp = 5;
                switch(currentOp){
                case 1:op1 += op2;text.setText(""+op1+"+");break;
                case 2:op1 -= op2;text.setText(""+op1);break;
                case 3:op1 *= op2;text.setText(""+op1);break;
                case 4:op1 /= op2;text.setText(""+op1);break;
                case 5:op1=Math.IEEEremainder(op1, op2);text.setText(""+op1);break;
                }
                           
                   }
                   }
                   else if(str.equals("sqrt")){
                            String temp = text.getText().trim();
                            Double ctemp = Double.parseDouble(temp);
                            text.setText(""+Math.sqrt(ctemp));
                   }
                   else if(str.equals("+")){
                            buff.setLength(0);
                            if(currentOp==0)
            {
                preOp = currentOp = 1;
                op2 = 0;
                text.setText(""+op1);
            }
            else
            {
                currentOp = preOp;
                preOp = 1;
                switch(currentOp){
                case 1:op1 += op2;text.setText(""+op1);break;
                case 2:op1 -= op2;text.setText(""+op1);break;
                case 3:op1 *= op2;text.setText(""+op1);break;
                case 4:op1 /= op2;text.setText(""+op1);break;
                case 5:op1=Math.IEEEremainder(op1, op2);text.setText(""+op1);break;
                }
            }
 
                           
                   }
                   else if(str.equals("-")){
                            buff.setLength(0);
                            if(currentOp==0){
                                     preOp=currentOp=2;
                                     op2=0;
                                     text.setText(""+op1);
                            }
                            else{
                                     currentOp = preOp;
                                     preOp = 2;
                                     switch(currentOp){
                                     case 1:op1 += op2; text.setText(""+op1);break;
                                     case 2:op1 -= op2; text.setText(""+op1);break;
                                     case 3:op1 *= op2; text.setText(""+op1);break;
                                     case 4:op1 /= op2; text.setText(""+op1);break;
                                     case 5:op1=Math.IEEEremainder(op1, op2);text.setText(""+op1);break;
                                     }
                            }
                   }
                   else if(str.equals("*")){
                            buff.setLength(0);
                            if(currentOp==0){
                                     preOp = currentOp = 3;
                                     op2 = 0;
                                     text.setText(""+op1);
                            }
                            else{
                                     currentOp = preOp;
                                     preOp = 3;
                                     switch(currentOp){
                                     case 1:op1 += op2; text.setText(""+op1);break;
                                     case 2:op1 -= op2; text.setText(""+op1);break;
                                     case 3:op1 *= op2; text.setText(""+op1);break;
                                     case 4:op1 /= op2; text.setText(""+op1);break;
                                     case 5:op1=Math.IEEEremainder(op1, op2);text.setText(""+op1);break;
                                     }
                            }
                   }
                   else if(str.equals("/")){
                            buff.setLength(0);
                            if(currentOp==0){
                                     preOp = currentOp = 4;
                                     op2 = 0;
                                     text.setText(""+op1);
                            }
                            else{
                                     currentOp = preOp;
                                     preOp = 4;
                                     switch(currentOp){
                                     case 1:op1 += op2; text.setText(""+op1);break;
                                     case 2:op1 -= op2; text.setText(""+op1);break;
                                     case 3:op1 *= op2; text.setText(""+op1);break;
                                     case 4:op1 /= op2; text.setText(""+op1);break;
                                     case 5:op1=Math.IEEEremainder(op1, op2);text.setText(""+op1);break;
                                     }
                            }
                   }
                   else if(str.equals("="))// =
        {
            if(currentOp==0)
            {
                buff.setLength(0);
                text.setText(""+op2);
            }
            else
            {
                buff.setLength(0);
                currentOp =preOp;
                switch(currentOp){
                          case 1:op1=op1+op2;text.setText(""+op1);break;
                          case 2:op1=op1-op2;text.setText(""+op1);break;
                          case 3:op1=op1*op2;text.setText(""+op1);break;
                          case 4:op1=op1/op2;text.setText(""+op1);break;
                          case 5:op1=Math.IEEEremainder(op1, op2);text.setText(""+op1);break;
                }
                currentOp=0;
                op2=0;
            }
        }
                   else if(str.equals(".")){
                             isDouble=true;
                             //text.setText((buff.append("0"+str)).toString());
                            if(text.getText().trim().indexOf(".")!=-1){
                                    
                            }
                            else{
                                     text.setText((buff.append(""+str)).toString());
                                    
                                    
                            }
                            System.out.println(str);
                   }
                   else if(str.equals("0"))//如果选择的是"0"这个数字键
        {
            if(text.getText().trim().equals("0.")){
                    
                      text.setText(buff.append("0").toString());
            }
            else{
                text.setText(buff.append(str).toString());
                op2=Double.parseDouble(text.getText().trim());
                if(currentOp==0)
                    op1=op2;
            }
        }        
 
                   else{
            text.setText(buff.append(str).toString());    //append()将指定的字符串追加到此字符序列
            op2=Double.parseDouble(text.getText().trim());
            if(currentOp==0)
                op1=op2;
        }
 
         }
   
         public static void main(String[] args) {
                   // TODO Auto-generated method stub
                   Calculator frame = new Calculator();
                   frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(282,260);
        frame.setResizable(false);    //setResizable(false)设置窗体不可改变大小
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
 
         }
 
}