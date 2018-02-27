#pragma once
#ifndef ROOM_H
#define ROOM_H

struct _Room
{
	unsigned int Num;
	unsigned int Class;
	int occupied;
	char period[12];
};

/*
Get room number by order
input: room order range in (0, 100)
output: room number
*/
inline int getRoomNum(int id);

/*
Get room order by number
input: room number
output: room order range in (0, 100)
*/
inline int getRoomOrder(int id);

/*
To calc the price
*/
double getRoomPrice(unsigned int, int);

/*
Get room information initial
*/
void RoomInit();

/*
Set room information
*/
void setRoomInfo();

/*
Update room information after updating 
*/
void getRoomInfoUpdated();
#endif // !ROOM_H
