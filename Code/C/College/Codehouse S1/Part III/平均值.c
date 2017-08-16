#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int a[20];

int comp ( const void *a, const void *b ){
    return * ( int * ) a - * ( int * ) b;
}

int main(){
    int q=1,p=19,i=0;
    double ave;
    for (;i<20;i++)
    	scanf("%d",a+i);
    qsort(a,20,sizeof(int),comp);
    while(a[q]==a[q-1]) q++;
    while(a[p]==a[p-1]) p--;
    for(i=q;i<p;i++)	ave+=a[i];
    printf("count=%d,average=%f\n",p-q,ave/(p-q));	
	return 0;    
}
