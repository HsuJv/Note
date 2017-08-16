//  Programming with Java
//  by John R. Hubbard
//  Copyright 2004 by McGraw-Hill
//  ch11\ex01\Main.java

//package ch12.ex01;

import java.io.*;

public class ToUpperCase{
  public static void main(String[] args) {
    String inFile = "Alice.txt";
    String outFile = "AliceUpperCase.txt";
    try {
      System.out.println("Reading from:\t" + inFile);
      FileReader fileReader = new FileReader(inFile);
      BufferedReader in = new BufferedReader(fileReader);
      System.out.println("Writing to:\t" + outFile);
      FileWriter fileWriter = new FileWriter(outFile);
      PrintWriter out = new PrintWriter(fileWriter);
      String line = null;
      int numLines = 0;
      while ((line = in.readLine()) != null) {
        out.println(line.toUpperCase());
        ++numLines;
      }
      in.close();
      out.close();
      System.out.println("Copied " + numLines + " lines.");
    } catch(IOException exception) {
      System.out.println("exception: " + exception);
    }
  }
}

/*  Output:
Reading from:   Alice.txt
Writing to:     AliceUppercase.txt
Copied 8 lines.
*/
