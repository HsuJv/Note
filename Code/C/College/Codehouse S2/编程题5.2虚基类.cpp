#include<iostream>
#include<string.h>
using namespace std;
class Data
{
protected:
	char *name;
public:
	Data(char *n)
	{
		name=new char[strlen(n)+1];
		strcpy(name,n);
	}
	~Data()
	{
		delete[]name;
	}
	void print()
	{
		cout<<"name="<<name<<endl;
	}
};

class Teacher:virtual public Data
{
protected:
	float sal;
public:
	Teacher(char *n,float s):Data(n)
	{
		sal=s;
	}
	void print()
	{
		cout<<"sal="<<sal<<endl; 
	}
};
class Student:virtual public Data
{
protected:
	char *id;
public:
	Student(char *n,char *i):Data(n)
	{
		id=new char[strlen(i)+1];
		strcpy(id,i);
	}
	~Student()
	{
		delete []id;
	}
	void print()
	{
		Data::print();
		cout<<"id="<<id<<endl;
	}
};
class Postgrad:public Student
{
protected:
	char *dn;
public:
	Postgrad(char *n,char *i,char *d):Student(n,i),Data(n)
	{
		dn=new char[strlen(d)+1];
		strcpy(dn,d);
	}
	 ~Postgrad()
	 {
	 	delete []dn;
	 }
	 void print()
	 {
	 	Student::print();
	 	cout<<"dn="<<dn<<endl;
	 }
};
class Tpost:public Teacher,public Postgrad
{
public:
	Tpost(char *n,char *i,char *d,float s):Data(n),Teacher(n,s),Postgrad(n,i,d)
	{
	}
	void print()
	{
		cout<<"The teacher and postgraduate:"<<endl;
		Postgrad::print();
		Teacher::print();
	}
};
int main()
{
	char name[80];
	char id[80];
	char dn[80];
	float sal;
	cin>>name>>id>>dn>>sal;
	Tpost t(name,id,dn,sal);
	t.print();
	return 0;
}
