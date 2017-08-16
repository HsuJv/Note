//  Programming with Java
//  by John R. Hubbard
//  Copyright 2004 by McGraw-Hill
//  ch12\pr03\Encryptor.java

//package ch12.pr03;

import java.io.*;

public class Encryptor {
  private int key;

  public Encryptor(int key) {
    this.key = key;
  }

  public void encrypt(String inFile, String outFile) throws IOException {
    FileReader fileReader = new FileReader(inFile);
    BufferedReader in = new BufferedReader(fileReader);
    FileWriter fileWriter = new FileWriter(outFile);
    PrintWriter out = new PrintWriter(fileWriter);
    String line=null;
    while ((line = in.readLine()) != null) {
      out.println(encrypted(line));
    }
    in.close();
    out.close();
  }

  private String encrypted(String line) {
  	StringBuffer buf = new StringBuffer();
  	for (int i=0; i<line.length(); i++)
  	  buf.append(encrypted(line.charAt(i)));
  	return buf.toString();
  }

  private char encrypted(char ch) {
  	return (char)((ch + 128 + key) % 128);
  }
}
