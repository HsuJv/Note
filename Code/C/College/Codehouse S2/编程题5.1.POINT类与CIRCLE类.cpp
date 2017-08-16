#include<iostream>
using namespace std;
class POINT
{
protected:
	int x,y;
public:
	POINT(int x1=0,int y1=0)
	{
		x=x1;
		y=y1;
	}
	void change(int x2,int y2)
	{
		x=x2;
		y=y2;
	}
	void show()
	{
		cout<<"("<<x<<","<<y<<")"<<endl;
	}
};
class CIRCLE: public POINT
{ 
private:
		int r; // ±íÊ¾Ô²µÄ°ë¾¶ 
public: 
    CIRCLE (int x1,int y1,int r1);
    void show () ; 
};
CIRCLE::CIRCLE(int x1,int y1,int r):POINT(x1,y1),r(5)
{
}
void CIRCLE::show () 
{
 cout<<"the center of the circle is:\n"; 
 POINT::show () ;
 cout<<"the radius is:"<<r<<endl;  
}
int main ( )
{
 	POINT p (2, 3);
	CIRCLE c (3, 4, 5);
	cout<<"original p:\n";
	p.show ();
	p.change (20,30);
	cout<<"changed p:\n";
	p.show ();
    cout<<"original c:\n";
    c.show ( );
    c.change (30,40);
    cout<<"changed c:\n";
    c.show ( );
    return 0;
}
