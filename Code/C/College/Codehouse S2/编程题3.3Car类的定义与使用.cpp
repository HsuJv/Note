#include<iostream>
#include<string.h>
using namespace std;
class Car
{
private:
    char *brand;
	char *type;
	int year;
	double price;
public:
	Car(char *b,char *t,int y,double p);
	Car();
	char *GetBrand()
	{
		return brand;
	}
	char *GetType()
	{
		return type;
	}
	int GetYear()
	{
		return year;
	}		
	double GetPrice()
	{
		return price;
	}
	~Car()
	{
		delete []brand;
		delete []type;
	}
};
Car::Car(char *b,char *t,int y,double p)
{
	brand=new char[strlen(b)+1];
	strcpy(brand,b);
	type=new char[strlen(t)+1];
	strcpy(type,t);
	year=y;
	price=p;
}
Car::Car( ) 
{ 
    brand=new char[20]; 
	strcpy(brand,"undefinition"); 
	type=new char[20]; 
	strcpy(type,"undefinition"); 
	year=2000; 
	price=0; 
}
int main()
{
 	Car car1("FIAT","Palio",2007,6.5);
	cout<<car1.GetBrand (  ) <<" "<<car1.GetType (  ) <<" "<<car1.GetYear (  )
	<<" " <<car1.GetPrice (  ) <<endl;
	Car car2;
	cout<<car2.GetBrand (  )<<" "<<car2.GetType (  )<<" "<<car2.GetYear (  )
	<<" " <<car2.GetPrice (  )<<endl;
	return 0;
}
