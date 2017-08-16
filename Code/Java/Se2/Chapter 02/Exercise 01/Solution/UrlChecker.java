package chapter02;

import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

class UrlChecker {

    public static void main(String[] args) {
        Pattern Mypattern = Pattern.compile("^((https?|ftp)://|(www|ftp)\\.)[a-z0-9-]+(\\.[a-z0-9-]+[a-z]+)+([/?].*)?$");
        Scanner input = new Scanner(System.in);
        System.out.println("Enter the Url to be checked: ");
        String name = input.nextLine();
        Matcher Mymatcher = Mypattern.matcher(name);
        Boolean Myboolean = Mymatcher.matches();
        if (Myboolean == true) {
            System.out.println("Url is correct");
        } else {
            System.out.println("Url is incorrect");
        }
    }
}