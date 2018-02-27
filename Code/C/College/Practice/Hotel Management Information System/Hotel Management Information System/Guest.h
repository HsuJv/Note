#pragma once
#ifndef GUEST_H
#define GUEST_H

struct _Guest {
	char name[256];
	char address[256];
	char telephone[16];
	unsigned int membership;
};

/*
Add a guest
*/
void GuestAdd();

/*
Edit information of a guest
*/
void GuestEdit();

/*
Delete information of a guest
*/
void GuestDel();

/*
Display all the guests information
*/
void GuestList();

/*
Login with the access of vips
*/
int GuestLogin();

/*
Set the period
input: a sequence memory to store the date
output: return true if success
*/
int setBookDate(char*);
/*
Register a booking
*/
void GuestBook();

/*
Search room available
input: 
arg1: if true than this founction will display hints
arg2: the room type to search, need hint to be false
output: the first available room number
*/
int GuestSearch(int, int);

/*
Group bookings
*/
void VipBook();

/*
Count how many rooms available
input: the room type code to count
output: count
*/
int AvailableRoomCount(int);

/*
The main function while login with the access of guest
*/
void GuestMain();
#endif // !GUEST_H
