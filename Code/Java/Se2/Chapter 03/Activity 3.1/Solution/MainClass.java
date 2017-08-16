package messenger;

import java.util.Scanner;

public class MainClass 
{

    public void showMenu() 
    {
        int option;
        Scanner sc = new Scanner(System.in);

        System.out.println("---------Menu---------");
        System.out.println("1. SMS");
        System.out.println("2. Email");
        System.out.println("3. Exit");
        System.out.print("\nChoose the option (1/2/3): ");

        option = sc.nextInt();

        switch (option) 
        {
            case 1:
                getSMSDetails();
                break;
            case 2:
                getEmailDetails();
                break;
            case 3:
                System.exit(0);
                break;
            default:
                showMenu();
                break;
        }
    }

    //SMS Method
    public void getSMSDetails() 
    {
        Scanner sc = new Scanner(System.in);
        String contact, message;

        System.out.println("=======================================");
        System.out.print("Enter the contact no: ");
        contact = sc.nextLine();
        System.out.print("\nEnter the message: ");
        message = sc.nextLine();
        SMSMessage sObj = new SMSMessage(contact, message);
        MessageProcessor<SMSMessage> message1 = new MessageProcessor<>(sObj);
        message1.printResult();

    }

    //Email Method
    public void getEmailDetails() 
    {
        Scanner sc = new Scanner(System.in);
        String email, message;

        System.out.println("=======================================");
        System.out.print("Enter the email id: ");
        email = sc.nextLine();
        System.out.print("\nEnter the message: ");
        message = sc.nextLine();
        EmailMessage eObj = new EmailMessage(email, message);
        MessageProcessor<EmailMessage> message2 = new MessageProcessor<>(eObj);
        message2.printResult();
    }

    public static void main(String[] args) 
    {
        MainClass mc = new MainClass();
        mc.showMenu();
    }
}
