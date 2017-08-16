#include <iostream>
#include <string>
using namespace std;

class Data{
	public:
		Data(string Name):name(Name){}
		virtual void print()=0;
	protected:
		string name;
};

class Teacher:public Data{
	public:
		Teacher(string Name,int Sal):Data(Name),sal(Sal){}
		
		void print(){
			cout<<"Name:"<<name<<endl;
			cout<<"sal="<<sal<<endl;
		}
		
	protected:
		int sal;
};

class Student:public Data{
	public:
		Student(string Name,string Id):Data(Name),id(Id){}
		void print(){
			cout<<"Name:"<<name<<endl;
			cout<<"id="<<id<<endl;
		}
		
	protected:
		string id;
};

class PostGrad:public Student{
	public:
		PostGrad(string Name,string Id,string Dn):Student(Name,Id),dn(Dn){}
		
		void print(){
			cout<<"Name:"<<name<<endl;
			cout<<"id="<<id<<endl;
			cout<<"dn="<<dn<<endl;
		}
		
	protected:
		string dn;
};

class Tpost:virtual public Teacher,virtual public PostGrad{
	public:
		Tpost(string Name,string Id,string Dn,int Sal):Teacher(Name,Sal),PostGrad(Name,Id,Dn){}
	
		void print(){
			cout<<"Name:"<<Teacher::name<<endl;
			cout<<"sal="<<sal<<endl;
			cout<<"id="<<id<<endl;
			cout<<"dn="<<dn<<endl;
		}
};

int main (){
	Teacher tobj("Zhuhong", 2000);
	Student sobj("Wanghui", "B05030417");
	PostGrad pobj("Lixuefeng", "Yj040217", "Computer Department");
	Tpost tpobj("Liuling", "Yz040318", "Society Department", 800);
	cout << "the teacher:\n";
	tobj.print (  ) ;
	cout << "\nthe student:\n";
	sobj.print (  ) ;
	cout << "\nthe postgraduate:\n";
	pobj.print (  ) ;
	cout << "\nthe teacher and postgraduate:\n";
	tpobj.print (  ) ;
	return 0;
}
