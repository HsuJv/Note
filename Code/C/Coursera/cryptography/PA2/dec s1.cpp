#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<math.h>
#include<ctype.h>
#include<iostream>
#include<algorithm>
using namespace std;

int main(){
	char a[100],b[100],c[100];
	int a1[35],b1[35],c1[35];
	FILE *f1,*f2,*f3;
	f1=fopen("c7.txt","r");
	f2=fopen("c1.txt","r");
	f3=fopen("c4.txt","r");
	for (int i=1;i<=62;i++){
		fscanf(f1,"%c",a+i);
		fscanf(f2,"%c",b+i);
		fscanf(f3,"%c",c+i);
	}
	fclose(f1);fclose(f2);fclose(f3);
	memset(a1,0,sizeof(a1));
	memset(b1,0,sizeof(b1));
	memset(c1,0,sizeof(c1));
	int j=1;
	for (int i=1;i<=62;i++){
	    if (a[i]>=65) a1[j]+=(a[i]-55);
	      else a1[j]+=(a[i]-48);
	    if (b[i]>=65) b1[j]+=(b[i]-55);
	      else b1[j]+=(b[i]-48);
	    if (c[i]>=65) c1[j]+=(c[i]-55);
	      else c1[j]+=(c[i]-48);
		if (i%2){
			a1[j]*=16;
			b1[j]*=16;
			c1[j]*=16;
		}
		else j++;
	}
	for (int i=1;i<=31;i++){
		int t1,t2;
		t1=(a1[i]^b1[i])&64;
		t2=(a1[i]^c1[i])&64;
		if(t1&&t2&&(b1[i]!=c1[i])) printf("%d:%d ",i,a1[i]^32);
	}
	return 0;
}
