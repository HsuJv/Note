//  Programming with Java
//  by John R. Hubbard
//  Copyright 2004 by McGraw-Hill
//  ch12\pr15\WritePaper.java

//package ch12.pr15;

import java.io.*;
import java.util.Random;

public class WritePaper {
  public static void main(String[] args) {
    if (args.length != 5) {
      System.err.println("Usage: java WritePaper <nouns> <verbs> "
                       + "<adjectives> <adverbs> <paper>");
      System.exit(-1);
    }
    String[] nouns = null;
    String[] verbs = null;
    String[] adjvs = null;
    String[] advbs = null;
    try {
      nouns = read(args[0]);
      verbs = read(args[1]);
      adjvs = read(args[2]);
      advbs = read(args[3]);
      String[][] words = {nouns, verbs, adjvs, advbs};
      write(words, args[4]);
    } catch(IOException exception) {
      System.out.println("exception: " + exception);
    }
  }

  private static String[] read(String file) throws IOException {
    FileReader reader = new FileReader(file);
    BufferedReader in = new BufferedReader(reader);
    int n = Integer.parseInt(in.readLine());
    String[] array = new String[n];
    for (int i=0; i<n; i++)
      array[i] = in.readLine();
    in.close();
    return array;
  }

  private static void write(String[][] words, String paper) throws IOException {
    FileWriter writer = new FileWriter(paper);
    PrintWriter out = new PrintWriter(writer);
    Random random = new Random();
    int numSentences = random.nextInt(10) + 2;
    for (int i=0; i<numSentences; i++) {
      StringBuffer buf = new StringBuffer("Your ");
      buf.append(words[2][random.nextInt(words[2].length)] + " ");
      buf.append(words[0][random.nextInt(words[0].length)] + " ");
      buf.append(words[3][random.nextInt(words[3].length)] + " ");
      buf.append(words[1][random.nextInt(words[1].length)] + " my ");
      buf.append(words[2][random.nextInt(words[2].length)] + " ");
      buf.append(words[0][random.nextInt(words[0].length)] + ".");
      
      System.out.println(buf);
      
    }
    
    
  }

  private static void print(String[] a) {
  	for (int i=0; i<a.length; i++)
  	  System.out.println((i+1) + ".\t" + a[i]);
  }
}

//    String line=null;
//    while ((line = in.readLine()) != null) {
//      out.println(encrypted(line));
//    }
