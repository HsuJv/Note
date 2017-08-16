#include <iostream>
using namespace std;

#define f(i, a, b) for(int i = a; i < b; i++)

template<class T>
void bubble_sort(T a[], int num){
	f(i, 0, num - 1){
		bool p;
		p = 1;
		f(j, i+1, num)
			if (a[i] > a[j]){
				p = 0;
				T tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		if(p) break;
	}
}

template<class T>
void print(T a[],int num){
	f(i, 0, num){
		cout<<a[i]<<",";
	}
	cout<<endl;
}

int main(){
	int a[6];
	double b[7];
	f(i, 0, 6) cin>>a[i];
	f(i, 0, 7) cin>>b[i];
	bubble_sort(a, 6); bubble_sort(b, 7);
	print(a, 6); print(b, 7);
	return 0;	
}
