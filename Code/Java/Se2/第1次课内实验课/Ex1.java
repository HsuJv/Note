import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Ex1{
	public static void main(String[] args) {
		Pattern myPattern = Pattern.compile("[\\w[.-]]+@[\\w[.-]]+\\.[\\w]+");
		Matcher myMatcher = myPattern.matcher("yangj@njupt.edu.cn");
		boolean myBoolean = myMatcher.matches();
		if(myBoolean){
			System.out.println("This is a email address");
		}
		else{
			System.out.println("This is not a email address");
		}
	}
}