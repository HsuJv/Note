#pragma once
#ifndef BILL_H
#define BILL_H

struct _Bill
{
	unsigned int bill_num;
	char name[256];
	unsigned int membership;
	char tel[256];
	unsigned int room;
	unsigned int room_type;
	unsigned int stuff;
	double account;
	double paid;
	char period[12];
	char date[6];
};

/*
Comfirm the bill information
return 1 if comfirmed
*/
int BillComfirm();

/*
Add a bill to databse
*/
void BillAdd();

/*
Change the period which has been stored
*/
void getPeriodChange();

/*
Checkout
*/
void getBillCheckout();

/*
Get a overview of all views
*/
void BillOverview();
#endif // !BILL_H
