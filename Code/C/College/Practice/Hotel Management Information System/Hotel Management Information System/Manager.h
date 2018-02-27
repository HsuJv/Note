#pragma once
#ifndef MANAGER_H
#define MANAGER_H

/*
Function that handles manager login
return 0 if failed
*/
int ManagerLogin();

/*
Set a new manager password
*/
void setManagerPassword();

/*
Function that handles guests' info
*/
void GuestInfoMenu();

/*
Function that handles cashiers' info
*/
void CashierInfoMenu();

/*
The main function while login with the access of admin
*/
void ManagerMain();
#endif // !MANAGER_H
