//  Programming with Java
//  by John R. Hubbard
//  Copyright 2004 by McGraw-Hill
//  ch12\pr03\Decrypt.java

//package ch12.pr03;

import java.io.*;

public class Decrypt {
  public static void main(String[] args) {
    String inFile = "Alice1.txt";
    String outFile = "Alice2.txt";
    int key = -7;
    System.out.println("Decrypting " + inFile + " to " + outFile
        + " with a key of " + key);
    Encryptor encryptor = new Encryptor(key);
    try {
      encryptor.encrypt(inFile, outFile);
    } catch(IOException exception) {
      System.out.println("exception: " + exception);
    }
  }
}

/*  Output:
Decrypting A:\Alice.txt to A:\Alice1.txt with a key of -7
*/
