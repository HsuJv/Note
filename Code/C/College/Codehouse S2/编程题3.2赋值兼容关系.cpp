#include <iostream>
using namespace std;
class Base
{ 
public:
  int i;
  Base(int x): i(x)
  {   }
  void show (  )   
  {
   cout << "i in Base is: " << i << endl;  
  }
};
class Derived: public Base
{
public:
  Derived ( int x ): Base ( x )
  {  }
  void show (  ) 
  {
   cout << "i in Derived is: " << i << endl;  
  }
};
    
int  main (  ) 
{
  Base b1(10);              //定义基类对象b1，初始值为10
  cout << "基类对象 b1.show (  ) :\n";        
  b1.show (  ) ;
  Derived d1(20);               //定义派生类对象d1，初始值为20
  b1=d1;                      //用派生类对象给基类对象赋值
  cout << "基类b1=d1,  b1.show (  ) :\n"; 
  b1.show (  ) ;
  cout << "派生类对象 d1.show (  ) :\n";   
  d1.show (  ) ;
  Base &b2=d1;                 //用派生类对象来初始化基类引用
  cout << "引用b2=d1, b2.show (  ) :\n";  
  b2.show (  ) ;
  Base *b3=&d1;             //派生类对象的地址赋给指向基类的指针
  cout << "基类指针b3=&d1, b3->show (  ) :\n";
  b3->show (  ) ;
  Derived  *d4 =new Derived(50);      //定义派生类指针并生成新对象，初值为50
  Base *b4 = d4 ;                 //派生类指针赋给指向基类的指针
  cout << "基类指针b4 = d4, b4->show (  ) :\n";
  b4->show (  ) ;
  cout << "派生类指针d4, d4->show (  ) :\n";
  d4->show (  ) ;
  delete d4;
  return 0;
}
