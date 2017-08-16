#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Vehicle{
	protected:
		int MaxSpeed;
		int Weight;
	public:
		Vehicle(int m, int w){
			MaxSpeed = m;
			Weight = w;
			cout<<"Constructing Vehicle..."<<endl;
		}
		
		~Vehicle(){
			cout<<"Destructing Vehicle..."<<endl;
		}
		
		void Run(){
			cout<<"The vehicle is running!"<<endl;
		}
		
		void Stop(){
			cout<<"Please stoping running!"<<endl;
		}
		
		void Show(){
			cout<<"It's maxspeed is:"<<MaxSpeed<<endl;
			cout<<"It's weight is:"<<Weight<<endl;
		}
};

class Bicycle: virtual public Vehicle{
	protected:
		int Height;
	public:
		Bicycle(int m, int w, int h):Vehicle(m, w){
			Height = h;
			cout<<"Constructing Bicycle..."<<endl;
		}
		
		~Bicycle(){
			cout<<"Destructing Bicycle..."<<endl;
		}
		
		void Show(){
			Vehicle::Show();
			cout<<"It's height is:"<<Height<<endl;
		}
};

class Car: virtual public Vehicle{
	protected:
		int SeatNum;
	public:
		Car(int m, int w, int s):Vehicle(m, w){
			SeatNum = s;
			cout<<"Constructing Car..."<<endl;
		}
		
		~Car(){
			cout<<"Destructing Car..."<<endl;
		}
		
		void Show(){
			Vehicle::Show();
			cout<<"It's seatnum is:"<<SeatNum<<endl;
		}
};

class MotorCycle: public Bicycle, public Car{
	public:
		MotorCycle(int m, int w, int h, int s):Bicycle(m, w, h), Car(m, w, s), Vehicle(m, w){
			cout<<"Constructing MotorCycle..."<<endl;
		}
		
		~MotorCycle(){
			cout<<"Destructing MotorCyelce..."<<endl;
		}
		
		void Show(){
			cout<<"It's maxspeed is:"<<Vehicle::MaxSpeed<<endl;
			cout<<"It's weight is:"<<Vehicle::Weight<<endl;
			cout<<"It's height is:"<<Height<<endl;
			cout<<"It's seatnum is:"<<SeatNum<<endl;
		}
};

int main(){
	//freopen("in.txt", "r", stdin);
	MotorCycle mc(120, 70, 1, 2);
	mc.Show();
	return 0;
}
