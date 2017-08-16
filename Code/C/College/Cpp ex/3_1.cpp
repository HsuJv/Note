#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <string>
#include <cmath>
using std::cin;
using std::cout;
using std::endl;

class Container{
	protected:
		double radius;
	public:
		Container(double r){
			radius = r;
		}
		virtual double area() = 0;
		virtual double volume() = 0;
		virtual void print() = 0;
};

class Cube: public Container{
	public:
		Cube(double r):Container(r){		};
		
		double area(){
			return radius * radius * 6;
		}
	
		double volume(){
			return radius * radius * radius;
		}
		
		void print(){
			cout<<"The area of is Cube is "<<area()<<", and its volume is "<<volume()<<".\n";
		}
};

class Sphere: public Container{
	public:
		Sphere(double r):Container(r){		};
		
		double area(){
			return 4 * radius * radius * M_PI;
		}
		
		double volume(){
			return 4 / 3 * radius * radius * radius * M_PI;
		}
		
		void print(){
			cout<<"The area of is Sphere is "<<area()<<", and its volume is "<<volume()<<".\n";
		}
};

class Cylinder: public Container{
	protected:
		double high;
	public:
		Cylinder(double r, double h):Container(r){
			high  = h;
		};
		
		double area(){
			return 2 * radius * radius * M_PI + 2 * radius * M_PI * high;
		}
		
		double volume(){
			return radius * radius * M_PI * high;
		}
		
		void print(){
			cout<<"The area of is Cylinder is "<<area()<<", and its volume is "<<volume()<<".\n";
		}
};

int main(){
	Container *p;
	Cube cu(1);
	Sphere s(2);
	Cylinder cy(3, 4);
	p = &cu;
	cout<<p->area()<<endl;
	cout<<p->volume()<<endl;
	p->print();
	p = &s;
	cout<<p->area()<<endl;
	cout<<p->volume()<<endl;
	p->print();
	p = &cy;
	cout<<p->area()<<endl;
	cout<<p->volume()<<endl;
	p->print();
}
