package chapter07;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class WordSearching {

    public static void main(String args[]) {
        Scanner input1 = new Scanner(System.in);
            System.out.println("Enter the file in which you want to search the word: ");
            String stringSearch1 = input1.nextLine();
        File f=new File(stringSearch1);
        try (BufferedReader bf = new BufferedReader(new FileReader(f))) {
            Scanner input = new Scanner(System.in);
            System.out.println("Enter the word you want to search: ");
            String stringSearch = input.nextLine();
            int linecount = 0;
            int linecount1 = 0;
            String line;
            System.out.println("Searching for " + stringSearch + " in file...");


            while ((line = bf.readLine()) != null) {

                String txt[] = line.split(" ");


                for (int i = 0; i < txt.length; i++) {

                    if (txt[i].equals(stringSearch)) {
                        linecount++;
                    }
                }
            }


            int i = linecount + linecount1;
            System.out.println("The string appears in the document " + i+" times");


        } catch (IOException e) {
            System.out.println("IO Error Occurred: " + e.toString());
        }
    }
}