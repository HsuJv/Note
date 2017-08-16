#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int a[50];
int n;

int fib(int n){
	if (n==0) return 0;
	if (n==1||n==2)  a[n]=1;
	if (!a[n])
    	a[n]=fib(n-1)+fib(n-2);
    return a[n];
}

int main(){
    int i=0;
    memset(a,0,sizeof(a));
    scanf("%d",&n);
    while (i<n){
    	printf("%12d",fib(++i));
    	if (!(i%6)) printf("\n");
	}
    return 0;
}



