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
         JMenu cEdit = new JMenu("�༭(E)");
         JMenu cView = new JMenu("�鿴(V)");
         JMenu cHelp = new JMenu("����(H)");
         JMenuItem cCopy = new JMenuItem("����(C)");
         JMenuItem cPaste = new JMenuItem("ճ��(P)");
         JMenuItem cStandard = new JMenuItem("��׼��");
         JMenuItem cScience = new JMenuItem("��ѧ��");
         JMenuItem cGroup = new JMenuItem("�鿴����");
         JMenuItem cHelpItem = new JMenuItem("��������");
         JTextField text = new JTextField("0.",20);
        
         StringBuffer copyBoard = new StringBuffer(20);       //������
         StringBuffer buff = new StringBuffer();
         StringBuffer memory=new StringBuffer(20);//Mϵ��
        
         boolean isDouble=false;
        
         int preOp,currentOp=0;//��׼λ
         double op1=0,op2=0;//������
        
         JButton bM = new JButton("   ");
         JButton bOther;
         JButton bNumber;
         JButton bOperator;
        
         public Calculator(){
                  
                   super("�� �� ��");
                   cMenuBar.setOpaque(true);    // setOpaque(true);���ÿؼ���͸��   setOpaque(false);���ÿؼ�͸��
                  
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
                   //cMenuBar.addSeparator();  �����ӷָ���
                  
                   cMenuBar.add(cHelp);
                  
                  
                  
                   JPanel cTop = new JPanel();
                   text.setHorizontalAlignment(JTextField.RIGHT);    //textˮƽ���뷽ʽ
                   text.setEditable(false);   //ʹ������������Ŀؼ����ܱ��༭�������Ϊtrue���߲����������������ؼ����Ա༭
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
                   bOther.setMargin(new Insets(3,2,3,2));   //setMargin(new Insets(3,2,3,2))  ���ð�ť�߿�ͱ�ǩ֮��  �൱�����������3,2,Ȼ������3,2��ʾ��Ϊ3,��Ϊ2��һ������
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
            
                   String str = e.getActionCommand();    // getActionCommand()������˶�����ص������ַ���
                  
                  
                   if(str.equals("����(C)")){
                            String temp = text.getText().trim();    //trim() �����ַ����ĸ���������ǰ���հ׺�β���հ�
                           
                           
                           
                            copyBoard.replace(0,copyBoard.length(),temp);
                            cPaste.setEnabled(true);
                   }
                   else  if(str.equals("ճ��(P)")){
                           
                           
                            text.setText(copyBoard.toString());
                   }
                   else if(str.equals("��������")){
                           
                            JOptionPane.showMessageDialog(this, " 1.CE :����ı���                                                                   2.BackSpace :��ɾ����������\n " +
                                               "3.C :ɾ����ǰ����                                                                  4.MC :���������\n " +
                                               "5.MR :�ָ��������������ı���                                         6.MS :���ı���������뻺����\n" +
                                               "7.M+ :���ı���ֵ�뻺����������ӵ�����ʾ���        8. 1/x :���ı����е�����Ϊ���ĵ���\n" +
                                               "9.sqrt:���ı����е�������ƽ����                                     10.+/- :��������");
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
                   else if(str.equals("0"))//���ѡ�����"0"������ּ�
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
            text.setText(buff.append(str).toString());    //append()��ָ�����ַ���׷�ӵ����ַ�����
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
        frame.setResizable(false);    //setResizable(false)���ô��岻�ɸı��С
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
 
         }
 
}