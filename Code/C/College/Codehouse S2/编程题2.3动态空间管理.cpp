#include<iostream>
using namespace std;
int main()
{
	int num,positive=0,negative=0;
	int i,j=0;
	int *p=new int[20];
	cin>>num;
	if(num<=0||num>20)
		 cout<<"number error.\n";
	else
	{
		i=num;
		while(i--)
		{
			cin>>p[j++];
			if(p[j-1]>0)
				positive++;
			else if(p[j-1]<0)
				negative++;
		}
		cout<<"There are "<<num<<" figures,\n";

		cout<<positive<<" of them are positive numbers,\n";

		cout<<negative<<" of them are negatives.\n";
	}
	delete []p;
	return 0;
}
