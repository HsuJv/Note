#include "../h/polynominal.h"

inline void flush(){
	while(getchar()!='\n');//flush the in stream
	//fflush(stdout)
}

inline void displayMenu(){
	cout << "-------------------------MENU-------------------------" << endl;
	cout << "--------------(1)Input a polynominal------------------" << endl;
	cout << "--------------(2)Display the polynominals-------------" << endl;
	cout << "--------------(3)Polynominal addition-----------------" << endl;
	cout << "--------------(4)Polynominal multiplication-----------" << endl;
	cout << "--------------(5)Exit---------------------------------" << endl;
	cout << "Input your option: ";
}

int main(int argc, char const *argv[]){
	freopen("1.txt", "w", stdout);
	double op = 0;
	polynominal p, q;
	bool init = false;
	do{
		system("cls");
		displayMenu();
		do{
			cin >> op;
			flush();
			cout << endl;
			if (op<1 || op>5 || op!=(int)op){
				cout << "Invalid option, please input a integer between 1 and 5." << endl;
				cout << "Do input a valid option: ";
				op = 0;
			}
		}while(!op);
		switch((int)op){
			case 1: 
			if (init){
				cout << "Already two polynominals exist! ";
				cout << "You are ought not to choose this option." << endl;
				cout << "Or do you want to change the value of polynominal p or q?(Y/N)";
				char ch;
				do{
					cin >> ch;
					flush();
					if (ch=='y' || ch=='Y') init = false;
					else if(ch=='n' || ch=='N');
					else {
						cout << "You will input Y or N to make a choice." << endl;
					}
				}while(ch!='n' && ch!='N' && ch!='y' && ch!='Y');
			}
			if (!init){
				cout << "Please input two polynominals p & q," << endl;
				cout << "at an order of power descending." << endl;
				cout << "Each one should be end with a minus exponent." << endl;
				cin >> p >> q;
				init = true;
			}
			break;
			case 2:
			if (!init){
				cout << "There aren't any polynominals exist." << endl;
				cout << "Please choose option 1 first." << endl;
				break;
			} 
			cout << "p = " << p << "q = " << q; break;
			case 3:
			if (!init){
				cout << "There aren't any polynominals exist." << endl;
				cout << "Please choose option 1 first." << endl;
				break;
			}  
			cout << "p + q = " << p + q; break;
			case 4:
			if (!init){
				cout << "There aren't any polynominals exist." << endl;
				cout << "Please choose option 1 first." << endl;
				break;
			}  
			cout << "p * q = " ; p * q; break;
			case 5: return 0;
		}
		cout << "Press any key to back to menu..." << endl;
		system("pause > nul");
	}while(1);
}
