#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Base{
	public:
		int i;
		
		Base(int x):i(x){		}
		
		void show(){
			cout<<"i in Base is: "<<i<<endl;
		}
};

class Derived: public Base{
	public:
		Derived(int x):Base(x){		}
		
		void show(){
			cout<<"i in Derived is: "<<i<<endl;
		}
};

int main(){
	Base b1(1);
	cout<<"基类对象 b1.show():"<<endl;
	b1.show();
	Derived d1(2);
	b1 = d1;
	cout<<"基类 b1 = d1, b1.show():"<<endl;
	b1.show();
	cout<<"派生类对象 d1.show():"<<endl;
	d1.show();
	Base &b2 = d1;
	cout<<"引用b2 = d1, b2.show():"<<endl;
	b2.show();
	Base *b3 = &d1;
	cout<<"基类指针 b3 = &d1, b3->show():"<<endl;
	b3->show();	
	Derived *d4 = &d1;
	Base *b4 = d4;
	cout<<"基类指针 b4 = d4, b4->show()"<<endl;
	b4->show();
	cout<<"派生类指针 d4, d4->show():"<<endl;
	d4->show();
	return 0; 
}
