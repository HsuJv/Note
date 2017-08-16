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
using std::ostream;
using std::istream;

template<class T>
class complex{
	private:
		T real, imag;
	public:
		complex(T r = 0, T i = 0){
			real = r;
			imag = i;
		}
		
		void print(){
			cout<<real;
			if (imag>0) cout<<" + "<<imag<<"i";
			else if(imag<0) cout<<" - "<<abs(imag)<<"i";
		}
		
		friend complex operator + (complex<T>& a, complex<T>& b){
			complex<T> c;
			c.real = a.real + b.real;
			c.imag = a.imag + b.imag;
			return c;
		}

		friend istream& operator >>(istream& in, complex<T>& obj){
			cout<<"Input real and imag of a complex"<<endl;
			in>>obj.real;
			in>>obj.imag;
			return in;
		}
		
		friend ostream& operator <<(ostream& out, complex<T>& obj){
				out<<obj.real;
				if (obj.imag>0) out<<" + "<<obj.imag<<"i";
				else if(obj.imag<0) out<<" - "<<abs(obj.imag)<<"i";
				return out;
		}
};

int main(){
	complex<double> A;
	cin>>A;
	cout<<A;
	return 0;
}
