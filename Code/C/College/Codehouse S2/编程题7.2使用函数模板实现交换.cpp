#include<iostream>
using namespace std;
template<class T>
void sawp(T *a,T *b)
{
	T *temp=a;
	a=b;
	b=temp;
}
int main()
{
	int a,b;
	double c,d;
	cin>>a>>b>>c>>d;
	swap(a,b);
	swap(c,d);
	cout<<"a="<<a<<",b="<<b<<endl;
	cout<<"c="<<c<<",d="<<d<<endl;
	return 0;
}
