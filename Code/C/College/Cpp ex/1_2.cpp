#include<iostream>
#include<cstring>
using std::cin;
using std::cout;
using std::endl;

class Boy;
class Girl{
	private:
		char *Name;
		int Age;
	public:
		Girl(char *, int);
		~Girl();
		char* get_name();
		int get_age();
		void print_info();
		void VisitBoy(Boy&);
		friend Boy;
		friend void VisitBoyGirl(Boy&, Girl&);
};

class Boy{
	private:
		char *Name;
		int Age;
	public:
		Boy(char *, int);
		~Boy();
		char* get_name();
		int get_age();
		void print_info();
		void VisitGirl(Girl&);
		friend Girl;
		friend void VisitBoyGirl(Boy&, Girl&);
};

Girl::Girl(char *name = 0, int age = 0){
	if (name){
		Name = new char[strlen(name)+1];
		strcpy(Name, name);
		Age = age;
	}
}

Girl::~Girl(){cout<<"Class Girl ends."<<endl;}

char* Girl::get_name(){return Name;}

int Girl::get_age(){return Age;}

void Girl::print_info(){
	cout<<"Girl "<<get_name()<<" is "<<get_age()<<" years old;"<<endl;
}

void Girl::VisitBoy(Boy &b){
	cout<<"Girl "<<get_name()<<"'s friend is "<<b.Name<<endl;
}

Boy::Boy(char *name = 0, int age = 0){
	if (name){
		Name = new char[strlen(name)+1];
		strcpy(Name, name);
		Age = age;
	}
}

Boy::~Boy(){cout<<"Class Boy ends."<<endl;}

char* Boy::get_name(){return Name;}

int Boy::get_age(){return Age;}

void Boy::print_info(){
	cout<<"Boy "<<get_name()<<" is "<<get_age()<<" years old;"<<endl;
}

void Boy::VisitGirl(Girl &g){
	cout<<"Boy "<<get_name()<<"'s friend is "<<g.Name<<endl;
}

void VisitBoyGirl(Boy &b, Girl &g){
	cout<<b.Name<<" and "<<g.Name<<" are friends"<<endl;
}

int main(){
//	freopen("out.txt", "w", stdout);
	Boy b("Tom", 10);
	Girl g("Amy", 15);
	b.print_info();
	g.print_info();
	b.VisitGirl(g);
	g.VisitBoy(b);
	VisitBoyGirl(b, g);
	return 0;
}
