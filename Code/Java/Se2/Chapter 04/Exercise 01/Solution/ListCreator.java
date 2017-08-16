package chapter04;

import java.util.Arrays;
import java.util.Collection;
import java.util.LinkedList;
import java.util.Random;
import java.util.Scanner;
import java.util.TreeMap;

public class ListCreator 
{
    TreeMap ctg, cust;
    Country country;
    Animal animal;
    Fruit fruit;
    
    public ListCreator() 
    {
        ctg = new TreeMap();
        cust = new TreeMap();
    }

    public void showMenu() 
    {
        int option;
        Scanner sc = new Scanner(System.in);

        System.out.println("---------Menu---------");
        System.out.println("1. Play");
        System.out.println("2. Instructions");
        System.out.println("3. Quit");
        System.out.print("\nChoose the option: ");

        option = sc.nextInt();

        switch (option) 
        {
            case 1:
                playGame();
                break;
            case 2:
                instructGame();
                break;
            case 3:
                System.exit(0);
                break;
            default:
                showMenu();
                break;
        }
    }

    public void playGame() 
    {
        genCtgList();
        addItem();
        Scanner sc = new Scanner(System.in);
        int rnd, rnd2, size, count = 0, flag;
        String value=null;
        Random rd;
        StringBuffer guess = new StringBuffer();
        StringBuffer wrgString = new StringBuffer();
        StringBuffer rgtString = new StringBuffer();

        System.out.println("=======================================================");
        System.out.println("Let's play the game.");
        rd = new Random();
        
        if(cust.size()==1)
        {
            rnd2 = rd.nextInt(cust.size());
        }
        else
        {
            rnd2 = rd.nextInt(cust.size()-1);
        }
        
               
        String cat = cust.get(cust.keySet().toArray()[rnd2]).toString();
        
        switch(cat)
        {
            case "Country": country = (Country)cust.get(cust.keySet().toArray()[rnd2]);
                            rnd = rd.nextInt(country.name.size());
                            value = country.name.get(rnd).toString();
                            break;
            case "Animal": animal = (Animal)cust.get(cust.keySet().toArray()[rnd2]);
                           rnd = rd.nextInt(animal.name.size());
                           value = animal.name.get(rnd).toString();
                           break;
            case "Fruit": fruit = (Fruit)cust.get(cust.keySet().toArray()[rnd2]);
                           rnd = rd.nextInt(fruit.name.size());
                           value = fruit.name.get(rnd).toString();
                           break;
            default: System.out.println("Not Valid");
                break;
        }
       
        size = value.length();

        for (int j = 0; j < size; j++) 
        {
            System.out.print("_ ");
            guess.append("_ ");
            rgtString.append(value.charAt(j) + " ");
        }


        while (true) 
        {
            flag = 0;

            System.out.print("\n\nEnter your guess: ");
            String ch = sc.nextLine();
            ch = ch.toUpperCase();


            for (int i = 0; i < size; i++) 
            {
                if (value.charAt(i) == ch.charAt(0)) 
                {
                    String tmp = String.valueOf(value.charAt(i));
                    guess.replace(i * 2, (i * 2) + 1, tmp);
                    flag = 1;
                    
                }
            }
            

            if (flag == 0) 
            {
                wrgString.append(ch + ", ");
                System.out.println("\nMisses: " + wrgString);
                count++;
            }
            
            System.out.println(guess);

            if (guess.toString().equalsIgnoreCase(rgtString.toString())) 
            {
                System.out.println("---------- Congrats :) You won ------------");
                break;
            }
        }
    }

    public void instructGame() 
    {
        System.out.println("-------------Instructions---------------");
        System.out.println("1. You need to guess letters for the row of dashes");
        System.out.println("2: If you guess the correct letter, it will appear in the next statement");
        System.out.println("3: If you guess the incorrect letter, it will appear in the list of missed letter.");
        showMenu();

    }

    public void genCtgList() 
    {
        ctg.put(1, new Country());
        ctg.put(2, new Animal());
        ctg.put(3, new Fruit());
        
        int size = ctg.size();
        System.out.println("=======================================================");
        System.out.println("The available categories are: ");
        for (int i = 0; i < size; i++) 
        {
            System.out.println(ctg.keySet().toArray()[i] + " " + ctg.get(i + 1));
        }
    }

    public void genCustList(TreeMap obj) 
    {
        int size = obj.size();

        for (int i = 0; i < size; i++) 
        {
            int input = (Integer) obj.keySet().toArray()[i];
            System.out.println(input + " " + cust.get(input));
        }
    }

    public void addItem() 
    {
        String choice;
        int input, count = 1;
        Scanner sc = new Scanner(System.in);
        
        do 
        {
            System.out.println("=======================================================");
            System.out.println("Select the category that you want to add (1/2/3): ");
            input = sc.nextInt();


            cust.put(input, ctg.get(input));
            System.out.println("=======================================================");
            System.out.println("The customized list is: ");
            genCustList(cust);

            
            if (cust.size() < ctg.size()) 
            {
                do
                {
                    System.out.println("=======================================================");
                    System.out.print("Do you want to add more? (Y/N): ");
                    choice = sc.next();
                }while(!(choice.toUpperCase().equals("N")||(choice.toUpperCase().equals("Y"))));
            } 
            else 
            {
                System.out.println("=======================================================");
                System.out.println("You cannot add more categories");
                break;
            }
            count++;
        } while (choice.toUpperCase().equals("Y"));
        
        System.out.println("=======================================================");
        System.out.println("The final list is: ");
        genCustList(cust);
    }

    public static void main(String[] args) 
    {
        ListCreator lc = new ListCreator();
        lc.showMenu();
    }
}
