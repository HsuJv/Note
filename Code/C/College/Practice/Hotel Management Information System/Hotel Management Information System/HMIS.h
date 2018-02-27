#pragma once
#ifndef HMIS_H
#define HMIS_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>
#include <io.h>

// Constant Value

#define Group_Admin (BYTE)0x1
#define Group_Cashier (BYTE)0x3
#define Group_VIP_GUEST (BYTE)0x5
#define Group_NORM_GUEST (BYTE)0xf

#define File_Admin "admin"
#define File_Room "room"
#define File_Cashier "cashier"
#define File_Guest "guest"
#define File_Bill "bill"

#define Class_Double_Room 2
#define Class_Triple_Room 3
#define Class_Quadruple_Room 4
#define Class_VIP_Room 1

#define Price_Double_Room 200
#define Price_Triple_Room 300
#define Price_Quadruple_Room 400
#define Price_VIP_Room 500

// Function declearation
/*
Init for this production
file that stored the admin password will be created with the default pwd "admin"
*/
void _init_();

/*
Main Menu
*/
int _menu_();

/*
Get the password input
*/
char* getPassword();

/*
Function that to set a new password
with the point to raw pwd input, the new pwd output
*/
char* setPassword(char*);

/*
Validate if the date input is comfermed to the format
input: a 5 characters string
output: return true if and only if the first two chars represent a meaningful day and the last two
chars represent a meaningful month
*/
int validateDate(char*);

/*
Count how many days there are from 1st Jan to the date input
*/
int countDays(char*);
#endif // !HMIS_H
