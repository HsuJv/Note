package details;
import java.util.*;
public class Candidates {
    private String name, qualification, status;
    private int age;
    
    public void getCandiatesDetails(){
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter your name:");
        name=sc.next();
        System.out.println("Enter your qualification:");
        qualification=sc.next();
        System.out.println("Enter your age:");
        age=sc.nextInt();
        AgeValidation obj=new AgeValidation();
        obj.validateAge();
    }
    private class AgeValidation{
        public void validateAge(){
            if(age>=21 && age<=25){
                status="selected";
            }
            else{
                status="rejected";
            }
           
        }
    }
    public void printCandiatesDetails(){
        System.out.println("Name: "+name);
        System.out.println("Qualification: "+qualification);
        System.out.println("Age: "+age);
        System.out.println("Selection Status: "+status);
    }
    public static void main(String args[]){
        Candidates candidate=new Candidates();
        candidate.getCandiatesDetails();
        candidate.printCandiatesDetails();
        
    }
}
