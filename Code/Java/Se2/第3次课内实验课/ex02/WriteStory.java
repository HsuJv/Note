//  Programming with Java
//  by John R. Hubbard
//  Copyright 2004 by McGraw-Hill
//  ch12\pr15\WriteStory.java

//package ch12.pr15;

import java.io.*;
import java.util.Random;

public class WriteStory {
  private static Random random = new Random();
  private static String[] prnns;
  private static String[] nouns;
  private static String[] verbs;
  private static String[] adjvs;
  private static String[] advbs;

  public static void main(String[] args) {
    if (args.length != 6) {
      System.err.println("Usage: java WriteStory <pronouns> <nouns> "
                       + "<verbs> <adjectives> <adverbs> <paper>");
      System.exit(-1);
    }
    try {
      prnns = read(args[0]);
      nouns = read(args[1]);
      verbs = read(args[2]);
      adjvs = read(args[3]);
      advbs = read(args[4]);
      write(args[5]);
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

  private static void write(String paper) throws IOException {
    FileWriter writer = new FileWriter(paper);
    PrintWriter out = new PrintWriter(writer);
    System.out.print(randomSentence("First"));
    System.out.print(randomSentence(" Then"));
    System.out.print(randomSentence(" Earlier"));
    System.out.print(randomSentence(" Later that afternoon"));
    System.out.println(randomSentence(" Finally"));
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
First, your girlfriend's long-winded cousin suspiciously listened to your girlfr
iend's boring uncle. Then, my boyfriend's idiotic barber mysteriously listened t
o your sneaky professor. Earlier, Bob's long haired professor shyly disagreed wi
th my neighbor's little best friend. Later that afternoon, Bob's long-winded sis
ter surprisingly pinched your neighbor's sneaky neighbor. Finally, my roommate's
 soft cousin sometimes laughed at my boyfriend's wonderful professor.
*/
