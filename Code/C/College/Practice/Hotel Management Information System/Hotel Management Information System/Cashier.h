#pragma once
#ifndef CASHIER_H
#define CASHIER_H

struct _Cashier {
	char account[256];
	char pwd[16];
	unsigned int id;
};

/*
Function that handles cashier login
return 0 if failed
*/
int CashierLogin();

/*
Add a cashier
*/
void CashierAdd();

/*
Delete information of a cashier
*/
void CashierDel();

/*
Display all the cashiers information
*/
void CashierList();

/*
The main founction will login with the access of cashier
*/
void CashierMain();
#endif // !CASHIER_H
