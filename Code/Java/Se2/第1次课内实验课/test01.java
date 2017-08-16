import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class test01{
	public static void main(String[] args) {
		p("a".matches("[abc]"));
		p("a".matches("[^abc]"));
		p("A".matches("[a-zA-Z]"));
		p("A".matches("[a-z]|[A-Z]"));
		p("A".matches("[a-z[A-Z]]"));
		p("R".matches("[A-Z&&[RFG]]"));
	}
	public static void p(Object o){
		System.out.println(o);
	}
}