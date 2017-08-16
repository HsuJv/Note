#include<iostream>
using std::cin;
using std::cout;
using std::endl;

class Time{
	private: 
		int Hour, Minute, Second;
	public:
		Time(int, int, int);
		Time(const Time&);
		~Time();
		void change(int, int, int);
		int get_hour();
		int get_minute();
		int get_second();
		void print_time();
		void inc_second();
};

Time::Time(int h = 0, int m = 0, int s = 0){
	Hour = h;
	Minute = m;
	Second = s;
}

Time::Time(const Time &t){
	Hour = t.Hour;
	Minute = t.Minute;
	Second = t.Second;
} 

Time::~Time(){
	cout<<"Class ends."<<endl;
}

void Time::change(int h , int m, int s){
	Hour = h;
	Minute = m;
	Second = s;
}

int Time::get_hour(){return Hour;}
int Time::get_minute(){return Minute;}
int Time::get_second(){return Second;}

void Time::print_time(){
	cout<<"Now is "<<get_hour()<<" : "<<get_minute()<<" : "<<get_second()<<endl;
}

void Time::inc_second(){
	Second++;
	if (Second == 60){
		Second = 0;
		Minute++;
	}
	if (Minute == 60){
		Minute = 0;
		Hour++;
	}
	if (Hour == 24){
		Hour = 0;
	}
}

void f(Time  *t){ 
   t->print_time();
}


int main(){
	Time t;
	cout<<"After constructing:"<<endl;
	t.print_time();
	t.change(23, 59, 59);
	cout<<"After changing:"<<endl;
	t.print_time();
	t.inc_second();
	cout<<"After increase a second:"<<endl;
	t.print_time();
	f(&t);
	return 0;
}
