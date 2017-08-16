#include <iostream> 
#include <cmath>
#include <math.h> 
using namespace std;
class POINT{
	protected:
		double x,y;
	public:
		POINT(double x1=0,double y1=0){
			x=x1;
			y=y1;
		}
	void show(){
		cout<<"("<<x<<","<<y<<")"<<endl;
	}
	double getx(){return x;}
	double gety(){return y;}
};
class CIRCLE: public POINT{ 
	private:
 		const double PI; // 常数据成员
  		POINT r1,r2; // 两个对象成员， r1 表示圆心， r1 和 r2 有距离作为半径
  		double r; // 表示圆的半径 
	public: 
  		CIRCLE ( POINT p1, POINT p2); 
    	double circum ()  ; 
    	double area () ; 
    	void show () ; 
};

CIRCLE::CIRCLE(POINT p1,POINT p2):PI(3.14159){
	r1=p1;
	r2=p2;
	r=sqrt(pow((r1.getx()-r2.getx()),2)+pow((r1.gety()-r2.gety()),2));
}

double CIRCLE::circum(){
	return 2*PI*r;
}

double CIRCLE::area(){
	return PI*r*r;
}

void CIRCLE::show () {
 cout<<"the center of the circle is:\n"; 
 r1.show () ;
 cout<<"the radius is:"<<r<<endl; 
 cout<<"the area is:"<<area()<<endl; 
 cout<<"the circumference is:"<<circum()<<endl; 
}

int main () 
{ 
 double x[4]; 
 int i; 
     for (i=0;i<4;i++) 
           cin>>x[i]; // 点的横纵坐标由输入给定 
     POINT p1(x[0],x[1]),p2(x[2],x[3]); 
     CIRCLE c(p1,p2); 
     cout<<"the information about c is:\n"; 
     c.show (); 
     return 0; 
} 
