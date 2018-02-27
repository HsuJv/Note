#pragma once
#ifndef VIGENERE_H
#define VIGENERE_H

/*
Get the data encryptd by vigenere cipher
Input: the pointer to the data which is to be encryptd, the size of the data
Output: none
*/
void getVigenereEncrypt(PBYTE, unsigned int);

/*
Get the data decryptd by vigenere cipher
Input: the pointer to the data which is to be decryptd, the size of the data
Output: none
*/
#define getVigenereDecrypt getVigenereEncrypt

#endif // !VIGENERE_H
