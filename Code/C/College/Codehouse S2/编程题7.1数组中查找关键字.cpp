#include<iostream>
using namespace std;
template<class T>
int SeqSearch(T list[],int n,T key)
{
	int i;
	for(i=0;i<n;i++)
	{
		if(list[i]==key)
		{
			cout<<"The index of "<<key<<" is:"<<i<<endl;
			break;
		}
	}
	if(i==n)
	cout<<"No found "<<key<<endl;
	return 0;
}
int main()
{
	int m;
	double n;
	int a[5]={1,2,3,4,5};
	double b[5]={1.1,2.2,3.3,4.4,5.5};
	cin>>m>>n;
	SeqSearch(a,5,m);
	SeqSearch(b,5,n);
	return 0;
}
