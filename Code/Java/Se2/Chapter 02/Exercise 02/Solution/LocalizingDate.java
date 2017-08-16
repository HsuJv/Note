package chapter02;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;
import java.util.Scanner;

public class LocalizingDate {

    Scanner br = new Scanner(System.in);
    Locale currentLocale = Locale.US;
    
    Date today = new Date();
    DateFormat df;
    SimpleDateFormat sdf;

    public static void main(String[] args) {
        
        LocalizingDate dateApp = new LocalizingDate();
        dateApp.run();
    }

    public void run() {
        String line = "";


        this.printMenu();
        try {
            line = this.br.next();
        } catch (Exception e) {
            System.out.println(e);
        }

        switch (line) {
            case "1":
                setEnglish();
                run();
                break;
            case "2":
                setFrench();
                run();
                break;
case "3":
                setChinese();
                run();
                break;
    case "4":
                setItalian();
                run();
                break;
        }
    }

    public void printMenu() {
        System.out.println("=== Localizing Date Application ===");

        System.out.println("\n--- Choose Language Option ---");
        System.out.println("1. Set to English");
        System.out.println("2. Set to French");
        System.out.println("3. Set to Chinese");
        System.out.println("4. Set to Italian");
        System.out.println("q. Quit");
        System.out.print("Enter a command:");
        df = DateFormat.getDateInstance(DateFormat.DEFAULT, currentLocale);
    }
    public void setEnglish() {
        
        currentLocale = Locale.US;
        

        sdf = new SimpleDateFormat("EEEE MMMM d, y G kk:mm:ss zzzz", currentLocale);
        System.out.println(sdf.format(today));
    }
    
    public void setFrench() {
        currentLocale = Locale.FRANCE;
       

        sdf = new SimpleDateFormat("EEEE MMMM d, y G kk:mm:ss zzzz", currentLocale);
        System.out.println(sdf.format(today));
    
    }
    public void setChinese() {
        
        currentLocale = Locale.CHINESE;
        

        sdf = new SimpleDateFormat("EEEE MMMM d, y G kk:mm:ss zzzz", currentLocale);
        System.out.println(sdf.format(today));
    }
    public void setItalian() {
        
        currentLocale = Locale.ITALIAN;
        

        sdf = new SimpleDateFormat("EEEE MMMM d, y G kk:mm:ss zzzz", currentLocale);
        System.out.println(sdf.format(today));
    }
}
