#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

void create(int a[],int n){
	int i=0;
	for (;i<n;i++)
		*(a+i)=i+1;
}

void print(int a[],int n){
	int i=0;
	for (;i<n;i++)
		printf("%d,",*(a+i));
}

int main(){
	int *array, n;
	scanf ("%d", &n);
	array = (int *)malloc(n*sizeof(int ));
	create (array, n);
	print (array, n);
	return 0;  
}
