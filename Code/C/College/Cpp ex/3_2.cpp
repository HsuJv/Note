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

class complex{
	private:
		float real, imag;
	public:
		complex(float r = 0, float i = 0){
			real = r;
			imag = i;
		}
		
		void print(){
			cout<<real;
			if (imag>0) cout<<" + "<<imag<<"i";
			else if(imag<0) cout<<" - "<<abs(imag)<<"i";
		}
		
		friend complex operator + (complex& a, complex& b);
		
		friend complex operator - (complex& a, complex& b);
		
		friend complex operator ++(complex& a);
		
		complex operator *(complex& a){
			complex c;
			c.real = this->real * a.real - this->imag * a.imag;
			c.imag = this->imag * a.real + this->real * a.imag;
			return c;
		}
		
		complex operator /(complex& a){
			complex c;
			c.real = this->real * a.real + this->imag * a.imag;
			c.real /= (a.real * a.real + a.imag * a.imag);
			c.imag = this->imag * a.real - this->real * a.imag;
			c.imag /= (a.real * a.real + a.imag * a.imag);
			return c;
		}
		
		complex operator ++(int ){
			complex c(this->real, this->imag);
			this->imag++;
			this->real++;
			return c;
		}
};

complex operator + (complex& a, complex& b){
	complex c;
	c.real = a.real + b.real;
	c.imag = a.imag + b.imag;
	return c;
}

complex operator - (complex& a, complex& b){
	complex c;
	c.real = a.real - b.real;
	c.imag = a.imag - b.imag;
	return c;
}

complex operator ++(complex& a){
	a.real++;
	a.imag++;
	return a;
}

int main(){
	complex A1(2.3, 4.6), A2(3.6, 2.8);
	complex A3, A4, A5, A6;
	A3 = A1 + A2;
	A4 = A1 - A2;
	A5 = A1 * A2;
	A6 = A1 / A2;
	cout<<"A1 = ";
	A1.print();
	cout<<endl<<"A2 = ";
	A2.print();
	cout<<endl<<"A3 = A1 + A2 = ";
	A3.print();
	cout<<endl<<"A4 = A1 - A2 = ";
	A4.print();
	cout<<endl<<"A5 = A1 * A2 = ";
	A5.print();
	cout<<endl<<"A6 = A1 / A2 = ";
	A6.print();
	A3 = ++A1;
	cout<<endl<<"after A3 = ++A1";
	cout<<endl<<"A1 = ";
	A1.print();
	cout<<endl<<"A3 = ";
	A3.print();
	A4 = A2++;
	cout<<endl<<"after A4 = A2++";
	cout<<endl<<"A2 = ";
	A2.print();
	cout<<endl<<"A4 = ";
	A4.print(); 
	return 0;
}
