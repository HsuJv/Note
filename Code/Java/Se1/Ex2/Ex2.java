import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Ex2 extends JFrame implements ActionListener {

	JTextArea memoryArea = new JTextArea("", 1, 3);
	JTextArea dispresult = new JTextArea("0.    ", 1, 20);

	Font font = new Font("Gungsuh", Font.PLAIN, 18);

	JButton clear = new JButton("C"); 
	JButton[] jbuttons = new JButton[35]; 

	double result = 0, first = 0, second = 0;
	double memery = 0;
	char firstsymbol = '\0', secondsymbol = '\0';
	boolean prev = true, repeat = true, dot = true;

	Ex2() {
		super("Calculator");
		try {
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} catch (Exception e) {
			System.out.println(e);
		}

		JPanel resultField = new JPanel(); 
		JPanel buttonField = new JPanel(); 
		Container all = getContentPane();

		GridLayout gridl;
		gridl = new GridLayout(6, 6, 3, 3);

		clear.setFont(font);
		memoryArea.setFont(font);
		dispresult.setFont(font);
		memoryArea.setEditable(false);
		clear.addActionListener(this);
		dispresult.setEditable(false);

		resultField.add(memoryArea);
		resultField.add(clear);
		resultField.add(dispresult);

		all.setLayout(new FlowLayout());
		all.add(resultField);

		String[] buttonname = { "sin", "MC", "0", "1", "2", "+", "cos", "MR", "3", "4", "5", "-", "tan", "MS", "6", "7",
				"8", "x", "+/-", "M+", "9", ".", "=", "/", "1/x", "x！", "log", "ln", "e", "%", "x^2", "x^y","arcsin","arccos","arctan" }; // 各种按键显示名称

		buttonField.setLayout(gridl); // JPanel buttonField = new JPanel()
		for (int i = 0; i < 35; i++) {

			jbuttons[i] = new JButton(buttonname[i]);
			jbuttons[i].addActionListener(this);
			jbuttons[i].setFont(font);
			buttonField.add(jbuttons[i]);

		} // end of i

		all.add(buttonField);
		setSize(580, 350);
		setResizable(true);
		setVisible(true);

	} // end of MyComputer

	public void pressNumber(String n) {
		if (prev) {
			dispresult.setText(n); // dispresult JTextArea("0. ", 1, 20);
			prev = false;
		} else
			dispresult.append(n);
	} // end of pressNumber

	public boolean divide(double d) {
		if (d == 0) {
			dispresult.setText("除数不能为0");
			prev = true;
			repeat = true;
			firstsymbol = '\0';
			secondsymbol = '\0';
			return true;
		}
		return false;
	} // end of divide

	public void actionPerformed(ActionEvent e) {
		Object source = e.getSource();

		if (source == clear) {
			dispresult.setText("0.");
			firstsymbol = '\0';
			secondsymbol = '\0';
			prev = true;
			repeat = true;
			dot = true;
			return;
		} // clear

		if (source == jbuttons[0]) {
			double temp = Math.sin(Double.parseDouble(dispresult.getText()));
			dispresult.setText(String.valueOf(temp));
			prev = true;
			repeat = false;
			dot = true;
			return;
		} // sin

		if (source == jbuttons[1]) {
			memery = 0;
			memoryArea.setText(" ");
			prev = true;
			repeat = false;
			dot = true;
			return;
		} // MC

		if (source == jbuttons[2]) {
			pressNumber("0");
			repeat = false;
			return;
		} // 0

		if (source == jbuttons[3]) {
			pressNumber("1");
			repeat = false;
			return;
		} // 1

		if (source == jbuttons[4]) {
			pressNumber("2");
			repeat = false;
			return;
		} // 2

		if (source == jbuttons[5]) {
			dot = true;
			if (repeat) { 
				firstsymbol = '+';
				return;
			}
			second = Double.parseDouble(dispresult.getText());
			switch (secondsymbol) {
			case '*':
				second *= first;
				break;
			case '/':
				if (divide(second))
					return;
				second = first / second;
			} // end of switch(secondsymbol)
			secondsymbol = '\0';
			switch (firstsymbol) {
			case '\0':
				result = second;
				firstsymbol = '+';
				break;
			case '+':
				result += second;
				dispresult.setText(String.valueOf(result));
				break;
			case '-':
				result -= second;
				firstsymbol = '+';
				dispresult.setText(String.valueOf(result));
				break;
			case '*':
				result *= second;
				firstsymbol = '+';
				dispresult.setText(String.valueOf(result));
				break;
			case '/':
				if (divide(second))
					return;
				result /= second;
				firstsymbol = '+';
				dispresult.setText(String.valueOf(result));
			} // end of switch(firstsymbol)
			prev = true;
			repeat = true;
			return;

		} // +

		if (source == jbuttons[6]) {
			double temp = Math.cos(Double.parseDouble(dispresult.getText()));
			dispresult.setText(String.valueOf(temp));
			prev = true;
			repeat = false;
			dot = true;
			return;
		} // cos

		if (source == jbuttons[7]) {
			/*
			 * if(memoryArea.getText().equals(" M "))
			 * dispresult.setText(String.valueOf(memery)); else
			 */
			dispresult.setText(String.valueOf(memery));
			prev = true;
			repeat = false;
			dot = true;
			return;
		} // MR

		if (source == jbuttons[8]) {
			pressNumber("3");
			repeat = false;
			return;
		} // 3

		if (source == jbuttons[9]) {
			pressNumber("4");
			repeat = false;
			return;
		} // 4

		if (source == jbuttons[10]) {
			pressNumber("5");
			repeat = false;
			return;
		} // 5
        
		if (source == jbuttons[11]) {
			dot = true;
			if (repeat) {
				firstsymbol = '-';
				return;
			}
			second = Double.parseDouble(dispresult.getText());
			switch (secondsymbol) {
			case '*':
				second *= first;
				break;
			case '/':
				if (divide(second))
					return;
				second = first / second;
			} // end of switch(secondsymbol)
			secondsymbol = '\0';
			switch (firstsymbol) {
			case '\0':
				result = second;
				firstsymbol = '-';
				break;
			case '+':
				result += second;
				firstsymbol = '-';
				dispresult.setText(String.valueOf(result));
				break;
			case '-':
				result -= second;
				dispresult.setText(String.valueOf(result));
				break;
			case '*':
				result *= second;
				firstsymbol = '-';
				dispresult.setText(String.valueOf(result));
				break;
			case '/':
				if (divide(second))
					return;
				result /= second;
				firstsymbol = '-';
				dispresult.setText(String.valueOf(result));
			} // end of switch(firstsymbol)
			prev = true;
			repeat = true;
			return;

		} // -

	    if (source == jbuttons[12]) {
			double temp = Math.tan(Double.parseDouble(dispresult.getText()));
			dispresult.setText(String.valueOf(temp));
			prev = true;
			repeat = false;
			dot = true;
			return;
		} // tan

		if (source == jbuttons[13]) {
			memery = Double.parseDouble(dispresult.getText());
			if (memery != 0)
				memoryArea.setText(" M ");
			prev = true;
			repeat = false;
			dot = true;
			return;
		} // MS

		if (source == jbuttons[14]) {
			pressNumber("6");
			repeat = false;
			return;
		} // 6

		if (source == jbuttons[15]) {
			pressNumber("7");
			repeat = false;
			return;
		} // 7

		if (source == jbuttons[16]) {
			pressNumber("8");
			repeat = false;
			return;
		} // 8

		if (source == jbuttons[17]) {
			dot = true;
			if (repeat) {
				if (secondsymbol == '\0')
					firstsymbol = '*';
				else
					secondsymbol = '*';
				return;
			}
			second = Double.parseDouble(dispresult.getText());
			switch (secondsymbol) {
			case '\0':
				switch (firstsymbol) {
				case '\0':
					result = second;
					firstsymbol = '*';
					break;
				case '+':
				case '-':
					first = second;
					secondsymbol = '*';
					break;
				case '*':
					result *= second;
					dispresult.setText(String.valueOf(result));
					break;
				case '/':
					if (divide(second))
						return;
					result /= second;
					firstsymbol = '*';
					dispresult.setText(String.valueOf(result));
				} // end of switch(firstsymbol)
				break;
			case '*':
				first *= second;
				dispresult.setText(String.valueOf(first));
				break;
			case '/':
				if (divide(second))
					return;
				first /= second;
				secondsymbol = '*';
				dispresult.setText(String.valueOf(first));
			} // end of switch(secondsymbol)

			prev = true;
			repeat = true;
			return;

		} // *
		
		if (source == jbuttons[18]) {
			double temp = -Double.parseDouble(dispresult.getText());
			dispresult.setText(String.valueOf(temp));
			prev = true;
			repeat = false;
			dot = true;
			return;
		} // +/-

		if (source == jbuttons[19]) {
			memery += Double.parseDouble(dispresult.getText());
			if (memery != 0)
				memoryArea.setText(" M ");
			// dispresult.setText(String.valueOf(memery));
			prev = true;
			repeat = false;
			dot = true;
			return;
		} // M+

		if (source == jbuttons[20]) {
			pressNumber("9");
			repeat = false;
			return;
		} // 9

		if (source == jbuttons[21]) {
			if (dot) {
				pressNumber(".");
				dot = false;
				repeat = false;
			}
			return;
		} // .

		if (source == jbuttons[22]) {
			second = Double.parseDouble(dispresult.getText());
			dot = true;
			switch (secondsymbol) {
			case '*':
				second *= first;
				break;
			case '/':
				if (divide(second))
					return;
				second = first / second;
			} // end of switch(secondsymbol)
			secondsymbol = '\0';

			switch (firstsymbol) {
			case '+':
				result += second;
				break;
			case '-':
				result -= second;
				break;
			case '*':
				result *= second;
				 dispresult.setText(String.valueOf(result));
				break;
			case '%':
				result %= second;
				dispresult.setText(String.valueOf(result));
				break;
			case '^':
				result = Math.pow(result,second);
				dispresult.setText(String.valueOf(result));
				break;
			case '/':
				if (divide(second))
					return;
				result /= second;
			} // end of switch(firstsymbol)
			if (firstsymbol != '\0')
				dispresult.setText(String.valueOf(result));
			firstsymbol = '\0';
			prev = true;
			repeat = false;
			return;

		} // =	
		
		if (source == jbuttons[23]) {
			dot = true;
			if (repeat) {
				if (secondsymbol == '\0')
					firstsymbol = '/';
				else
					secondsymbol = '/';
				return;
			}
			second = Double.parseDouble(dispresult.getText());
			switch (secondsymbol) {
			case '\0':
				switch (firstsymbol) {
				case '\0':
					result = second;
					firstsymbol = '/';
					break;
				case '+':
				case '-':
					first = second;
					secondsymbol = '/';
					break;
				case '*':
					result *= second;
					firstsymbol = '/';
					dispresult.setText(String.valueOf(result));
					break;
				case '/':
					if (divide(second))
						return;
					result /= second;
					dispresult.setText(String.valueOf(result));
				} // end of switch(firstsymbol)
				break;
			case '*':
				first *= second;
				secondsymbol = '/';
				dispresult.setText(String.valueOf(first));
				break;
			case '/':
				if (divide(second))
					return;
				first /= second;
				dispresult.setText(String.valueOf(first));
			} // end of switch(secondsymbol)

			prev = true;
			repeat = true;
			return;

		} // '/'
		
		if (source == jbuttons[24]) {
			double temp = 1.0 / (Double.parseDouble(dispresult.getText()));
			dispresult.setText(String.valueOf(temp));
			prev = true;
			repeat = false;
			dot = true;
			return;
		} // 1/x
		
		if (source == jbuttons[25]) {
			int temp = Integer.parseInt(dispresult.getText());
			int s = 1;
			for (int i = 1; i <= temp; i++) {
				s = s * i;
			}
			dispresult.setText(String.valueOf(s));
			prev = true;
			repeat = false;
			dot = true;
			return;
		} // x!

		if (source == jbuttons[26]) {
			double temp = (Double.parseDouble(dispresult.getText()));
			temp = Math.log(temp) / Math.log(10);
			dispresult.setText(String.valueOf(temp));
			prev = true;
			repeat = false;
			dot = true;
			return;
		} // log

		if (source == jbuttons[27]) {
			double temp = (Double.parseDouble(dispresult.getText()));
			temp = Math.log(temp);
			dispresult.setText(String.valueOf(temp));
			prev = true;
			repeat = false;
			dot = true;
			return;
		} // ln

		if (source == jbuttons[28]) {

			double temp = Math.exp(1);
			dispresult.setText(String.valueOf(temp));
			prev = true;
			repeat = false;
			dot = true;
			return;
		} // e

		if (source == jbuttons[29]) {
			dot = true;
			if (repeat) { 
				firstsymbol = '%';
				return;
			}
			second = Double.parseDouble(dispresult.getText());
			result=second;
			firstsymbol = '%';
			prev = true;
			repeat = true;
			return;
		} // %

		if (source == jbuttons[30]) {
			double temp = (Double.parseDouble(dispresult.getText()));
			temp=Math.pow(temp, 2);
			dispresult.setText(String.valueOf(temp));
			prev = true;
			repeat = false;
			dot = true;
			return;
		} // x^2

		if (source == jbuttons[31]) {
			dot = true;
			if (repeat) { 
				firstsymbol = '^';
				return;
			}
			second = Double.parseDouble(dispresult.getText());
			result=second;
			firstsymbol = '^';
			prev = true;
			repeat = true;
			return;
		} // x^y

		 if(source==jbuttons[32]) {
			double temp = Math.asin(Double.parseDouble(dispresult.getText()));
			dispresult.setText(String.valueOf(temp));
			prev = true;
			repeat = false;
			dot = true;
			return;
			}
		
	   if(source==jbuttons[33]) {
		double temp = Math.acos(Double.parseDouble(dispresult.getText()));
		dispresult.setText(String.valueOf(temp));
		prev = true;
		repeat = false;
		dot = true;
		return;}
	
	    if(source==jbuttons[34]) {
		double temp = Math.atan(Double.parseDouble(dispresult.getText()));
		dispresult.setText(String.valueOf(temp));
		prev = true;
		repeat = false;
		dot = true;
		return;}
	}
	public static void main(String args[]) {
		Ex2 mc = new Ex2();
	}

} // end of class