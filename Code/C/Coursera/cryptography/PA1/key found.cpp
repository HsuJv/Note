#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define N 7

int main(){
	int me[500],p[260],t,temp,key[N];
	double sum,pi,pit;	
	double pl[26] = {8.19, 1.47, 3.83, 3.91, 12.25, 2.26, 1.71, 4.57, 7.10, 0.14, 0.41, 3.77, 3.34, 7.06, 7.26, 2.89, 0.09, 6.85, 6.36, 9.41, 2.58, 1.09, 1.59, 0.21, 1.58, 0.08};
	
	memset(me,0,sizeof(me));
	freopen("c.txt","r",stdin);
	for (int i=0;i<470;i++)
	  scanf("%d",me+i);
	for (int j=0;j<N;j++){
		pit=0.0;
		for (int k=0;k<=255;k++){
		  memset(p,0,sizeof(p));
		  sum=0.0;
		  for (int i=0;i<470;i++)
		     if(i%N==j){
		     	sum+=1.0;
		   	    t=me[i]^k;
		   	    if (t<32||t>127) goto next;
		   	    if (t>=48&&t<=57) goto next;
		   	    if (t>=65&&t<=90) t+=32;
		   	    p[t]++;
		     }
		  pi=0.0;
		  for (int i=97;i<=122;i++)
		    pi+=(p[i]*pl[i-97]/(sum*sum));
		  if (pi>pit){
			  temp=k;
			  pit=pi;
		  }
		  next: ;
	    }
	    key[j]=temp;
	}
	for (int j=0;j<N;j++)
	  printf("%d ",key[j]);
	printf("\n");
	freopen("plain.txt","w",stdout);
	for (int i=0;i<470;i++)
	  printf("%c",key[i%N]^me[i]);
	return 0;
}
