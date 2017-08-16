#include<iostream>
#include<string.h>
using namespace std;
class Date
{
	int year,month,day;
public:
	Date(int y=2016,int m=5,int d=15)
	{
		year=y;
		month=m;
		day=d;
	}
	int Getyear()
	{
		return year;
	}
	int Getmonth()
	{
		return month;
	}
	int Getday()
	{
		return day;
	}
	void Setdate(int y,int m,int d)
	{
		year=y;
		month=m;
		day=d;
	}
};
class Product
{
	char *name;
	double price;
	Date deptime;
	char *factory;
	bool easy_break;
	Date valtime;
	char *color;
	char *shape;
	double weight;
public:
	Product(char *n);
	Product(char *n,double p);
	Product(char *n,double p,int x,int y,int z);
	void Setproduct(char *n,double p,int x,int y,int z,char *f,bool e,int a,int b,int c,char *co,char *sh,double w);
	void output();
};
Product::Product(char *n)
{
	name=new char[strlen(n)+1];
	strcpy(name,n);
	cout<<"Constrcting One...."<<endl;
}
Product::Product(char *n,double p)
{
	name=new char[strlen(n)+1];
	strcpy(name,n);
	price=p;
	cout<<"Constrcting Two...."<<endl;
}
Product::Product(char *n,double p,int x,int y,int z):deptime(x,y,z)
{
	name=new char[strlen(n)+1];
	strcpy(name,n);
	price=p;
	cout<<"Constrcting Three...."<<endl;
}
void Product::Setproduct(char *n,double p,int x,int y,int z,char *f,bool e,int a,int b,int c,char *co,char *sh,double w)
{
	name=new char[strlen(n)+1];
	strcpy(name,n);
	price=p;
	deptime.Setdate(x,y,z);
	factory=new char[strlen(f)+1];
	strcpy(factory,f);
	easy_break=e;
	valtime.Setdate(a,b,c);
	color=new char[strlen(co)+1];
	strcpy(color,co);
	shape=new char[strlen(sh)+1];
	strcpy(shape,sh);
	weight=w; 
}
void Product::output( )
{
    cout<<name<<"-"<<price<<endl;
	cout<<deptime.Getyear()<<"-"<<deptime.Getmonth()<<"-"<<deptime.Getday()<<endl;
	cout<<factory<<"  "<<easy_break<<endl;
	cout<<valtime.Getyear()<<"-"<<valtime.Getmonth()<<"-"<<valtime.Getday()<<endl;
}

int main()
{
	char A[20];
	cin>>A;
	Product p1("car");
	Product p2("glass",1000);
	Product p3("bicycle",2000,2016,5,20);
	p1.Setproduct("car",100000,2009,3,14,"nanjing",0,2010,10,14,"red","car",1000);
	p1.output();
	return 0;
}
