package chapter07;
import java.io.*;
import java.util.*;
public class BookDetails {
   String bookName,authorName,price,choice,line;
   char choice_c;
    public void writeDetails(){
        do{
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter the Book Name:");
        bookName=sc.next();
        System.out.println("Enter the Author Name:");
        authorName=sc.next();
        System.out.println("Enter the Price:");
        price=sc.next();
        try(FileWriter fw=new FileWriter("BookDetails.txt",true)){
            fw.write(bookName+"\t"+authorName+"\t"+price+"\n");
            
        }catch(Exception e){
            System.out.println(e);
        }
        System.out.println("Do you want to add more records (y/n)");
        choice=sc.next().toLowerCase();
        choice_c=choice.charAt(0);
        }while(choice_c=='y');
        System.out.println("---------------------------------------");
        displayMenu();
    }
    public void displayDetails(){
      try (BufferedReader br = new BufferedReader(new FileReader("BookDetails.txt"))) {{
           while ((line = br.readLine())!= null) { 
               System.out.println(line);
           }
           System.out.println("---------------------------------------");
           }
        }catch(Exception e){
            System.out.println(e);
        }
        displayMenu();
    }
    public void displayMenu(){
        Scanner sc=new Scanner(System.in);
        System.out.println("1. Enter Book Details");
        System.out.println("2. View All Book Details");
        System.out.println("3. Exit");
        System.out.println("Enter your choice");
        int i=sc.nextInt();
        System.out.println("---------------------------------------");
        switch(i){
            case 1: writeDetails();
                    break;
            case 2: displayDetails();
                    break;
            case 3: System.exit(0);
                    break;
            default: System.out.println("Please enter a valid input");
                     displayMenu();
        }
    }
    public static void main(String args[]){
        
        BookDetails obj=new BookDetails();
        obj.displayMenu();
    }
}
