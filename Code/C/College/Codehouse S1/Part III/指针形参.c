#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

void Find(int *a,int n,int *max,int *maxPos,int *min,int *minPos){
	int i; 
	*max=*min=a[0]; 
	for (i=1;i<n;i++) 
		if (a[i]>*max) 
			{*max=a[i];*maxPos=i;} 
		else if(a[i]<*min) 
			{*min=a[i];*minPos=i;} 
}  

int main(){
	int array[10]={23,45,90,-9,43,90,4,2,-9};
	int max,min,maxPos=0,minPos=0;
	Find(array,9,&max,&maxPos,&min,&minPos);
	printf("max=%d, maxPos=%d, min=%d, minPos=%d\n",max,maxPos,min,minPos);
	return 0;
}
