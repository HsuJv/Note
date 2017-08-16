//  Programming with Java
//  by John R. Hubbard
//  Copyright 2004 by McGraw-Hill
//  ch12\ex02\WriteGossip.java

//package ch12.ex02;

import java.io.*;
import java.util.Random;

public class WriteGossip {
  private static Random random = new Random();
  private static String[] prnns;
  private static String[] nouns;
  private static String[] verbs;
  private static String[] adjvs;
  private static String[] advbs;

  public static void main(String[] args) {
    final String PATH = "";
    try {
      prnns = read(PATH + "Prnns.txt");
      nouns = read(PATH + "Nouns.txt");
      verbs = read(PATH + "Verbs.txt");
      adjvs = read(PATH + "Adjvs.txt");
      advbs = read(PATH + "Advbs.txt");
      write(PATH + "Gossip.txt");
    } catch(IOException exception) {
      System.out.println("exception: " + exception);
    }
    System.out.println("Finished.");
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

  private static void write(String paper) throws IOException {
    FileWriter writer = new FileWriter(paper);
    PrintWriter out = new PrintWriter(writer);
    out.print(randomSentence("First"));
    out.print(randomSentence(" Then"));
    out.print(randomSentence(" Earlier"));
    out.print(randomSentence(" Later that afternoon"));
    out.println(randomSentence(" Finally"));
    out.close();
  }

  private static String randomSentence(String firstWord) {
    StringBuffer buf = new StringBuffer(firstWord + ", ");
    buf.append(next(prnns) + " ");
    buf.append(next(adjvs) + " ");
    buf.append(next(nouns) + " ");
    buf.append(next(advbs) + " ");
    buf.append(next(verbs) + " ");
    buf.append(next(prnns) + " ");
    buf.append(next(adjvs) + " ");
    buf.append(next(nouns) + ".");
    return buf.toString();
  }

  private static String next(String[] array) {
    int i = random.nextInt(array.length);
    return array[i];
  }
}

/*  Output:
First, Amy's irrelevant mailman yesterday tripped over his quiet dog. Then, her obedient fiance shamelessly kissed Bob's idiotic barber. Earlier, my contientious dog mysteriously yelled at his hilarious professor. Later that afternoon, your neighbor's inarticulate cousin excitedly talked to my boyfriend's mendacious neighbor. Finally, her suspicious dog anxiously talked to his unhelpful ex-girlfriend.
*/
