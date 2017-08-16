#include<iostream>
using namespace std;
class point
{
private:
	float x,y;
public:
	point(float a=0,float b=0)
	{
		x=a;
		y=b;
	}
	float get_x()
	{
		return x;
	}
	float get_y()
	{
		return y;
	}
	point operator ++()
	{
		if(x>=0&&x<=640)
		{
			if(x==640&&y>=0&&y<480)
			++y;
			else if(x==640&&y==480);
			else if(y>=0&&y<480)
			{
				++x;
				++y;
			}
		}
		return *this;
	}
	point operator --()
	{
        if(x>=0&&x<=640)
		{
			if(x==0&&y>=0&&y<480)
			--y;
			else if(x==0&&y==0);
			else if(y>0&&y<=480)
			{
				--x;
				--y;
			}
		}
		return *this;
	}
};
int main()
{
	float a,b;
	cin>>a;
	cin>>b;
	point p(a,b);
	for(int j=0;j<5;j++)
	{
		cout<<"p:x="<<p.get_x()<<",y="<<p.get_y()<<endl;
		++p;
	}
	for(int j=0;j<5;j++)
	{
		cout<<"p:x="<<p.get_x()<<",y="<<p.get_y()<<endl;
		--p;
	}
	return 0;
}

